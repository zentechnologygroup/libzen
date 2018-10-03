# Unit converter ###############################################################

set(CONVERT_SOURCE convert.cc)
add_executable(ztgconvert ${CONVERT_SOURCE})
target_link_libraries(ztgconvert ztgunitmanager)

################################################################################