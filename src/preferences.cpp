#include "preferences.h"

void Preferences::setFFmpegBinary(QString binary)
{
    QSettings *settings = Preferences::getSettings();
    settings->setValue(FFMPEG_BINARY, binary);
}

void Preferences::setOverwriteOutput(bool overwriteOutput)
{
    QSettings *settings = Preferences::getSettings();
    settings->setValue(OVERWRITE_OUTPUT, overwriteOutput);
}

void Preferences::setShowNotificationWhenConverted(bool showNotificationWhenConverted)
{
    QSettings *settings = Preferences::getSettings();
    settings->setValue(SHOW_NOTIFICATION_CONVERTED, showNotificationWhenConverted);
}

QString Preferences::getFFmpegBinary()
{
    QSettings *settings = Preferences::getSettings();
    return settings->value(FFMPEG_BINARY, "ffmpeg").toString();
}

bool Preferences::getOverwriteOutput()
{
    QSettings *settings = Preferences::getSettings();
    return settings->value(OVERWRITE_OUTPUT).toBool();
}

bool Preferences::getShowNotificationWhenConverted()
{
    QSettings *settings = Preferences::getSettings();
    return settings->value(SHOW_NOTIFICATION_CONVERTED).toBool();
}

QSettings *Preferences::getSettings()
{
    QSettings *settings = new QSettings(ORG_NAME, APP_NAME);
    return settings;
}
