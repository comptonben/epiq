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

 - To view the published alarms visit https://epiq-code-challenge.000webhostapp.com/api/read-alarms.php

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

## Resources
 - https://thispointer.com/c-11-multithreading-part-1-three-different-ways-to-create-threads/
 - https://stackoverflow.com/questions/268680/how-can-i-monitor-the-thread-count-of-a-process-on-linux
 - https://stackoverflow.com/questions/51776246/curl-post-request-in-c
 - https://gist.github.com/Cartexius/4c437c084d6e388288201aadf9c8cdd5
 - https://raymii.org/s/tutorials/Cpp_project_setup_with_cmake_and_unit_tests.html
 - https://www.markdownguide.org/basic-syntax/