cmake_minimum_required(VERSION 3.0.0)

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif ()

project(MyProject)

# add 3rdparty external
add_subdirectory(external)

set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB PROJECT_EXAMPLES "src/*.cpp")
foreach (SRC ${PROJECT_EXAMPLES})
    get_filename_component(EXAMPLE_TARGET ${SRC} NAME_WE)
    add_executable(${EXAMPLE_TARGET} ${SRC})
    target_include_directories(${EXAMPLE_TARGET} PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}
            external/oneTBB/include
            external/include
            )

    target_link_libraries(${EXAMPLE_TARGET} PRIVATE
            pthread
            tbb
            benchmark
            )
endforeach (SRC)

add_executable(main main.cpp)

