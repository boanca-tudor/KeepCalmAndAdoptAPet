#pragma once
#include <string>
#include <iostream>

class Dog
{
public:
	/// <summary>
	/// Default constructor for the Dog class
	/// </summary>
	Dog();

	/// <summary>
	/// Constructor for the dog class with initializers for all fields
	/// </summary>
	/// <param name="breed">The breed of the dog</param>
	/// <param name="name">The name of the dog</param>
	/// <param name="age">The age of the dog</param>
	/// <param name="photograph">The photograph of the dog</param>
	Dog(std::string breed, std::string name, size_t age, std::string photograph);

	/// <summary>
	/// Destructor for the dog
	/// </summary>
	~Dog();

	// Getters
	std::string GetBreed() const;
	std::string GetName() const;
	size_t GetAge() const;
	std::string GetPhotograph() const;

	// Setters
	void SetBreed(std::string newBreed);
	void SetName(std::string newName);
	void SetAge(size_t newAge);
	void SetPhotograph(std::string newPhotograph);

	/// <summary>
	/// Equality operator for the dog class
	/// </summary>
	/// <param name="other">The dog to compare the current object with</param>
	/// <returns>True if the dogs are identical, false otherwise</returns>
	bool operator==(const Dog& other) const;
	/// <summary>
	/// Insertion operator for the dog class
	/// </summary>
	/// <param name="os">The stream object to write the data of the dog to</param>
	/// <param name="dog">The dog whose fields will be written</param>
	/// <returns>A stream object which contains the data of the dog</returns>
	friend std::ostream& operator<<(std::ostream& os, const Dog& dog);

	friend std::istream& operator>>(std::istream& is, Dog& dog);
private:
	std::string breed;
	std::string name;
	size_t age;
	std::string photograph;
};

class DogTests
{
public:
	static void TestAllDog();
	static void TestConstructorsAndGettersDog();
	static void TestSettersDog();
	static void TestEqualityDog();
	static void TestExtractionOperator();
};
