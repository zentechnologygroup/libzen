# Unit converter ###############################################################

set(SOURCES ztg_unit_manager_test.cpp)
add_executable(ztgunitmanagertest ${SOURCES})
target_link_libraries(ztgunitmanagertest ztgunitmanager ${GSL_LIBRARIES} gtest)

################################################################################