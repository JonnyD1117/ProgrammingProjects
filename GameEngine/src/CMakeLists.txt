###########################################
#   Compile Platform Independent Libs
###########################################
#add_subdirectory( assets )
add_subdirectory( engine )
#add_subdirectory( tools )

###########################################
#   Compile Platform Dependent Libs
###########################################
# Support Cross-Platform Compilation (default to LINUX)
# add_subdirectory( platform ) 

###################################
#   Compile Engine 
###################################

set(target dftd_game_engine)

set(sources
    main.cpp
)

set(project_libaries
    engine
)

add_executable( ${target} ${sources})
target_link_libraries(${target} PUBLIC ${project_libaries})