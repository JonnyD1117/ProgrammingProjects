set(target main)

set(sources
    main.cpp
)

set(libs
    embind
)

add_executable(${target} ${sources})
target_link_libraries(${target} PRIVATE ${libs})




# Detect Emscripten
if(EMSCRIPTEN)
    message(STATUS "Compiling for Emscripten")

    # Include embind headers
    target_include_directories(${target} PRIVATE "$ENV{EMSDK}/upstream/emscripten/system/include")

    # Emscripten options
    target_link_options(${target} PRIVATE
        "-s WASM=1"
        "-s ALLOW_MEMORY_GROWTH=1"
    )

    set_target_properties(${target} PROPERTIES SUFFIX ".html")

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(${target} PRIVATE "-O2")
    endif()
endif()