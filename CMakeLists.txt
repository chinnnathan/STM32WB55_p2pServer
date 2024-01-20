
cmake_minimum_required(VERSION 3.5)

project(BLE_p2pServer CXX C ASM)


# set(CMAKE_C_STANDARD 99)
# set(CMAKE_C_STANDARD_REQUIRED ON)
# set(CMAKE_C_EXTENSIONS ON)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS ON)
set(EXECUTABLE ${PROJECT_NAME}.elf)

# set (srcs /home/nchinn/workspace/STM32/F407/MouseWiggle/startup_stm32f407xx.s)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Core)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Lib)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Lib/Servo)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Lib/intf)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Lib/ble)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Lib/utility)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/STM32_WPAN)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Drivers)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Utilities)
# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Middlewares/Third_Party/FreeRTOS/Source)
# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/IO)
# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Devices/BT)
# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Tasks)

if( DEFINED DEBUG_PRINT)
    message("==============================")
    message ("${srcs}")
    message("==============================")
endif()
add_executable(${EXECUTABLE} "${srcs}")

target_compile_definitions(${EXECUTABLE} PRIVATE
    -DUSE_HAL_DRIVER
    -DSTM32WB55xx
    )

target_include_directories(${EXECUTABLE} PRIVATE
    "${libdeps}"
    )

target_compile_options(${EXECUTABLE} PRIVATE
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=soft

    -fdata-sections
    -ffunction-sections
    -g3
    -ggdb
    -gdwarf-2
    -Wall
    -Wextra
    -pedantic

    $<$<COMPILE_LANGUAGE:CXX>:@${CMAKE_SOURCE_DIR}/gcc-options-cxx.txt>
    $<$<CONFIG:Debug>:-Og>
    )

target_link_options(${EXECUTABLE} PRIVATE
    -T${CMAKE_SOURCE_DIR}/STM32WB55RGVX_FLASH.ld
    # -T/home/nchinn/workspace/STM32/F407/MouseWiggle/STM32F407VETX_FLASH.ld
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=soft
    -specs=nosys.specs
    -lc
    -lm
    -lnosys
    -Wl,-Map=${PROJECT_NAME}.map,--cref
    -Wl,--gc-sections
    -Wl,--print-memory-usage
    # -g
    -ggdb
    -gdwarf-2
    )

add_definitions(-w)

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
POST_BUILD
COMMAND arm-none-eabi-size ${EXECUTABLE})

# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
POST_BUILD
COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
# COMMAND arm-none-eabi-objcopy -O elf ${EXECUTABLE} ${PROJECT_NAME}.elf)
COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)