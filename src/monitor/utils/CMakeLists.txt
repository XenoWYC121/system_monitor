
aux_source_directory(./ SRC)

add_library(monitor_utils OBJECT ${SRC} ${HEADERS})

set(ALL_UTILS_OBJECTS ${ALL_UTILS_OBJECTS};$<TARGET_OBJECTS:monitor_utils> PARENT_SCOPE)