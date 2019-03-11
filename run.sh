# Script to compile and build our cross platform Zia's API

rm -rf build && mkdir build && cd build
if [[ "$OS" == *"Windows"* ]]; then
    echo "Suicidal user who wants to hurt himself detected."
    conan install .. --build=missing && cmake .. -G "Visual Studio 15 Win64"
    cmake --build . --target ALL_BUILD --config Release
elif [[ "$OSTYPE" == "darwin"* ]]; then
	echo "Rich user with a lot of money detected."
	conan install .. --build=missing
    cmake .. -G "Unix Makefiles" && cmake --build . && \
        export DYLD_LIBRARY_PATH=$(pwd)/build/bin/ && \
        echo -e "\\033[35mDYLD_LIBRARY_PATH set to "$(pwd)"/bin/\\033[0m"
else
	echo "User with a cardboard OS and who will probably not have the right packages to run conan detected."
	conan install .. --build=missing -s compiler.libcxx=libstdc++11
    cmake .. -G "Unix Makefiles" && cmake --build .
fi
