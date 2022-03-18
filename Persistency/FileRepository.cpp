#include "Persistency/FileRepository.h"
#include <fstream>


FileRepository::FileRepository(const std::string& path, bool initialize) :
	Repository { Repository() },
	filePath{ path },
	initialize{ initialize }
{
	ReadData();
}

void FileRepository::ReadData()
{
	std::ifstream inputFile;
	inputFile.open(filePath, std::ios::in);

	Dog next;
	while (inputFile >> next)
		Repository::AddElement(next);

	inputFile.close();
}

void FileRepository::WriteData()
{
	std::ofstream outputFile;
	outputFile.open(filePath, std::ios::out);

	for (const Dog& d : Repository::GetArray())
		outputFile << d;

	outputFile.close();
}
		
void FileRepository::AddElement(const Dog& newDog)
{
	Repository::AddElement(newDog);
	WriteData();
}

void FileRepository::RemoveElement(size_t position)
{
	Repository::RemoveElement(position);
	WriteData();
}

void FileRepository::UpdateElementName(size_t position, std::string newName)
{
	Repository::UpdateElementName(position, newName);
	WriteData();
}

void FileRepository::UpdateElementBreed(size_t position, std::string newBreed)
{
	Repository::UpdateElementBreed(position, newBreed);
	WriteData();
}

void FileRepository::UpdateElementAge(size_t position, size_t newAge)
{
	Repository::UpdateElementAge(position, newAge);
	WriteData();
}

void FileRepository::UpdateElementPhotograph(size_t position, std::string newPhotograph)
{
	Repository::UpdateElementPhotograph(position, newPhotograph);
    WriteData();
}

void FileRepository::UpdateAllAttributes(size_t position, std::string newName, std::string newBreed, size_t newAge, std::string newPhotograph)
{
    Repository::UpdateAllAttributes(position, newName, newBreed, newAge, newPhotograph);
    WriteData();
}

bool FileRepository::IsInitializable() const
{
	return initialize;
}

