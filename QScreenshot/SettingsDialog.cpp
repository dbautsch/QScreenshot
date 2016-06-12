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

#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"
#include "MainWindow.h"

#include <QSettings>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::closeEvent(QCloseEvent *)
{
    ReadSettings();
}

void SettingsDialog::on_pushButton_clicked()
{
    //!<    save button clicked

    WriteSettings();
}

void SettingsDialog::on_horizontalSlider_sliderMoved(int position)
{
    //!<    JPEG compression quality slider has changed

    ui->label_2->setText(QString::number(position));
}

void SettingsDialog::on_horizontalSlider_2_sliderMoved(int position)
{
    //!<    PNG compression quality slider has changed

    ui->label_4->setText(QString::number(position));
}

void SettingsDialog::ReadSettings()
{
    QSettings settings(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);

    ui->horizontalSlider->setValue(settings.value("JPEG_Quality", 80).toInt());
    ui->horizontalSlider_2->setValue(settings.value("PNG_Quality", 7).toInt());

    QPoint ptGeometry;

    ptGeometry.setX(settings.value("GEOMETRY_LEFT", std::numeric_limits<int>::min()).toInt());
    ptGeometry.setY(settings.value("GEOMETRY_TOP", std::numeric_limits<int>::min()).toInt());

    emit RestoreApplicationGeometry(ptGeometry);
}

void SettingsDialog::WriteSettings()
{
    QSettings settings(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);

    settings.setValue("JPEG_Quality", ui->horizontalSlider->value());
    settings.setValue("PNG_Quality", ui->horizontalSlider_2->value());
}

void SettingsDialog::on_horizontalSlider_valueChanged(int value)
{
    on_horizontalSlider_sliderMoved(value);
}

void SettingsDialog::on_horizontalSlider_2_valueChanged(int value)
{
    ui->label_4->setText(QString::number(value));
}

void SettingsDialog::SaveApplicationGeometry(const QPoint & ptPos)
{
    QSettings settings(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);

    settings.setValue("GEOMETRY_LEFT", ptPos.x());
    settings.setValue("GEOMETRY_TOP", ptPos.y());
}
