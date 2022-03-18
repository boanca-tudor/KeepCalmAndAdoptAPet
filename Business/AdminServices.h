#pragma once
#include "Persistency/FileRepository.h"
#include "Validation/Validator.h"
#include <exception>

class AdminServices
{
public:
	/// <summary>
	/// Constructor for the Services class
	/// </summary>
	/// <param name="repo">The repository on which the services class operates</param>
	AdminServices(Repository& repo);

	/// <summary>
	/// Adds a new dog to the repository
	/// Also performs data validation
	/// </summary>
	/// <param name="breed">The breed of the dog</param>
	/// <param name="name">The name of the dog</param>
	/// <param name="age">The age of the dog</param>
	/// <param name="photograph">The photograph link of the dog</param>
	void AddDog(std::string breed, std::string name, size_t age, std::string photograph);

	/// <summary>
	/// Removes a dog from the repository
	/// </summary>
	/// <param name="position">The position of the dog which will be removed</param>
	void RemoveDog(size_t position);

	/// <summary>
	/// Updates the name of a dog from the repository
	/// Performs data validation for the new name
	/// </summary>
	/// <param name="position">The position of the dog</param>
	/// <param name="newName">The new name of the dog</param>
	void UpdateDogName(size_t position, std::string newName);

	/// <summary>
	/// Updates the breed of a dog from the repository
	/// Performs data validation for the new breed
	/// </summary>
	/// <param name="position">The position of the dog</param>
	/// <param name="newBreed">The new breed of the dog</param>
	void UpdateDogBreed(size_t position, std::string newBreed);

	/// <summary>
	/// Updates the age of a dog from the repository
	/// Performs data validation for the new age
	/// </summary>
	/// <param name="position">The position of the dog</param>
	/// <param name="newBreed">The new age of the dog</param>
	void UpdateDogAge(size_t position, size_t newAge);

	/// <summary>
	/// Updates the photograph of a dog from the repository
	/// Performs data validation for the new photograph
	/// </summary>
	/// <param name="position">The position of the dog</param>
	/// <param name="newBreed">The new photograph of the dog</param>
	void UpdateDogPhotograph(size_t position, std::string newPhotograph);

    void UpdateAllAttributes(size_t position, std::string, std::string, size_t, std::string);
	
	/// <summary>
	/// Prints the contents of the repository
	/// </summary>
    Repository& GetRepo() const;

	/// <summary>
	/// Adds 10 entries to the repository
	/// </summary>
	void InitializeRepo();

	friend class AdminServicesTests;
private:
	Repository& repository;
};


class AdminServicesTests
{
public:
	static void TestAll();
	static void TestConstructors();
	static void TestAdd();
	static void TestRemove();
	static void TestUpdate();
};
