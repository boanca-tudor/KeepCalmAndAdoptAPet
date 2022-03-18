#ifndef REPOCOMMANDS_H
#define REPOCOMMANDS_H

#include "Business/command.h"
#include "Business/AdminServices.h"

class AddCommand : public ICommand
{
public:
    explicit AddCommand(AdminServices& repo, std::string name, std::string breed, size_t age, std::string photo);

    void Execute() override;
    void Undo() override;
    void Redo() override;
private:
    AdminServices& services;
    std::string name;
    std::string breed;
    size_t age;
    std::string photo;
};

class RemoveCommand : public ICommand
{
public:
    explicit RemoveCommand(AdminServices& repo, Dog d, size_t position);

    void Execute() override;
    void Undo() override;
    void Redo() override;
private:
    AdminServices& services;
    Dog dog;
    size_t position;
};

class UpdateCommand : public ICommand
{
public:
    explicit UpdateCommand(AdminServices& repo, size_t position, Dog d, std::string newName, std::string newBreed, size_t newAge, std::string newPhoto);

    void Execute() override;
    void Undo() override;
    void Redo() override;
private:
    AdminServices& services;
    size_t position;
    std::vector<std::string> names;
    std::vector<std::string> breeds;
    std::vector<size_t> ages;
    std::vector<std::string> photos;
};

#endif // REPOCOMMANDS_H
