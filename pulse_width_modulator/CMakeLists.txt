set(COMPONENT "pulse_width_modulator")

file(GLOB SRCS "*.h" "*.cpp")

add_library(${COMPONENT} STATIC ${SRCS})
target_link_libraries(${COMPONENT} pico_stdlib hardware_pwm)
target_include_directories(${COMPONENT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(test)