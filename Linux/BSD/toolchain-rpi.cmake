set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Change this to `aarch64-linux-gnu` for a 64-bit Raspberry Pi
set(CROSS_COMPILE_TOOLCHAIN arm-linux-gnueabihf)

set(CMAKE_C_COMPILER ${CROSS_COMPILE_TOOLCHAIN}-gcc)
set(CMAKE_CXX_COMPILER ${CROSS_COMPILE_TOOLCHAIN}-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Set the sysroot if available (modify the path accordingly)
set(CMAKE_SYSROOT /path/to/raspberrypi/sysroot)
set(CMAKE_FIND_ROOT_PATH /path/to/raspberrypi/sysroot)

# Ensure libraries are found
set(CMAKE_PREFIX_PATH "/path/to/raspberrypi/sysroot/usr")
