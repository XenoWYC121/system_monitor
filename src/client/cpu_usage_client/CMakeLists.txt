
add_library(cpu_usage_client cpu_usage_client.cpp)

target_include_directories(cpu_usage_client PUBLIC ${PROTO_LIB_HEADER})

target_link_libraries(cpu_usage_client proto_lib)