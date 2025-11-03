set(target ArgumentParser)

set(sources
    main.cpp
)

add_executable(${target} ${sources})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

