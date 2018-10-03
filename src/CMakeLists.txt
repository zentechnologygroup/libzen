set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/ztg_unit_manager.cc)
set(INCLUDES ${PROJECT_SOURCE_DIR}/include/units.hpp)
set(PREAMBLE units-vars.cc)
set(TMP_FILE ${SOURCES}.tmp)

file(REMOVE ${SOURCES})

add_custom_command(
  OUTPUT ${SOURCES}
  COMMAND ${CMAKE_CXX_COMPILER} -E ${PREAMBLE} -std=c++14 -I../include > ${TMP_FILE}
  COMMAND cat ${PREAMBLE} > ${SOURCES}
  COMMAND ${PROJECT_SOURCE_DIR}/scripts/extract-cv ${TMP_FILE} >> ${SOURCES}
  COMMAND rm ${TMP_FILE}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(ztggen DEPENDS ${SOURCES}) 

set_source_files_properties(${SOURCES} PROPERTIES GENERATED TRUE)

add_library(ztgunitmanager SHARED ${SOURCES} ${INCLUDES})
target_link_libraries(ztgunitmanager)
add_dependencies(ztgunitmanager ztggen)