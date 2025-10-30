set(target screen)

# set(sources 
#     empty.cpp
#     NCursesWrapper.hpp
# )

set( libs
    # Curses::Curses
    ncurses
)

add_library(${target} INTERFACE ${sources})

target_link_libraries(${target} INTERFACE ${libs})
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

