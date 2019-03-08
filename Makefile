CC="gcc"
DEST="/usr/local/bin/changeBacklight"

changeBacklight:
	$(CC) -o changeBacklight changeBacklight.c

install:
	$(CC) -o changeBacklight changeBacklight.c
	cp changeBacklight $(DEST)
	chown root.root $(DEST)
	chmod 4705 $(DEST)

remove:
	rm /usr/local/bin/changeBacklight

clean:
	rm changeBacklight
