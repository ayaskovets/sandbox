set(TARGET matrix_views)
set(INCLUDE include)

add_library(${TARGET} INTERFACE)
target_include_directories(${TARGET}
    INTERFACE ${INCLUDE})

add_subdirectory(tests)
