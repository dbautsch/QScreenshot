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

    bool    GetLoginPasswordForService(const QString    & strServiceName,
                                       QString          & strLogin,
                                       QString          & strPassword);

    void    SetLoginPasswordForService(const QString    & strServiceName,
                                       const QString    & strLogin,
                                       const QString    & strPassword);

private:
    void    EncryptText(const QString   & strText,
                        QByteArray      & baEncrypted);

    QString DecryptText(const QByteArray & baEncrypted);
};

#endif // PASSWORDSSHELTER_H
