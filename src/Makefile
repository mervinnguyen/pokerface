# Makefile: Poker
# Date Created: 5/21/2024
# Modifications:
# 	4/5/24 ~ Created Makefile and added make for unit_test_gui

# GTK 2.0 Makefile Variables
GTKINC	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --cflags gtk+-2.0`
GTKLIBS	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --libs gtk+-2.0`

# Variables
CC = gcc
DEBUG = -g -DDEBUG
# DEBUG = -O2
CFLAGS = -Wall -std=c11 -pedantic $(DEBUG) -c
LFLAGS = -Wall -std=c11 -pedantic $(DEBUG) -lm
# MAIN = -DMAIN


# In progress

# Default target
all:

# Generates all the Unit Tests
test: unit_test_gui

# Target for clean-up
clean:
	rm -rf *.o unit_test_gui







# Target for gui.o
gui.o: gui.c gui.h
	$(CC) $(CFLAGS) $(GTKINC) $(GTKLIBS) gui.c -o gui.o

# Target for GUI Unit unit_test_gui
unit_test_gui.o: unit_test_gui.c gui.h
	$(CC) $(CFLAGS) $(GTKINC) $(GTKLIBS) unit_test_gui.c -o unit_test_gui.o

# Target for GUI Unit unit_test_gui
unit_test_gui: unit_test_gui.o gui.o
	$(CC) $(LFLAGS) $(GTKINC) $(GTKLIBS) unit_test_gui.o gui.o -o unit_test_gui







