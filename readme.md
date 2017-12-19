# Simple Convert

Application to convert multiple files to another filetype.

## Screenshots

![Simple Convert mainwindow](data/screenshots/mainwindow.png)

## What can I do with it?

You can convert multiple files (at once!) to another filetype using FFMPEG.
This application provides an easy to understand UI and will convert all the files
to a specified directory.

## Required packages

- setuptools
- pygobject >= 3.24
- ffmpeg-python >= 0.1.9

Install these packages using `easy_install` or `pip` but make sure you
install them for Python 3.


## How to build

```
$ python3 setup.py install
```

And then you can run `simpleconvert`.

###ModuleNotFoundError

If you get the `ModuleNotFoundError` make sure you installed the required
packages for Python 3.

To install the required packages for Python 3 just run

```
$ python3 -m easy_install 'pygobject>=3.24'
$ python3 -m easy_install 'ffmpeg-python>=0.1.9'
```
