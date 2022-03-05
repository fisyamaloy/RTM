set(TARGET Multithreading)

set(SOURCE_FILES
   main.cpp
   Asynchrony.hpp)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(${TARGET} ${SOURCE_FILES})
target_link_libraries(${TARGET} Threads::Threads)
