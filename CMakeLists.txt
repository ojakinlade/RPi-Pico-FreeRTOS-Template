# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(RPi-Pico-FreeRTOS)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Tell CMake where to find the executable source file
add_executable(RPi-Pico-FreeRTOS
    src/main.cpp
)

FILE(GLOB FreeRTOS_src FreeRTOS-Kernel/*.c)

add_library( FreeRTOS STATIC
    ${FreeRTOS_src}
    FreeRTOS-Kernel/portable/GCC/ARM_CM0/port.c
    FreeRTOS-Kernel/portable/MemMang/heap_3.c
)

target_include_directories(FreeRTOS PUBLIC
    FreeRTOS-Kernel/include
    include/
    FreeRTOS-Kernel/portable/GCC/ARM_CM0
)

# Add pico_stdlib library, add more if used
target_link_libraries(RPi-Pico-FreeRTOS
    pico_stdlib
    hardware_gpio
    FreeRTOS
 )

# Enable usb output, disable uart output
pico_enable_stdio_usb(RPi-Pico-FreeRTOS 1)
pico_enable_stdio_uart(RPi-Pico-FreeRTOS 0)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(RPi-Pico-FreeRTOS)