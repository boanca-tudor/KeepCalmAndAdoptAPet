#pragma once
#include "Persistency/FileRepository.h"
#include "Persistency/AdoptionList.h"
#include <vector>

class UserServices
{
public:
	/// <summary>
	/// Constructor for the UserServices class
	/// </summary>
	/// <param name="repo">The repo the user services class depends on</param>
	UserServices(Repository& repo);

	/// <summary>
	/// Constructor for the UserServices class
	/// </summary>
	/// <param name="repo">The repo the user services class depends on</param>
	/// <param name="writeMode">The mode in which the data will be displayed to the user</param>
	UserServices(Repository& repo, const std::string& writeMode);

	~UserServices();

	/// <summary>
	/// Adds a new dog to the adoption list of the user
	/// </summary>
	/// <param name="dog">The dog to be added</param>
	void AddToAdoptionList(const Dog& dog);

	/// <summary>
	/// Moves the index to the next dog in the list
	/// </summary>
	void GoToNextDog();

	/// <summary>
	/// Filters all dogs in the repo by their breed and maximum age
	/// </summary>
	/// <param name="breed">The breed to filter by</param>
	/// <param name="age">The maximum age to filter by</param>
	void FilterByBreedAndAge(std::string breed, size_t age);

	/// <summary>
	/// Reinitializes the current dog list to the list in the repo, and sets the index to 0
	/// </summary>
	void ReinitializeDogList();

	void WriteData();

	// Getters
	const AdoptionList& GetAdoptionList() const;
	const Dog& GetCurrentDog() const;
	const std::string& GetFileName() const;
	const std::string& GetWriteMode() const;

	void SetWriteMode(const std::string& newMode);

	friend class UserServicesTests;
private:
	Repository& repo;
	std::vector<Dog> currentDogList;
	AdoptionList adoptionList;
	AdoptionListWriter* writer;
	size_t index;
	std::string writeMode;
};


class UserServicesTests
{
public:
	static void TestAll();
	static void TestConstructor();
	static void TestSkippingAndAdoption();
	static void TestFilteringAndReinitialization();
	static void TestGetters();
};
