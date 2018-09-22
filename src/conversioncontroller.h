#pragma once

#include <QObject>
#include <QProcess>

class ConversionController: public QObject
{
    Q_OBJECT

public:
    explicit ConversionController(QObject *parent = 0);
    ~ConversionController();

    void convertFiles();

signals:
    void missingFFMPEGBinary();
    void noOutputDirectory();
    void on_fileConverted(int filesConverted, int totalFiles);

private:
    QProcess *ffmpegProcess;
    int totalFiles = 0;
    int filesConverted = 0;
    bool canceled = false;
};

