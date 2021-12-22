#pragma once
#include <exception>

namespace Danils
{
class VectorException : public std::exception
{
public:
    enum class ErrorsCodes
    {
        OUT_OF_RANGE       = -1,
        CONTAINER_IS_EMPTY = 1,
    };

    VectorException(const ErrorsCodes dataState) { this->mDataState = dataState; }

    const char* what() const override
    {
        switch (mDataState)
        {
            case ErrorsCodes::OUT_OF_RANGE:
                return "Out of range, buddy";
            case ErrorsCodes::CONTAINER_IS_EMPTY:
                return "Vector is empty, boy";
            default:
                return "Unknown state, man";
        }
    }

private:
    ErrorsCodes mDataState;
};
}  // namespace Danils
