

add_executable(cpu_service cpu_service.cpp ${PROTO_FILES})

protobuf_generate(TARGET cpu_service
        PROTOS ${PROTO_FILES}
        IMPORT_DIRS ${PROJECT_SOURCE_DIR}/src/proto
        PROTOC_OUT_DIR ${PROJECT_BINARY_DIR}/src/proto)



target_link_libraries(cpu_service ${Protobuf_LIBRARIES})

target_include_directories(cpu_service PUBLIC ${PROJECT_BINARY_DIR}/src/proto ${Protobuf_INCLUDE_DIRS})