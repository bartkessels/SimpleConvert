# Simple Convert

Application to convert multiple files to another filetype using FFMPEG.

## Screenshots

![Simple Convert mainwindow](data/screenshots/mainwindow.png)

## What can I do with it?

SimpleConvert is a small application to convert video and/or
audio files to any filetype using ffmpeg. This application aims
to provide an easy to understand interface so everyone will be
able to use the power of ffmpeg.

## Required packages

### Building

- qt5-devel

### Installing

- qt5
- ffmpeg

## How to build

```
$ qmake
$ make install
```

And then run `simpleconvert`

## Generate RPM package

```
$ cd data/packaging/RPM
$ spectool -g simpleconvert.spec
$ fedpkg --release f28 local
```

This will create a RPM file which you can install using you package manager.

## Generate flatpak bundle

```
$ cd data/packaging/flatpak
$ flatpak-builder --repo=simpleconvert_repo simpleconvert net.bartkessels.simpleconvert.json
$ flatpak build-bundle simpleconvert_repo simpleconvert.flatpak net.bartkessels.simpleconvert
```

This will create a flatpak bundle called `simpleconvert.flatpak`. To install the flatpak bundle
just run the flatpak install command.

```
$ flatpak install simpleconvert.flatpak
```
