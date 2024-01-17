# pull library name from directory name
get_filename_component(libname ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" libname ${libname})

message(STATUS "Adding the libname: ${libname}")

set(libdeps
    "${libdeps}"
    ${CMAKE_CURRENT_LIST_DIR}/Inc
)

# Define library
set ( srcs
    "${srcs}"
    ${CMAKE_CURRENT_LIST_DIR}/Src/dbg_trace.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/otp.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm_list.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm_queue.c
)

set (srcs "${srcs}" PARENT_SCOPE)
set (libdeps "${libdeps}" PARENT_SCOPE)
