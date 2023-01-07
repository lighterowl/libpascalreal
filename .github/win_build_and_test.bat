call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars32.bat"
mkdir build
cd build
C:\vcpkg\vcpkg.exe install check
cmake .. -DCMAKE_BUILD_TYPE=%1 -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake -G Ninja
ninja -v
ninja test
