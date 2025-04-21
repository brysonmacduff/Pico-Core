file(GLOB SRCS "*.h" "*.cpp")

set(TEST_EXEC "${COMPONENT}_test")

add_executable(${TEST_EXEC} ${SRCS})
set_target_properties(${TEST_EXEC} PROPERTIES RUNTIME_OUTPUT_NAME "${TEST_EXEC}.bin")
target_link_libraries(${TEST_EXEC} ${COMPONENT})
