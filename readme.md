# Simple Convert

Application to convert multiple files to another filetype.

## Screenshots

![Simple Convert mainwindow](data/screenshots/mainwindow.png)

## What can I do with it?

You can convert multiple files (at once!) to another filetype using FFMPEG.
This application provides an easy to understand UI and will convert all the files
to a specified directory.

## Required packages

### Building

- gcc
- meson
- gtk3-devel
- gettext

### Installing

- gtk3
- ffmpeg

## How to build

```
$ meson --prefix=/usr build
$ cd build
$ ninja install
```

And then run `simpleconvert`
