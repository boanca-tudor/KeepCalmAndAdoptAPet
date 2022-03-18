#include <QApplication>
#include <memory>
#include <QDebug>
#include <QDir>
#include "UI/ModeWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DogTests::TestAllDog();
    RepositoryTests::TestAll();
    AdminServicesTests::TestAll();
    UserServicesTests::TestAll();

    std::unique_ptr<Repository> repo = std::make_unique<FileRepository>("dogs.txt");
    std::unique_ptr<AdminServices> adminServices = std::make_unique<AdminServices>(*repo.get());
    std::unique_ptr<UserServices> userServices = std::make_unique<UserServices>(*repo.get());
    std::unique_ptr<UndoServices> undoServices = std::make_unique<UndoServices>();

    std::unique_ptr<ModeWindow> modeWindow = std::make_unique<ModeWindow>(*adminServices.get(), *userServices.get(), *undoServices.get());
    modeWindow->show();
    qDebug() << QDir::current();

    return a.exec();
}
