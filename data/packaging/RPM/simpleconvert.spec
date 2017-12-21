Name:		simpleconvert
Version:	1.0
Release:	1%{dist}
Summary:	Simple Convert is a small application to convert multiple files to another filetype

License:	GPLv3+
URL:		https://github.com/bartkessels/simpleconvert
Source0:	https://github.com/bartkessels/%{name}/archive/%{version}/%{name}-%{version}.tar.gz

BuildRequires:	gcc
BuildRequires:	meson
BuildRequires:	gtk3-devel
BuildRequires:	gettext

Requires:	gtk3
Requires:	ffmpeg

%description
You can convert multiple files (at once!) to another filetype using FFMPEG.
This application provides an easy to understand UI and will convert all the files
to a specified directory.

%global debug_package %{nil}

%prep
%autosetup -p1

%build
%meson
%meson_build

%install
rm -rf $RPM_BUILD_ROOT
%meson_install
%find_lang %{name}

%files -f %{name}.lang
%{bindir}/%{name}
%{_datadir}/applications/net.bartkessels.%{name}.desktop
%{_datadir}/appdata/net.bartkessels.%{name}.appdata.xml
%{_datadir}/icons/hicolor/*/apps/net.bartkessels.%{name}.png
%{_datadir}/icons/hicolor/*/apps/net.bartkessels.%{name}-symbolic.png

%changelog
* Thu Dec 21 2017 Bart Kessels <bartkessels@bk-mail.com> 1.0
- First release