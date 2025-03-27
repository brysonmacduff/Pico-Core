cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH

set(PICO_BOARD pico_w)
set(PICO_SDK_PATH "/home/bryson/projects/raspberry_pi_pico_w/pico-sdk")

# note: this must happen before project()
include(pico_sdk_import.cmake)

project(pico_core C CXX ASM)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_subdirectory(pulse_width_modulator)