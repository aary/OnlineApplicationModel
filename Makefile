# highest target; sews together all objects into executable
all: main.cpp hash.h hash.cpp utilities.h utilities.cpp
	g++  main.cpp hash.cpp utilities.cpp -o application

# make clean - remove .o files, executable, tarball
clean:
	rm -f application

fresh:
	rm -f application *.dat