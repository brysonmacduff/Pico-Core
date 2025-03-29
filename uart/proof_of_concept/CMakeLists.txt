file(GLOB SRCS "*.h" "*.cpp")

set(TEST_FIRMWARE "${COMPONENT}_poc")

add_executable(${TEST_FIRMWARE} ${SRCS})

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(${TEST_FIRMWARE} pico_stdlib hardware_uart)

# configure to use stdout over usb
pico_enable_stdio_usb(${TEST_FIRMWARE} 1)
pico_enable_stdio_uart(${TEST_FIRMWARE} 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${TEST_FIRMWARE})