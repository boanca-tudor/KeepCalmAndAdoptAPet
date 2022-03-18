#ifndef COMMAND_H
#define COMMAND_H


class ICommand
{
public:
    virtual void Execute() = 0;
    virtual void Undo() = 0;
    virtual void Redo() = 0;
};

#endif // COMMAND_H
