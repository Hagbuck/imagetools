CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=imagetools
OUTEXT=out
OBJF=obj
SRCF=src

all: $(EXEC)

imagetools: basic_tools.o main.o
	$(CC) -o $@.$(OUTEXT) $(OBJF)/basic_tools.o $(OBJF)/main.o $(LDFLAGS)

basic_tools.o: $(SRCF)/basic_tools.c
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/basic_tools.c $(CFLAGS)

PGM.o: $(SRCF)/PGM.c
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/PGM.c $(CFLAGS)

main.o: $(SRCF)/main.c $(SRCF)/basic_tools.h
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/main.c $(CFLAGS)

clean:
	rm -rf $(OBJF)/*.o