
add_executable(TestWindow ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
target_link_libraries(TestWindow PRIVATE ${PROJECT_NAME})

add_test(NAME "Test Window" COMMAND TestWindow)
