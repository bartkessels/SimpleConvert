#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    movie = new QMovie(":icons/loading");
    ui->lblLoadingIndicator->setMovie(movie);
    ui->lblLoadingIndicator->show();
    movie->start();
    ui->vLayoutMainButtons->setAlignment(Qt::AlignTop);
    updateUI(false, 0);
}

MainWindow::~MainWindow()
{
    /* Kill current process if there
     * are files being converted
     */
    if (filesConverted > 0) {
        ffmpegProcess->kill();
    }

    delete movie;
    delete ui;
}

/**
 * @brief MainWindow::on_btnAddFile_clicked
 *
 * Show file dialog and add selected file
 * to the listview
 */
void MainWindow::on_btnAddFile_clicked()
{
    QFileDialog dialog(this, tr("Open Media Files"));
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (!dialog.exec()) {
        return;
    }

    for (int i = 0; i < dialog.selectedFiles().count(); i++) {
        QFile *file = new QFile(dialog.selectedFiles().at(i));

        ListItemFile *listItem = new ListItemFile(file);
        ui->lvFiles->addItem(listItem);
    }
}

/**
 * @brief MainWindow::on_btnRemoveFile_clicked
 *
 * Remove selected file from the listview
 */
void MainWindow::on_btnRemoveFile_clicked()
{
    if (ui->lvFiles->selectionModel()->selectedIndexes().size() > 0) {
        int startIndex = ui->lvFiles->selectionModel()->selectedIndexes().first().row();
        int count = ui->lvFiles->selectionModel()->selectedIndexes().count();

        ui->lvFiles->model()->removeRows(startIndex, count);
    }
}

/**
 * @brief MainWindow::on_btnSelectOutputFolder_clicked
 *
 * Show folder dialog and enter the selected folder
 * path into the output line edit
 */
void MainWindow::on_btnSelectOutputFolder_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select Output Directory"),
                                                          QStandardPaths::locate(QStandardPaths::HomeLocation,
                                                                                 QString(),
                                                                                 QStandardPaths::LocateDirectory),
                                                          QFileDialog::ShowDirsOnly);
    if (directory.length() > 0) {
        ui->editOutputFolder->setText(directory);
    }
}

/**
 * @brief MainWindow::on_actionConvert_Files_triggered
 *
 * Disable UI interaction and convert all the files
 * to the selected audio type and update status widgets
 */
void MainWindow::on_actionConvert_Files_triggered()
{
    int totalFilesToConvert = ui->lvFiles->count();
    if (totalFilesToConvert < 1) {
        return;
    }

    if (ui->editOutputFolder->text().length() <= 0) {
        QMessageBox::warning(this, tr("No Output Folder"), tr("Please specify an output folder..."));
        return;
    }

    if (!QFile::exists(ui->editOutputFolder->text())) {
        QMessageBox::warning(this, tr("Output Folder Does Not Exist"), tr("The specified output folder does not seem to exist..."));
        return;
    }

    updateUI(true, totalFilesToConvert);
    processNextFile();
}

/**
 * @brief MainWindow::on_actionStop_conversion_triggered
 *
 * Stop converting files if any conversion is going on and
 * the user wants to stop it
 */
void MainWindow::on_actionStop_conversion_triggered()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, tr("Stop Conversion"), tr("Are you sure you want to"
                                                                                              "stop the conversion?"),
                                                              QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        ffmpegProcess->kill();
        canceled = true;
        updateUI(false, 0);
    }
}

/**
 * @brief MainWindow::on_actionPreferences_triggered
 *
 * Open preferences dialog
 */
void MainWindow::on_actionPreferences_triggered()
{
    PreferencesDialog preferencesDialog;
    preferencesDialog.exec();
}

/**
 * @brief MainWindow::on_actionAbout_Qt_triggered
 *
 * Show about Qt dialog
 */
void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

/**
 * @brief MainWindow::on_actionAbout_SimpleConvert_triggered
 *
 * Show about SimpleConvert dialog
 */
void MainWindow::on_actionAbout_SimpleConvert_triggered()
{
    QMessageBox::about(this, tr("About SimpleConvert"), tr("SimpleConvert is a small application to "
                                                           "convert video and/or audio files to any "
                                                           "filetype using ffmpeg.\n\n"
                                                           "This application aims to provide an easy "
                                                           "to understand interface so everyone will "
                                                           "be able to use the power of ffmpeg"));
}

/**
 * @brief MainWindow::on_fileConverted
 *
 * Enable widgets if all the files are
 * converted and clear status bar widgets
 *
 * @param int exitCode the code with which the process is exited
 */
void MainWindow::on_fileConverted(int exitCode)
{
    Q_UNUSED (exitCode)

    int totalFilesToConvert = ui->lvFiles->count();
    filesConverted++;

    ui->pbStatus->setValue(filesConverted);

    if (filesConverted >= totalFilesToConvert || canceled) {
        updateUI(false, 0);
        ffmpegProcess->deleteLater();

        /* Check if we need to show a notification */
        if (Preferences::getShowNotificationWhenConverted() && !canceled) {
            QMessageBox::information(this, tr("Converting Finished"),
                                     tr("All your files are converted"));
        }

        filesConverted = 0;
        canceled = false;
    } else {
        processNextFile();
    }
}

/**
 * @brief MainWindow::processNextFile
 *
 * Convert next file in the listview
 */
void MainWindow::processNextFile()
{
    QString ffmpegBinary = Preferences::getFFmpegBinary();
    int nextFileIndex = filesConverted;
    ListItemFile *currentFile = dynamic_cast<ListItemFile*>(ui->lvFiles->item(nextFileIndex));

    QStringList ffmpegArguments;
    ffmpegArguments.append("-i");
    ffmpegArguments.append(currentFile->getFilePath());
    ffmpegArguments.append(getOutputFilePath(currentFile->getFileName()));

    /* Check if we should overwrite the output file if it exists */
    if (Preferences::getOverwriteOutput()) {
        ffmpegArguments.append("-y");
    } else {
        ffmpegArguments.append("-n");
    }

    ffmpegProcess = new QProcess(this);
    connect (ffmpegProcess, SIGNAL(finished(int)), this, SLOT(on_fileConverted(int)));
    ffmpegProcess->setProcessChannelMode(QProcess::MergedChannels);
    ffmpegProcess->start(ffmpegBinary, ffmpegArguments);
}

/**
 * @brief MainWindow::getOutputFilePath
 *
 * Get output file path based on the input file
 * name
 *
 * @param inputFileName name of the input file
 * @return full path of the output file with extension
 */
QString MainWindow::getOutputFilePath(QString inputFileName)
{
    QString outputPath = ui->editOutputFolder->text();
    QString extension = ui->cbOutputType->currentText();

    extension.replace(".", "");
    return outputPath + "/" + inputFileName + "." + extension;
}

/**
 * @brief MainWindow::updateUI
 *
 * Update UI when files are converting
 *
 * @param filesConverting wheter or not there are files being converted
 * @param totalFilesToConvert the number of files which are going to be converted
 */
void MainWindow::updateUI(bool filesConverting, int totalFilesToConvert)
{
    ui->actionConvert_Files->setEnabled(!filesConverting);
    ui->actionStop_conversion->setEnabled(filesConverting);

    disableLayout(ui->hLayoutCentralWidget, !filesConverting, true);
    disableLayout(ui->hLayoutStatusBar, true, filesConverting);

    ui->lblStatus->setText(tr("Converting %1 file(s)...").arg(totalFilesToConvert));
    ui->pbStatus->setRange(0, totalFilesToConvert);
}

/**
 * @brief MainWindow::disableLayout
 *
 * Recursively disable or hide widgets inside
 * a layout
 *
 * @param obj the layout which children should be iterated over
 * @param enabled wheter or not the children should be enabled
 * @param visible wheter or not the children should be visible
 */
void MainWindow::disableLayout(QLayoutItem *obj, bool enabled, bool visible)
{
    if (obj->widget() != NULL) {
        obj->widget()->setEnabled(enabled);
        obj->widget()->setVisible(visible);
    } else if (obj->layout() != NULL) {
        for (int i = 0; i < obj->layout()->count(); i++) {
            QLayoutItem *widget = obj->layout()->itemAt(i);
            disableLayout(widget, enabled, visible);
        }
    }
}
