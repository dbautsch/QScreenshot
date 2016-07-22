/*!
*	Copyright (c) 2016 Dawid Bautsch dawid.bautsch@gmail.com
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
*	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
*	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
*	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
*	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
*	IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*	THE SOFTWARE.
*/

#include "PasswordsShelter.h"
#include "SettingsDialog.h"

#include <QSettings>
#include <QDebug>
#include <QCryptographicHash>
#include <QException>

#include <openssl/evp.h>
#include <openssl/conf.h>
#include <openssl/bn.h>
#include <openssl/err.h>

PasswordsShelter::PasswordsShelter()
{
#ifdef WANT_SOME_TESTS
    //  very simple unit test
    RunTests();
#else
    ReadWebServiceData();
#endif
}

PasswordsShelter::~PasswordsShelter()
{
    WriteWebServiceData();
}

bool PasswordsShelter::GetLoginPasswordForService(const QString    & strServiceName,
                                                  QString          & strLogin,
                                                  QString          & strPassword)
{
    /*!
     *  Get the pair - login and password for given web service name from the shelter.
     */

    for (int i = 0; i < webServiceDataList.size(); ++i)
    {
        const WebServiceData & wsd = webServiceDataList[i];

        if (wsd.strServiceName.toLower() != strServiceName.toLower())
            continue;

        strLogin    = wsd.strLogin;
        strPassword = DecryptText(wsd.baPassword, wsd.baIV);

        break;
    }

    return (strLogin.isEmpty() == false) && (strPassword.isEmpty() == false);
}

void PasswordsShelter::SetLoginPasswordForService(const QString    & strServiceName,
                                                  const QString    & strLogin,
                                                  const QString    & strPassword)
{
    /*!
     *  Save the pair - login and password for given web service to shelter.
     */

    bool bFound         = false;

    QByteArray baIV;

    GenerateIV(baIV);

    for (int i = 0; i < webServiceDataList.size(); ++i)
    {
        WebServiceData & wsd    = webServiceDataList[i];

        if (wsd.strServiceName != strServiceName)
            continue;

        bFound          = true;

        wsd.strLogin    = strLogin;
        wsd.baIV        = baIV;

        EncryptText(strPassword, wsd.baPassword, baIV);

        break;
    }

    if (!bFound)
    {
        webServiceDataList.push_back(WebServiceData());

        WebServiceData & wsd    = webServiceDataList.back();

        wsd.strLogin            = strLogin;
        wsd.strServiceName      = strServiceName;
        wsd.baIV                = baIV;

        EncryptText(strPassword, wsd.baPassword, wsd.baIV);
    }
}

bool PasswordsShelter::EncryptText(const QString    & strText,
                                   QByteArray       & baEncrypted,
                                   const QByteArray & baIV)
{
    /*!
    *   Encrypt text using strSecrectSHA key. It is a well known hash of the
    *   passphrase given by user.
    */

    UCharData iv, secretHash;
    UCharData inputData, resultData;
    bool bRET                       = true;

    baEncrypted.clear();

    QByteArray2UCharData(baIV, &iv);
    QByteArray2UCharData(baSecretSHA, &secretHash);

    QByteArray baInput;

    baInput.append(strText);
    baInput = baInput.toBase64();

    //  convert input string to unsigned char array
    QByteArray2UCharData(baInput, &inputData, true);

    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);

    resultData.uCapacity            = baInput.size();
    resultData.uCapacity            += resultData.uCapacity % 16;
    resultData.uCapacity            *= 4;

    resultData.pucData              = new unsigned char [resultData.uCapacity];

    if (OpenSSL_Encrypt(&inputData,
                        secretHash.pucData,
                        iv.pucData,
                        &resultData) == false)
    {
        bRET                        = false;
    }

    UCharData2QByteArray(&resultData, baEncrypted);

    EVP_cleanup();
    ERR_free_strings();

    return bRET;
}

QString PasswordsShelter::DecryptText(const QByteArray & baEncrypted,
                                      const QByteArray & baIV)
{
    /*!
     *  Decrypt text using strSecretSHA key. It is a well known hash of the
     *  passphrase given by user.
     *
     *  \param baEncrypted [in] Input data to be decrypted.
     *  \param baIV [in] Initialisation vector used to encrypt the data.
     */

    UCharData iv, secretHash;
    UCharData inputData, resultData;
    QByteArray baDecrypted;
    QString strRET;

    QByteArray2UCharData(baIV, &iv);
    QByteArray2UCharData(baSecretSHA, &secretHash);

    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);

    QByteArray2UCharData(baEncrypted, &inputData);

    resultData.uCapacity        = baEncrypted.size();
    resultData.uCapacity        += resultData.uCapacity % 16;

    resultData.pucData          = new unsigned char [resultData.uCapacity];

    if (OpenSSL_Decrypt(&inputData,
                        secretHash.pucData,
                        iv.pucData,
                        &resultData))
    {
        UCharData2QByteArray(&resultData, baDecrypted);

        QByteArray baDecoded    = QByteArray::fromBase64(baDecrypted);
        strRET                  = QString::fromUtf8(baDecoded);
    }

    EVP_cleanup();
    ERR_free_strings();

    return strRET;
}

void PasswordsShelter::ReadWebServiceData()
{
    //!<    read all services data from configuration file

    webServiceDataList.clear();

    QSettings settings(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);

    int iCount                  = settings.beginReadArray("PASSWORDS_SHELTER");

    for (int i = 0; i < iCount; ++i)
    {
        settings.setArrayIndex(i);
        WebServiceData wsd;

        wsd.strLogin            = settings.value("LOGIN").toString();
        wsd.baPassword          = settings.value("PASSWORD").toByteArray();
        wsd.baIV                = settings.value("IV").toByteArray();
        wsd.strServiceName      = settings.value("SERVICE_NAME").toString();

        if (wsd.strServiceName.trimmed().isEmpty())
            continue;

        //  read extra data for this service
        wsd.extraData.bAskForLoginData  = settings.value("ASK_FOR_LOGIN_DATA", true).toBool();

        webServiceDataList.push_back(wsd);
    }
}

void PasswordsShelter::WriteWebServiceData()
{
    //!<    write all services data to configuration file

    QSettings settings(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);
    int i = 0;

    settings.beginWriteArray("PASSWORDS_SHELTER", webServiceDataList.size());

    foreach (const WebServiceData & wsd, webServiceDataList)
    {
        settings.setArrayIndex(i);

        settings.setValue("LOGIN", wsd.strLogin);
        settings.setValue("PASSWORD", wsd.baPassword);
        settings.setValue("IV", wsd.baIV);
        settings.setValue("SERVICE_NAME", wsd.strServiceName);

        //  save extra data for this service
        settings.setValue("ASK_FOR_LOGIN_DATA", wsd.extraData.bAskForLoginData);

        ++i;
    }

    settings.endArray();
}

void PasswordsShelter::SetSecretKey(const QByteArray & baSecretSHA)
{
    this->baSecretSHA = baSecretSHA;
}

bool PasswordsShelter::GenerateIV(QByteArray & baIV)
{
    //!<    generate initialisation vector using semirandom number generator.
    //!<    \param baIV [out] Initialisation vector.

    BIGNUM * pResult    = BN_new();

    if (pResult == NULL)
        return false;

    int iResult         = BN_rand(pResult, 128, 0, 0);

    if (iResult == 1)
    {
        //  random number has been generated
        unsigned char ucResult[16];

        if (BN_bn2mpi(pResult, ucResult) != 0)
        {
            //  success
            baIV    = QByteArray(reinterpret_cast<char*>(ucResult), 16);
        }
    }
    else
    {
        BN_free(pResult);
        return false;
    }

    BN_free(pResult);

    return true;
}

QByteArray PasswordsShelter::CalculateSecretSHA(const QString & strInput)
{
    //!<    calculate SHA256 hash of given input string.

    QByteArray baInput;

    baInput.append(strInput);

    return CalculateSecretSHA(baInput);
}

QByteArray PasswordsShelter::CalculateSecretSHA(const QByteArray & baInput)
{
    //!< calculate SHA256 hash of given input data.

    return QCryptographicHash::hash(baInput, QCryptographicHash::Sha256);
}

void PasswordsShelter::QByteArray2UCharData(const QByteArray & ba, UCharData *pData, bool b16Align)
{
    /*!
    *   Convert QByteArray to unsigned char. This function allocates memory.
    *
    *   \param ba [in] Input data to convert.
    *   \param ppucResult [out] Output data, the function will allocate needed
    *       memory for the output.
    */

    if (pData == NULL)
        return;

    if (pData->pucData == NULL)
    {
        if (b16Align)
        {
            pData->uCapacity    = ba.size() + (ba.size() % 16);

            if (pData->uCapacity < 16)
                pData->uCapacity+= 16 - pData->uCapacity;
        }
        else
        {
            pData->uCapacity    = ba.size();
        }

        pData->pucData      = new unsigned char [pData->uCapacity];
    }

    memset(pData->pucData, 0, pData->uCapacity);

    for (int i = 0; i < ba.size(); ++i)
        pData->pucData[i]   = ba[i];

    pData->uLen             = ba.size() + 1;
}

void PasswordsShelter::UCharData2QByteArray(const UCharData * pData, QByteArray & baResult)
{
    /*!
    *   Convert unsigned char to QByteArray.
    *
    *   \param pucData [in] Input data - array of unsigned chars.
    *   \param baResult [out] Reference to QByteArray object - function will
    *       put the result into it.
    */

    baResult.clear();

    for (unsigned i = 0; i < pData->uLen; ++i)
    {
        baResult.append(pData->pucData[i]);
    }
}

QString PasswordsShelter::QByteArray2String(const QByteArray & baInput)
{
    QString strRET;

    for (int i = 0; i < baInput.size(); ++i)
    {
        strRET += QString::number(baInput.at(i)) + " ";
    }

    return strRET;
}

bool PasswordsShelter::OpenSSL_Encrypt(UCharData       *   pInputData,
                                       unsigned char   *   pucKey,
                                       unsigned char   *   pucIV,
                                       UCharData       *   pResultData)
{
    /*!
     *  Encrypt data using AES 256 bit cipher.
     *
     *  \param pInputData [in]
     *  \param pucKey [in]
     *  \param pucIV [in]
     *  \param pResultData [out]
     */

    EVP_CIPHER_CTX * pContext   = NULL;

    int iInputLen               = pInputData->uCapacity;
    int iTotalLen               = 0;

    pContext                    = EVP_CIPHER_CTX_new();

    if (pContext == NULL)
    {
        //  failed to create openssl cipher context
        return false;
    }

    if (EVP_EncryptInit(pContext, EVP_aes_256_cbc(), pucKey, pucIV) != 1)
    {
        //  an error occured
        EVP_CIPHER_CTX_free(pContext);
        return false;
    }

    if (EVP_EncryptUpdate(pContext,
                          pResultData->pucData,
                          &iTotalLen,
                          pInputData->pucData,
                          iInputLen)
            != 1)
    {
        //  failed to encrypt data
        EVP_CIPHER_CTX_free(pContext);

        return false;
    }

    int iExtraLen               = 0;

    if (EVP_EncryptFinal_ex(pContext,
                            pResultData->pucData + iTotalLen,
                            &iExtraLen) != 1)
    {
        //  failed to encrypt data
        EVP_CIPHER_CTX_free(pContext);

        return false;
    }

    pResultData->uLen           = iTotalLen + iExtraLen;

    EVP_CIPHER_CTX_free(pContext);

    return true;
}

bool PasswordsShelter::OpenSSL_Decrypt(UCharData       *   pInputData,
                                       unsigned char   *   pucKey,
                                       unsigned char   *   pucIV,
                                       UCharData       *   pResultData)
{
    /*!
     *  Decrypt data encrypted using AES256 cipher.
     *
     *  \param pInputData [in]
     *  \param pucKey [in]
     *  \param pucIV [in]
     *  \param pResultData [out]
     */

    EVP_CIPHER_CTX * pContext   = NULL;
    int iInputLen               = pInputData->uLen;
    int iOutputLen              = pResultData->uCapacity;


    pContext                    = EVP_CIPHER_CTX_new();

    if (pContext == NULL)
    {
        //  failed to create openssl cipher context
        return false;
    }

    if (EVP_DecryptInit_ex(pContext,
                           EVP_aes_256_cbc(),
                           NULL,
                           pucKey,
                           pucIV)
        != 1)
    {
        EVP_CIPHER_CTX_free(pContext);

        return false;
    }

    if (EVP_DecryptUpdate(pContext,
                          pResultData->pucData,
                          &iOutputLen,
                          pInputData->pucData,
                          iInputLen)
        != 1)
    {
        EVP_CIPHER_CTX_free(pContext);

        return false;
    }
    else
    {
        pResultData->uLen   = iOutputLen;
    }

    return true;
}

#ifdef WANT_SOME_TESTS
bool PasswordsShelter::TestEncryption(const QByteArray & baIV, const QString & strInputText, QByteArray & baResult)
{
    return EncryptText(strInputText, baResult, baIV);
}

bool PasswordsShelter::TestDecryption(const QByteArray & baIV, const QByteArray & baEncrypted, QString & strResult)
{
    strResult = DecryptText(baEncrypted, baIV);

    return (strResult.isEmpty() == false);
}

bool PasswordsShelter::RunTests()
{
    QByteArray baSHA;
    QByteArray baEncrypted;
    QByteArray baIV;

    QList < QString > inputData = {

        QStringLiteral("Mogę jeść szkło, i mi nie szkodzi."),
        QStringLiteral("śðóæśðłłśðąśćłżźl"),
        QStringLiteral("Sîne klâwen durh die wolken sint geslagen"),
        QStringLiteral("er stîget ûf mit grôzer kraft"),
        QStringLiteral("Τη γλώσσα μου έδωσαν ελληνική"),
        QStringLiteral("από το Άξιον Εστί"),
        QStringLiteral("На берегу пустынных волн"),
        QStringLiteral("Стоял он, дум великих полн"),
        QStringLiteral("ვეპხის ტყაოსანი შოთა რუსთაველი"),
        QStringLiteral("ღმერთსი შემვედრე, ნუთუ კვლა დამხსნას სოფლისა"),
        QStringLiteral("யாமறிந்த மொழிகளிலே தமிழ்மொழி போல் இனிதாவது எங்கும் காணோம்"),
        QStringLiteral("பாமரராய் விலங்குகளாய், உலகனைத்தும் இகழ்ச்சிசொலப் பான்மை கெட்டு"),
        QStringLiteral("काचं शक्नोम्यत्तुम् । नोपहिनस्ति माम् ॥"),
        QStringLiteral("Jeg kan spise glas, det gør ikke ondt på mig."),
        QStringLiteral(" kå Glas frässa, ond des macht mr nix!"),
        QStringLiteral("אני יכול לאכול זכוכית וזה לא מזיק לי"),
        QStringLiteral("Би шил идэй чадна, надад хортой биш"),
        QStringLiteral("ᐊᓕᒍᖅ ᓂᕆᔭᕌᖓᒃᑯ ᓱᕋᙱᑦᑐᓐᓇᖅᑐᖓ")
    };

    QString strDecrypted;
    QString strPass     = "UltraStrongP4ssw0rD!12ążć";

    baSHA               = CalculateSecrectSHA(strPass);
    SetSecretKey(baSHA);

    GenerateIV(baIV);
    bool bOK            = true;

    for (int i = 0; i < inputData.size(); ++i)
    {
        if (TestEncryption(baIV, inputData.at(i), baEncrypted) == false)
        {
            qDebug() << "Failed to execute TestEncryption()";
            return false;
        }

        if (TestDecryption(baIV, baEncrypted, strDecrypted) == false)
        {
            qDebug() << "Failed to execute TestDecryption()";
            return false;
        }

        if (inputData.at(i) != strDecrypted)
        {
            bOK         = false;

            qDebug() << "Failed to decrypt `" << inputData.at(i) << "`" << ", decrypted=`" << strDecrypted << "`";
        }
    }

    if (bOK)
    {
        qDebug() << "All encryption tests has been passed.";
    }
    else
    {
        qDebug() << "Some of the encryption tests has failed.";
    }

    return bOK;
}

void PasswordsShelter::PrintQByteArray(const QByteArray & ba, const QString & strName)
{
    QString str = "QByteArray(" + strName + "): ";

    for (int i = 0; i < ba.size(); ++i)
    {
        str     += QString::number(ba.at(i)) + " ";
    }

    qDebug() << str;
}

void PasswordsShelter::PrintUCharData(const UCharData & data, const QString & strName)
{
    QString str = "UCharData(" + strName + "): ";

    for (unsigned i = 0; i < data.uLen; ++i)
    {
        str     += QString::number(data.pucData[i]) + " ";
    }

    qDebug() << str;
}

#endif


void PasswordsShelter::SetServiceExtraData(const QString            & strServiceName,
                                           const ServiceExtraData   & sed)
{
    bool bFound                 = false;

    for (int i = 0; i < webServiceDataList.size(); ++i)
    {
        WebServiceData & wsd    = webServiceDataList[i];

        if (wsd.strServiceName != strServiceName)
            continue;

        bFound                  = true;
        wsd.extraData           = sed;

        break;
    }

    if (bFound == false)
    {
        //  no extra data has been found - there is no such account in the system for given service
        //  let's create an empty account
        webServiceDataList.push_back(WebServiceData());

        WebServiceData & wsd    = webServiceDataList.back();

        wsd.strServiceName      = strServiceName;
        wsd.extraData           = sed;
    }
}

bool PasswordsShelter::GetServiceExtraData(const QString            & strServiceName,
                                           ServiceExtraData         & sed)
{
    bool bFound                 = false;

    foreach (const WebServiceData & wsd, webServiceDataList)
    {
        if (wsd.strServiceName != strServiceName)
            continue;

        sed                     = wsd.extraData;
        bFound                  = true;

        break;
    }

    return bFound;
}

int PasswordsShelter::GetServicesCount()
{
    //!< Get the number of registered services info in the passwords shelter.

    return webServiceDataList.size();
}

void PasswordsShelter::GetServiceAt(int iIDX, QString & strServiceName)
{
    //!< Get name of the service at given index. May not return correct
    //! values, when the index is wrong.

    if (iIDX < 0 || iIDX >= webServiceDataList.size())
        return;

    const WebServiceData & wsd = webServiceDataList[iIDX];

    strServiceName = wsd.strServiceName;
}

void PasswordsShelter::DeleteServiceInfo(const QString & strServiceName)
{
    //!<    Remove service data from container. Does not affect configuration
    //!     file. SubmitChanges() must be called after the execution.

    for (int i = 0; i < webServiceDataList.size(); ++i)
    {
        const WebServiceData & wsd = webServiceDataList[i];

        if (wsd.strServiceName != strServiceName)
            continue;

        webServiceDataList.removeAt(i);
        break;
    }
}

void PasswordsShelter::SubmitChanges()
{
    //!<    Write all changes to configuration file.

    WriteWebServiceData();
}
