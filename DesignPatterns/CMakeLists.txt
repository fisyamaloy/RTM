set(TARGET DesignPatterns)

set(SOURCE_FILES
   main.cpp
   Pimpl/Pimpl.hpp
   Pimpl/Pimpl.cpp
   Factory/Factory.hpp)

add_executable(${TARGET} ${SOURCE_FILES})
