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

#include "CaptureRectDrawer.h"

CaptureRectDrawer::CaptureRectDrawer(QObject *parent) : QObject(parent)
{
    pScreenRectDialog   = new ScreenRectDialog();
}

CaptureRectDrawer::~CaptureRectDrawer()
{
    delete pScreenRectDialog;
}

void CaptureRectDrawer::ShowRect()
{
    pScreenRectDialog->SetRectPos(QPoint(200, 200));
    pScreenRectDialog->SetRectSize(255, 255);
    pScreenRectDialog->EnableRect();

    pScreenRectDialog->show();

}
