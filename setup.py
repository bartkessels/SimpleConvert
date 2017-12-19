import os
from os import environ, path
from subprocess import call
from setuptools import setup
from setuptools.command.install import install

application_name='simpleconvert'
prefix = environ.get('prefix', '/usr/share')
datadir = path.join(prefix, 'share')

class InstallGtk(install):

    def run(self):
        """Run custom commands needed for GTK

        Create required folders, run the default setup,
        update icon cache and desktop files database
        """
        if not os.path.exists(path.join(datadir, application_name)):
            os.makedirs(path.join(datadir, application_name))

        install.run(self)

        print('Updating icon cache...')
        call(['gtk-update-icon-cache', '-qtf', path.join(datadir, 'icons', 'hicolor')])

        print('Updating desktop database...')
        call(['update-desktop-database', '-q', path.join(datadir, 'applications')])


setup(
    name='Simple Convert',
    version='0.5',
    author='Bart Kessels',
    author_email='bartkessels@bk-mail.com',
    description='Application to convert multiple files to another filetype',

    license='GPLv3+',
    url='https://github.com/bartkessels/simpleconvert',

    entry_points={
        'setuptools.installation': [
            'eggsecutable = simpleconvert.__main__:main'
        ],
        'gui_scripts': [
            'simpleconvert = __main__:main'
        ],
    },

    packages=[
        'simpleconvert',
    ],

    install_requires=[
        'pygobject',
        'ffmpeg-python'
    ],

    data_files=[
        (path.join(datadir, application_name), ['data/ui/mainwindow.glade']),
        (path.join(datadir, 'applications'), ['data/net.bartkessels.simpleconvert.desktop']),
        (path.join(datadir, 'appdata'), ['data/net.bartkessels.simpleconvert.appdata.xml'])
    ],

    cmdclass={
        'install':InstallGtk,
    },
)
