
Debian
====================
This directory contains files used to package bared/bare-qt
for Debian-based Linux systems. If you compile bared/bare-qt yourself, there are some useful files here.

## bare: URI support ##


bare-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bare-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bareqt binary to `/usr/bin`
and the `../../share/pixmaps/bare128.png` to `/usr/share/pixmaps`

bare-qt.protocol (KDE)

