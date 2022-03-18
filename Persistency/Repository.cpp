#include "Persistency/Repository.h"
#include <assert.h>
#include <sstream>
#include <algorithm>

Repository::Repository() :
	elementsArray {std::vector<Dog>()}
{
}

Repository::Repository(size_t maxSize) :
	elementsArray { std::vector<Dog>(maxSize)}
{
}

Repository::~Repository()
{
}

const Dog& Repository::operator[](size_t position)
{
	return elementsArray[position];
}

bool Repository::operator==(const Repository& other) const
{
	return elementsArray == other.elementsArray;
}

void Repository::AddElement(const Dog& newDog)
{
	elementsArray.push_back(newDog);
    std::sort(elementsArray.begin(), elementsArray.end(), [](const Dog& d1, const Dog& d2) -> bool
    {
        return d1.GetName() <= d2.GetName();
    });
}

void Repository::RemoveElement(size_t position)
{
	elementsArray.erase(elementsArray.begin() + position);
}

int Repository::FindElement(const Dog& dog) const
{
	auto i = std::find(elementsArray.begin(), elementsArray.end(), dog);
	if (i == elementsArray.end())
		return -1;
	return i - elementsArray.begin();
}

void Repository::UpdateElementName(size_t position, std::string newName)
{
	elementsArray[position].SetName(newName);
}

void Repository::UpdateElementBreed(size_t position, std::string newBreed)
{
	elementsArray[position].SetBreed(newBreed);
}

void Repository::UpdateElementAge(size_t position, size_t newAge)
{
	elementsArray[position].SetAge(newAge);
}

void Repository::UpdateElementPhotograph(size_t position, std::string newPhotograph)
{
    elementsArray[position].SetPhotograph(newPhotograph);
}

void Repository::UpdateAllAttributes(size_t position, std::string newName, std::string newBreed, size_t newAge, std::string newPhoto)
{
    UpdateElementName(position, newName);
    UpdateElementBreed(position, newBreed);
    UpdateElementAge(position, newAge);
    UpdateElementPhotograph(position, newPhoto);
}

size_t Repository::GetSize() const
{
	return elementsArray.size();
}

const std::vector<Dog>& Repository::GetArray() const
{
	return elementsArray;
}

std::ostream& operator<<(std::ostream& os, const Repository& repo)
{
//	TextTable t;

//	t.add("Name");
//	t.add("Age");
//	t.add("Breed");
//	t.add("Photograph");
//	t.endOfRow();

//	for (const Dog& d : repo.elementsArray)
//	{
//		t.add(d.GetName());
//		t.add(std::to_string(d.GetAge()));
//		t.add(d.GetBreed());
//		t.add(d.GetPhotograph());
//		t.endOfRow();
//	}

//	return os << t;
}

void RepositoryTests::TestAll()
{
	TestConstructorsAndAssignment();
	TestAdd();
	TestRemoveSubscript();
	TestUpdate();
	TestFind();
	//TestPrint();
}

void RepositoryTests::TestConstructorsAndAssignment()
{
	Repository repo1;
	assert(repo1.GetSize() == 0);

	Repository repo2(10);
	assert(repo2.GetSize() == 10);

	repo2.AddElement(Dog("Beagle", "Ion", 5, "dogs.ro"));
	repo1 = repo2;

	assert(repo1.elementsArray == repo2.elementsArray);
}

void RepositoryTests::TestAdd()
{
	Repository repo2;
	Dog d1("Idk", "Idk", 1, "google.com");
	Dog d2("Idk", "Idk1", 1, "google.com");
	Dog d3("Idk", "Idk2", 1, "google.com");
	Dog d4("Idk", "Idk3", 1, "google.com");
	repo2.AddElement(d1);
	repo2.AddElement(d2);
	repo2.AddElement(d3);
	repo2.AddElement(d4);

	assert(repo2[0] == d1);
	assert(repo2[1] == d2);
	assert(repo2[2] == d3);
	assert(repo2[3] == d4);
}

void RepositoryTests::TestRemoveSubscript()
{
	Repository repo2;
	Dog d1("Idk", "Idk", 1, "google.com");
	Dog d2("Idk", "Idk1", 1, "google.com");
	Dog d3("Idk", "Idk2", 1, "google.com");
	Dog d4("Idk", "Idk3", 1, "google.com");
	repo2.AddElement(d1);
	repo2.AddElement(d2);
	repo2.AddElement(d3);
	repo2.AddElement(d4);

	repo2.RemoveElement(1);

	assert(repo2[0] == d1);
	assert(repo2[1] == d3);
	assert(repo2[2] == d4);
}

void RepositoryTests::TestUpdate()
{
	Repository repo2;
	Dog d1("Idk", "Idk", 1, "google.com");
	repo2.AddElement(d1);

	repo2.UpdateElementAge(0, 2);
	assert(repo2[0].GetAge() == 2);
	repo2.UpdateElementName(0, "Ion");
	assert(repo2[0].GetName() == "Ion");
	repo2.UpdateElementBreed(0, "Beagle");
	assert(repo2[0].GetBreed() == "Beagle");
	repo2.UpdateElementPhotograph(0, "dogs.com");
	assert(repo2[0].GetPhotograph() == "dogs.com");
}

void RepositoryTests::TestFind()
{
	Repository repo2;
	Dog d1("Idk", "Idk", 1, "google.com");
	Dog d2("Idk", "Idk1", 1, "google.com");
	Dog d3("Idk", "Idk2", 1, "google.com");
	Dog d4("Idk", "Idk3", 1, "google.com");
	repo2.AddElement(d1);
	repo2.AddElement(d2);
	repo2.AddElement(d3);
	repo2.AddElement(d4);

	size_t position = repo2.FindElement(d3);
	assert(position == 2);

	size_t position2 = repo2.FindElement(Dog("d1", "d1", 1, "google.com"));
	assert(position2 == -1);
}

void RepositoryTests::TestPrint()
{
	Repository repo2;
	Dog d1("Beagle", "Ion", 1, "google.com");
	repo2.AddElement(d1);
	Dog d2("Husky", "Charlie", 2, "dogs.ro");
	repo2.AddElement(d2);

	std::stringbuf buffer;
	std::ostream os(&buffer);
	os << repo2;
	assert(buffer.str() == "Ion 1 Beagle google.com\nCharlie 2 Husky dogs.ro\n");
}

RepositoryException::RepositoryException(const std::string& message) :
	message{ message }
{
}

const char* RepositoryException::what() const noexcept
{
	return message.c_str();
}
