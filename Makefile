all: make

# test >make clean all test

# Goes into src/ directory make 
make:
	(cd src/; make; cd ..)
	cp src/Client bin/
	cp src/Server bin/

test:
	(cd src/; make unitTest1; cd ..)
	(cd src/; make unitTest2; cd ..)
	cp unitTest1 bin/
	cp unitTest2 bin/

# Fix tar (user) so that it's inside a poker folder
tar:
# gtar cvzf Chess_V1.0_src.tar.gz README.txt LICENSE.txt INSTALL.txt Makefile bin/ doc/ src/
# gtar cvzf Chess_V1.0.tar.gz README.txt LICENSE.txt INSTALL.txt bin/ doc/Chess_UserManual.pdf
	
clean:
	(cd src/; make clean; cd ..)
	(cd bin/; rm *; cd ..)
	rm *.tar.gz
