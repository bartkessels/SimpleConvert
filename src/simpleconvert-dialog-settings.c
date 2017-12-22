/* simpleconvert-dialog-settings.c
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

#include "simpleconvert-dialog-settings.h"

struct _SimpleconvertDialogSettings {
    GtkDialog parent_instance;

    /* Widget templates */
    GtkButton *btn_apply;
    GtkButton *btn_cancel;
    GtkSwitch *switch_overwrite_output_file;
    GtkSwitch *switch_convert_done_notification;
};

G_DEFINE_TYPE (SimpleconvertDialogSettings, simpleconvert_dialog_settings, GTK_TYPE_DIALOG)

/*
 * =============================================================================
 * Signatures
 *
 */
static void simpleconvert_dialog_settings_class_init (SimpleconvertDialogSettingsClass *klass);
static void simpleconvert_dialog_settings_init (SimpleconvertDialogSettings *self);

/* Callback functions */
static void simpleconvert_dialog_settings_cb_btn_apply_clicked (GtkWidget *caller,
                                                                gpointer   user_data);
static void simpleconvert_dialog_settings_cb_btn_cancel_clicked (GtkWidget *caller,
                                                                 gpointer   user_data);

/*
 * =============================================================================
 * Public function implementations
 *
 */
SimpleconvertDialogSettings *
simpleconvert_dialog_settings_new (GtkWindow *parent_window)
{
    g_assert (GTK_IS_WINDOW (parent_window));

    SimpleconvertDialogSettings *dialog_settings;

    dialog_settings = g_object_new (SIMPLECONVERT_TYPE_DIALOG_SETTINGS,
                                    "transient-for", parent_window,
                                    NULL);

    return dialog_settings;
}

/*
 * =============================================================================
 * Private function implementations
 *
 */
static void
simpleconvert_dialog_settings_class_init (SimpleconvertDialogSettingsClass *klass)
{
    GtkWidgetClass *widget_class;

    widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/net/bartkessels/simpleconvert/dialog-settings.ui");

    gtk_widget_class_bind_template_child (widget_class, SimpleconvertDialogSettings, btn_apply);
    gtk_widget_class_bind_template_child (widget_class, SimpleconvertDialogSettings, btn_cancel);
    gtk_widget_class_bind_template_child (widget_class, SimpleconvertDialogSettings, switch_overwrite_output_file);
    gtk_widget_class_bind_template_child (widget_class, SimpleconvertDialogSettings, switch_convert_done_notification);
}

static void
simpleconvert_dialog_settings_init (SimpleconvertDialogSettings *self)
{
    g_assert (GTK_IS_WIDGET (self));
    g_assert (SIMPLECONVERT_IS_DIALOG_SETTINGS (self));

    gboolean overwrite_output_file;
    gboolean convert_done_notification;

    gtk_widget_init_template (GTK_WIDGET (self));

    g_signal_connect (self->btn_apply, "clicked",
                      G_CALLBACK (simpleconvert_dialog_settings_cb_btn_apply_clicked),
                      self);
    g_signal_connect (self->btn_cancel, "clicked",
                      G_CALLBACK (simpleconvert_dialog_settings_cb_btn_cancel_clicked),
                      self);

    /* Load settings */
    overwrite_output_file = simpleconvert_settings_get_overwrite_output_file ();
    convert_done_notification = simpleconvert_settings_get_convert_done_notification ();

    /* Display settings in UI */
    gtk_switch_set_active (self->switch_overwrite_output_file, overwrite_output_file);
    gtk_switch_set_active (self->switch_convert_done_notification, convert_done_notification);
}

 /*
 * =============================================================================
 * Callback function implementations
 *
 */
static void
simpleconvert_dialog_settings_cb_btn_apply_clicked (GtkWidget *caller,
                                                    gpointer   user_data)
{
    g_assert (GTK_IS_BUTTON (caller));
    g_assert (SIMPLECONVERT_IS_DIALOG_SETTINGS (user_data));

    SimpleconvertDialogSettings *self;
    gboolean overwrite_output_file;
    gboolean convert_done_notification;

    self = SIMPLECONVERT_DIALOG_SETTINGS (user_data);
    overwrite_output_file = gtk_switch_get_state (self->switch_overwrite_output_file);
    convert_done_notification = gtk_switch_get_state (self->switch_convert_done_notification);

    simpleconvert_settings_set_overwrite_output_file (overwrite_output_file);
    simpleconvert_settings_set_convert_done_notication (convert_done_notification);

    gtk_dialog_response (GTK_DIALOG (self), GTK_RESPONSE_OK);
}

static void
simpleconvert_dialog_settings_cb_btn_cancel_clicked (GtkWidget *caller,
                                                     gpointer   user_data)
{
    g_assert (GTK_IS_BUTTON (caller));
    g_assert (SIMPLECONVERT_IS_DIALOG_SETTINGS (user_data));

    SimpleconvertDialogSettings *self;

    self = SIMPLECONVERT_DIALOG_SETTINGS (user_data);

    gtk_dialog_response (GTK_DIALOG (self), GTK_RESPONSE_CANCEL);
}
