# window.py
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

class ListBoxItem(Gtk.Label):
    """ListBoxItem for a file

    This class contains the default
    layout for a ListBoxItem
    """

    file_path = None
    file_name = None


    def __init__(self, file_path, file_name):
        Gtk.Label.__init__(self)

        self.file_path = file_path
        self.file_name = file_name

        self.setup_label(file_name)


    def setup_label(self, file_name):
        """Setup the label

        Add the file name to the label and
        make sure it's aligned to the right
        """
        self.set_text(file_name)
        self.set_justify(Gtk.Justification.LEFT)
        self.set_xalign(0)

