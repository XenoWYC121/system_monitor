# 查找 GTest 库
find_package(GTest REQUIRED)
# GTest 的头文件
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(monitor_test01 monitor/monitor_test01.cpp)

# 链接测试库
target_link_libraries(monitor_test01
        ${GTEST_BOTH_LIBRARIES})

# 添加到测试
gtest_discover_tests(monitor_test01)