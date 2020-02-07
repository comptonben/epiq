# Epiq Code Challenge

## Installation Instructions
### Requirements:
 - git
 - g++
 - cmake
 - libcurl
 - gtest
 
### To install git, g++, cmake, and libcurl run the following commands
``` console
sudo apt install git
sudo apt install g++
sudo apt install cmake
sudo apt-get install libcurl4-gnutls-dev
```

### To install gtest follow these instructions
 - create the linux library:
``` console
sudo apt-get install libgtest-dev
cd /usr/src/googletest/googletest
sudo mkdir build
cd build
sudo cmake ..
sudo make
sudo cp libgtest* /usr/lib/
cd ..
sudo rm -rf build
```
 -  link the library for use:
``` console
sudo mkdir /usr/local/lib/googletest
sudo ln -s /usr/lib/libgtest.a /usr/local/lib/googletest/libgtest.a
sudo ln -s /usr/lib/libgtest_main.a /usr/local/lib/googletest/libgtest_main.a
```

## Build and Run Instructions
### Pulling down the Repo
 - Pull from git:
``` console
git clone https://github.com/comptonben/epiq
```

### Platform Temperature Manager
 - Build challenge part (from same directory where you pulled from git):
``` console
cd epiq/part1/build
cmake ..
make
```

 - Run challenge part:
``` console 
./PTM
```

### TMP125 Driver
 - Build challenge part (from same directory where you pulled from git):
``` console
cd epiq/part2/build
cmake ..
make
```

 - Run challenge part test package:
``` console 
./test/tmp125_driver_test
```