#include "preferences.h"

void Preferences::setFFmpegBinary(QString binary)
{
    QSettings settings(ORG_NAME, APP_NAME);
    settings.setValue(FFMPEG_BINARY, binary);
}

void Preferences::setOverwriteOutput(bool overwriteOutput)
{
    QSettings settings(ORG_NAME, APP_NAME);
    settings.setValue(OVERWRITE_OUTPUT, overwriteOutput);
}

void Preferences::setShowNotificationWhenConverted(bool showNotificationWhenConverted)
{
    QSettings settings(ORG_NAME, APP_NAME);
    settings.setValue(SHOW_NOTIFICATION_CONVERTED, showNotificationWhenConverted);
}

void Preferences::setShowPromptBeforeCancellation(bool showPromptBeforeCancellation)
{
    QSettings settings(ORG_NAME, APP_NAME);
    settings.setValue(SHOW_PROMPT_BEFORE_CANCELLATION, showPromptBeforeCancellation);
}

QString Preferences::getFFmpegBinary()
{
    QSettings settings(ORG_NAME, APP_NAME);
    return settings.value(FFMPEG_BINARY, "ffmpeg").toString();
}

bool Preferences::getOverwriteOutput()
{
    QSettings settings(ORG_NAME, APP_NAME);
    return settings.value(OVERWRITE_OUTPUT).toBool();
}

bool Preferences::getShowNotificationWhenConverted()
{
    QSettings settings(ORG_NAME, APP_NAME);
    return settings.value(SHOW_NOTIFICATION_CONVERTED).toBool();
}

bool Preferences::getShowPromptBeforeCancellation()
{
    QSettings settings(ORG_NAME, APP_NAME);
    return settings.value(SHOW_PROMPT_BEFORE_CANCELLATION).toBool();
}
