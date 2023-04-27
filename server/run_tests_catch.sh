if [ ! -d "build" ]; then
    Write-Output "Creating build folder"
    mkdir build
fi
cd ./build

echo "Building CMAKE solution"
cmake ../
# cmake --build . --target TESTS
cmake --build .

cd ./test
./TESTS
