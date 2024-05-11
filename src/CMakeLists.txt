add_subdirectory(proto)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${PROTO_LIB_HEADER})

# message(WARNING "${PROTO_LIB_HEADER}")

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

add_subdirectory(monitor)

add_subdirectory(service)