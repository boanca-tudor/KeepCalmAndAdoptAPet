#include "Business/UserServices.h"
#include <exception>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <fstream>

UserServices::UserServices(Repository& repo) :
	repo { repo },
	currentDogList{ repo.GetArray() },
	adoptionList { AdoptionList() },
	writer { nullptr },
	index {0},
	writeMode {""}
{
}

UserServices::UserServices(Repository& repo, const std::string& writeMode) :
	repo{ repo },
	currentDogList{ repo.GetArray() },
	adoptionList{ AdoptionList() },
	writer { nullptr },
	index{ 0 },
	writeMode { writeMode }
{
}

UserServices::~UserServices()
{
	delete writer;
}

void UserServices::AddToAdoptionList(const Dog& dog)
{
	adoptionList.AddDog(dog);
	GoToNextDog();
}

void UserServices::GoToNextDog()
{
	if (index == currentDogList.size() - 1)
	{
		index = 0;
		return;
	}
	index++;
}

void UserServices::FilterByBreedAndAge(std::string breed, size_t age)
{
	std::vector<Dog> newList(currentDogList.size());

	auto it = std::copy_if(currentDogList.begin(), currentDogList.end(), newList.begin(),
		[breed, age](const Dog& dog) 
		{
			if (breed == "")
				return dog.GetAge() < age;
			return dog.GetBreed() == breed && dog.GetAge() < age; 
		}
	);
	
	newList.resize(it - newList.begin());

	currentDogList = newList;

	index = 0;
}

const AdoptionList& UserServices::GetAdoptionList() const
{
	return adoptionList;
}

const Dog& UserServices::GetCurrentDog() const
{
	return currentDogList[index];
}

const std::string& UserServices::GetFileName() const
{
	return writer->GetFileName();
}

const std::string& UserServices::GetWriteMode() const
{
	return writeMode;
}

void UserServices::SetWriteMode(const std::string& newMode)
{
	if (newMode == "CSV")
	{
		writeMode = newMode;
		writer = new CSVAdoptionListWriter("adoption_list.csv");
	}
	else if (newMode == "HTML")
	{
		writeMode = newMode;
		writer = new HTMLAdoptionListWriter("adoption_list.html");
	}
    else if (newMode == "InApp")
    {
        writeMode = newMode;
    }
	else
	{
        throw std::exception();
	}
}

void UserServices::ReinitializeDogList()
{
	if (currentDogList == repo.GetArray())
		return;
	currentDogList = repo.GetArray();
	index = 0;
}

void UserServices::WriteData()
{
	writer->WriteToFile(adoptionList);
}

void UserServicesTests::TestAll()
{
	TestConstructor();
	TestSkippingAndAdoption();
	TestFilteringAndReinitialization();
	TestGetters();
}

void UserServicesTests::TestConstructor()
{
	FileRepository repo("test.txt");
	repo.AddElement(Dog("Golden_Retriever", "Rex", 1, "https://google.ro"));
	repo.AddElement(Dog("Beagle", "Bob", 2, "https://google.com"));
	repo.AddElement(Dog("Dalmatian", "Ted", 5, "https://google.com"));
	repo.AddElement(Dog("Shiba_Inu", "Gigel", 3, "https://google.com"));
	repo.AddElement(Dog("Husky", "Ace", 6, "https://google.com"));
	repo.AddElement(Dog("Schnauzer", "Jax", 4, "photo.ro"));
	repo.AddElement(Dog("Pug", "Samson", 3, "https://dogs.com/photos/1"));
	repo.AddElement(Dog("Husky", "Chase", 2, "https://dogs.com/photos/2"));
	repo.AddElement(Dog("Dalmatian", "Leo", 5, "https://dogs.com/photos/3"));
	repo.AddElement(Dog("Schnauzer", "Duke", 6, "https://dogs.com/photos/4"));
	UserServices s1(repo);
	assert(s1.currentDogList == repo.GetArray());
	assert(s1.index == 0);

	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void UserServicesTests::TestSkippingAndAdoption()
{
	FileRepository repo("test.txt");
	repo.AddElement(Dog("Golden Retriever", "Rex", 1, "https://google.ro"));
	repo.AddElement(Dog("Beagle", "Bob", 2, "https://google.com"));
	UserServices s1(repo);
	
	s1.AddToAdoptionList(s1.repo[s1.index]);
	//assert(s1.adoptionList.size() == 1);
	//assert(s1.adoptionList[0] == s1.repo[0]);
	assert(s1.index == 1);

	s1.GoToNextDog();
	assert(s1.index == 0);

	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void UserServicesTests::TestFilteringAndReinitialization()
{
	FileRepository repo("test.txt");
	repo.AddElement(Dog("Golden Retriever", "Rex", 1, "https://google.ro"));
	repo.AddElement(Dog("Beagle", "Bob", 2, "https://google.com"));
	repo.AddElement(Dog("Dalmatian", "Ted", 5, "https://google.com"));
	repo.AddElement(Dog("Shiba Inu", "Gigel", 3, "https://google.com"));
	repo.AddElement(Dog("Husky", "Ace", 6, "https://google.com"));
	repo.AddElement(Dog("Schnauzer", "Jax", 4, "photo.ro"));
	repo.AddElement(Dog("Pug", "Samson", 3, "https://dogs.com/photos/1"));
	repo.AddElement(Dog("Husky", "Chase", 2, "https://dogs.com/photos/2"));
	repo.AddElement(Dog("Dalmatian", "Leo", 5, "https://dogs.com/photos/3"));
	repo.AddElement(Dog("Schnauzer", "Duke", 6, "https://dogs.com/photos/4"));
	UserServices s1(repo);
	
	s1.FilterByBreedAndAge("Husky", 10);
	assert(s1.currentDogList.size() == 2);
	assert(s1.currentDogList[0] == Dog("Husky", "Ace", 6, "https://google.com"));
	assert(s1.currentDogList[1] == Dog("Husky", "Chase", 2, "https://dogs.com/photos/2"));

	s1.ReinitializeDogList();
	assert(s1.currentDogList.size() == 10);
	assert(s1.index == 0);

	s1.FilterByBreedAndAge("", 6);
	assert(s1.currentDogList.size() == 8);

	s1.ReinitializeDogList();
	assert(s1.currentDogList.size() == 10);
	assert(s1.index == 0);

	s1.ReinitializeDogList();
	assert(s1.currentDogList.size() == 10);
	assert(s1.index == 0);

	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void UserServicesTests::TestGetters()
{
	FileRepository repo("test.txt");
	repo.AddElement(Dog("Golden Retriever", "Rex", 1, "https://google.ro"));
	repo.AddElement(Dog("Beagle", "Bob", 2, "https://google.com"));
	UserServices s1(repo);

	s1.AddToAdoptionList(s1.repo[s1.index]);

	s1.GoToNextDog();

	//assert(s1.GetAdoptionList() == s1.adoptionList);
    assert(s1.GetCurrentDog() == Dog("Beagle", "Bob", 2, "https://google.com"));
	try
	{
		s1.AddToAdoptionList(s1.repo[s1.index]);
		assert(false);
	}
	catch (std::exception& ex)
	{
		assert(true);
	}

	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}
