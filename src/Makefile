CC = clang

SRC = main.c scenemanager.c lua_functions.c codepoints.c define.c scene/main_menu.c scene/settings.c
CFLAGS = -std=c99 -lraylib -lm -g -Wall -llua
INCDIRS = -I/usr/include/lua5.4/
make:

	$(CC) $(SRC) -o ../run $(CFLAGS) $(INCDIRS) $(LIBDIRS)

android:

	cp -r ./* $(ANDROIDDIR)cpp
	cp -r ../assets/ $(ANDROIDDIR)
	
	rm $(ANDROIDDIR)/cpp/run.sh

clean:

	rm -rf ../assets/save
