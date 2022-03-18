#pragma once
#include "Repository.h"

class FileRepository :
    public Repository
{
public:
    FileRepository(const std::string& path, bool initialize = false);

    void AddElement(const Dog& newDog) override;
    void RemoveElement(size_t position) override;

	void UpdateElementName(size_t position, std::string newName) override;
	void UpdateElementBreed(size_t position, std::string newBreed) override;
	void UpdateElementAge(size_t position, size_t newAge) override;
	void UpdateElementPhotograph(size_t position, std::string newPhotograph) override;
    void UpdateAllAttributes(size_t position, std::string newName, std::string newBreed, size_t newAge, std::string newPhotograph) override;

    bool IsInitializable() const;
protected:
    std::string filePath;
    bool initialize;
private:
    void ReadData();
    void WriteData();
};

