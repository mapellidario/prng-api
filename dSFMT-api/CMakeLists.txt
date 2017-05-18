project(dSFMT-api)

add_library(dSFMT-api dSFMT-api.c dSFMT-api.h)
include_directories(${dSFMT_SOURCE_DIR})

set(dSFMT_DEPENDENCIES ${dSFMT_DEPENDENCIES} dSFMT)
target_link_libraries(dSFMT-api ${dSFMT_DEPENDENCIES})
