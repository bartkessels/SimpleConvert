#pragma once

#include <QMainWindow>
#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QFile>
#include <QMovie>
#include <QDebug>

#include "listitemfile.h"
#include "preferencesdialog.h"
#include "preferences.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnAddFile_clicked();
    void on_btnRemoveFile_clicked();
    void on_btnSelectOutputFolder_clicked();
    void on_actionConvert_Files_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionAbout_SimpleConvert_triggered();
    void on_fileConverted(int exitCode);

    void on_actionPreferences_triggered();

private:
    void processNextFile();
    QString getOutputFilePath(QString inputFileName);
    void updateUI(bool filesConverting, int totalFilesToConvert);

    Ui::MainWindow *ui;
    QProcess *ffmpegProcess;
    int filesConverted = 0;
};
