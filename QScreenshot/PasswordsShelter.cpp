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
#include <openssl/evp.h>
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

void PasswordsShelter::EncryptText(const QString    & strText,
                                   QByteArray       & baEncrypted,
                                   const QByteArray & baIV)
{
    /*!
    *   Encrypt text using strSecrectSHA key. It is a well known hash of the
    *   passphrase given by user.
    */


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

void PasswordsShelter::SetSecretKey(const QString & strSecretSHA)
{
    this->strSecretSHA = strSecretSHA;
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

void PasswordsShelter::IVToByteArray(unsigned char * pucIV, QByteArray * pbaIV)
{
    //!<    convert from unsigned char to QByteArray.
    //!<    \param [in] pucIV
    //!<    \param [out] pbaIV
}
