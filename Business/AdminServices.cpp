#include "Business/AdminServices.h"
#include <exception>
#include <assert.h>
#include <fstream>

AdminServices::AdminServices(Repository& repo) :
	repository { repo }
{
}


void AdminServices::AddDog(std::string breed, std::string name, size_t age, std::string photograph)
{
	if (!Validator::ValidDogAttributes(breed, name, age, photograph)) throw ValidatorException("Invalid dog parameters!");

	Dog newDog = Dog(breed, name, age, photograph);

	int found = repository.FindElement(newDog);

	if (found != -1) throw RepositoryException("A dog with the given name already exists!");
	this->repository.AddElement(newDog);
}

void AdminServices::RemoveDog(size_t position)
{
	if (position >= this->repository.GetSize()) throw RepositoryException("Outside of the bounds of the array!");

	this->repository.RemoveElement(position);
}

void AdminServices::UpdateDogName(size_t position, std::string newName)
{
	if (position >= this->repository.GetSize()) throw RepositoryException("Outside of the bounds of the array!");

	if (!Validator::ValidDogName(newName)) throw ValidatorException("Invalid dog name!");

	this->repository.UpdateElementName(position, newName);
}

void AdminServices::UpdateDogBreed(size_t position, std::string newBreed)
{
	if (position >= this->repository.GetSize()) throw RepositoryException("Outside of the bounds of the array!");

	if (!Validator::ValidDogBreed(newBreed)) throw ValidatorException("Invalid dog breed!");

	this->repository.UpdateElementBreed(position, newBreed);
}

void AdminServices::UpdateDogAge(size_t position, size_t newAge)
{
	if (position >= this->repository.GetSize()) throw RepositoryException("Outside of the bounds of the array!");

	if (!Validator::ValidDogAge(newAge)) throw ValidatorException("Invalid dog age!");

	this->repository.UpdateElementAge(position, newAge);
}

void AdminServices::UpdateDogPhotograph(size_t position, std::string newPhotograph)
{
	if (position >= this->repository.GetSize()) throw RepositoryException("Outside of the bounds of the array!");

	if (!Validator::ValidDogPhotograph(newPhotograph)) throw ValidatorException("Invalid dog photograph!");

    this->repository.UpdateElementPhotograph(position, newPhotograph);
}

void AdminServices::UpdateAllAttributes(size_t position, std::string newName, std::string newBreed, size_t newAge, std::string newPhoto)
{
    UpdateDogName(position, newName);
    UpdateDogBreed(position, newBreed);
    UpdateDogAge(position, newAge);
    UpdateDogPhotograph(position, newPhoto);
}

Repository& AdminServices::GetRepo() const
{
	return this->repository;
}


void AdminServices::InitializeRepo()
{
	AddDog("Golden_Retriever", "Rex", 1, "https://google.ro");
	AddDog("Beagle", "Bob", 2, "https://google.com");
	AddDog("Dalmatian", "Ted", 5, "https://google.com");
	AddDog("Shiba_Inu", "Gigel", 3, "https://google.com");
	AddDog("Husky", "Ace", 6, "https://google.com");
	AddDog("Schnauzer", "Jax", 4, "photo.ro");
	AddDog("Pug", "Samson", 3, "https://dogs.com/photos/1");
	AddDog("Husky", "Chase", 2, "https://dogs.com/photos/2");
	AddDog("Dalmatian", "Leo", 5, "https://dogs.com/photos/3");
	AddDog("Schnauzer", "Duke", 6, "https://dogs.com/photos/4");
}

void AdminServicesTests::TestAll()
{
	TestConstructors();
	TestAdd();
	TestRemove();
	TestUpdate();
}

void AdminServicesTests::TestConstructors()
{
	FileRepository repo("test.txt");
	AdminServices s2(repo);
	assert(s2.repository.GetSize() == 0);

	assert(s2.GetRepo() == repo);
}

void AdminServicesTests::TestAdd()
{
	FileRepository repo("test.txt");

	AdminServices s2(repo);
	s2.AddDog("Beagle", "Rex", 5, "dogs.ro");

    assert(s2.repository[0].GetName() == "Rex");
    assert(s2.repository[0].GetBreed() == "Beagle");
	assert(s2.repository[0].GetAge() == 5);
	assert(s2.repository[0].GetPhotograph() == "dogs.ro");

	s2.AddDog("Husky", "Ted", 3, "dogs.ro");
	assert(s2.repository[1].GetName() == "Ted");
	assert(s2.repository[1].GetBreed() == "Husky");
	assert(s2.repository[1].GetAge() == 3);
	assert(s2.repository[1].GetPhotograph() == "dogs.ro");

	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void AdminServicesTests::TestRemove()
{
	FileRepository repo("test.txt");

	AdminServices s2(repo);
	s2.InitializeRepo();
	s2.RemoveDog(2);

    assert(s2.repository[0].GetName() == "Ace");
    assert(s2.repository[0].GetBreed() == "Husky");
    assert(s2.repository[0].GetAge() == 6);
    assert(s2.repository[0].GetPhotograph() == "https://google.com");

	assert(s2.repository[1].GetName() == "Bob");
	assert(s2.repository[1].GetBreed() == "Beagle");
	assert(s2.repository[1].GetAge() == 2);
	assert(s2.repository[1].GetPhotograph() == "https://google.com");

    assert(s2.repository[2].GetName() == "Duke");
    assert(s2.repository[2].GetBreed() == "Schnauzer");
    assert(s2.repository[2].GetAge() == 6);
    assert(s2.repository[2].GetPhotograph() == "https://dogs.com/photos/4");

	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void AdminServicesTests::TestUpdate()
{
	FileRepository repo("test.txt");

	AdminServices s2(repo);
	s2.AddDog("Beagle", "Rex", 5, "dogs.ro");

	assert(s2.repository[0].GetName() == "Rex");
	assert(s2.repository[0].GetBreed() == "Beagle");
	assert(s2.repository[0].GetAge() == 5);
	assert(s2.repository[0].GetPhotograph() == "dogs.ro");

	s2.UpdateDogAge(0, 2);
	assert(s2.repository[0].GetAge() == 2);
	s2.UpdateDogName(0, "Ted");
	assert(s2.repository[0].GetName() == "Ted");
	s2.UpdateDogBreed(0, "Shiba_Inu");
	assert(s2.repository[0].GetBreed() == "Shiba_Inu");
	s2.UpdateDogPhotograph(0, "dogs.ro");
	assert(s2.repository[0].GetPhotograph() == "dogs.ro");

	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}
