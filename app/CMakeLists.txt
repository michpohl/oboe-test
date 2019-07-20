cmake_minimum_required(VERSION 3.4.1)

add_library(native-lib
        SHARED

        src/main/cpp/native-lib.cpp

        src/main/cpp/AudioEngine.cpp

        src/main/cpp/DataSource.h

        src/main/cpp/AAssetDataSource.cpp

        src/main/cpp/logging.h

        src/main/cpp/NDKExtractor.cpp

        src/main/cpp/Constants.h

        src/main/cpp/OpenGLFunctions.cpp

        src/main/cpp/Player.cpp

        src/main/cpp/Mixer.h

        src/Main/cpp/MonoToStereo.h

        src/main/cpp/IRenderableAudio.h

        src/main/cpp/UtilityFunctions.cpp

        )

# Set the path to the Oboe directory.
set (OBOE_DIR /Volumes/Work/Repos/Android/oboe-test/oboe)

# Add the Oboe library as a subdirectory.
add_subdirectory (${OBOE_DIR} ./oboe)

# Specify the path to the Oboe header files.
include_directories (${OBOE_DIR}/include)



target_link_libraries(
        native-lib
        android
        mediandk
        oboe
        GLESv2
)