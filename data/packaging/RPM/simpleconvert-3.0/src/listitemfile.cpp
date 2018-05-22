#include "listitemfile.h"

ListItemFile::ListItemFile(QFile *file) :
    file(file)
{
    setText(getFileName());
    setToolTip(getFilePath());
}

ListItemFile::~ListItemFile()
{
    delete file;
}

QString ListItemFile::getFilePath()
{
    return file->fileName();
}

QString ListItemFile::getFileName()
{
    QFileInfo info(file->fileName());
    return info.fileName();
}
