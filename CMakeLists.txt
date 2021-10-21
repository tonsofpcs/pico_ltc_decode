cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(ltc_decoder C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_LTC_DECODE_PATH ${PROJECT_SOURCE_DIR})

# Initialize the SDK
pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

add_executable(ltc_decode)

if (TARGET tinyusb_device)
# enable usb output, disable uart output
pico_enable_stdio_usb(ltc_decode 1)
pico_enable_stdio_uart(ltc_decode 0)

elseif(PICO_ON_DEVICE)
message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()

pico_generate_pio_header(ltc_decode ${CMAKE_CURRENT_LIST_DIR}/differential_manchester.pio)

target_sources(ltc_decode PRIVATE ltc_decode.c)

target_link_libraries(ltc_decode PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(ltc_decode)
