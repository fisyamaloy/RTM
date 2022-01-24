#include <filesystem>

// Filesystem is a crossplatform library which allows working with files and folders
namespace file_system_examples
{
	namespace fs = std::filesystem;

	void example_1() 
	{
		// Path to executable file
		std::cout << fs::current_path() << std::endl;

		auto disc_c = fs::path("C:");
        auto space_c = fs::space(disc_c);
		
		// Total size in bytes
        std::cout << "Total: " << space_c.capacity / 1024 / 1024 / 1024 << " GB" << std::endl;
        // Free size in bytes
        std::cout << "Free: " << space_c.free / 1024 / 1024 / 1024 << " GB" << std::endl;
        // Free size which available for user
        std::cout << "Available: " << space_c.available / 1024 / 1024 / 1024 << " GB" << std::endl;

		endl(std::cout);
	}
}
