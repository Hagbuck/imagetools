CC=gcc
CFLAGS=-W -Wall -pedantic
LDFLAGS=
EXEC=imagetools
OUTEXT=out
OBJF=obj
SRCF=src

all: $(EXEC)

imagetools: basic_tools.o PGM_P2.o BMP.o console_interface.o main.o
	$(CC) -o $@.$(OUTEXT) $(OBJF)/basic_tools.o $(OBJF)/console_interface.o $(OBJF)/PGM_P2.o $(OBJF)/BMP.o $(OBJF)/main.o $(LDFLAGS)

basic_tools.o: $(SRCF)/basic_tools.c
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/basic_tools.c $(CFLAGS)

console_interface.o: $(SRCF)/console_interface.c
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/console_interface.c $(CFLAGS)

PGM_P2.o: $(SRCF)/PGM_P2.c
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/PGM_P2.c $(CFLAGS)

BMP.o: $(SRCF)/BMP.c
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/BMP.c $(CFLAGS)

main.o: $(SRCF)/main.c $(SRCF)/basic_tools.h $(SRCF)/console_interface.h $(SRCF)/PGM_P2.h $(SRCF)/BMP.o
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/main.c $(CFLAGS)

clean:
	rm -rf $(OBJF)/*.o