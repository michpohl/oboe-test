cmake_minimum_required(VERSION 3.4.1)

add_library(native_lib
        SHARED

        src/main/cpp/native_lib.cpp

        src/main/cpp/AudioEngine.cpp

        )

# Set the path to the Oboe directory.
set (OBOE_DIR /Volumes/Work/Repos/Android/oboe-test/oboe)

# Add the Oboe library as a subdirectory.
add_subdirectory (${OBOE_DIR} ./oboe)

# Specify the path to the Oboe header files.
include_directories (${OBOE_DIR}/include)

target_link_libraries(oboe)