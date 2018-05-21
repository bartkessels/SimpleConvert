#pragma once

#include <QListWidgetItem>
#include <QFile>
#include <QFileInfo>

class ListItemFile : public QListWidgetItem
{
public:
    explicit ListItemFile(QFile *file);
    ~ListItemFile();
    QString getFilePath();
    QString getFileName();

private:
    QFile *file;
};
