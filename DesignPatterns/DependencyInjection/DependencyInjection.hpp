#pragma once
#include <memory>
#include <string_view>
#include "../Factory/Factory.hpp"

namespace DIPattern
{
    struct FilesWorker
    {
        FilesWorker(std::unique_ptr<FactoryParttern::IFileOutputter> fileOutputter)
        {
            this->fileOutputter = std::move(fileOutputter);
        }

        void write(std::string_view path, std::string_view text)
        {
            fileOutputter->writeMessage(path, text);
        }

    private:
        std::unique_ptr<FactoryParttern::IFileOutputter> fileOutputter;
    };
}  // namespace DIPattern
