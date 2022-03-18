#pragma once
#include "Domain/Dog.h"
#include <exception>

class ValidatorException : public std::exception
{
public:
	ValidatorException(const std::string& message);
	const char* what() const noexcept override;
private:
	std::string message;
};

class Validator
{
public:
	static bool ValidDogAttributes(std::string breed, std::string name, size_t age, std::string photograph);
	static bool ValidDogBreed(std::string breed);
	static bool ValidDogName(std::string name);
	static bool ValidDogAge(size_t age);
	static bool ValidDogPhotograph(std::string photograph);
};
