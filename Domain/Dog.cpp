#include "Domain/Dog.h"
#include <assert.h>
#include <sstream>

Dog::Dog() :
	breed{ "" }, name{ "" }, age{ 0 }, photograph{ "" }
{
}

Dog::Dog(std::string breed, std::string name, size_t age, std::string photograph) :
	breed { breed }, name { name }, age { age }, photograph { photograph }
{
}

Dog::~Dog()
{
}

std::string Dog::GetBreed() const
{
	return this->breed;
}

std::string Dog::GetName() const
{
	return this->name;
}

size_t Dog::GetAge() const
{
	return this->age;
}

std::string Dog::GetPhotograph() const
{
	return this->photograph;
}

void Dog::SetBreed(std::string newBreed)
{
	this->breed = newBreed;
}

void Dog::SetName(std::string newName)
{
	this->name = newName;
}

void Dog::SetAge(size_t newAge)
{
	this->age = newAge;
}

void Dog::SetPhotograph(std::string newPhotograph)
{
	this->photograph = newPhotograph;
}

bool Dog::operator==(const Dog& other) const
{
	return this->name == other.name && this->age == other.age && this->breed == other.breed && this->photograph == other.photograph;
}

std::ostream& operator<<(std::ostream& os, const Dog& dog)
{
	return os << dog.name << " " << dog.age << " " << dog.breed << " " << dog.photograph << '\n';
}

std::istream& operator>>(std::istream& is, Dog& dog)
{
	return is >> dog.name >> dog.age >> dog.breed >> dog.photograph;
}

void DogTests::TestAllDog()
{
	TestConstructorsAndGettersDog();
	TestSettersDog();
	TestEqualityDog();
	TestExtractionOperator();
}

void DogTests::TestConstructorsAndGettersDog()
{
	Dog d1;
	assert(d1.GetName() == "");
	assert(d1.GetBreed() == "");
	assert(d1.GetPhotograph() == "");
	assert(d1.GetAge() == 0);

	Dog d2("Something", "Ion", 2, "google.com");
	assert(d2.GetName() == "Ion");
	assert(d2.GetBreed() == "Something");
	assert(d2.GetPhotograph() == "google.com");
	assert(d2.GetAge() == 2);
}

void DogTests::TestSettersDog()
{
	Dog d1;
	d1.SetName("Ion");
	d1.SetBreed("Something");
	d1.SetAge(1);
	d1.SetPhotograph("site.ro");

	assert(d1.GetName() == "Ion");
	assert(d1.GetBreed() == "Something");
	assert(d1.GetPhotograph() == "site.ro");
	assert(d1.GetAge() == 1);
}

void DogTests::TestEqualityDog()
{
	Dog d1;
	d1.SetName("Ion");
	d1.SetBreed("Something");
	d1.SetAge(1);
	d1.SetPhotograph("site.ro");

	Dog d2;
	d2.SetName("Ion");
	d2.SetBreed("Something");
	d2.SetAge(1);
	d2.SetPhotograph("site.ro");

	assert(d1 == d2);
	d2.SetName("Gigel");
	assert(!(d1 == d2));
}

void DogTests::TestExtractionOperator()
{
	Dog d1;
	d1.SetName("Ion");
	d1.SetBreed("Something");
	d1.SetAge(1);
	d1.SetPhotograph("site.ro");
	std::stringbuf buffer; 
	std::ostream os(&buffer);
	os << d1; 
	assert(buffer.str() == "Ion 1 Something site.ro\n");
}
