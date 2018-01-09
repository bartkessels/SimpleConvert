/* simpleconvert-settings.c
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

#include "simpleconvert-settings.h"

/*
 * =============================================================================
 * Signatures
 *
 */
static GSettings *simpleconvert_settings_get_gsettings ();

 /*
 * =============================================================================
 * Public function implementations
 *
 */
void
simpleconvert_settings_set_overwrite_output_file (gboolean overwrite_output_file)
{
    GSettings *settings;

    settings = simpleconvert_settings_get_gsettings ();

    g_settings_set_boolean (settings, SETTINGS_KEY_OVERWRITE_OUTPUT, overwrite_output_file);
}

void
simpleconvert_settings_set_convert_done_notication (gboolean convert_done_notification)
{
    GSettings *settings;

    settings = simpleconvert_settings_get_gsettings ();

    g_settings_set_boolean (settings, SETTINGS_KEY_CONVERT_DONE_NOTICIATION, convert_done_notification);
}

void
simpleconvert_settings_set_remove_converted_from_list (gboolean remove_converted_from_list)
{
    GSettings *settings;

    settings = simpleconvert_settings_get_gsettings ();

    g_settings_set_boolean (settings, SETTINGS_KEY_REMOVE_CONVERTED_FROM_LIST, remove_converted_from_list);
}

gboolean
simpleconvert_settings_get_overwrite_output_file ()
{
    GSettings *settings;
    gboolean overwrite_output;

    settings = simpleconvert_settings_get_gsettings ();
    overwrite_output = g_settings_get_boolean (settings, SETTINGS_KEY_OVERWRITE_OUTPUT);

    return overwrite_output;
}

gboolean
simpleconvert_settings_get_convert_done_notification ()
{
    GSettings *settings;
    gboolean convert_done_notification;

    settings = simpleconvert_settings_get_gsettings ();
    convert_done_notification = g_settings_get_boolean (settings, SETTINGS_KEY_REMOVE_CONVERTED_FROM_LIST);

    return convert_done_notification;
}

gboolean
simpleconvert_settings_get_remove_converted_from_list ()
{
    GSettings *settings;
    gboolean remove_from_list_converted;

    settings = simpleconvert_settings_get_gsettings ();
    remove_from_list_converted = g_settings_get_boolean (settings, SETTINGS_KEY_REMOVE_CONVERTED_FROM_LIST);

    return remove_from_list_converted;
}

 /*
 * =============================================================================
 * Private function implementations
 *
 */
static GSettings *
simpleconvert_settings_get_gsettings ()
{
    GSettings *settings;

    settings = g_settings_new (APPLICATION_ID);

    return settings;
}
