

add_executable(memory_usage_client memory_usage_client.cpp ${HEADERS})

target_link_libraries(memory_usage_client proto_lib)