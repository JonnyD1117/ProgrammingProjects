set(target CppArgumentParser)

set(sources
    ArgumentParser.cpp
)

set(libs

)

add_library(${target} STATIC ${sources})

target_link_libraries(${target} PUBLIC ${libs})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

