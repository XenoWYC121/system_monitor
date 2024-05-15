

add_library(sys_info_client sys_info_client.cpp ${HEADERS})

target_link_libraries(sys_info_client proto_lib)