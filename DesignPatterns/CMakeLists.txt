set(TARGET DesignPatterns)

set(SOURCE_FILES
   main.cpp
   Patterns.hpp
   PimplPattern.hpp
   PimplPattern.cpp
   PimplFileOutputter.hpp)

add_executable(${TARGET} ${SOURCE_FILES})
