CC=gcc
CFLAGS=-W -Wall -pedantic
LDFLAGS= -lm
EXEC=imagetools
OUTNAME=imagetools
OUTEXT=out
OBJF=obj
SRCF=src

all: $(EXEC)

imagetools: basic_tools.o Matrix.o RGB.o PGM_P2.o BMP.o console_interface.o command_line_interface.o main.o main_cli.o
	$(CC) -o $(OUTNAME)-ci.$(OUTEXT) $(OBJF)/basic_tools.o $(OBJF)/Matrix.o $(OBJF)/RGB.o $(OBJF)/console_interface.o $(OBJF)/PGM_P2.o $(OBJF)/BMP.o $(OBJF)/main.o $(LDFLAGS)
	$(CC) -o $(OUTNAME)-cli.$(OUTEXT) $(OBJF)/basic_tools.o $(OBJF)/Matrix.o $(OBJF)/RGB.o $(OBJF)/command_line_interface.o $(OBJF)/PGM_P2.o $(OBJF)/BMP.o $(OBJF)/main_cli.o $(LDFLAGS)

ci: basic_tools.o Matrix.o RGB.o PGM_P2.o BMP.o console_interface.o main.o
	$(CC) -o $(OUTNAME)-ci.$(OUTEXT) $(OBJF)/basic_tools.o $(OBJF)/Matrix.o $(OBJF)/RGB.o $(OBJF)/console_interface.o $(OBJF)/PGM_P2.o $(OBJF)/BMP.o $(OBJF)/main.o $(LDFLAGS)

cli: basic_tools.o Matrix.o RGB.o PGM_P2.o BMP.o command_line_interface.o main_cli.o
	$(CC) -o $(OUTNAME)-cli.$(OUTEXT) $(OBJF)/basic_tools.o $(OBJF)/Matrix.o $(OBJF)/RGB.o $(OBJF)/command_line_interface.o $(OBJF)/PGM_P2.o $(OBJF)/BMP.o $(OBJF)/main_cli.o $(LDFLAGS)

basic_tools.o:
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/basic_tools.c $(CFLAGS)

Matrix.o:
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/Matrix.c $(CFLAGS)

RGB.o:
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/RGB.c $(CFLAGS)

PGM_P2.o:
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/PGM_P2.c $(CFLAGS)

BMP.o:
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/BMP.c $(CFLAGS)

console_interface.o:
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/console_interface.c $(CFLAGS)

command_line_interface.o:
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/command_line_interface.c $(CFLAGS)

main.o:
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/main.c $(CFLAGS)

main_cli.o:
	$(CC) -o $(OBJF)/$@ -c $(SRCF)/main_cli.c $(CFLAGS)

clean:
	rm -rf $(OBJF)/*.o