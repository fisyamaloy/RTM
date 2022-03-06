#pragma once
#include <memory>
#include <string_view>

namespace FactoryParttern
{
    struct IFileOutputter
    {
        virtual void writeMessage([[maybe_unused]] std::string_view filePath,
                                  [[maybe_unused]] std::string_view message) const = 0;

        virtual ~IFileOutputter() = default;
    };

    struct WindowsFileOutputter : IFileOutputter
    {
        WindowsFileOutputter()                       = default;
        WindowsFileOutputter(WindowsFileOutputter&&) = default;
        ~WindowsFileOutputter()                      = default;

        void writeMessage([[maybe_unused]] std::string_view filePath,
                          [[maybe_unused]] std::string_view message) const override
        {
            // Specific code for windows-system
        }
    };

    struct LinuxFileOutputter : IFileOutputter
    {
        LinuxFileOutputter()                     = default;
        LinuxFileOutputter(LinuxFileOutputter&&) = default;
        ~LinuxFileOutputter()                    = default;

        void writeMessage([[maybe_unused]] std::string_view filePath,
                          [[maybe_unused]] std::string_view message) const override
        {
            // Specific code for Linux-system
        }
    };

    enum class SystemType
    {
        WINDOWS,
        LINUX
    };

    struct FileOutputterFactory
    {
        std::unique_ptr<IFileOutputter> createFileOutputter(const SystemType systemType) const
        {
            switch (systemType)
            {
                case SystemType::WINDOWS:
                {
                    return std::make_unique<WindowsFileOutputter>();
                }
                case SystemType::LINUX:
                {
                    return std::make_unique<LinuxFileOutputter>();
                }
                default:
                {
                    return std::make_unique<LinuxFileOutputter>();
                }
            }
        }
    };

}  // namespace FactoryParttern
