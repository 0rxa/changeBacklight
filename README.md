# Suckless way to change backlight brightness.
Application to control backlight, features soft mode using intel driver
and hard mode using acpi_video0.

Simplest it can get in terms of usability.

	Usage: changeBacklight [moph]
		-m: set mode hard(h) or soft(s), will default to hard mode
		-o: set operation\n\t ++, --, max, min
		-p: set percentage, will be ignored on hard mode
		-h: display this help message
	This program must be executed as root

	Compile:
		make
	Install:
		make install
	Uninstall:
		make remove
