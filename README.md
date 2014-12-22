OnlineApplicationModel
================================

###Basic Description
Final high school project dealing with a self designed hash function using another self created pseudorandom number generator, an inheritance hierarchy, and binary file read/write

###Some more details about its working
The project is meant to be a simple replica of an online university application (which is what we were both busy with at the time) data system in which users can create an application, modify it and submit it. There are also "manager" accounts which are used to look at submitted applications. The heart of the project is in the development of a hash function (now looking back is probably not suitable as the underlying pseudorandom number generator is not cryptographically secure, although is provides a large period) created with the help of a Sophie-Germain (safe) prime based pseudorandom number generator (resembling the Blum Blum Shub in its bit rotations) that I had created the preceeding summer. 

More details about the project can be found in the project report within this repository (projectReport.pdf).
<br>
###How to run the project
To run the project simply compile it with a C++ compiler such as g++ (if on mac, open terminal and type g++ main.cpp) and run the executable (note the absence of header files indicating a high school project) The *.dat files are local applications saved in binary format. 

A very simple makefile that I created then is also included in the project. To use it type `make` in terminal and then execute the executable named `application` by doing `./application`. Do `make clean` followed to `make` to recompile and rerun.
<br>

**Creators:** Aaryaman Sagar (mathematical foundations and Object Oriented Design), Aditya Sule (Object Oriented Design and general functionality)
