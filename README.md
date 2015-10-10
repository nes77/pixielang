# pixielang
PIXIE: The Engine and Base Libraries for the Pixie Language

[![Build Status](https://travis-ci.org/nes77/pixielang.svg?branch=master)](https://travis-ci.org/nes77/pixielang)

Compilation Steps for Debian-based Systems:
------------------

Ensure you have g++-4.9 or higher installed.

Install the following packages.
* libboost1.55-dev 
* libboost-regex1.55-dev 
* libboost-filesystem1.55-dev 
* libboost-program-options1.55-dev
* cmake (3.0 or higher)

If you don't have access to cmake3 on your system, use the following instruction to add a repository for it.
* add-apt-repository ppa:george-edison55/cmake-3.x

Next, build the build scripts with CMake:

* cmake CMakeLists.txt

Run Make:

* make

And optionally run the tests:

* ctest
