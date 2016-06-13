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

#ifndef PASSWORDSSHELTER_H
#define PASSWORDSSHELTER_H

#include <QString>
#include <QList>

typedef struct
{
   QString          strLogin;       //!<    login - plain text

   QByteArray       baPassword;     //!<    password in an encrypted form

   QString          strServiceName; //!<    web service name, eg. imageshack.us

   QByteArray       baIV;           //!<    encryption initialisation vector used to encrypt password,
                                    //!<    semi-random number generated each time a password is saved
}
WebServiceData;

typedef QList < WebServiceData > WebServiceDataList;

/*!
 * \brief The PasswordsShelter class
 *
 *  This class is designed to hold user login and password data
 *  in a secure way. The passwords are stored encrypted.
 */
class PasswordsShelter
{
public:
    PasswordsShelter();

    bool                GetLoginPasswordForService(const QString    & strServiceName,
                                                   QString          & strLogin,
                                                   QString          & strPassword);

    void                SetLoginPasswordForService(const QString    & strServiceName,
                                                   const QString    & strLogin,
                                                   const QString    & strPassword);

    void                SetSecretKey(const QString & strSecretSHA);

private:
    WebServiceDataList  webServiceDataList;

    QString             strSecretSHA;


    void                ReadWebServiceData();

    void                WriteWebServiceData();

    void                EncryptText(const QString       & strText,
                                    QByteArray          & baEncrypted,
                                    const QByteArray    &   baIV);

    QString             DecryptText(const QByteArray    & baEncrypted,
                                    const QByteArray    & baIV);

    void                GenerateIV(QByteArray & baIV);

    void                IVToByteArray(unsigned char * pucIV, QByteArray * pbaIV);
};

#endif // PASSWORDSSHELTER_H
