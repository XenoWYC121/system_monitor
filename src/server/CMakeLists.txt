

add_executable(grpc_server sync_grpc_server.cpp main.cpp ${HEADERS})

target_link_libraries(grpc_server proto_lib memory_usage_client cpu_usage_client)