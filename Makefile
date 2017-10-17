CC=gcc
CFLAGS=-W -Wall -pedantic
LDFLAGS=
EXEC=imagetools
OUTEXT=out
OBJF=obj
SRCF=src

all: $(EXEC)

imagetools: basic_tools.o main.o PGM_P2.o
	$(CC) -o $@.$(OUTEXT) $(OBJF)/basic_tools.o $(OBJF)/PGM_P2.o $(OBJF)/main.o $(LDFLAGS)

basic_tools.o: $(SRCF)/basic_tools.c
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/basic_tools.c $(CFLAGS)

PGM_P2.o: $(SRCF)/PGM_P2.c
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/PGM_P2.c $(CFLAGS)

main.o: $(SRCF)/main.c $(SRCF)/basic_tools.h $(SRCF)/PGM_P2.h
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/main.c $(CFLAGS)

clean:
	rm -rf $(OBJF)/*.o