

add_executable(cpu_service cpu_service.cpp main.cpp ${HEADERS})

target_link_libraries(cpu_service proto_lib monitor)
