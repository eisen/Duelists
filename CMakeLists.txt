cmake_minimum_required(VERSION 3.20)
project(Duelists)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source files
set(SOURCES
    main.cpp
    Character.cpp
    Enemy.cpp
    Log.cpp
    Player.cpp
)

# Header files
set(HEADERS
    Character.h
    Enemy.h
    Log.h
    Player.h
)

find_package(glfw3 CONFIG REQUIRED)

# Find raylib
find_package(raylib CONFIG REQUIRED)

# Create executable
add_executable(Duelists ${SOURCES} ${HEADERS})

# Link raylib
target_link_libraries(Duelists PRIVATE raylib glfw)

# Compiler options
if(MSVC)
    # MSVC-specific flags to match Visual Studio settings
    target_compile_options(Duelists PRIVATE
        /W3          # Warning level 3
        /sdl         # Enable additional security checks
        /permissive- # Conformance mode
    )

    # Debug configuration
    target_compile_definitions(Duelists PRIVATE
        $<$<CONFIG:Debug>:_DEBUG;_CONSOLE>
        $<$<CONFIG:Release>:NDEBUG;_CONSOLE>
    )

    # Enable function-level linking and intrinsics in Release
    target_compile_options(Duelists PRIVATE
        $<$<CONFIG:Release>:/Gy;/Oi>
    )
else()
    # GCC/Clang flags
    target_compile_options(Duelists PRIVATE
        -Wall
        -Wextra
    )
endif()

# Set subsystem to console for Windows
if(WIN32)
    set_target_properties(Duelists PROPERTIES
        WIN32_EXECUTABLE FALSE
    )
endif()