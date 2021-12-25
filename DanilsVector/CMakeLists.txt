set(TARGET DanilsVector)

set(SOURCE_FILES
   main.cpp
   Vector.hpp
   VectorException.hpp)

add_executable(${TARGET} ${SOURCE_FILES})

target_link_libraries(${TARGET} PRIVATE ${EXTRA_LIBS} CONAN_PKG::gtest)

target_include_directories(${TARGET} PRIVATE
    $<TARGET_PROPERTY:MemAllocChecker,SOURCE_DIR>/..)
