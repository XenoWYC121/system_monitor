# 查找grpc
find_package(gRPC REQUIRED)

# 查找 GTest 库
find_package(GTest REQUIRED)
# GTest 的头文件
include_directories(${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src/include)

# add_executable(monitor_test01 monitor/monitor_test01.cpp)

file(GLOB_RECURSE test_source ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

foreach (item IN ITEMS ${test_source})
    cmake_path(GET item STEM target_item)
    list(APPEND test_target ${target_item})
endforeach ()
foreach (source_file target_name IN ZIP_LISTS test_source;test_target)
    add_executable(${target_name} ${source_file})
    # 链接测试库
    target_link_libraries(${target_name} ${GTEST_BOTH_LIBRARIES} monitor gRPC::grpc++)
    # 加入到测试用例
    gtest_discover_tests(${target_name})
endforeach ()

