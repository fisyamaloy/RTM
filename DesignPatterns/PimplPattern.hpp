#pragma once
#include <memory>
#include <string_view>

namespace PimplPattern
{
    struct FileWorker
    {
    private:
        struct FileOutputter;
        std::unique_ptr<FileOutputter> fileOutputter;

    public:
        FileWorker();
        FileWorker(FileWorker&&) noexcept;
        ~FileWorker() noexcept;
        
        virtual void outputMessage([[maybe_unused]] std::string_view path,
                                   [[maybe_unused]] std::string_view text);
    };

};  // namespace PimplPattern
