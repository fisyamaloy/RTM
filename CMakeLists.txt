cmake_minimum_required(VERSION 3.17.0)

project(RTM)

# Global settings. Should probably be moved to a separate file later.
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CXX_EXTENSIONS off)

# For those VSCode users
set(EXPORT_COMPILE_COMMANDS TRUE)

# Set warnings level higher and force treating them as errors.
# GCC TBD
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/master/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake" TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)


conan_cmake_run(CONANFILE conanfile.txt
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

enable_testing()

add_subdirectory(CustomKeyForHash)
add_subdirectory(ADLExample)
add_subdirectory(Standart_17)
add_subdirectory(DesignPatterns)
add_subdirectory(Multythreading)
add_subdirectory(Danils)
add_subdirectory(Caching)
