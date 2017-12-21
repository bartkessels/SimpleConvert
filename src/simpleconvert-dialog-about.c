/* simpleconvert-dialog-about.c
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

#include "simpleconvert-dialog-about.h"

struct _SimpleconvertDialogAbout {
    GtkAboutDialog parent_instance;
};

G_DEFINE_TYPE (SimpleconvertDialogAbout, simpleconvert_dialog_about, GTK_TYPE_ABOUT_DIALOG)

/*
 * =============================================================================
 * Signatures
 *
 */
static void simpleconvert_dialog_about_class_init (SimpleconvertDialogAboutClass *klass);
static void simpleconvert_dialog_about_init (SimpleconvertDialogAbout *self);

/*
 * =============================================================================
 * Public function implementations
 *
 */
SimpleconvertDialogAbout *
simpleconvert_dialog_about_new (GtkWindow *parent_window)
{
    g_assert (GTK_IS_WINDOW (parent_window));

    SimpleconvertDialogAbout *dialog_about;

    dialog_about = g_object_new (SIMPLECONVERT_TYPE_DIALOG_ABOUT,
                                 "transient-for", parent_window,
                                 NULL);

    return dialog_about;
}

/*
 * =============================================================================
 * Private function implementations
 *
 */
static void
simpleconvert_dialog_about_class_init (SimpleconvertDialogAboutClass *klass)
{
    GtkWidgetClass *widget_class;

    widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/net/bartkessels/simpleconvert/dialog-about.ui");
}

static void
simpleconvert_dialog_about_init (SimpleconvertDialogAbout *self)
{
    g_assert (SIMPLECONVERT_IS_DIALOG_ABOUT (self));
    g_assert (GTK_IS_WIDGET (self));

    gtk_widget_init_template (GTK_WIDGET (self));
}
