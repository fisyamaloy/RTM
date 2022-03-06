#include <iostream>
#include "Patterns.hpp"

int main()
{
	// Factory method
    FactoryParttern::FileOutputterFactory outputterFactory;
    auto linuxFileOtputter = 
		outputterFactory.createFileOutputter(FactoryParttern::SystemType::LINUX);
	
	// Dependency injection
	DIPattern::FilesWorker fileWorker(std::move(linuxFileOtputter));
	fileWorker.write("BabePath", "Hello, world");

	PimplPattern::FileWorker fw;
    fw.outputMessage("path", "string");

	return 0;
}
