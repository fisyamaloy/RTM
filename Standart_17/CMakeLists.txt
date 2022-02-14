set(TARGET Standart_17)

set(SOURCE_FILES
   main.cpp
   Examples.hpp)

add_executable(${TARGET} ${SOURCE_FILES})

add_subdirectory(Examples)
