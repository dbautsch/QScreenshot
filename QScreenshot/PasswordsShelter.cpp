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
        //webServiceDataList.push_back(WebServiceData());

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

    unsigned char * pucIV           = NULL;
    unsigned char * pucSecretSHA    = NULL;
    UCharData inputData, resultData;
    bool bRET                       = true;

    baEncrypted.clear();

    QByteArray2uchar(baIV, &pucIV);
    QByteArray2uchar(baSecretSHA, &pucSecretSHA);

    QByteArray baInput;

    baInput.append(strText);

    //  convert input string to unsigned char array
    inputData.pucData               = new unsigned char [baInput.size()];
    QByteArray2uchar(baInput, inputData.pucData);
    inputData.uLen                  = baInput.size();

    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);

    resultData.pucData              = new unsigned char [baInput.size() * 2];

    if (OpenSSL_Encrypt(&inputData,
                        pucSecretSHA,
                        pucIV,
                        &resultData) == false)
    {
        bRET                        = false;
    }

    delete [] pucIV;
    delete [] pucSecretSHA;

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

    unsigned char * pucIV           = NULL;
    unsigned char * pucSecretSHA    = NULL;

    QByteArray2uchar(baIV, &pucIV);
    QByteArray2uchar(baSecretSHA, &pucSecretSHA);

    delete [] pucIV;
    delete [] pucSecretSHA;

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

void PasswordsShelter::QByteArray2uchar(const QByteArray & ba, unsigned char ** ppucResult)
{
    if (ppucResult == NULL)
        return;

    *ppucResult = new unsigned char [ba.size()];

    for (int i = 0; i < ba.size(); ++i)
        (*ppucResult)[i]    = ba[i];
}

void PasswordsShelter::uchar2QByteArray(const unsigned char * pucData, QByteArray & baResult)
{
    baResult.clear();
    baResult.append(reinterpret_cast<const char*>(pucData));
}

bool PasswordsShelter::OpenSSL_Encrypt(UCharData       *   pInputData,
                                       unsigned char   *   pucKey,
                                       unsigned char   *   pucIV,
                                       UCharData       *   pResultData)
{
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

    return true;
}
