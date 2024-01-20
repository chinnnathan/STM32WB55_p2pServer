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
    ${CMAKE_CURRENT_LIST_DIR}/Src/app_debug.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/app_entry.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/hw_timerserver.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/hw_uart.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/main.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32_lpm_if.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32wbxx_hal_msp.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32wbxx_hal_timebase_tim.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32wbxx_it.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/system_stm32wbxx.c

    ${CMAKE_CURRENT_LIST_DIR}/startup_stm32wb55rgvx.s
)

set (srcs "${srcs}" PARENT_SCOPE)
set (libdeps "${libdeps}" PARENT_SCOPE)
