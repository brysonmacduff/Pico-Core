project(simple_test C CXX)

set(COMPONENT "simple_test")

file(GLOB SRCS "*.cpp" "*.h")

add_library(${COMPONENT} STATIC ${SRCS})
target_include_directories(${COMPONENT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install libraries to file system
install(TARGETS ${COMPONENT} ARCHIVE DESTINATION ${LIB_INSTALL_DIR})
# Install header files to file system
file(GLOB INCS "*.h")
install(FILES ${INCS} DESTINATION ${INC_INSTALL_DIR})

add_subdirectory(test)