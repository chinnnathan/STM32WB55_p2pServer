# pull library name from directory name
get_filename_component(libname ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" libname ${libname})

message(STATUS "Adding the libname: ${libname}")

set(libdeps
    "${libdeps}"
    ${CMAKE_CURRENT_LIST_DIR}/App
)

# Define library
set ( srcs
    "${srcs}"
    # ${CMAKE_CURRENT_LIST_DIR}/Startup/startup_stm32f103ctx.s
    
    ${CMAKE_CURRENT_LIST_DIR}/App/app_ble.c
    ${CMAKE_CURRENT_LIST_DIR}/App/p2p_server_app.c

    ${CMAKE_CURRENT_LIST_DIR}/Target/hw_ipcc.c

)

set (srcs "${srcs}" PARENT_SCOPE)
set (libdeps "${libdeps}" PARENT_SCOPE)
