cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "5" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(allocHomeWork VERSION ${PROJECT_VESRION})

add_executable(test_alloc main.cpp)
add_library(alloc_lib lib.cpp)

set_target_properties(alloc_lib test_alloc PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(alloc_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(test_alloc
alloc_lib
)

if (MSVC)
    target_compile_options(alloc_lib PRIVATE
        /W4
    )
    target_compile_options(test_alloc PRIVATE
        /W4
    )
else ()
    target_compile_options(alloc_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_alloc PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS test_alloc RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "NN")
include(CPack)
