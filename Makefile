CC="gcc"
DEST="/usr/local/bin/cb"
LOCAL="cb"

changeBacklight:
	$(CC) -o $(LOCAL) changeBacklight.c functions.c

install:
	$(CC) -o $(LOCAL) changeBacklight.c functions.c
	cp $(LOCAL) $(DEST)
	chown root.root $(DEST)
	chmod 4705 $(DEST)

remove:
	rm $(DEST)

clean:
	rm $(LOCAL)
