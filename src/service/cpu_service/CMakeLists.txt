

add_executable(cpu_service cpu_service.cpp main.cpp ${PROTO_FILES} ${PROTO_LIB_HEADER})

target_link_libraries(cpu_service proto_lib monitor)
