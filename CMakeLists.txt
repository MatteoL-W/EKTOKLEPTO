# Cmake version 3.11 in for FetchContent
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(thomas_was_not_alone)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set directory paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# /////////////////

set(TARGET_NAME ${PROJECT_NAME})

add_executable(${TARGET_NAME})

# Get source files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*")
# link files to project target
target_sources(${TARGET_NAME} PRIVATE ${SRC_FILES})
target_include_directories(${TARGET_NAME} PRIVATE "src/")

# Enable C++17
set_target_properties(${TARGET_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )

# Enable good warnings
if (MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /W3)
else()
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
endif()

# Set the project folder
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER ${PROJECT_NAME})
# Set the folder where the executable will be created
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# GLM
include(${CMAKE_DIR}/LinkGLM.cmake)
LinkGLM(${TARGET_NAME} PRIVATE)

# OpenGL
find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
    target_include_directories(${TARGET_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS})
    target_link_libraries(${TARGET_NAME} ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenGL was not found on the system")
endif()

#SDL2
if (WIN32)
    set(SDL2_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.20/x86_64-w64-mingw32/include)
    set(SDL2_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.20/x86_64-w64-mingw32/lib/libSDL2.a;
            ${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.20/x86_64-w64-mingw32/lib/libSDL2main.a)

    set(SDL2IMAGE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/include)
    set(SDL2IMAGE_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/lib/libSDL2_image.a)

    set(SDL2TTF_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf-2.0.18/x86_64-w64-mingw32/include)
    set(SDL2TTF_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf-2.0.18/x86_64-w64-mingw32/lib/libSDL2_ttf.a)

    # On linux
else ()
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

    # Find and link SDL2
    find_package(SDL2 REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

    # Find and link SDL2_image
    find_package(SDL2_image REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})

    # Find and link SDL2_ttf
    find_package(SDL2_ttf REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_TTF_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})
endif ()

# /////////////////////////////////////////////////////////////////////////////
# /////////////////////////////////// BUILD ///////////////////////////////////
# /////////////////////////////////////////////////////////////////////////////

target_include_directories(${TARGET_NAME} PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

if (UNIX)
    target_link_libraries(${TARGET_NAME} -ldl -lSDL2 -lSDL2_image -lSDL2_ttf)
endif ()

if (WIN32) # Copy .dll to build folder
    # SET SDL2 flags
    target_link_libraries(${TARGET_NAME} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lglu32 -lopengl32 ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

    # Duplicate librarys in bin/
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.20/x86_64-w64-mingw32/lib/libSDL2.dll.a"
            "${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.20/x86_64-w64-mingw32/lib/libSDL2main.a"
            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/SDL2_image.dll"
            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/libpng16-16.dll"
            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/libjpeg-9.dll"
            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/zlib1.dll"
            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/libtiff-5.dll"
            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/libwebp-7.dll"
            "${PROJECT_SOURCE_DIR}/lib/SDL2_ttf-2.0.18/x86_64-w64-mingw32/lib/libSDL2_ttf.a"
            $<TARGET_FILE_DIR:${TARGET_NAME}>
            )
endif ()


# Copy res folder after a build
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets/
        $<TARGET_FILE_DIR:${TARGET_NAME}>/assets
        )