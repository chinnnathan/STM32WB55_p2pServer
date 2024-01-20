# pull library name from directory name
get_filename_component(libname ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" libname ${libname})

message(STATUS "Adding the libname: ${libname}")

set(libdeps
    "${libdeps}"
    ${CMAKE_CURRENT_LIST_DIR}/CMSIS/Device/ST/STM32WBxx/Include
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Inc
    # ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Inc/Legacy
    ${CMAKE_CURRENT_LIST_DIR}/CMSIS/Include
    ${CMAKE_CURRENT_LIST_DIR}/BSP/P-NUCLEO-WB55.Nucleo/
)

# Define library
set ( srcs
    "${srcs}"
    # ${CMAKE_CURRENT_LIST_DIR}/Startup/startup_stm32f103ctx.s
    
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_adc.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_adc_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_cortex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_dma.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_dma_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_exti.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_flash.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_flash_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_gpio.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_hsem.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_ipcc.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_pwr.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_pwr_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_rcc.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_rcc_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_rng.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_rtc.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_rtc_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_tim.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_tim_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_uart.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_uart_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_ll_adc.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_ll_rcc.c

    ${CMAKE_CURRENT_LIST_DIR}/BSP/P-NUCLEO-WB55.Nucleo/stm32wbxx_nucleo.c

)

set (srcs "${srcs}" PARENT_SCOPE)
set (libdeps "${libdeps}" PARENT_SCOPE)
