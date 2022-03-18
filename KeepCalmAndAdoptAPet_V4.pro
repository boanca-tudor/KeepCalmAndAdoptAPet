QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Business/AdminServices.cpp \
    Business/UserServices.cpp \
    Business/repocommands.cpp \
    Business/undoservices.cpp \
    Domain/Dog.cpp \
    Persistency/AdoptionList.cpp \
    Persistency/FileRepository.cpp \
    Persistency/HTMLTable.cpp \
    Persistency/Repository.cpp \
    UI/AddWindow.cpp \
    UI/AdministratorWindow.cpp \
    UI/AdoptionListTypeWindow.cpp \
    UI/Charts/DogChart.cpp \
    UI/FilterWindow.cpp \
    UI/ModeWindow.cpp \
    UI/UI.cpp \
    UI/UserWindow.cpp \
    UI/adoptionlistmodel.cpp \
    UI/adoptionlistviewer.cpp \
    Validation/Validator.cpp \
    main.cpp

HEADERS += \
    Business/AdminServices.h \
    Business/UserServices.h \
    Business/command.h \
    Business/repocommands.h \
    Business/undoservices.h \
    Domain/Dog.h \
    Persistency/AdoptionList.h \
    Persistency/FileRepository.h \
    Persistency/HTMLTable.h \
    Persistency/Repository.h \
    UI/AddWindow.h \
    UI/AdministratorWindow.h \
    UI/AdoptionListTypeWindow.h \
    UI/Charts/DogChart.h \
    UI/FilterWindow.h \
    UI/ModeWindow.h \
    UI/UI.h \
    UI/UserWindow.h \
    UI/adoptionlistmodel.h \
    UI/adoptionlistviewer.h \
    Validation/Validator.h

TRANSLATIONS += \
    KeepCalmAndAdoptAPet_V4_ro_RO.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Images/AppIcon.ico \
    Images/KeepCalm.png \
    Stylesheets/AdminButton.qss \
    Stylesheets/ModeButton.qss


RC_ICONS = Images/AppIcon.ico
