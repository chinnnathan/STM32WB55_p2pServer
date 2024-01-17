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
    ${CMAKE_CURRENT_LIST_DIR}/Src/hci_tl.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/hci_tl_if.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/shci.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/shci_tl.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/shci_tl_if.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/tl_mbox.c
)

set (srcs "${srcs}" PARENT_SCOPE)
set (libdeps "${libdeps}" PARENT_SCOPE)
