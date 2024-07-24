CC = clang

SRC	= main.c codepoints.c define.c resource.c language.c\
		scene/main_menu.c scene/settings.c

CFLAGS	= -std=c99 -lraylib -lm -g -Wall -lsqlite3
INCDIRS	= -I/usr/include/lua5.4/ -I../raylib/src/
LIBDIRS	= -L../raylib/src/ 
make:

	$(CC) $(SRC) -o ../run $(CFLAGS) $(INCDIRS) $(LIBDIRS)

android:

	cp -r ./* $(ANDROIDDIR)cpp
	cp -r ../assets/ $(ANDROIDDIR)
	
	rm $(ANDROIDDIR)/cpp/run.sh

clean:

	rm -rf ../assets/save
