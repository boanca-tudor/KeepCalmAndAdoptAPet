#include "repocommands.h"
#include <algorithm>

AddCommand::AddCommand(AdminServices &services, std::string name, std::string breed, size_t age, std::string photo) :
    services {services},
    name {name},
    breed {breed},
    age {age},
    photo {photo}
{

}

void AddCommand::Execute()
{
    services.AddDog(breed, name, age, photo);
}

void AddCommand::Undo()
{
    auto pos = std::find(services.GetRepo().GetArray().begin(), services.GetRepo().GetArray().end(), Dog(breed, name, age, photo));
    services.RemoveDog(pos - services.GetRepo().GetArray().begin());
}

void AddCommand::Redo()
{
    services.AddDog(breed, name, age, photo);
}

RemoveCommand::RemoveCommand(AdminServices &services, Dog d, size_t position) :
    services {services},
    dog {d},
    position {position}
{
}

void RemoveCommand::Execute()
{
    services.RemoveDog(position);
}

void RemoveCommand::Undo()
{
    services.GetRepo().AddElement(dog);
}

void RemoveCommand::Redo()
{
    services.RemoveDog(position);
}

UpdateCommand::UpdateCommand(AdminServices &services, size_t position, Dog d, std::string newName, std::string newBreed, size_t newAge, std::string newPhoto) :
    services {services},
    position {position},
    names {std::vector<std::string>()},
    breeds {std::vector<std::string>()},
    ages {std::vector<size_t>()},
    photos {std::vector<std::string>()}
{
    names.push_back(d.GetName());
    names.push_back(newName);

    breeds.push_back(d.GetBreed());
    breeds.push_back(newBreed);

    ages.push_back(d.GetAge());
    ages.push_back(newAge);

    photos.push_back(d.GetPhotograph());
    photos.push_back(newPhoto);
}

void UpdateCommand::Execute()
{
    services.UpdateAllAttributes(position, names[1], breeds[1], ages[1], photos[1]);
}

void UpdateCommand::Undo()
{
    services.UpdateAllAttributes(position, names[0], breeds[0], ages[0], photos[0]);
}

void UpdateCommand::Redo()
{
    services.UpdateAllAttributes(position, names[1], breeds[1], ages[1], photos[1]);
}
