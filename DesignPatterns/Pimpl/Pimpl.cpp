#include "Pimpl.hpp"
#include <iostream>

struct PimplPattern::FileWorker::FileOutputter
{
    void outputMessage([[maybe_unused]] std::string_view path,
                       [[maybe_unused]] std::string_view text)
    {
#ifdef _WIN32
        std::cout << "Windows - path: " << path << " text: " << text << std::endl;
#elif __linux__
        std::cout << "Linux - path: " << path << " text: " << text << std::endl;
#endif
    }
};

PimplPattern::FileWorker::FileWorker() : fileOutputter(new FileOutputter()) {}

PimplPattern::FileWorker::FileWorker(FileWorker&&) noexcept = default;

PimplPattern::FileWorker::~FileWorker() noexcept = default;

void PimplPattern::FileWorker::outputMessage([[maybe_unused]] std::string_view path,
                                             [[maybe_unused]] std::string_view text)
{
    fileOutputter->outputMessage(path, text);
}
