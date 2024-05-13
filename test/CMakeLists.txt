# 查找grpc
find_package(gRPC REQUIRED)

# 查找protobuf
find_package(Protobuf REQUIRED)

# 查找 GTest 库
find_package(GTest REQUIRED)
# GTest 的头文件
include_directories(${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src/include ${PROJECT_BINARY_DIR}/src/proto)

# add_executable(monitor_test01 monitor/monitor_test01.cpp)

file(GLOB_RECURSE test_source ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

foreach (item IN ITEMS ${test_source})
    cmake_path(GET item STEM target_item)
    list(APPEND test_target ${target_item})
endforeach ()

# 添加C宏定义
add_compile_definitions(
        CPU_SERVICE_PATH="${PROJECT_BINARY_DIR}/src/service/cpu_service/cpu_service"
        MEMORY_SERVICE_PATH="${PROJECT_BINARY_DIR}/src/service/memory_service/memory_service"
)

foreach (source_file target_name IN ZIP_LISTS test_source;test_target)
    add_executable(${target_name} ${source_file})
    # 链接测试库
    target_link_libraries(${target_name} ${GTEST_BOTH_LIBRARIES} monitor gRPC::grpc++ proto_lib cpu_usage_client memory_usage_client)
    # 加入到测试用例
    gtest_discover_tests(${target_name})
endforeach ()

