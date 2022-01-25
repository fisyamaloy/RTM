#include <filesystem>
#include <fstream>
#include <vector>

// Filesystem is a crossplatform library which allows working with files and folders
namespace file_system_examples
{
    namespace fs = std::filesystem;

    void example_1()
    {
        // Path to executable file
        std::cout << fs::current_path() << std::endl;

        const auto disc_c  = fs::path("C:");
        const auto space_c = fs::space(disc_c);

        // Total size in bytes
        std::cout << "Total: " << space_c.capacity / 1024 / 1024 / 1024 << " GB" << std::endl;
        // Free size in bytes
        std::cout << "Free: " << space_c.free / 1024 / 1024 / 1024 << " GB" << std::endl;
        // Free size which available for user
        std::cout << "Available: " << space_c.available / 1024 / 1024 / 1024 << " GB" << std::endl;

        endl(std::cout);
    }

    void example_2()
    {
        const fs::path filePath =
            "C:\\Users\\Danil_Fisiuk\\source\\repos\\RTM\\Standart_17\\Examples\\Inlet.txt";

        std::cout << "Path to file " << filePath << std::endl;
        std::cout << "Parent path " << filePath.parent_path() << std::endl;
        std::cout << "Filename " << filePath.filename() << std::endl;
        std::cout << "Extension " << filePath.extension() << std::endl;

        std::cout << "Separator in my OS is " << fs::path::preferred_separator << std::endl;

        const fs::path root      = "C:\\";
        const fs::path  dir       = "Danil_Fisiuk\\source\\repos\\RTM\\Standart_17\\Examples";
        const fs::path  inputFile = "Inlet.txt";

        // We can format pathes using path-objects
        const auto pathInputFIle = root / dir / inputFile;
        std::cout << pathInputFIle << std::endl;

        std::cout << std::endl;
    }

    // Creating directories
    void example_3() 
    {
        const auto currentPath = fs::current_path();

        fs::create_directory(currentPath / "Fisya");
        fs::create_directories(currentPath / "Fisya" / "a");
        fs::create_directories(currentPath / "Fisya" / "b");
        fs::create_directories(currentPath / "Fisya" / "b" / "bb_1");
        fs::create_directories(currentPath / "Fisya" / "b" / "bb_2");
        std::cout << "Directories created!\n";

        std::cout << std::endl;
    }

    // Removing directories
    void example_4()
    {
        const auto currentPath = fs::current_path();

        fs::remove(currentPath / "Fisya" / "b" / "bb_1");
        fs::remove_all(currentPath / "Fisya" / "b");
        std::cout << "Directories removed!\n";

        std::cout << std::endl;
    }

    template<class... Extention>
    std::vector<fs::path> getDirFilesByExtFilter(const fs::path& dirPath, Extention&&... exts) 
    {
        const auto dirIter     = fs::directory_iterator(dirPath);
        const auto filesAmount = std::count_if(begin(dirIter), end(dirIter), 
                                 [](const auto& file) { return file.is_regular_file(); });

        size_t i = 0;
        std::vector<fs::path> files(filesAmount);
        for (auto&& entry : fs::recursive_directory_iterator(dirPath))
        {
            if (fs::is_regular_file(entry))
            {
                const bool fileExtMatchesFilter = ((entry.path().extension().string() == exts) || ...);
                if (fileExtMatchesFilter)
                {
                    files[i++] = entry.path();
                }
            }
        }
        files.resize(i);
        
        return files;
    }

    std::vector<fs::path> getDirFilesByExtFilter(const fs::path& dirPath)
    {
        const auto dirIter     = fs::directory_iterator(dirPath);
        const auto filesAmount = std::count_if(begin(dirIter), end(dirIter), 
                                 [](const auto& file) { return file.is_regular_file(); });
        std::vector<fs::path> files(filesAmount);
        size_t i = 0;
        for (auto&& entry : fs::recursive_directory_iterator(dirPath))
        {
            if (fs::is_regular_file(entry))
            {
                files[i++] = entry.path();
            }
        }

        return files;
    }

    template <class... T>
    void createFiles(const fs::path& path, T&&... args)
    {
        auto createFile = [&path](const char fileName[]) {
            std::ofstream file(path / fileName);
            file << "\n";
            file.close();
        };

        (createFile(args), ...);
    }

    void example_5() 
    {
        const auto path = fs::current_path() / "Fisya";
        fs::create_directory(path);
        createFiles(path, "file_1.txt", "file_2.in", "file_3.png", "file_4.png", "file_5.mp3",
                    "file_6.mp3", "file_7.mp3");
    
        const auto files = getDirFilesByExtFilter(path, ".mp3", ".png");
        for (auto&& file : files)
        {
            std::cout << file.filename() << " ";
        }

        std::cout << std::endl;
    }

}  // namespace file_system_examples
