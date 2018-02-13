/* simple-convert-window-main.c
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

#include "simpleconvert-window-main.h"

struct _SimpleconvertWindowMain {
    GtkApplicationWindow parent_instance;

    /* Template widgets */
    GtkGrid *grd_main;
    GtkButton *btn_add;
    GtkButton *btn_remove;
    GtkButton *btn_convert;
    GtkSpinner *sp_working;
    GtkFileChooserButton *fcbtn_output;
    GtkComboBoxText *cb_extension;
    GtkListBox *lb_files;
};

G_DEFINE_TYPE (SimpleconvertWindowMain, simpleconvert_window_main, GTK_TYPE_APPLICATION_WINDOW)

/*
 * =============================================================================
 * Signatures
 *
 */
static void simpleconvert_window_main_class_init (SimpleconvertWindowMainClass *klass);
static void simpleconvert_window_main_init (SimpleconvertWindowMain *self);
const gchar * simpleconvert_window_main_get_selected_extension (SimpleconvertWindowMain *self);
static void simpleconvert_window_main_add_file_to_list (SimpleconvertWindowMain *self,
                                                        GFile                   *file);
static void simpleconvert_window_main_set_working (SimpleconvertWindowMain *self,
                                                   gboolean                 working);
static void simpleconvert_window_main_convert_file (GTask        *task,
                                                    gpointer      source_object,
                                                    gpointer      task_data,
                                                    GCancellable *cancellable);
static void simpleconvert_window_main_convert_done (GObject      *source_object,
                                                    GAsyncResult *result,
                                                    gpointer      user_data);

/* Callback functions */
static gboolean simpleconvert_window_main_register_shortcuts (GtkWidget   *caller,
                                                              GdkEventKey *event,
                                                              gpointer     user_data);
static void simpleconvert_window_main_cb_btn_add_clicked (GtkWidget *caller,
                                                          gpointer   user_data);
static void simpleconvert_window_main_cb_btn_remove_clicked (GtkWidget *caller,
                                                             gpointer   user_data);
static void simpleconvert_window_main_cb_btn_convert_clicked (GtkWidget *caller,
                                                              gpointer   user_data);
static void simpleconvert_window_main_cb_lb_files_selection_changed (GtkWidget     *caller,
                                                                     GtkListBoxRow *row,
                                                                     gpointer       user_data);

/*
 * =============================================================================
 * Public function implementations
 *
 */
SimpleconvertWindowMain *
simpleconvert_window_main_new (GApplication *app)
{
    g_assert (G_IS_APPLICATION (app));

    SimpleconvertWindowMain *window;

    window = g_object_new (SIMPLECONVERT_TYPE_WINDOW_MAIN,
                           "application", app,
                           "default-width", WINDOW_WIDTH,
                           "default-height", WINDOW_HEIGHT,
                           NULL);

    return window;
}

/*
 * =============================================================================
 * Private function implementations
 *
 */
static void
simpleconvert_window_main_class_init (SimpleconvertWindowMainClass *klass)
{
    GtkWidgetClass *widget_class;

    widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/net/bartkessels/simpleconvert/window-main.ui");

    gtk_widget_class_bind_template_child (widget_class, SimpleconvertWindowMain, grd_main);
    gtk_widget_class_bind_template_child (widget_class, SimpleconvertWindowMain, btn_add);
    gtk_widget_class_bind_template_child (widget_class, SimpleconvertWindowMain, btn_remove);
    gtk_widget_class_bind_template_child (widget_class, SimpleconvertWindowMain, btn_convert);
    gtk_widget_class_bind_template_child (widget_class, SimpleconvertWindowMain, sp_working);
    gtk_widget_class_bind_template_child (widget_class, SimpleconvertWindowMain, fcbtn_output);
    gtk_widget_class_bind_template_child (widget_class, SimpleconvertWindowMain, cb_extension);
    gtk_widget_class_bind_template_child (widget_class, SimpleconvertWindowMain, lb_files);
}

static void
simpleconvert_window_main_init (SimpleconvertWindowMain *self)
{
    g_assert (SIMPLECONVERT_IS_WINDOW_MAIN (self));
    g_assert (GTK_IS_WINDOW (self));
    g_assert (GTK_IS_WIDGET (self));

    gtk_widget_init_template (GTK_WIDGET (self));

    /* Connect signals */
    g_signal_connect (self, "key_press_event",
                      G_CALLBACK (simpleconvert_window_main_register_shortcuts),
                      self);
    g_signal_connect (self->btn_add, "clicked",
                      G_CALLBACK (simpleconvert_window_main_cb_btn_add_clicked),
                      self);
    g_signal_connect (self->btn_remove, "clicked",
                      G_CALLBACK (simpleconvert_window_main_cb_btn_remove_clicked),
                      self);
    g_signal_connect (self->btn_convert, "clicked",
                      G_CALLBACK (simpleconvert_window_main_cb_btn_convert_clicked),
                      self);
    g_signal_connect (self->lb_files, "row-selected",
                      G_CALLBACK (simpleconvert_window_main_cb_lb_files_selection_changed),
                      self);
}

const gchar *
simpleconvert_window_main_get_selected_extension (SimpleconvertWindowMain *self)
{
    g_assert (SIMPLECONVERT_IS_WINDOW_MAIN (self));

    const gchar *extension;

    extension = gtk_combo_box_get_active_id (GTK_COMBO_BOX (self->cb_extension));

    return extension;
}

const gchar *
simpleconvert_window_main_get_output_path (SimpleconvertWindowMain *self)
{
    g_assert (SIMPLECONVERT_IS_WINDOW_MAIN (self));

    GFile *output_file;
    const gchar *output_path;

    output_file = gtk_file_chooser_get_file (GTK_FILE_CHOOSER (self->fcbtn_output));
    output_path = g_file_get_path (output_file);

    return output_path;
}

static void
simpleconvert_window_main_add_file_to_list (SimpleconvertWindowMain *self,
                                            GFile                   *file)
{
    g_assert (SIMPLECONVERT_IS_WINDOW_MAIN (self));
    g_assert (G_IS_FILE (file));

    SimpleconvertWidgetListboxitem *widget_lbi;

    widget_lbi = simpleconvert_widget_listboxitem_new (file);

    gtk_list_box_insert (GTK_LIST_BOX (self->lb_files), GTK_WIDGET (widget_lbi), -1);
    gtk_widget_show_all (GTK_WIDGET (self->lb_files));
}

static void
simpleconvert_window_main_set_working (SimpleconvertWindowMain *self,
                                       gboolean                 working)
{
    g_assert (SIMPLECONVERT_IS_WINDOW_MAIN (self));

    gtk_widget_set_visible (GTK_WIDGET (self->sp_working), working);
    gtk_widget_set_sensitive (GTK_WIDGET (self->btn_convert), !working);
    gtk_widget_set_sensitive (GTK_WIDGET (self->grd_main), !working);
}

static void
simpleconvert_window_main_convert_file (GTask        *task,
                                        gpointer      source_object,
                                        gpointer      task_data,
                                        GCancellable *cancellable)
{
    g_assert (SIMPLECONVERT_IS_WINDOW_MAIN (source_object));
    g_assert (GTK_IS_WIDGET (task_data));

    SimpleconvertWindowMain *self;
    GtkWidget *selected_row;
    SimpleconvertWidgetListboxitem *selected_lbi;
    const gchar *output_path;
    const gchar *extension;
    const gchar *input_file_name;
    const gchar *input_file_path;
    const gchar *output_file_path;
    const gchar *overwrite_output;
    const gchar *command;
    FILE *fp;

    self = SIMPLECONVERT_WINDOW_MAIN (source_object);
    selected_row = GTK_WIDGET (task_data);
    selected_lbi = g_list_nth_data (gtk_container_get_children (GTK_CONTAINER (selected_row)), 0);

    output_path = simpleconvert_window_main_get_output_path (self);
    extension = simpleconvert_window_main_get_selected_extension (self);
    input_file_name = simpleconvert_widget_listboxitem_get_file_name (selected_lbi);
    input_file_path = simpleconvert_widget_listboxitem_get_file_path (selected_lbi);
    output_file_path = g_strconcat (output_path, "/", input_file_name, extension, NULL);

    /*
     * Check if we need to overwrite the output file
     */
    overwrite_output = " -n";
    if (simpleconvert_settings_get_overwrite_output_file ()) {
        overwrite_output = " -y";
    }

    /*
     * Create the ffmpeg command
     */
    command = g_strconcat("ffmpeg", overwrite_output, " -i \"",
                          input_file_path,
                          "\" \"",
                          output_file_path, "\"",
                          NULL);

    fp = popen (command, "r");

    if (fp == NULL) {
        g_print ("Failed to convert %s to %s\n", input_file_path, output_file_path);
        return;
    }

    pclose (fp);
}

static void
simpleconvert_window_main_convert_done (GObject      *source_object,
                                        GAsyncResult *result,
                                        gpointer      user_data)
{
    g_assert (SIMPLECONVERT_IS_WINDOW_MAIN (source_object));
    g_assert (GTK_IS_WIDGET (user_data));

    SimpleconvertWindowMain *self;
    GtkWidget *selected_row;

    self = SIMPLECONVERT_WINDOW_MAIN (source_object);
    selected_row = GTK_WIDGET (user_data);

    if (simpleconvert_settings_get_remove_converted_from_list ()) {
        gtk_widget_destroy (selected_row);
    }

    /*
     * Update UI if there are no records anymore
     */
    if (g_list_length (gtk_list_box_get_selected_rows (GTK_LIST_BOX (self->lb_files))) == 0) {
        gtk_list_box_unselect_all (GTK_LIST_BOX (self->lb_files));
        simpleconvert_window_main_set_working (self, FALSE);
    }
}

/*
 * =============================================================================
 * Private callback implementations
 *
 */
static gboolean
simpleconvert_window_main_register_shortcuts (GtkWidget   *caller,
                                              GdkEventKey *event,
                                              gpointer     user_data)
{
    g_assert (SIMPLECONVERT_IS_WINDOW_MAIN (user_data));

    /*
     * Only continue if the CTRL key is pressed
     */
    if (! (event->state & GDK_CONTROL_MASK))
        return FALSE;

    SimpleconvertWindowMain *self;

    self = SIMPLECONVERT_WINDOW_MAIN (user_data);

    switch (event->keyval) {

    case GDK_KEY_plus: // CTRL + +
        simpleconvert_window_main_cb_btn_add_clicked (GTK_WIDGET (self->btn_add),
                                                      self);
        break;

    case GDK_KEY_minus: // CTRL + -
        simpleconvert_window_main_cb_btn_remove_clicked (GTK_WIDGET (self->btn_remove),
                                                         self);
        break;

    case GDK_KEY_Return: // CTRL + Return
        simpleconvert_window_main_cb_btn_convert_clicked (GTK_WIDGET (self->btn_convert),
                                                          self);
        break;
    };

    return FALSE;
}

static void
simpleconvert_window_main_cb_btn_add_clicked (GtkWidget *caller,
                                              gpointer   user_data)
{
    g_assert (GTK_IS_BUTTON (caller));
    g_assert (SIMPLECONVERT_IS_WINDOW_MAIN (user_data));

    SimpleconvertWindowMain *self;
    GtkFileFilter *file_filter;
    GtkWidget *file_chooser;
    gint file_chooser_result;
    GSList *selected_files;

    self = SIMPLECONVERT_WINDOW_MAIN (user_data);
    file_filter = gtk_file_filter_new ();
    file_chooser = gtk_file_chooser_dialog_new (_("Select files"),
                                                GTK_WINDOW (self),
                                                GTK_FILE_CHOOSER_ACTION_OPEN,
                                                _("Cancel"), GTK_RESPONSE_CANCEL,
                                                _("Add"), GTK_RESPONSE_ACCEPT,
                                                NULL);

    gtk_file_filter_add_mime_type (file_filter, "video/*");
    gtk_file_chooser_set_select_multiple (GTK_FILE_CHOOSER (file_chooser), TRUE);
    gtk_file_chooser_set_filter (GTK_FILE_CHOOSER (file_chooser), file_filter);

    file_chooser_result = gtk_dialog_run (GTK_DIALOG (file_chooser));

    if (file_chooser_result == GTK_RESPONSE_ACCEPT) {
        selected_files = gtk_file_chooser_get_files (GTK_FILE_CHOOSER (file_chooser));

        guint selected_files_length = g_slist_length (selected_files);
        GFile *file;

        /*
         * Add every opened file to the listbox
         */
        for (int files_iterator = 0; files_iterator < selected_files_length; files_iterator++) {
            file = g_slist_nth_data (selected_files, files_iterator);

            simpleconvert_window_main_add_file_to_list (self, file);
        }

        g_slist_free (selected_files);
    }

    gtk_widget_destroy (GTK_WIDGET (file_chooser));
}

static void
simpleconvert_window_main_cb_btn_remove_clicked (GtkWidget *caller,
                                                 gpointer   user_data)
{
    g_assert (GTK_IS_BUTTON (caller));
    g_assert (SIMPLECONVERT_IS_WINDOW_MAIN (user_data));

    g_return_if_fail (gtk_widget_is_sensitive (caller));

    SimpleconvertWindowMain *self;
    GList *selected_rows;
    guint total_selected_rows;

    self = SIMPLECONVERT_WINDOW_MAIN (user_data);
    selected_rows = gtk_list_box_get_selected_rows (GTK_LIST_BOX (self->lb_files));
    total_selected_rows = g_list_length (selected_rows);

    /*
     * Remove every selected file from the listbox
     */
    for (int selected_rows_iterator = 0; selected_rows_iterator < total_selected_rows; selected_rows_iterator++) {
        SimpleconvertWidgetListboxitem *widget_lbi;

        widget_lbi = g_list_nth_data (selected_rows, selected_rows_iterator);
        gtk_widget_destroy (GTK_WIDGET (widget_lbi));
    }

    g_list_free (selected_rows);
}

static void
simpleconvert_window_main_cb_btn_convert_clicked (GtkWidget *caller,
                                                  gpointer   user_data)
{
    g_assert (GTK_IS_BUTTON (caller));
    g_assert (SIMPLECONVERT_IS_WINDOW_MAIN (user_data));

    SimpleconvertWindowMain *self;
    const gchar *output_path;
    GtkWidget *dialog_error;
    GList *selected_rows;
    guint total_selected_rows;

    self = SIMPLECONVERT_WINDOW_MAIN (user_data);
    output_path = simpleconvert_window_main_get_output_path (self);

    /*
     * Only continue if an output path is specified
     */
    if (output_path == NULL) {
        dialog_error = gtk_message_dialog_new_with_markup (GTK_WINDOW (self),
                                                           GTK_DIALOG_MODAL,
                                                           GTK_MESSAGE_WARNING,
                                                           GTK_BUTTONS_CLOSE,
                                                           MSG_ERROR_MISSING_OUTPUT);

        gtk_dialog_run (GTK_DIALOG (dialog_error));
        gtk_widget_destroy (GTK_WIDGET (dialog_error));

        return;
    }

    simpleconvert_window_main_set_working (self, TRUE);
    gtk_list_box_select_all (GTK_LIST_BOX (self->lb_files));
    selected_rows = gtk_list_box_get_selected_rows (GTK_LIST_BOX (self->lb_files));
    total_selected_rows = g_list_length (selected_rows);

    for (int i = 0; i < total_selected_rows; i++) {
        GtkWidget *selected_row;
        GTask *convert_task;

        selected_row = g_list_nth_data (selected_rows, i);

        convert_task = g_task_new (self,
                                   NULL,
                                   (void *) simpleconvert_window_main_convert_done,
                                   selected_row);
        g_task_set_task_data (convert_task,
                              selected_row,
                              NULL);
        g_task_run_in_thread (convert_task,
                              (void *) simpleconvert_window_main_convert_file);
    }

    g_list_free (selected_rows);
}

static void
simpleconvert_window_main_cb_lb_files_selection_changed (GtkWidget     *caller,
                                                         GtkListBoxRow *row,
                                                         gpointer       user_data)
{
    g_assert (GTK_IS_LIST_BOX (caller));
    g_assert (SIMPLECONVERT_IS_WINDOW_MAIN (user_data));

    SimpleconvertWindowMain *self;

    self = SIMPLECONVERT_WINDOW_MAIN (user_data);

    /*
     * Make sure the remove button only allows input
     * when a row is selected
     */
    gtk_widget_set_sensitive (GTK_WIDGET (self->btn_remove), row != NULL);
}
