#include <iostream>
#include "Patterns.hpp"

int main()
{
	// Factory method
    FileOutputterFactory outputterFactory;
    auto linuxFileOtputter = outputterFactory.createFileOutputter(SystemType::LINUX);
	
	// Dependency injection
	FilesWorker fileWorker(std::move(linuxFileOtputter));
	fileWorker.write("BabePath", "Hello, world");

	return 0;
}
