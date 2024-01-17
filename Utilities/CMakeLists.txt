# pull library name from directory name
get_filename_component(libname ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" libname ${libname})

message(STATUS "Adding the libname: ${libname}")

set(libdeps
    "${libdeps}"
    ${CMAKE_CURRENT_LIST_DIR}/lpm/tiny_lpm
    ${CMAKE_CURRENT_LIST_DIR}/sequencer
)

# Define library
set ( srcs
    "${srcs}"
    # ${CMAKE_CURRENT_LIST_DIR}/Startup/startup_stm32f103ctx.s
    
    ${CMAKE_CURRENT_LIST_DIR}/lpm/tiny_lpm/stm32_lpm.c

    ${CMAKE_CURRENT_LIST_DIR}/sequencer/stm32_seq.c

)

set (srcs "${srcs}" PARENT_SCOPE)
set (libdeps "${libdeps}" PARENT_SCOPE)
