add_executable(CalibrateTest ad9166_calibrate.c)
target_link_libraries(CalibrateTest LINK_PRIVATE ${LIBIIO_LIBRARIES} ad9166)
add_test(NAME CalibrateTest
         COMMAND CalibrateTest
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
