#pragma once

#include <QString>
#include <QSettings>

#define FFMPEG_BINARY "ffmpeg_binary"
#define OVERWRITE_OUTPUT "overwrite_output"
#define SHOW_NOTIFICATION_CONVERTED "show_notification_converted"

#define ORG_NAME "bartkessels"
#define APP_NAME "simpleconvert"

class Preferences
{
public:
    static void setFFmpegBinary(QString binary);
    static void setOverwriteOutput(bool overwriteOutput);
    static void setShowNotificationWhenConverted(bool showNotificationWhenConverted);
    static QString getFFmpegBinary();
    static bool getOverwriteOutput();
    static bool getShowNotificationWhenConverted();

private:
    static QSettings *getSettings();
};
