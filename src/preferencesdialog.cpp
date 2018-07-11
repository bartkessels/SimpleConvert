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
    bool showPromptBeforeCancellation = Preferences::getShowPromptBeforeCancellation();

    ui->editFFmpegBinary->setText(ffmpegBinary);
    ui->cbOverwriteOutput->setChecked(overwriteOutput);
    ui->cbShowNotificationConverted->setChecked(showNotificationConverted);
    ui->cbShowPromptCancellation->setChecked(showPromptBeforeCancellation);
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
    bool overwriteOutput = ui->cbOverwriteOutput->isChecked();
    bool showNotificationConverted = ui->cbShowNotificationConverted->isChecked();
    bool showPromptBeforeCancellation = ui->cbShowPromptCancellation->isChecked();

    Preferences::setFFmpegBinary(ffmpegBinary);
    Preferences::setOverwriteOutput(overwriteOutput);
    Preferences::setShowNotificationWhenConverted(showNotificationConverted);
    Preferences::setShowPromptBeforeCancellation(showPromptBeforeCancellation);

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
