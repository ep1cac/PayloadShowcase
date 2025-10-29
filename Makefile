CFLAGS=-Wall -Werror -Iheaders

ARCH ?= x64

ifeq ($(ARCH),x64)
	ARCH_FLAG=-m64
	CC:=x86_64-w64-mingw32-gcc
else ifeq ($(ARCH),x32)
	ARCH_FLAG=-m32
	CC:=i686-w64-mingw32-gcc
else
	$(error: Unsupported ARCH: $(ARCH))
endif

SRCDIR=./src/
HEADIR=./headers/

all: link

main: $(SRCDIR)main.c $(HEADIR)common.h
	$(CC) $(CFLAGS) $(ARCH_FLAG) -c $(SRCDIR)main.c -o main.o

crypt: $(SRCDIR)crypt.c $(HEADIR)crypt.h
	$(CC) $(CFLAGS) $(ARCH_FLAG) -c $(SRCDIR)crypt.c -o crypt.o

procinject: $(SRCDIR)procinject.c $(HEADIR)procinject.h
	$(CC) $(CFLAGS) $(ARCH_FLAG) -c $(SRCDIR)procinject.c -o procinject.o

link: main crypt procinject
	$(CC) $(CFLAGS) main.o crypt.o procinject.o -o shell.exe

clean:
	rm -vf shell.exe *.o
