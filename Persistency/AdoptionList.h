#pragma once
#include <vector>
#include "Domain/Dog.h"

class AdoptionListException : public std::exception
{
public:
    AdoptionListException(const std::string& message);
    const char* what() const noexcept override;
private:
    std::string message;
};

class AdoptionList
{
public:
	AdoptionList();
	void AddDog(const Dog& dog);

	const std::vector<Dog>& GetList() const;
private:
	std::vector<Dog> adoptionList;
};

class AdoptionListWriter
{
public:
	virtual void WriteToFile(const AdoptionList& adoptionList) = 0;

	const std::string& GetFileName() const;
	void SetFileName(const std::string& newFile);

    virtual ~AdoptionListWriter();
protected:
	std::string fileName;
};

class CSVAdoptionListWriter : public AdoptionListWriter
{
public:
	CSVAdoptionListWriter(const std::string& fileName);
	void WriteToFile(const AdoptionList& adoptionList);
};

class HTMLAdoptionListWriter : public AdoptionListWriter
{
public:
	HTMLAdoptionListWriter(const std::string& fileName);
	void WriteToFile(const AdoptionList& adoptionList);
};



