# Set standards
cmake_minimum_required(VERSION 3.8)
project(PROJECT)

# /////////////////////////////////////////////////////////////////////////////
# /////////////////////////////// DEPENDENCIES ////////////////////////////////
# /////////////////////////////////////////////////////////////////////////////

find_package(OpenGL REQUIRED)

# On windows
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
    find_package(SDL2 REQUIRED)
    find_package(SDL_image REQUIRED)
    find_package(SDL_ttf REQUIRED)
    # If doesnt work, try this
    # find_package(SDL2_image REQUIRED)
    # find_package(SDL2_ttf REQUIRED)
endif ()

# can be cleaner with : https://github.com/aminosbh/sdl2-cmake-modules

# /////////////////////////////////////////////////////////////////////////////
# /////////////////////////////////// BUILD ///////////////////////////////////
# /////////////////////////////////////////////////////////////////////////////

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*)
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Set the folder where the executable is created
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Enable good warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

if (UNIX)
    target_link_libraries(${PROJECT_NAME} -ldl -lSDL2 -lSDL2_image -lSDL2_ttf)
endif ()

if (WIN32) # Copy .dll to build folder
    # SET SDL2 flags
    target_link_libraries(${PROJECT_NAME} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lglu32 -lopengl32 ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

    # Duplicate librarys in bin/
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.20/x86_64-w64-mingw32/lib/libSDL2.dll.a"
            "${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.20/x86_64-w64-mingw32/lib/libSDL2main.a"
            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/SDL2_image.dll"
            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/libpng16-16.dll"
            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/libjpeg-9.dll"
            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/zlib1.dll"
            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/libtiff-5.dll"
            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/libwebp-7.dll"
            "${PROJECT_SOURCE_DIR}/lib/SDL2_ttf-2.0.18/x86_64-w64-mingw32/lib/libSDL2_ttf.a"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            )
endif ()

# Copy res folder after a build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets/
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
        )