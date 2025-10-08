#add_subdirectory( assets )
add_subdirectory( engine )
#add_subdirectory( tools )
#add_subdirectory( game )

# Tests Needs to be added last since it COULD 
# depend on every other library being built
add_subdirectory( tests )