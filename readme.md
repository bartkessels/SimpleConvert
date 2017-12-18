# Simple Convert

Application to convert multiple files to another filetype.

__NOTE__<br>
As of right now `ninja install` doesn't work. This will be fixed
in the next release.

## Screenshots

![Simple Convert mainwindow](data/screenshots/mainwindow.png)

## What can I do with it?

You can convert multiple files (at once!) to another filetype using FFMPEG.
This application provides an easy to understand UI and will convert all the files
to a specified directory.

## Required packages

### Building

- meson
- gtk3-devel
- python3
- pip3
- pygobject3-devel
- gettext

#### Python modules

- [ffmpeg-python](https://github.com/kkroening/ffmpeg-python)

### Installing

- pygobject3
- gettext

## How to build

__\* This is broken__

Make sure you've installed PIP3 and Python3. If you've got those the first
thing you need to install are the python modules

```
$ pip3 install ffmpeg-python
```

~~Now we can start building the application~~


~~$ meson --prefix=/usr build~~<br>
~~$ cd build~~<br>
~~$ ninja install~~


~~And then you can run `simpleconvert`~~
