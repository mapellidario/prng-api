project(ranlux-api)

add_library(ranlux-api ranlux-api.c ranlux-api.h)
include_directories(${ranlux_SOURCE_DIR})

set(RANLUXAPI_DEPENDENCIES ${RANLUXAPI_DEPENDENCIES} ranlxd ranlxs)
target_link_libraries(ranlux-api ${RANLUXAPI_DEPENDENCIES})
