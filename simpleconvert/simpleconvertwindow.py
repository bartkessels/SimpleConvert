# SimpleconvertWindow.py
#
# Copyright (C) 2017 Bart Kessels <bartkessels@bk-mail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

from gi.repository import Gtk
from .gi_composites import GtkTemplate
from threading import Thread
from pathlib import Path
import ffmpeg
import os

from simpleconvert.listboxitem import ListBoxItem

UI_FILE = os.path.dirname(os.path.realpath(__file__)) + '/ui/mainwindow.glade'

@GtkTemplate(ui=UI_FILE)
class SimpleconvertWindow(Gtk.ApplicationWindow):
    __gtype_name__ = 'simpleconvertWindow'

    sp_working = GtkTemplate.Child()
    lb_files = GtkTemplate.Child()
    cb_extension = GtkTemplate.Child()
    fcbtn_output = GtkTemplate.Child()
    grd_buttons = GtkTemplate.Child()
    btn_convert = GtkTemplate.Child()
    btn_remove = GtkTemplate.Child()

    def __init__(self, **kwargs):
        """Setup application interface"""
        super().__init__(**kwargs)
        self.init_template()

    @GtkTemplate.Callback
    def btn_convert_clicked(self, caller, **kwargs):
        """Export the selected files

        Iterate over each file and export it
        to the selected file path

        If the file path isn't set display a
        warning
        """
        if self.fcbtn_output.get_file() is None:
            dialog = Gtk.MessageDialog(self, 0, Gtk.MessageType.WARNING,
                                       Gtk.ButtonsType.OK, _('Please select an output folder'))
            dialog.run()
            dialog.destroy()

            return

        # Get necessary information
        file_ext = self.get_export_extension()
        output_path = self.fcbtn_output.get_file().get_path()

        # Iterate over files
        self.lb_files.select_all()
        rows = self.lb_files.get_selected_rows()

        for selected_row in rows:
            try:
                listbox_item = selected_row.get_child()
                output_file_name = listbox_item.file_name + file_ext
                output_file_path = output_path + '/' + output_file_name

                thread_convert = Thread(target = self.convert_file, args = (listbox_item.file_path, output_file_path), daemon=False)
                thread_convert.start()
            except Exception as ex:
                print(ex)
                dialog = Gtk.MessageDialog(self, 0, Gtk.MessageType.WARNING,
                                       Gtk.ButtonsType.OK, _('Something went wrong converting the file <filename>'))
                dialog.run()
                dialog.destroy()

    @GtkTemplate.Callback
    def btn_add_clicked(self, caller, **kwargs):
        """Add file(s) to listbox

        Let user select files to add to
        the listbox
        """
        filter_all = Gtk.FileFilter()
        filter_all.set_name('Multimedia')
        filter_all.add_mime_type('video/*')

        file_dialog = Gtk.FileChooserDialog(_('Please choose a file'), self,
                                            Gtk.FileChooserAction.OPEN,
                                            (Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL,
                                             _('Add'), Gtk.ResponseType.OK))

        file_dialog.set_select_multiple(True)
        file_dialog.set_filter(filter_all)

        response = file_dialog.run()

        if response == Gtk.ResponseType.OK:
            files = file_dialog.get_files()

            for cur_file in files:
                file_name = cur_file.get_basename()
                file_path = cur_file.get_path()

                file_widget = ListBoxItem(file_path, file_name)
                self.add_file_listbox(file_widget)

        file_dialog.destroy()

    @GtkTemplate.Callback
    def btn_remove_clicked(self, caller, **kwargs):
        """Remove file from listbox

        Remove the currently selected file(s)
        from the listbox
        """
        selected_rows = self.lb_files.get_selected_rows()

        for selected_row in selected_rows:
            selected_row.destroy()

        caller.set_sensitive(False)

    @GtkTemplate.Callback
    def lb_files_row_selected(self, caller, row, **kwargs):
        """Row in lb_files is selected

        Enable or disable remove button based on
        selection
        """
        selected_rows = self.lb_files.get_selected_rows()
        enable_remove_button = selected_rows is not None

        self.btn_remove.set_sensitive(enable_remove_button)

    def add_file_listbox(self, file_widget):
        """Add a file to the listbox

        Add a label with the filepath to the
        files listbox
        """
        row = Gtk.ListBoxRow()
        row.add(file_widget)

        row.show_all()

        self.lb_files.add(row)

    def get_export_extension(self):
        """Get selected extension

        Get the currently selected export
        extension
        """
        iter = self.cb_extension.get_active_iter()
        if iter != None:
            model = self.cb_extension.get_model()
            name, extension = model[iter][:2]

            return extension

        return None

    def convert_file(self, file_path, output_file_path):
        """Convert file

        Make sure the UI shows that it's currently loading
        and then convert the file, after the file is
        converted stop the loading animations

        Only converts files, if a folder is selected just
        ignore it
        """
        self.start_ui_loading()

        input_file = Path(file_path)
        output_file = Path(output_file_path)

        if not input_file.is_dir() and not output_file.exists():
            try:
                stream = ffmpeg.input(file_path)
                stream = ffmpeg.output(stream, output_file_path)

                ffmpeg.run(stream)
            except Exception as ex:
                print(ex)

        self.stop_ui_loading()

    def start_ui_loading(self):
        """Display loading animations"""
        self.sp_working.start()
        self.btn_convert.set_sensitive(False)
        self.grd_buttons.set_sensitive(False)
        self.lb_files.set_sensitive(False)

    def stop_ui_loading(self):
        """Stop loading animations"""
        self.sp_working.stop()
        self.btn_convert.set_sensitive(True)
        self.grd_buttons.set_sensitive(True)
        self.lb_files.set_sensitive(True)

