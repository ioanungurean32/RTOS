cmake_minimum_required(VERSION 3.27)

# Roots
include("../roots.cmake")

set(CONTEXT Macheta_RTOS+Debug)
set(TARGET ${CONTEXT})
set(DNAME STM32F407VGTx)
set(DPACK Keil::STM32F4xx_DFP@2.17.1)
set(DPACK_DIR "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1")
set(OUT_DIR "${SOLUTION_ROOT}/out/Macheta_RTOS/Debug")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COMPILE_COMMANDS ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)
set(COMPILE_COMMANDS ${OUT_DIR}/compile_commands.json)
set(COMPILE_MACROS_C ${OUT_DIR}/compile_macros_c.h)
set(LD_SCRIPT "${SOLUTION_ROOT}/Macheta_RTOS_Debug.sct")
set(LD_SCRIPT_PP ${LD_SCRIPT})

# Processor Options
set(CPU Cortex-M4)
set(FPU SP_FPU)
set(BYTE_ORDER Little-endian)

# Toolchain config map
set(COMPILER AC6)
include("toolchain.cmake")

# Setup project
project(${CONTEXT} LANGUAGES C ASM)

# Enable color diagnostics
set(CMAKE_COLOR_DIAGNOSTICS ON)

# Preprocessor options
set(CPP_OPTIONS_C "-xc" "-std=c99" "-fno-rtti" "-funsigned-char" "-fshort-enums" "-fshort-wchar" "-ffunction-sections" "-Wno-packed" "-Wno-missing-variable-declarations" "-Wno-missing-prototypes" "-Wno-missing-noreturn" "-Wno-sign-conversion" "-Wno-nonportable-include-path" "-Wno-reserved-id-macro" "-Wno-unused-macros" "-Wno-documentation-unknown-command" "-Wno-documentation" "-Wno-license-management" "-Wno-parentheses-equality")

# Compilation database
add_custom_target(database DEPENDS ${COMPILE_COMMANDS} ${COMPILE_MACROS_C})
add_custom_command(OUTPUT ${COMPILE_COMMANDS}
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_COMPILE_COMMANDS}" "${COMPILE_COMMANDS}"
  DEPENDS "${CMAKE_COMPILE_COMMANDS}"
)
add_custom_command(OUTPUT ${COMPILE_MACROS_C}
  COMMAND ${CPP} ${CPP_OPTIONS_C} ${CPP_DUMP_MACROS} "${COMPILE_MACROS_C}"
)
set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES})

# Setup context
add_executable(${CONTEXT})
set_target_properties(${CONTEXT} PROPERTIES PREFIX "" SUFFIX ".axf" OUTPUT_NAME "Macheta_RTOS")
set_target_properties(${CONTEXT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR})
add_library(${CONTEXT}_GLOBAL INTERFACE)

# Includes
target_include_directories(${CONTEXT} PUBLIC
  "${SOLUTION_ROOT}/RTE/_Debug"
  "${SOLUTION_ROOT}/RTE/CMSIS"
  "${SOLUTION_ROOT}/RTE/Compiler"
  "${SOLUTION_ROOT}/RTE/Device/STM32F407VGTx"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/Core/Include"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/Include"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/5.9.0/CMSIS/RTOS2/RTX/Include"
  "${CMSIS_PACK_ROOT}/Keil/ARM_Compiler/1.7.2/Include"
  "${CMSIS_PACK_ROOT}/Keil/MDK-Middleware/7.16.0/Board"
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include"
  "${CMSIS_PACK_ROOT}/Keil/STM32F4xx_DFP/2.17.1/Drivers/STM32F4xx_HAL_Driver/Inc"
)

# Defines
target_compile_definitions(${CONTEXT} PUBLIC
  $<$<COMPILE_LANGUAGE:C,CXX>:
    HSE_VALUE=8000000
    __MICROLIB
    STM32F407xx
    _RTE_
  >
)

# Compile options
target_compile_options(${CONTEXT} PUBLIC
  $<$<COMPILE_LANGUAGE:ASM>:
    "SHELL:${ASM_CPU}"
    "SHELL:${ASM_FLAGS}"
    "SHELL:${ASM_BYTE_ORDER}"
  >
  $<$<COMPILE_LANGUAGE:C>:
    "SHELL:${CC_CPU}"
    "SHELL:${CC_FLAGS}"
    "SHELL:${CC_BYTE_ORDER}"
    "SHELL:-std=c99"
    "SHELL:-fno-rtti"
    "SHELL:-funsigned-char"
    "SHELL:-fshort-enums"
    "SHELL:-fshort-wchar"
    "SHELL:-ffunction-sections"
    "SHELL:-Wno-packed"
    "SHELL:-Wno-missing-variable-declarations"
    "SHELL:-Wno-missing-prototypes"
    "SHELL:-Wno-missing-noreturn"
    "SHELL:-Wno-sign-conversion"
    "SHELL:-Wno-nonportable-include-path"
    "SHELL:-Wno-reserved-id-macro"
    "SHELL:-Wno-unused-macros"
    "SHELL:-Wno-documentation-unknown-command"
    "SHELL:-Wno-documentation"
    "SHELL:-Wno-license-management"
    "SHELL:-Wno-parentheses-equality"
  >
  $<$<COMPILE_LANGUAGE:C,CXX>:
    "SHELL:${_PI}\"${SOLUTION_ROOT}/RTE/_Debug/Pre_Include_Global.h\""
  >
)

# Compile Options Abstractions
add_library(${CONTEXT}_ABSTRACTIONS INTERFACE)
cbuild_set_options_flags(CC "debug" "on" "" "" CC_OPTIONS_FLAGS_${CONTEXT})
cbuild_set_options_flags(ASM "debug" "on" "" "" ASM_OPTIONS_FLAGS_${CONTEXT})
target_compile_options(${CONTEXT}_ABSTRACTIONS INTERFACE
  $<$<COMPILE_LANGUAGE:C>:
    "SHELL:${CC_OPTIONS_FLAGS_${CONTEXT}}"
  >
  $<$<COMPILE_LANGUAGE:ASM>:
    "SHELL:${ASM_OPTIONS_FLAGS_${CONTEXT}}"
  >
)

# Add groups and components
include("groups.cmake")
include("components.cmake")

target_link_libraries(${CONTEXT} PUBLIC
  Group_Source_Files
  Group_Mikroe
  ARM_CMSIS_CORE_5_6_0
  ARM_CMSIS_RTOS2_Keil_RTX5_Source_5_5_4
  Keil_Board_Support_STM32F4-Discovery_Buttons_2_0_0
  Keil_Board_Support_STM32F4-Discovery_LED_2_0_0
  Keil_Compiler_ARM_Compiler_Event_Recorder_DAP_1_5_1
  Keil_Device_STM32Cube_Framework_Classic_1_8_1
  Keil_Device_STM32Cube_HAL_Common_1_8_1
  Keil_Device_STM32Cube_HAL_Cortex_1_8_1
  Keil_Device_STM32Cube_HAL_DMA_1_8_1
  Keil_Device_STM32Cube_HAL_GPIO_1_8_1
  Keil_Device_STM32Cube_HAL_I2C_1_8_1
  Keil_Device_STM32Cube_HAL_PWR_1_8_1
  Keil_Device_STM32Cube_HAL_RCC_1_8_1
  Keil_Device_STM32Cube_HAL_SPI_1_8_1
  Keil_Device_STM32Cube_HAL_UART_1_8_1
  Keil_Device_Startup_2_6_3
)

# Linker options
target_link_options(${CONTEXT} PUBLIC
  "SHELL:${LD_CPU}"
  "SHELL:${_LS}\"${LD_SCRIPT_PP}\""
  "SHELL:--library_type=microlib"
  "SHELL:--map"
  "SHELL:--load_addr_map_info"
  "SHELL:--xref"
  "SHELL:--callgraph"
  "SHELL:--symbols"
  "SHELL:--info sizes"
  "SHELL:--info totals"
  "SHELL:--info unused"
  "SHELL:--info veneers"
  "SHELL:--strict"
  "SHELL:--summary_stderr"
  "SHELL:--info summarysizes"
)
set(LD_DEPS ${LD_SCRIPT})
set_target_properties(${CONTEXT} PROPERTIES LINK_DEPENDS "${LD_DEPS}")
