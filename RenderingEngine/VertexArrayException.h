#pragma once

#include <string>
#include <exception>

class VertexArrayException : public std::exception 
{
public:
	/* constructor */
	VertexArrayException(const std::string& message) noexcept;

	/* member function */
	virtual const char* what() const noexcept override;

	/* member variable */
	const std::string __message;
};