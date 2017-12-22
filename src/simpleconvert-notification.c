/* simpleconvert-notification.c
 *
 * Copyright © 2017 Bart Kessels <bartkessels@bk-mail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "simpleconvert-notification.h"

void
simpleconvert_notification_display (const gchar *title,
                                    const gchar *body)
{
    /*
     * Don't continue if the user doesn't want notifications
     */
    if (!simpleconvert_settings_get_convert_done_notification ()) {
        return;
    }

    const gchar *icon;
    NotifyNotification *notification;
    GError *error_notification = NULL; // Needs to be initialized immediately

    icon = "net.bartkessels.sipmleconvert";
    notification = notify_notification_new (title, body, icon);

    notify_notification_show (notification, &error_notification);

    if (error_notification != NULL) {
        g_error_free (error_notification);
    }
}
