/* simpleconvert-application.c
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

#include "simpleconvert-application.h"

struct _SimpleconvertApplication {
    GtkApplication parent_instance;
};

G_DEFINE_TYPE (SimpleconvertApplication, simpleconvert_application, GTK_TYPE_APPLICATION)

/*
 * =============================================================================
 * Signatures
 *
 */
static void simpleconvert_application_class_init (SimpleconvertApplicationClass *klass);
static void simpleconvert_application_init (SimpleconvertApplication *self);

/* Callback functions */
static void simpleconvert_application_cb_activate (GApplication *app);
static void simpleconvert_application_cb_startup (GApplication *app);
static void simpleconvert_application_cb_shortcuts (GSimpleAction *action,
                                                    GVariant      *parameter,
                                                    gpointer       user_data);
static void simpleconvert_application_cb_about (GSimpleAction *action,
                                                GVariant      *parameter,
                                                gpointer       user_data);
static void simpleconvert_application_cb_quit (GSimpleAction *action,
                                               GVariant      *parameter,
                                               gpointer       user_data);

/*
 * =============================================================================
 * App menu entries
 *
 */
const GActionEntry app_actions[] = {
        { "shortcuts", simpleconvert_application_cb_shortcuts },
        { "about", simpleconvert_application_cb_about },
        { "quit", simpleconvert_application_cb_quit }
};

/*
 * =============================================================================
 * Public function implementations
 *
 */
SimpleconvertApplication *
simpleconvert_application_new ()
{
    SimpleconvertApplication *app;

    app = g_object_new (SIMPLECONVERT_TYPE_APPLICATION,
                        "application-id", APPLICATION_ID,
                        "flags", G_APPLICATION_FLAGS_NONE,
                        NULL);

    return app;
}

/*
 * =============================================================================
 * Private function implementations
 *
 */
static void
simpleconvert_application_class_init (SimpleconvertApplicationClass *klass)
{
}

static void
simpleconvert_application_init (SimpleconvertApplication *self)
{
    g_assert (SIMPLECONVERT_IS_APPLICATION (self));

    g_signal_connect (self, "activate", G_CALLBACK (simpleconvert_application_cb_activate), NULL);
    g_signal_connect (self, "startup", G_CALLBACK (simpleconvert_application_cb_startup), NULL);
}

/*
 * =============================================================================
 * Callback function implementations
 *
 */
static void
simpleconvert_application_cb_activate (GApplication *app)
{
    g_assert (G_IS_APPLICATION (app));

    SimpleconvertWindowMain *window;

    window = simpleconvert_window_main_new (app);
    gtk_window_present (GTK_WINDOW (window));
}

static void
simpleconvert_application_cb_startup (GApplication *app)
{
    g_assert (G_IS_APPLICATION (app));
    g_assert (GTK_IS_APPLICATION (app));

    GObject *menu;
    GtkBuilder *builder;

    builder = gtk_builder_new_from_resource ("/net/bartkessels/simpleconvert/menu-app.ui");
    menu = gtk_builder_get_object (builder, "app-menu");

    g_return_if_fail (G_IS_MENU_MODEL (menu));

    g_action_map_add_action_entries (G_ACTION_MAP (app),
                                     app_actions,
                                     G_N_ELEMENTS (app_actions),
                                     app);
    gtk_application_set_app_menu (GTK_APPLICATION (app), G_MENU_MODEL (menu));
    g_object_unref (menu);
}

static void
simpleconvert_application_cb_about (GSimpleAction *action,
                                    GVariant      *parameters,
                                    gpointer       user_data)
{
    g_assert (GTK_IS_APPLICATION (user_data));

    GtkApplication *app;
    GtkWindow *window;
    SimpleconvertDialogAbout *dialog_about;

    app = GTK_APPLICATION (user_data);
    window = gtk_application_get_active_window (app);
    dialog_about = simpleconvert_dialog_about_new (window);

    gtk_dialog_run (GTK_DIALOG (dialog_about));
    gtk_widget_destroy (GTK_WIDGET (dialog_about));
}

static void
simpleconvert_application_cb_shortcuts (GSimpleAction *action,
                                        GVariant      *paramters,
                                        gpointer       user_data)
{
    g_assert (GTK_IS_APPLICATION (user_data));

    GtkApplication *app;
    GtkWindow *window;
    SimpleconvertWindowShortcuts *window_shortcuts;

    app = GTK_APPLICATION (user_data);
    window = gtk_application_get_active_window (app);
    window_shortcuts = simpleconvert_window_shortcuts_new (window);

    gtk_widget_show (GTK_WIDGET (window_shortcuts));
}

static void
simpleconvert_application_cb_quit (GSimpleAction *action,
                                   GVariant      *parameters,
                                   gpointer       user_data)
{
    g_assert (G_IS_APPLICATION (user_data));

    g_application_quit (G_APPLICATION (user_data));
}
