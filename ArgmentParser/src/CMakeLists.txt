set(target ArgumentParser)

set(sources
    main.cpp
)

add_library(${target} STATIC ${sources})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

