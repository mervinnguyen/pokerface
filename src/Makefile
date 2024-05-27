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
CFLAGS = -Wall -std=c11 -pedantic $(DEBUG) $(GTKINC) -c
LFLAGS = -Wall -std=c11 -pedantic $(DEBUG) $(GTKLIBS) -lm

# In progress

# Default target
all: pokerclient pokerserver

# Generates all the Unit Tests
test: unit_test_gui
	@echo ""
	@echo "All unit tests have been complied."
	@echo "To start enter ./(Executabe Name) into the terminal."
	@echo "	Ex: ./unit_test_gui"
	@echo ""

# Target for clean-up
clean:
	rm -rf *.o pokerclient pokerserver unit_test_gui
	@echo ""
	@echo "Excess files have been cleaned up."
	@echo ""

# Main Executables

# Target for pokerclient.o
pokerclient.o: pokerclient.c
	$(CC) $(CFLAGS) pokerclient.c -o pokerclient.o
# Target for pokerclient
pokerclient: pokerclient.o gui.o
	$(CC) $(LFLAGS) pokerclient.o gui.o -o pokerclient

# Target for pokerserver.o
pokerserver.o: pokerserver.c
	$(CC) $(CFLAGS) pokerserver.c -o pokerserver.o
# Target for pokerserver
pokerserver: pokerserver.o
	$(CC) $(LFLAGS) pokerserver.o -o pokerserver


# GUI Unit Test

# Target for gui.o
gui.o: gui.c gui.h
	$(CC) $(CFLAGS) gui.c -o gui.o
# Target for GUI Unit unit_test_gui
unit_test_gui.o: unit_test_gui.c gui.h
	$(CC) $(CFLAGS) unit_test_gui.c -o unit_test_gui.o
# Target for GUI Unit unit_test_gui
unit_test_gui: unit_test_gui.o gui.o
	$(CC) $(LFLAGS) unit_test_gui.o gui.o -o unit_test_gui







