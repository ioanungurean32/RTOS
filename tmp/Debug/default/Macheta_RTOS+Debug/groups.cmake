# groups.cmake

# group Source Files
add_library(Group_Source_Files OBJECT
  "${SOLUTION_ROOT}/main.c"
  "${SOLUTION_ROOT}/uart2.c"
  "${SOLUTION_ROOT}/tasks.c"
)
target_include_directories(Group_Source_Files PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Source_Files PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Source_Files_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Source_Files_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Source_Files PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Source_Files PUBLIC
  Group_Source_Files_ABSTRACTIONS
)

# group Mikroe
add_library(Group_Mikroe OBJECT
  "${SOLUTION_ROOT}/Mikroe/oledb.c"
  "${SOLUTION_ROOT}/Mikroe/oledb_resources.c"
  "${SOLUTION_ROOT}/Mikroe/proximity7.c"
  "${SOLUTION_ROOT}/Mikroe/temphum15.c"
  "${SOLUTION_ROOT}/Mikroe/c7seg.c"
)
target_include_directories(Group_Mikroe PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Mikroe PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Mikroe_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Mikroe_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Mikroe PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Mikroe PUBLIC
  Group_Mikroe_ABSTRACTIONS
)
