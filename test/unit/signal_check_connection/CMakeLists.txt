file(GLOB sources "*.cpp")
file(GLOB headers "*.hpp")

add_executable(test_signal_check_connection ${sources} ${headers})
target_link_libraries(test_signal_check_connection sigcxx gtest common)
