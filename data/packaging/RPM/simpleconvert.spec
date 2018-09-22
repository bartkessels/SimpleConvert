Name:			simpleconvert
Version:		3.2
Release:		1%{dist}
Summary:		Application to convert multiple files to another filetype using FFMPEG
Group:			Multimedia

License:		GPLv3+
URL:			https://github.com/bartkessels/simpleconvert
Source0:		https://github.com/bartkessels/%{name}/archive/%{version}/%{name}-%{version}.tar.gz

BuildRequires:	gcc
BuildRequires:	gcc-c++
BuildRequires:	make
BuildRequires:	qt5-devel
BuildRequires:	qt5-qtbase-devel

Requires:		qt5-qtbase
Requires:		ffmpeg

%description
SimpleConvert is a small application to convert video and/or audio files to any filetype using ffmpeg.
This application aims to provide an easy to understand interface so everyone will be able to use the power of ffmpeg.

%global debug_package %{nil}

%prep
%autosetup

%build
qmake-qt5 PREFIX=%{_prefix}
make %{?_smp_mflags}

%install
export INSTALL_ROOT=%{buildroot}
make install

%files
%{_bindir}/simpleconvert
%{_datarootdir}/net.bartkessels.simpleconvert/translations/*
%{_datarootdir}/appdata/net.bartkessels.simpleconvert.appdata.xml
%{_datarootdir}/applications/net.bartkessels.simpleconvert.desktop
%{_datarootdir}/icons/hicolor/*/apps/net.bartkessels.simpleconvert.*

%changelog
* Wed Jul 11 2018 Bart Kessels <bartkessels@bk-mail.com> 3.2
- Add setting to hide prompt before cancelling a request
- Add shortcuts for adding and removing media files

* Sat Jun 23 2018 Bart Kessels <bartkessels@bk-mail.com> 3.1
- Fix memory leaks
- Fix cancel button preferences window

* Tue May 22 2018 Bart Kessels <bartkessels@bk-mail.com> 3.0
- Rewrite to Qt
- Add option to set ffmpeg binary
- Allow user to cancel running conversion

* Wed Feb 14 2018 Bart Kessels <bartkessels@bk-mail.com> 2.0
- Update converting thread
- Update appstream translation

* Fri Jan 19 2018 Bart Kessels <bartkessels@bk-mail.com> 1.3
- Fix possible crash when input file doesn't exist
- Add option to remove file from list when done converting

* Fri Dec 22 2017 Bart Kessels <bartkessels@bk-mail.com> 1.2
- Add notification support
- Ship own add and remove icons

* Fri Dec 22 2017 Bart Kessels <bartkessels@bk-mail.com> 1.1
- Add settings window

* Thu Dec 21 2017 Bart Kessels <bartkessels@bk-mail.com> 1.0
- First release
