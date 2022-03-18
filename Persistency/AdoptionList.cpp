#include "Persistency/AdoptionList.h"
#include "Persistency/HTMLTable.h"
#include <fstream>
#include <algorithm>

AdoptionList::AdoptionList() :
	adoptionList{std::vector<Dog>()}
{
}

void AdoptionList::AddDog(const Dog& dog)
{
	auto pos = std::find(adoptionList.begin(), adoptionList.end(), dog);

    if (pos != adoptionList.end()) throw AdoptionListException("Dog already in adoption list!");
	adoptionList.push_back(dog);
}

const std::vector<Dog>& AdoptionList::GetList() const
{
	return adoptionList;
}

CSVAdoptionListWriter::CSVAdoptionListWriter(const std::string& fileName)
{
	SetFileName(fileName);
}

void CSVAdoptionListWriter::WriteToFile(const AdoptionList& adoptionList)
{
	std::ofstream outputFile;
	outputFile.open(fileName, std::ios_base::out);

	for (auto& dog : adoptionList.GetList())
	{
		outputFile << dog.GetName() << ',' << dog.GetBreed() << ',' << dog.GetAge() << ',' << dog.GetPhotograph();
		outputFile << '\n';
	}

	outputFile.close();
}

HTMLAdoptionListWriter::HTMLAdoptionListWriter(const std::string& fileName)
{
	SetFileName(fileName);
}

void HTMLAdoptionListWriter::WriteToFile(const AdoptionList& adoptionList)
{
	std::ofstream outputFile;
	outputFile.open(fileName, std::ios_base::out);

	outputFile << "<!DOCTYPE html>";

	outputFile << "<html>";
	outputFile << "<head>";
	outputFile << "<title> Adoption List </title>";
	outputFile << "</head>";

	outputFile << "<body>";

	HTMLTable table = HTMLTable();
	HTMLTable::Row topRow;
	topRow.AddToRow("Name");
	topRow.AddToRow("Breed");
	topRow.AddToRow("Age");
	topRow.AddToRow("Photograph");
	table.AddRow(topRow);
	for (auto& dog : adoptionList.GetList())
	{
		HTMLTable::Row newRow;
		newRow.AddToRow(dog.GetName());
		newRow.AddToRow(dog.GetBreed());
		newRow.AddToRow(std::to_string(dog.GetAge()));
		newRow.AddToRow(dog.GetPhotograph());
		table.AddRow(newRow);
	}

	outputFile << table;

	outputFile << "</body>";

	outputFile << "</html>";

	outputFile.close();
}

const std::string& AdoptionListWriter::GetFileName() const
{
	return fileName;
}

void AdoptionListWriter::SetFileName(const std::string& newFile)
{
    fileName = newFile;
}

AdoptionListWriter::~AdoptionListWriter()
{
}

AdoptionListException::AdoptionListException(const std::string& message) :
    message {message}
{
}

const char* AdoptionListException::what() const noexcept
{
    return message.c_str();
}
