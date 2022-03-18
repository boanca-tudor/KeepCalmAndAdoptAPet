#include "Validation/Validator.h"
#include <regex>

bool Validator::ValidDogAttributes(std::string breed, std::string name, size_t age, std::string photograph)
{
	return ValidDogBreed(breed) && ValidDogName(name) && ValidDogAge(age) && ValidDogPhotograph(photograph);
}

bool Validator::ValidDogBreed(std::string breed)
{
	return !breed.empty();
}

bool Validator::ValidDogName(std::string name)
{
	return !name.empty();
}

bool Validator::ValidDogAge(size_t age)
{
	return age <= 30;
}

bool Validator::ValidDogPhotograph(std::string photograph)
{
	return std::regex_match(photograph, std::regex("(^https:\/\/)?([a-zA-Z])+\.([a-z]{2,})(\/(.)+)?"));
}

ValidatorException::ValidatorException(const std::string& message) :
	message {message}
{
}

const char* ValidatorException::what() const noexcept
{
	return message.c_str();
}
