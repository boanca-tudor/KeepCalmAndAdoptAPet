#include "undoservices.h"

UndoException::UndoException(std::string message) :
    message {message}
{
}

const char *UndoException::what() const noexcept
{
    return message.c_str();
}

RedoException::RedoException(std::string message) :
    message {message}
{
}

const char *RedoException::what() const noexcept
{
    return message.c_str();
}

UndoServices::UndoServices()
{
    undoStack = std::stack<std::shared_ptr<ICommand>>();
    redoStack = std::stack<std::shared_ptr<ICommand>>();
}

void UndoServices::ExecuteCommand(std::shared_ptr<ICommand> command)
{
    redoStack = std::stack<std::shared_ptr<ICommand>>();
    command->Execute();
    undoStack.push(command);
}

void UndoServices::Undo()
{
    if (undoStack.empty())
        throw UndoException("No undo operations left!");
    undoStack.top()->Undo();
    redoStack.push(undoStack.top());
    undoStack.pop();
}

void UndoServices::Redo()
{
    if (redoStack.empty())
        throw RedoException("No redo operations left!");
    redoStack.top()->Redo();
    undoStack.push(redoStack.top());
    redoStack.pop();
}

