cmake_minimum_required(VERSION 3.1)
project(libpascalreal LANGUAGES C)

include(CTest)
find_package(PkgConfig REQUIRED)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS NO)

if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU"
        OR ${CMAKE_C_COMPILER_ID} MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Werror -pedantic-errors)
elseif(MSVC)
    add_compile_options(/W4 /WX)
endif()

pkg_check_modules(LIBCHECK REQUIRED check)
add_executable(libpascalreal_test libpascalreal.c test.c)
target_include_directories(libpascalreal_test PRIVATE ${LIBCHECK_INCLUDE_DIRS})
target_link_directories(libpascalreal_test PRIVATE ${LIBCHECK_LIBRARY_DIRS})
target_link_libraries(libpascalreal_test PRIVATE ${LIBCHECK_LIBRARIES} ${LIBCHECK_LDFLAGS})

add_test(NAME PascalRealTest COMMAND libpascalreal_test)
