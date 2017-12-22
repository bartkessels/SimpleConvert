/* simpleconvert-widget-listboxitem.c
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

#include "simpleconvert-widget-listboxitem.h"

#include "simpleconvert-widget-listboxitem.h"

struct _SimpleconvertWidgetListboxitem
{
    GtkLabel parent_instance;

    /* Member variables */
    const gchar *file_name;
    const gchar *file_path;
};

G_DEFINE_TYPE (SimpleconvertWidgetListboxitem, simpleconvert_widget_listboxitem, GTK_TYPE_LABEL)

/*
 * =============================================================================
 * Signatures
 *
 */
static void simpleconvert_widget_listboxitem_class_init (SimpleconvertWidgetListboxitemClass *klass);
static void simpleconvert_widget_listboxitem_init (SimpleconvertWidgetListboxitem *self);
static void simpleconvert_widget_listboxitem_setup (SimpleconvertWidgetListboxitem *self);

/*
 * =============================================================================
 * Public function implementations
 *
 */
SimpleconvertWidgetListboxitem *
simpleconvert_widget_listboxitem_new (GFile *file)
{
    g_assert (G_IS_FILE (file));

    SimpleconvertWidgetListboxitem *widget;

    widget = g_object_new (SIMPLECONVERT_TYPE_WIDGET_LISTBOXITEM,
                           NULL);

    widget->file_name = g_file_get_basename (file);
    widget->file_path = g_file_get_path (file);

    simpleconvert_widget_listboxitem_setup (widget);

    return widget;
}

const gchar *
simpleconvert_widget_listboxitem_get_file_name (SimpleconvertWidgetListboxitem *self)
{
    g_assert (SIMPLECONVERT_IS_WIDGET_LISTBOXITEM (self));

    return self->file_name;
}

const gchar *
simpleconvert_widget_listboxitem_get_file_path (SimpleconvertWidgetListboxitem *self)
{
    g_assert (SIMPLECONVERT_IS_WIDGET_LISTBOXITEM (self));

    return self->file_path;
}

/*
 * =============================================================================
 * Private function implementations
 *
 */
static void
simpleconvert_widget_listboxitem_class_init (SimpleconvertWidgetListboxitemClass *klass)
{
}

static void
simpleconvert_widget_listboxitem_init (SimpleconvertWidgetListboxitem *self)
{
}

static void
simpleconvert_widget_listboxitem_setup (SimpleconvertWidgetListboxitem *self)
{
    g_assert (SIMPLECONVERT_IS_WIDGET_LISTBOXITEM (self));

    /*
     * Setup self as label for listbox
     */
    gtk_label_set_text (GTK_LABEL (self), self->file_name);
    gtk_label_set_justify (GTK_LABEL (self), GTK_JUSTIFY_LEFT);
    gtk_label_set_xalign (GTK_LABEL (self), 0);

    gtk_widget_show_all (GTK_WIDGET (self));
}
