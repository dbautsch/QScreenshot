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

    QSettings settings(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);

    int iCount                          = settings.beginReadArray("PASSWORDS_SHELTER");
    bool bFound                         = false;

    for (int i = 0; i < iCount; ++i)
    {
        settings.setArrayIndex(i);

        if (settings.value("SERVICE_NAME").toString() != strServiceName)
        {
            continue;
        }

        strLogin                        = settings.value("LOGIN").toString();
        QByteArray baPasswordEncrypted  = settings.value("PASSWORD").toByteArray();

        strPassword                     = DecryptText(baPasswordEncrypted);
        bFound                          = true;

        break;
    }

    return bFound;
}

void PasswordsShelter::SetLoginPasswordForService(const QString    & strServiceName,
                                                  const QString    & strLogin,
                                                  const QString    & strPassword)
{
    /*!
     *  Save the pair - login and password for given web service to shelter.
     */
}

void PasswordsShelter::EncryptText(const QString   & strText,
                                   QByteArray      & baEncrypted)
{
    /*!
    *   Encrypt text using
    */
}

QString PasswordsShelter::DecryptText(const QByteArray & baEncrypted)
{

}
