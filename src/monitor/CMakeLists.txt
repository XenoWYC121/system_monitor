
add_subdirectory(utils)

aux_source_directory(./ SRC)

add_library(monitor ${SRC} ${HEADERS} ${ALL_UTILS_OBJECTS})