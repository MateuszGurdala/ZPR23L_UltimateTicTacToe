if [ ! -d "build" ]; then
    Write-Output "Creating build folder"
    mkdir build
fi
cd ./build

echo "Building CMAKE solution"
cmake ../
cmake --build .

echo "Running test demo app"
./UltimateTicTacToeServerGameTest