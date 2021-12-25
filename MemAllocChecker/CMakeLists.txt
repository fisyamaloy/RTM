set(TARGET MemAllocChecker)

set(SOURCE_FILES
   main.cpp
   MemAllocChecker.hpp)

add_executable(${TARGET} ${SOURCE_FILES})

target_include_directories(${TARGET} PRIVATE
    $<TARGET_PROPERTY:DanilsVector,SOURCE_DIR>/..)
