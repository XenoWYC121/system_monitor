
include_directories(${PROTO_TEST_HEADER})

add_executable(cpu_service cpu_service.cpp ${PROTO_FILES})

target_link_libraries(cpu_service proto_lib)
