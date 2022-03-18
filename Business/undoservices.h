#ifndef UNDOSERVICES_H
#define UNDOSERVICES_H

#include <stack>
#include <memory>
#include "Business/repocommands.h"

class UndoException : public std::exception
{
public:
    UndoException(std::string message);

    const char* what() const noexcept override;
private:
    std::string message;
};

class RedoException : public std::exception
{
public:
    RedoException(std::string message);

    const char* what() const noexcept override;
private:
    std::string message;
};

class UndoServices
{
public:
    UndoServices();

    void ExecuteCommand(std::shared_ptr<ICommand> command);
    void Undo();
    void Redo();
private:
    std::stack<std::shared_ptr<ICommand>> undoStack;
    std::stack<std::shared_ptr<ICommand>> redoStack;
};

#endif // UNDOSERVICES_H
