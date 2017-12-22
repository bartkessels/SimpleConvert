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

## Generate RPM package

```
$ cd data/packaging/RPM
$ spectool -g simpleconvert.spec
$ fedpkg --release f26 local
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

## COPR

If you have Fedora and don't want to build Simple Convert from source you can easily install it using dnf
copr.

```
$ dnf copr enable bartkessels/simpleconvert
$ dnf install simpleconvert
```
