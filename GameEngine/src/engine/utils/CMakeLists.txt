# Add Utility Libraries
add_subdirectory( strings )


# Creating Grouping of "sub-libraries" into single utils lib
set( target engine_utils )

set( libs 
    engine_utils_strings
)

# Create the Library Target
add_library(${target} INTERFACE )

# Group sub-libraries
target_link_libraries(${target} INTERFACE ${libs} ) 