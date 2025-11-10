
set( target assembler )

set( sources 
    assembler.cpp
)

set( libs 

)

add_library( ${target}_lib ${sources} ${libs})
target_link_libraries( ${target}_lib PRIVATE ${libs}) 
target_include_directories(${target}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



add_executable( ${target}  main.cpp )
target_link_libraries( ${target} PRIVATE ${target}_lib)
target_compile_definitions(${target} PRIVATE PROJECT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

