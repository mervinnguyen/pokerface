all: make

# test >make clean all test

# Goes into src/ directory and calls the make there
make:
	(cd src/; make; cd ..)
	cp src/unit_test_gui bin/
	cp -r src/gui_images bin/

# cp src/Client bin/
# cp src/Server bin/

# makes all the unit_tests and copys them to bin/
test:
	(cd src/; make unit_test_gui; cd ..)
	cp src/unit_test_gui bin/
	cp -r src/gui_images bin/
	@echo ""
	@echo "All unit tests have been complied."
	@echo "To start navigate the bin/ directory and enter./(Executabe Name) into the terminal."
	@echo "Ex:"
	@echo "	Step #1: cd bin/"
	@echo "	Step #2: ./unit_test_gui"
	@echo ""

# makes the gui unit_test and runs it
test-gui:
	(cd src/; make unit_test_gui; cd ..)
	cp src/unit_test_gui bin/
	cp -r src/gui_images bin/
	(cd src/; ./unit_test_gui; cd ..)
	@echo ""
	@echo "GUI has been tested."
	@echo ""

# --transform 's|^|poker/|' is used to place all the files into a folder called poker
tar:
	gtar cvzf Poker_Alpha.tar.gz --transform 's|^|poker/|' README COPYRIGHT INSTALL bin/ doc/Poker_UserManual.pdf
	gtar cvzf Poker_Alpha_src.tar.gz --transform 's|^|poker/|' README COPYRIGHT INSTALL Makefile bin/ doc/ src/
	@echo ""
	@echo "Tar files have been successfully created."
	@echo ""

# Cleans unneeded files in the poker directory
clean:
	(cd src/; make clean; cd ..)
	(cd bin/; rm -rf *; cd ..)
	rm -rf *.tar.gz
	@echo ""
	@echo "Excess files have been cleaned up."
	@echo ""
