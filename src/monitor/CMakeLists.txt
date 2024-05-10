
add_subdirectory(utils)

aux_source_directory(./ SRC)

set(Protobuf_USE_STATIC_LIBS ON)

add_library(monitor ${SRC} ${HEADERS} ${ALL_UTILS_OBJECTS} ${PROTO_FILES})

protobuf_generate(TARGET monitor
        PROTOS ${PROTO_FILES}
        IMPORT_DIRS ${PROJECT_SOURCE_DIR}/src/proto
        PROTOC_OUT_DIR ${PROJECT_BINARY_DIR}/src/proto)

target_link_libraries(monitor ${Protobuf_LIBRARIES})

target_include_directories(monitor PUBLIC ${PROJECT_BINARY_DIR}/src/proto ${Protobuf_INCLUDE_DIRS})
