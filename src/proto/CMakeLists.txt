find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf REQUIRED)

file(GLOB PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.proto)

add_library(proto_lib ${PROTO_FILES})
target_link_libraries(proto_lib PUBLIC gRPC::grpc++)

# 生成proto接口
protobuf_generate(TARGET proto_lib)

# 生成grpc的接口
protobuf_generate(
        TARGET proto_lib
        LANGUAGE grpc
        PLUGIN protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>
        PLUGIN_OPTIONS generate_mock_code=true
        GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc)

set(PROTO_LIB_HEADER ${PROJECT_BINARY_DIR}/src/proto PARENT_SCOPE)