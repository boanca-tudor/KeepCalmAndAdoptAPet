#include "UI/UI.h"
#include <iostream>
#include <windows.h>

Console::Console(AdminServices& adminServices, UserServices& userServices) :
	adminServices {adminServices}, userServices {userServices}
{
}

void Console::Start()
{
	SelectWriteMode();
	SelectWorkingMode();
}

void Console::SelectWriteMode()
{
	std::cout << "Please select how the data will be saved: \n";
	std::cout << "1. CSV\n";
	std::cout << "2. HTML\n";

	std::string mode;
	std::cin >> mode;

	if (mode.size() != 1)
	{
		std::cout << "Invalid mode!\n";
		exit(1);
	}

	switch (mode[0])
	{
		case '1':
		{
			userServices.SetWriteMode("CSV");
			return;
		}
		case '2':
		{
			userServices.SetWriteMode("HTML");
			return;
		}
		default:
		{
			std::cout << "Invalid mode!\n";
			exit(1);
		}
	}
}

void Console::SelectWorkingMode()
{
	bool done = false;

	while (!done)
	{
		std::cout << "Open application in:\n";
		std::cout << "1.Administrator mode\n";
		std::cout << "2.User mode\n";
		std::string mode;
		std::cin >> mode;
		if (mode.size() != 1)
		{
			std::cout << "Invalid mode!\n";
			return;
		}

		switch (mode[0])
		{
		case '1':
		{
			MainLoopAdministrator();
			break;
		}
		case '2':
		{
			MainLoopUser();
			break;
		}
		default:
		{
			std::cout << "Invalid mode!\n";
			done = true;
			break;
		}
		}
	}
}

void Console::MainLoopUser()
{
	std::string command;
	bool done = false;

	PrintUserMenu();
	while (!done)
	{
		std::cout << "Please input your command:\n";
		std::cin >> command;

		if (command.size() != 1)
			std::cout << "Invalid command!\n";

		else
		{
			switch (command[0])
			{
			case '1':
			{
				AdoptNoFilter();
				break;
			}
			case '2':
			{
				AdoptFilter();
				break;
			}
			case '3':
			{
				PrintAdoptionList();
				break;
			}
			case '0':
			{
				done = true;
				break;
			}
			default:
			{
				std::cout << "Invalid command!\n";
				break;
			}
			}
		}
	}
}

void Console::MainLoopAdministrator()
{
	std::string command;
	bool done = false;

	PrintAdminMenu();
	while (!done)
	{
		std::cout << "Please input your command:\n";
		std::cin >> command;
		if (command.size() != 1)
			std::cout << "Invalid command!\n";
		
		else
		{
			try
			{
				switch (command[0])
				{
				case '1':
				{
					AddDog();
					break;
				}
				case '2':
				{
					RemoveDog();
					break;
				}
				case '3':
				{
					UpdateDog();
					break;
				}
				case '4':
				{
					PrintAllDogs();
					break;
				}
				case '0':
				{
					done = true;
					break;
				}
				default:
				{
					std::cout << "Invalid command!\n";
					break;
				}
				}
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << '\n';
			}
		}
	}
}

void Console::AddDog()
{
	std::string name, breed, photo;
	size_t age;
	std::cout << "Please input a name, breed, age and a photo link\n";
	std::cin >> name;
	std::cin >> breed;
	std::cin >> age;
	std::cin >> photo;

	this->adminServices.AddDog(breed, name, age, photo);
}

void Console::RemoveDog()
{
	size_t position;
	std::cout << "Please input the position of the dog you wish to remove\n";
	std::cin >> position;

	this->adminServices.RemoveDog(position);
}

void Console::UpdateDog()
{
	size_t position;
	std::cout << "Please input the position of the dog you wish to update\n";
	std::cin >> position;
	std::cout << "Please input the attribute you would like to modify\n"
			  << "B for breed, N for name, A for age, P for photograph\n";

	std::string updateAttribute;
	std::cin >> updateAttribute;

	if (updateAttribute.size() != 1)
	{
		std::cout << "Invalid command!\n";
		return;
	}

	switch (updateAttribute[0])
	{
	case 'b':
	case 'B':
	{
		std::string newBreed;
		std::cout << "Please input the new breed\n";
		std::cin >> newBreed;
		UpdateDogBreed(position, newBreed);
		break;
	}
	case 'n':
	case 'N':
	{
		std::string newName;
		std::cout << "Please input the new name\n";
		std::cin >> newName;
		UpdateDogBreed(position, newName);
		break;
	}
	case 'a':
	case 'A':
	{
		size_t newAge;
		std::cout << "Please input the new age\n";
		std::cin >> newAge;
		UpdateDogAge(position, newAge);
		break;
	}
	case 'p':
	case 'P':
	{
		std::string newPhoto;
		std::cout << "Please input the new photo\n";
		std::cin >> newPhoto;
		UpdateDogPhoto(position, newPhoto);
		break;
	}
	default:
	{
		std::cout << "Invalid attribute!\n";
		break;
	}
	}
}

void Console::UpdateDogName(size_t position, std::string newName)
{
	this->adminServices.UpdateDogName(position, newName);
}

void Console::UpdateDogAge(size_t position, size_t newAge)
{
	this->adminServices.UpdateDogAge(position, newAge);
}

void Console::UpdateDogBreed(size_t position, std::string newBreed)
{
	this->adminServices.UpdateDogBreed(position, newBreed);
}

void Console::UpdateDogPhoto(size_t position, std::string newPhoto)
{
	this->adminServices.UpdateDogPhotograph(position, newPhoto);
}

void Console::PrintAllDogs()
{
	std::cout << adminServices.GetRepo();
}

void Console::PrintAdminMenu()
{
	std::cout << "1.Add a new dog\n";
	std::cout << "2.Remove a dog\n";
	std::cout << "3.Update an existing dog\n";
	std::cout << "4.Print all available dogs\n";
	std::cout << "0.Exit\n";
}

void Console::PrintUserMenu()
{
	std::cout << "1.View all available dogs\n";
	std::cout << "2.Filter dogs by breed and age\n";
	std::cout << "3.View adoption list\n";
	std::cout << "0.Exit\n";
}

void Console::AdoptNoFilter()
{
	UserReinitializeDogList();

	std::string command;
	bool done = false;

	while (!done)
	{
		std::cout << userServices.GetCurrentDog();
		std::cout << "Would you like to adopt this dog?(Y for yes, N for no, E for exit)\n";
		std::cin >> command;

		if (command.size() != 1)
			std::cout << "Invalid command!\n";

		else
		{
			try
			{
				switch (command[0])
				{
				case 'Y':
				case 'y':
				{
					AdoptDog();
					break;
				}
				case 'N':
				case 'n':
				{
					NoAdoptDog();
					break;
				}
				case 'E':
				case 'e':
				{
					done = true;
					break;
				}
				default:
				{
					std::cout << "Invalid command!\n";
					break;
				}
				}
			}
			catch (std::exception& ex)
			{
				std::cout << ex.what() << '\n';
			}
		}
	}
}

void Console::AdoptFilter()
{
	UserReinitializeDogList();
	FilterByBreedAndAge();

	std::string command;
	bool done = false;

	while (!done)
	{
		std::cout << userServices.GetCurrentDog();
		
		std::cout << "Would you like to adopt this dog?(Y for yes, N for no, E for exit)\n";
		std::cin >> command;

		if (command.size() != 1)
			std::cout << "Invalid command!\n";

		else
		{
			try
			{
				switch (command[0])
				{
				case 'Y':
				case 'y':
				{
					AdoptDog();
					break;
				}
				case 'N':
				case 'n':
				{
					NoAdoptDog();
					break;
				}
				case 'E':
				case 'e':
				{
					done = true;
					break;
				}
				default:
				{
					std::cout << "Invalid command!\n";
					break;
				}
				}
			}
			catch (std::exception& ex)
			{
				std::cout << ex.what() << '\n';
			}
		}
	}
}

void Console::PrintAdoptionList()
{
	if (userServices.GetWriteMode() == "CSV")
	{
		userServices.WriteData();

		std::string command = "notepad " + userServices.GetFileName();

		system("E:");
		system("cd Facultate\\Anul 1\\Sem 2\\OOP\\Assignments\\a67-911-Boanca-Tudor\\KeepCalmAndAdoptAPet_V2");
		system(command.c_str());
	}
	else
	{
		userServices.WriteData();

		system("E:");
		system("cd Facultate\\Anul 1\\Sem 2\\OOP\\Assignments\\a67-911-Boanca-Tudor\\KeepCalmAndAdoptAPet_V2");
		system(userServices.GetFileName().c_str());
	}
}

void Console::AdoptDog()
{
	userServices.AddToAdoptionList(userServices.GetCurrentDog());
}

void Console::NoAdoptDog()
{
	userServices.GoToNextDog();
}

void Console::FilterByBreedAndAge()
{
	std::cout << "Please input a breed and an age:\n";
	std::string breed, blank;
	std::getline(std::cin, blank);
	std::getline(std::cin, breed);
	size_t age;
	std::cin >> age;

	userServices.FilterByBreedAndAge(breed, age);
}

void Console::UserReinitializeDogList()
{
	userServices.ReinitializeDogList();
}
