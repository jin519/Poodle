#pragma once

#include <string>
#include <exception>

class TextureException : public std::exception 
{
public:
    /* constructor */
    TextureException(const std::string& message) noexcept;

    /* member function */
    virtual const char* what() const noexcept override;

private:
    /* member variable */
    const std::string __message;
};