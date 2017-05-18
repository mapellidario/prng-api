cmake_minimum_required (VERSION 2.6)
project(random-test)

# general settings
# set(CMAKE_BUILD_TYPE Release)
set(DSFMT_MEXP "216091" CACHE STRING "dSFMT exponent")
add_definitions(-DDSFMT_MEXP=${DSFMT_MEXP})

#build libraries
include_directories("${PROJECT_SOURCE_DIR}/dSFMT")
add_subdirectory (dSFMT)
set(DSFMT_EXTRA_LIBS ${DSFMT_EXTRA_LIBS} dSFMT)
include_directories("${PROJECT_SOURCE_DIR}/dSFMT-api")
add_subdirectory (dSFMT-api)
set(DSFMTAPI_EXTRA_LIBS ${DSFMTAPI_EXTRA_LIBS} dSFMT-api)

include_directories("${PROJECT_SOURCE_DIR}/ranlux")
add_subdirectory (ranlux)
set(RANLUX_EXTRA_LIBS ${RANLUX_EXTRA_LIBS} ranlxs ranlxd)
include_directories("${PROJECT_SOURCE_DIR}/ranlux-api")
add_subdirectory (ranlux-api)
set(RANLUXAPI_EXTRA_LIBS ${RANLUXAPI_EXTRA_LIBS} ranlux-api)

# build main
add_executable(api-ov api-ov.c)
target_link_libraries(api-ov ${DSFMT_EXTRA_LIBS} ${DSFMTAPI_EXTRA_LIBS} ${RANLUX_EXTRA_LIBS} ${RANLUXAPI_EXTRA_LIBS} ${CMAKE_CXX_FLAGS_DEBUG})
add_executable(api-ov-bis api-ov-bis.c)
target_link_libraries(api-ov-bis ${DSFMT_EXTRA_LIBS} ${DSFMTAPI_EXTRA_LIBS} ${RANLUX_EXTRA_LIBS} ${RANLUXAPI_EXTRA_LIBS} ${CMAKE_CXX_FLAGS_DEBUG})
add_executable(bench-ram bench-ram.c)
target_link_libraries(bench-ram ${DSFMT_EXTRA_LIBS} ${DSFMTAPI_EXTRA_LIBS} ${RANLUX_EXTRA_LIBS} ${RANLUXAPI_EXTRA_LIBS} ${CMAKE_CXX_FLAGS_DEBUG})
add_executable(bench-disk bench-disk.c)
target_link_libraries(bench-disk ${DSFMT_EXTRA_LIBS} ${DSFMTAPI_EXTRA_LIBS} ${RANLUX_EXTRA_LIBS} ${RANLUXAPI_EXTRA_LIBS} ${CMAKE_CXX_FLAGS_DEBUG})
add_executable(bench-ram-repeat bench-ram-repeat.c)
target_link_libraries(bench-ram-repeat ${DSFMT_EXTRA_LIBS} ${DSFMTAPI_EXTRA_LIBS} ${RANLUX_EXTRA_LIBS} ${RANLUXAPI_EXTRA_LIBS} ${CMAKE_CXX_FLAGS_DEBUG})
add_executable(bench-disk-repeat bench-disk-repeat.c)
target_link_libraries(bench-disk-repeat ${DSFMT_EXTRA_LIBS} ${DSFMTAPI_EXTRA_LIBS} ${RANLUX_EXTRA_LIBS} ${RANLUXAPI_EXTRA_LIBS} ${CMAKE_CXX_FLAGS_DEBUG})

# install
install(TARGETS api-ov DESTINATION bin)
install(TARGETS api-ov-bis DESTINATION bin)
install(TARGETS bench-ram DESTINATION bin)
install(TARGETS bench-disk DESTINATION bin)
install(TARGETS bench-disk-repeat DESTINATION bin)
install(TARGETS bench-ram-repeat DESTINATION bin)
