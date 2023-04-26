# HOW TO BUILD AND RUN GAME SERVER

## For WIN32:

#### powershell -ExecutionPolicy Bypass -File build_win32.ps1

<br/>

## For Linux:

#### sh ./build_linux.sh

<br/>

# TO RUN UNIT TESTS (LINUX ONLY)

## Install Catch2:

#### git clone https://github.com/catchorg/Catch2.git

#### cd Catch2

#### cmake -Bbuild -H. -DBUILD_TESTING=OFF

#### sudo cmake --build build/ --target install

<br/>

## Run testing script:

#### sh ./run_tests_catch.sh