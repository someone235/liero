# Compiling on Linux with Clang #

I haven't tested this with GCC lately, but it should probably work perhaps with some minor adjustments to the source.

**NOTE: Only x86/x86-64 is supported at the moment.**

These steps are required to compile Liero on Linux with GCC:
  * Install a mercurial client (e.g. `apt-get install mercurial`).
  * Get the source from http://code.google.com/p/liero/source/checkout, put it in a directory called "liero".
  * Get headers and libs for SDL (e.g. `apt-get install libsdl1.2-dev`).
  * Install CMake (e.g. `apt-get install cmake-qt-gui`).
  * Run CMake and configure/generate for the source in the "liero" directory (pick e.g. the UNIX Makefile generator).
  * Run "make".

The binary "openliero" should appear if everything went right. Note that you need to get the Liero files in order to run the openliero binary. The easiest is to get them from http://liero.be/download/lierov133winxp.zip and put them in the same directory as the openliero binary.