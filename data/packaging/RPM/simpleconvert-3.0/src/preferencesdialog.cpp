#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);

    /* Load all preferences into ui */
    QString ffmpegBinary = Preferences::getFFmpegBinary();
    bool overwriteOutput = Preferences::getOverwriteOutput();
    bool showNotificationConverted = Preferences::getShowNotificationWhenConverted();

    ui->editFFmpegBinary->setText(ffmpegBinary);
    ui->cbOverwriteOutput->setChecked(overwriteOutput);
    ui->cbShowNotificationConverted->setChecked(showNotificationConverted);
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

/**
 * @brief PreferencesDialog::on_buttonBox_accepted
 *
 * Save preferences
 */
void PreferencesDialog::on_buttonBox_accepted()
{
    QString ffmpegBinary = ui->editFFmpegBinary->text();
    bool overwriteOutput = ui->cbOverwriteOutput;
    bool showNotificationConverted = ui->cbShowNotificationConverted;

    Preferences::setFFmpegBinary(ffmpegBinary);
    Preferences::setOverwriteOutput(overwriteOutput);
    Preferences::setShowNotificationWhenConverted(showNotificationConverted);

    this->close();
}

/**
 * @brief PreferencesDialog::on_buttonBox_rejected
 *
 * Close dialog without saving preferences
 */
void PreferencesDialog::on_buttonBox_rejected()
{
    this->close();
}
