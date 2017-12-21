/* simpleconvert-window-shortcuts.c
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

#include "simpleconvert-window-shortcuts.h"

struct _SimpleconvertWindowShortcuts {
    GtkShortcutsWindow parent_instance;
};

G_DEFINE_TYPE (SimpleconvertWindowShortcuts, simpleconvert_window_shortcuts, GTK_TYPE_SHORTCUTS_WINDOW)

/*
 * =============================================================================
 * Signatures
 *
 */
 static void simpleconvert_window_shortcuts_class_init (SimpleconvertWindowShortcutsClass *klass);
 static void simpleconvert_window_shortcuts_init (SimpleconvertWindowShortcuts *self);

 /*
 * =============================================================================
 * Public function implementations
 *
 */
SimpleconvertWindowShortcuts *
simpleconvert_window_shortcuts_new (GtkWindow *parent_window)
{
    g_assert (GTK_IS_WINDOW (parent_window));

    SimpleconvertWindowShortcuts *window_shortcuts;

    window_shortcuts = g_object_new (SIMPLECONVERT_TYPE_WINDOW_SHORTCUTS,
                                     "transient-for", parent_window,
                                     NULL);

    return window_shortcuts;
}

 /*
 * =============================================================================
 * Private function implementations
 *
 */
 static void
simpleconvert_window_shortcuts_class_init (SimpleconvertWindowShortcutsClass *klass)
{
    GtkWidgetClass *widget_class;

    widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/net/bartkessels/simpleconvert/window-shortcuts.ui");
}

 static void
simpleconvert_window_shortcuts_init (SimpleconvertWindowShortcuts *self)
{
    g_assert (GTK_IS_WIDGET (self));

    gtk_widget_init_template (GTK_WIDGET (self));
}
