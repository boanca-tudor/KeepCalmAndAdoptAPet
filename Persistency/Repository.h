#pragma once
#include "Domain/Dog.h"
#include <vector>
#include <string>
#include <iostream>

class RepositoryException : public std::exception
{
public:
	RepositoryException(const std::string& message);
	const char* what() const noexcept override;
private:
	std::string message;
};

class Repository
{
public:
	Repository();
	Repository(size_t maxSize);

	virtual ~Repository();

	/// <summary>
	/// Indexing operator for the repository
	/// </summary>
	/// <param name="position">The position of the element</param>
	/// <returns>The element on the given position in the repository</returns>
	const Dog& operator[](size_t position);

	/// <summary>
	/// Insertion operator for the repository class
	/// </summary>
	/// <param name="os">The stream object to write to</param>
	/// <param name="repo">The repo to be written</param>
	/// <returns>A stream containing the elements of the repository</returns>
	friend std::ostream& operator<<(std::ostream& os, const Repository& repo);

	/// <summary>
	/// Equality operator for the repository
	/// </summary>
	/// <param name="other">The object to compare with</param>
	/// <returns>True if the repos have the same elements, False otherwise</returns>
	bool operator==(const Repository& other) const;

	/// <summary>
	/// Adds a new dog to the repository
	/// </summary>
	/// <param name="newDog">The new dog to be added</param>
	virtual void AddElement(const Dog& newDog);

	/// <summary>
	/// Removes an element from the repo by position
	/// </summary>
	/// <param name="position">The position of the element to be removed</param>
	virtual void RemoveElement(size_t position);

	/// <summary>
	/// Finds a dog in the repo by its name
	/// </summary>
	/// <param name="name">The name of the dog</param>
	/// <returns>The position of the dog</returns>
	int FindElement(const Dog& dog) const;

	/// <summary>
	/// Updates the name of a dog
	/// </summary>
	/// <param name="position">The position of the dog</param>
	/// <param name="newName">The new name of the dog</param>
	virtual void UpdateElementName(size_t position, std::string newName);

	/// <summary>
	/// Updates the breed of a dog
	/// </summary>
	/// <param name="position">The position of the dog</param>
	/// <param name="newBreed">The new breed of the dog</param>
	virtual void UpdateElementBreed(size_t position, std::string newBreed);

	/// <summary>
	/// Updates the age of a dog
	/// </summary>
	/// <param name="position">The position of the dog</param>
	/// <param name="newAge">The new age of the dog</param>
	virtual void UpdateElementAge(size_t position, size_t newAge);

	/// <summary>
	/// Updates the photograph of a dog
	/// </summary>
	/// <param name="position"></param>
	/// <param name="newPhotograph"></param>
	virtual void UpdateElementPhotograph(size_t position, std::string newPhotograph);

    /// <summary>
    /// Updates every attribute of a dog from the repository
    /// </summary>
    /// <param name="position">The position of the dog</param>
    /// <param name="newBreed">The new photograph of the dog</param>
    virtual void UpdateAllAttributes(size_t position, std::string newName, std::string newBreed, size_t newAge, std::string newPhoto);

	size_t GetSize() const;
	const std::vector<Dog>& GetArray() const;

	friend class RepositoryTests;
protected:
	std::vector<Dog> elementsArray;
};

class RepositoryTests
{
public:
	static void TestAll();
	static void TestConstructorsAndAssignment();
	static void TestAdd();
	static void TestRemoveSubscript();
	static void TestUpdate();
	static void TestFind();
	static void TestPrint();
};
