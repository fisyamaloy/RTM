set(TARGET Caching)

set(SOURCE_FILES
   MainTests.cpp
   CachingCRTP.hpp)

add_executable(${TARGET} ${SOURCE_FILES})

target_link_libraries(${TARGET} PRIVATE ${EXTRA_LIBS} CONAN_PKG::gtest)
