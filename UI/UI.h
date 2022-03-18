#pragma once
#include "Business/AdminServices.h"
#include "Business/UserServices.h"

class Console
{
public:
	Console(AdminServices& adminServices, UserServices& userServices);

	void Start();

	void SelectWriteMode();

	void SelectWorkingMode();
	void MainLoopUser();
	void MainLoopAdministrator();

	void AddDog();
	void RemoveDog();
	void UpdateDog();
	void UpdateDogName(size_t position, std::string newName);
	void UpdateDogAge(size_t position, size_t newAge);
	void UpdateDogBreed(size_t position, std::string newBreed);
	void UpdateDogPhoto(size_t position, std::string newPhoto);
	void PrintAllDogs();

	void AdoptNoFilter();
	void AdoptFilter();
	void PrintAdoptionList();
	void AdoptDog();
	void NoAdoptDog();
	void FilterByBreedAndAge();
	void UserReinitializeDogList();

	void PrintAdminMenu();
	void PrintUserMenu();
private:
	AdminServices& adminServices;
	UserServices& userServices;
};
