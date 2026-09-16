# components.cmake

# component ARM::CMSIS:CORE@5.6.0
add_library(ARM_CMSIS_CORE_5_6_0 INTERFACE)
target_include_directories(ARM_CMSIS_CORE_5_6_0 INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/Core/Include"
)
target_compile_definitions(ARM_CMSIS_CORE_5_6_0 INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_link_libraries(ARM_CMSIS_CORE_5_6_0 INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)

# component ARM::CMSIS:RTOS2:Keil RTX5&Source@5.5.4
add_library(ARM_CMSIS_RTOS2_Keil_RTX5_Source_5_5_4 OBJECT
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv7m.S"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Source/rtx_delay.c"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Source/rtx_evflags.c"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Source/rtx_evr.c"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Source/rtx_kernel.c"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Source/rtx_lib.c"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Source/rtx_memory.c"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Source/rtx_mempool.c"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Source/rtx_msgqueue.c"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Source/rtx_mutex.c"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Source/rtx_semaphore.c"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Source/rtx_system.c"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Source/rtx_thread.c"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Source/rtx_timer.c"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/Source/os_systick.c"
  "${SOLUTION_ROOT}/RTE/CMSIS/RTX_Config.c"
)
target_include_directories(ARM_CMSIS_RTOS2_Keil_RTX5_Source_5_5_4 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${SOLUTION_ROOT}/RTE/CMSIS"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Include"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/Include"
)
target_compile_definitions(ARM_CMSIS_RTOS2_Keil_RTX5_Source_5_5_4 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(ARM_CMSIS_RTOS2_Keil_RTX5_Source_5_5_4 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(ARM_CMSIS_RTOS2_Keil_RTX5_Source_5_5_4 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)
set_source_files_properties("${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv7m.S" PROPERTIES
  COMPILE_DEFINITIONS "__MICROLIB;STM32F407xx;_RTE_"
)

# component Keil::Board Support&STM32F4-Discovery:Buttons@2.0.0
add_library(Keil_Board_Support_STM32F4-Discovery_Buttons_2_0_0 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/MDK/Boards/ST/STM32F4-Discovery/Common/Buttons_F4Discovery.c"
)
target_include_directories(Keil_Board_Support_STM32F4-Discovery_Buttons_2_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/Keil/MDK-Middleware/7.16.0/Board"
)
target_compile_definitions(Keil_Board_Support_STM32F4-Discovery_Buttons_2_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Board_Support_STM32F4-Discovery_Buttons_2_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Board_Support_STM32F4-Discovery_Buttons_2_0_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Board Support&STM32F4-Discovery:LED@2.0.0
add_library(Keil_Board_Support_STM32F4-Discovery_LED_2_0_0 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/MDK/Boards/ST/STM32F4-Discovery/Common/LED_F4Discovery.c"
)
target_include_directories(Keil_Board_Support_STM32F4-Discovery_LED_2_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/Keil/MDK-Middleware/7.16.0/Board"
)
target_compile_definitions(Keil_Board_Support_STM32F4-Discovery_LED_2_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Board_Support_STM32F4-Discovery_LED_2_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Board_Support_STM32F4-Discovery_LED_2_0_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Compiler&ARM Compiler:Event Recorder&DAP@1.5.1
add_library(Keil_Compiler_ARM_Compiler_Event_Recorder_DAP_1_5_1 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/ARM_Compiler/1.7.2/Source/EventRecorder.c"
)
target_include_directories(Keil_Compiler_ARM_Compiler_Event_Recorder_DAP_1_5_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${SOLUTION_ROOT}/RTE/Compiler"
  "${CMSIS_PACK_ROOT}/Keil/ARM_Compiler/1.7.2/Include"
)
target_compile_definitions(Keil_Compiler_ARM_Compiler_Event_Recorder_DAP_1_5_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Compiler_ARM_Compiler_Event_Recorder_DAP_1_5_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Compiler_ARM_Compiler_Event_Recorder_DAP_1_5_1 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:STM32Cube Framework:Classic@1.8.1
add_library(Keil_Device_STM32Cube_Framework_Classic_1_8_1 INTERFACE)
target_include_directories(Keil_Device_STM32Cube_Framework_Classic_1_8_1 INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${SOLUTION_ROOT}/RTE/Device/STM32F407VGTx"
)
target_compile_definitions(Keil_Device_STM32Cube_Framework_Classic_1_8_1 INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_link_libraries(Keil_Device_STM32Cube_Framework_Classic_1_8_1 INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:STM32Cube HAL:Common@1.8.1
add_library(Keil_Device_STM32Cube_HAL_Common_1_8_1 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c"
)
target_include_directories(Keil_Device_STM32Cube_HAL_Common_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/STM32F4xx_HAL_Driver/Inc"
)
target_compile_definitions(Keil_Device_STM32Cube_HAL_Common_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_STM32Cube_HAL_Common_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_STM32Cube_HAL_Common_1_8_1 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:STM32Cube HAL:Cortex@1.8.1
add_library(Keil_Device_STM32Cube_HAL_Cortex_1_8_1 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c"
)
target_include_directories(Keil_Device_STM32Cube_HAL_Cortex_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Keil_Device_STM32Cube_HAL_Cortex_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_STM32Cube_HAL_Cortex_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_STM32Cube_HAL_Cortex_1_8_1 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:STM32Cube HAL:DMA@1.8.1
add_library(Keil_Device_STM32Cube_HAL_DMA_1_8_1 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c"
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c"
)
target_include_directories(Keil_Device_STM32Cube_HAL_DMA_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Keil_Device_STM32Cube_HAL_DMA_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_STM32Cube_HAL_DMA_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_STM32Cube_HAL_DMA_1_8_1 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:STM32Cube HAL:GPIO@1.8.1
add_library(Keil_Device_STM32Cube_HAL_GPIO_1_8_1 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c"
)
target_include_directories(Keil_Device_STM32Cube_HAL_GPIO_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Keil_Device_STM32Cube_HAL_GPIO_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_STM32Cube_HAL_GPIO_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_STM32Cube_HAL_GPIO_1_8_1 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:STM32Cube HAL:I2C@1.8.1
add_library(Keil_Device_STM32Cube_HAL_I2C_1_8_1 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c"
)
target_include_directories(Keil_Device_STM32Cube_HAL_I2C_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Keil_Device_STM32Cube_HAL_I2C_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_STM32Cube_HAL_I2C_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_STM32Cube_HAL_I2C_1_8_1 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:STM32Cube HAL:PWR@1.8.1
add_library(Keil_Device_STM32Cube_HAL_PWR_1_8_1 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c"
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c"
)
target_include_directories(Keil_Device_STM32Cube_HAL_PWR_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Keil_Device_STM32Cube_HAL_PWR_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_STM32Cube_HAL_PWR_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_STM32Cube_HAL_PWR_1_8_1 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:STM32Cube HAL:RCC@1.8.1
add_library(Keil_Device_STM32Cube_HAL_RCC_1_8_1 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c"
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c"
)
target_include_directories(Keil_Device_STM32Cube_HAL_RCC_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Keil_Device_STM32Cube_HAL_RCC_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_STM32Cube_HAL_RCC_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_STM32Cube_HAL_RCC_1_8_1 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:STM32Cube HAL:SPI@1.8.1
add_library(Keil_Device_STM32Cube_HAL_SPI_1_8_1 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c"
)
target_include_directories(Keil_Device_STM32Cube_HAL_SPI_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Keil_Device_STM32Cube_HAL_SPI_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_STM32Cube_HAL_SPI_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_STM32Cube_HAL_SPI_1_8_1 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:STM32Cube HAL:UART@1.8.1
add_library(Keil_Device_STM32Cube_HAL_UART_1_8_1 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c"
)
target_include_directories(Keil_Device_STM32Cube_HAL_UART_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Keil_Device_STM32Cube_HAL_UART_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_STM32Cube_HAL_UART_1_8_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_STM32Cube_HAL_UART_1_8_1 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:Startup@2.6.3
add_library(Keil_Device_Startup_2_6_3 OBJECT
  "${SOLUTION_ROOT}/RTE/Device/STM32F407VGTx/startup_stm32f407xx.s"
  "${SOLUTION_ROOT}/RTE/Device/STM32F407VGTx/system_stm32f4xx.c"
)
target_include_directories(Keil_Device_Startup_2_6_3 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include"
)
target_compile_definitions(Keil_Device_Startup_2_6_3 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_Startup_2_6_3 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
  $<$<COMPILE_LANGUAGE:ASM>:
    "SHELL:-masm=auto"
  >
)
target_link_libraries(Keil_Device_Startup_2_6_3 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)
set(COMPILE_DEFINITIONS
  __MICROLIB
  STM32F407xx
  _RTE_
)
cbuild_set_defines(AS_ARM COMPILE_DEFINITIONS)
set_source_files_properties("${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/MDK/Device/Source/ARM/STM32F40xxx_41xxx_OPT.s" PROPERTIES
  COMPILE_FLAGS "${COMPILE_DEFINITIONS}"
)
set(COMPILE_DEFINITIONS
  __MICROLIB
  STM32F407xx
  _RTE_
)
cbuild_set_defines(AS_ARM COMPILE_DEFINITIONS)
set_source_files_properties("${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/MDK/Device/Source/ARM/STM32F4xx_OTP.s" PROPERTIES
  COMPILE_FLAGS "${COMPILE_DEFINITIONS}"
)
set(COMPILE_DEFINITIONS
  __MICROLIB
  STM32F407xx
  _RTE_
)
cbuild_set_defines(AS_ARM COMPILE_DEFINITIONS)
set_source_files_properties("${SOLUTION_ROOT}/RTE/Device/STM32F407VGTx/startup_stm32f407xx.s" PROPERTIES
  COMPILE_FLAGS "${COMPILE_DEFINITIONS}"
)
