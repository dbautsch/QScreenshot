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
#include <openssl/evp.h>
#include <openssl/conf.h>
#include <openssl/bn.h>
#include <openssl/err.h>

PasswordsShelter::PasswordsShelter()
{
#ifdef WANT_SOME_TESTS
    //  very simple unit test
    RunTests();
#endif
}

bool PasswordsShelter::GetLoginPasswordForService(const QString    & strServiceName,
                                                  QString          & strLogin,
                                                  QString          & strPassword)
{
    /*!
     *  Get the pair - login and password for given web service name from the shelter.
     */

    foreach (const WebServiceData & wsd, webServiceDataList)
    {
        if (wsd.strServiceName != strServiceName)
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

    //  convert input string to unsigned char array
    QByteArray2UCharData(baInput, &inputData, true);

    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);

    resultData.uLen                 = (baInput.size() * 2);
    resultData.uLen                 += resultData.uLen % 16;

    if (resultData.uLen < 16)
        resultData.uLen             = 16 - resultData.uLen;

    resultData.pucData              = new unsigned char [resultData.uLen];

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
    QByteArray baDecrypted;

    return "";
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

QByteArray PasswordsShelter::CalculateSecrectSHA(const QString & strInput)
{
    QByteArray baInput;

    baInput.append(strInput);

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
            pData->uLen     = ba.size() + (ba.size() % 16);

            if (pData->uLen < 16)
                pData->uLen += 16 - pData->uLen;
        }
        else
        {
            pData->uLen     = ba.size();
        }

        pData->pucData      = new unsigned char [pData->uLen];
    }

    memset(pData->pucData, 0, pData->uLen);

    for (int i = 0; i < ba.size(); ++i)
        pData->pucData[i]   = ba[i];
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
    baResult.append(reinterpret_cast<const char*>(pData->pucData));
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

    int iInputLen               = pInputData->uLen;
    int iOutputLen              = pResultData->uLen;

    if (EVP_EncryptUpdate(pContext,
                          pResultData->pucData,
                          &iOutputLen,
                          pInputData->pucData,
                          iInputLen)
            != 1)
    {
        //  failed to encrypt data
        EVP_CIPHER_CTX_free(pContext);
    }

    pResultData->uLen           = iOutputLen;

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
    int iOutputLen              = pResultData->uLen;


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
                          pInputData->pucData,
                          &iInputLen,
                          pResultData->pucData,
                          iOutputLen)
        != 1)
    {
        EVP_CIPHER_CTX_free(pContext);

        return false;
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

    return true;
}

bool PasswordsShelter::RunTests()
{
    QByteArray baSHA;
    QByteArray baEncrypted;
    QByteArray baIV;
    QString strInput    = "test";
    QString strDecrypted;
    QString strPass     = "test_pass";

    baSHA               = CalculateSecrectSHA(strPass);
    SetSecretKey(baSHA);

    GenerateIV(baIV);

    if (TestEncryption(baIV, strInput, baEncrypted) == false)
    {
        qDebug() << "Failed to execute TestEncryption()";
        return false;
    }

    if (TestDecryption(baIV, baEncrypted, strDecrypted) == false)
    {
        qDebug() << "Failed to execute TestDecryption()";
        return false;
    }

    if (strInput == strDecrypted)
    {
        qDebug() << "Encryption test has been passed.";
    }
    else
    {
        qDebug() << "Encryption test has failed.";
    }

    return strInput == strDecrypted;
}
#endif
