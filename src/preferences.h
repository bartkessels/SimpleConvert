#pragma once

#include <QSettings>

#define OVERWRITE_OUTPUT "overwrite_output"
#define SHOW_NOTIFICATION_CONVERTED "show_notification_converted"

#define ORG_NAME "bartkessels"
#define APP_NAME "simpleconvert"

class Preferences
{
public:
    static void setOverwriteOutput(bool overwriteOutput);
    static void setShowNotificationWhenConverted(bool showNotificationWhenConverted);
    static bool getOverwriteOutput();
    static bool getShowNotificationWhenConverted();

private:
    static QSettings *getSettings();
};
