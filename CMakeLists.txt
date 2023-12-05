cmake_minimum_required(VERSION 3.10)

project(main)

set(SDL2_DIR c:/msys64/mingw64/x86_64-w64-mingw32/lib/cmake/SDL2)
set(SDL2_INCLUDE_DIRS C:/msys64/mingw64/x86_64-w64-mingw32/include/SDL2)
set(SDL2_LIBRARIES C:/msys64/mingw64/x86_64-w64-mingw32/lib/libSDL2.a)
set(SDL2_IMAGE_DIR c:/msys64/mingw64/x86_64-w64-mingw32/lib/cmake/SDL2_image)
set(SDL2_IMAGE_INCLUDE_DIRS C:/msys64/mingw64/x86_64-w64-mingw32/include/SDL2)
set(SDL2_IMAGE_LIBRARIES C:/msys64/mingw64/x86_64-w64-mingw32/lib/libSDL2_image.a)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find SDL2_image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

include_directories(

${CMAKE_SOURCE_DIR}/src
${CMAKE_SOURCE_DIR}/src/Core
${CMAKE_SOURCE_DIR}/src/Components
${CMAKE_SOURCE_DIR}/src/Systems
${CMAKE_SOURCE_DIR}/src/Managers
${CMAKE_SOURCE_DIR}/src/Utils)
# Add the path to your source files
set(SRC_DIR "${CMAKE_SOURCE_DIR}/../src")

# Add your source files
file(GLOB SRC_FILES
    src/*.cpp

    src/Core/*.cpp 
  
    src/Components/*.cpp

    src/Systems/*.cpp
 
    src/Managers/*.cpp

    src/Utils/*.cpp

  )

#verify that the SDL library included files are correct
message(STATUS "SDL2_DIR: ${SDL2_DIR}")
message(STATUS "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_LIBRARIES: ${SDL2_LIBRARIES}")
message(STATUS "SDL2_IMAGE_DIR: ${SDL2_IMAGE_DIR}")
message(STATUS "SDL2_IMAGE_INCLUDE_DIRS: ${SDL2_IMAGE_INCLUDE_DIRS}")
message(STATUS "SDL2_IMAGE_LIBRARIES: ${SDL2_IMAGE_LIBRARIES}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# Add the executable and link against both SDL2 and SDL2main
add_executable(main WIN32 ${SRC_FILES})
target_link_libraries(main PRIVATE ${SDL2_IMAGE_LIBRARIES} ${SDL2_LIBRARIES}  SDL2main)