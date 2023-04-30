# HOW TO BUILD AND RUN GAME SERVER
## cmake is required to build and run project
### For WIN32:

```powershell
powershell -ExecutionPolicy Bypass -File build_win32.ps1
```

<br/>

### For Linux:

```bash
sh ./build_linux.sh
```
#### also test of creating jsons can be run:
```bash
sh ./build_test_main_linux.sh
```
<br/>

# TO RUN UNIT TESTS (LINUX ONLY)

### Install Catch2:

```bash
git clone https://github.com/catchorg/Catch2.git

cd Catch2

cmake -Bbuild -H. -DBUILD_TESTING=OFF

sudo cmake --build build/ --target install
```

<br/>

### Run testing script:

```bash
sh ./run_tests_catch.sh
```
