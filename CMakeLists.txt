cmake_minimum_required (VERSION 2.6)
project (p1)
#file( GLOB LIB_SOURCES p1/*.c )
#file( GLOB LIB_HEADERS lib/*.h )
#add_library( p1Lib ${LIB_SOURCES} ${LIB_HEADERS} )

add_executable(ej1 ej1.c)
add_executable(ej2 ej2.c)
add_executable(ej3 ej3.c)
add_executable(ej4-restart ej4-restart.c)
add_executable(ej4-resethand ej4-resethand.c)
add_executable(ej5 ej5.c)
add_executable(ej5-mod.c)
add_executable(ej6.c)
add_executable(ej7.c)


#foreach( testsourcefile ${APP_SOURCES} )
    # I used a simple string replace, to cut off .cpp.
    #string( REPLACE ".c" "" testname ${testsourcefile} )
#    add_executable( ${testname} ${testsourcefile} )
    # Make sure YourLib is linked to each app
#    target_link_libraries( ${testname} p1Lib )
#endforeach( testsourcefile ${APP_SOURCES} )

set(
        CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/out
)