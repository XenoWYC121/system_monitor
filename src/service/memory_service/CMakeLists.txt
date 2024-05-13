

add_executable(memory_service memory_service.cpp ${HEADERS})

target_link_libraries(memory_service monitor proto_lib)