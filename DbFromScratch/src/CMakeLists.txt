#############################
#   Source Compilation
#############################
# add_subdirectory( db )
# add_subdirectory( network )
# add_subdirectory( detection )

#############################
#   Executable Compilation
#############################
set(target main)

set(sources main.cpp )

# Set Project Libaries
set(libs )

# Create Executable
add_executable(${target} ${sources} )

target_link_libraries(${target} PUBLIC ${libs})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})