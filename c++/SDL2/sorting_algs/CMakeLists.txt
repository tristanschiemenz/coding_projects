cmake_minimum_required(VERSION 3.10)

project(Sorting_Algs)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src/include)

# Libraries directories
link_directories(${CMAKE_SOURCE_DIR}/src/lib)

# Define the executable and its sources
add_executable(Sorting_Algs main.cpp main_menu.cpp SortingAlgs.cpp)

# Linking the required libraries
target_link_libraries(Sorting_Algs 
    -lmingw32 
    ${CMAKE_SOURCE_DIR}/src/lib/libSDL2main.a 
    ${CMAKE_SOURCE_DIR}/src/lib/libSDL2.dll.a 
    ${CMAKE_SOURCE_DIR}/src/lib/libSDL2_ttf.dll.a 
)

# Copy the required DLLs to the output directory
add_custom_command(TARGET Sorting_Algs POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/SDL2.dll
    $<TARGET_FILE_DIR:Sorting_Algs>)

add_custom_command(TARGET Sorting_Algs POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/SDL2_ttf.dll
    $<TARGET_FILE_DIR:Sorting_Algs>)

# Copy Font
add_custom_command(TARGET Sorting_Algs POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/Font.ttf
    $<TARGET_FILE_DIR:Sorting_Algs>)
