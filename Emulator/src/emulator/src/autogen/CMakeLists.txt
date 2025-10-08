
set( target auto_generated_code )



# Compile Library
add_library( ${target}  ${AUTOGEN_FILES} )
target_link_libraries(${target} PUBLIC ${libs})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})