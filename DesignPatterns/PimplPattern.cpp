#include "PimplPattern.hpp"
#include "PimplFileOutputter.hpp"

PimplPattern::FileWorker::FileWorker() : fileOutputter(new FileOutputter()) {}

PimplPattern::FileWorker::FileWorker(FileWorker&&) noexcept = default;

PimplPattern::FileWorker::~FileWorker() noexcept = default;

void PimplPattern::FileWorker::outputMessage([[maybe_unused]] std::string_view path,
                                             [[maybe_unused]] std::string_view text)
{
    fileOutputter->outputMessage(path, text);
}
