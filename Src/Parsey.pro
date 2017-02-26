QT += core gui widgets

TARGET = Parsey
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    main.cpp \
    UI/MainWindow.cpp \
    Controller/AppController.cpp \
    UI/FilesListWidget.cpp \
    UI/FilesListModel.cpp \
    Model/FilesModel.cpp

HEADERS  += \
    UI/MainWindow.h \
    Controller/AppController.h \
    UI/FilesListWidget.h \
    UI/FilesListModel.h \
    Model/FilesModel.h

DESTDIR = $$OUT_PWD/product
EXE_PATH = $$DESTDIR\\$$TARGET.exe
MOC_DIR = $$OUT_PWD/moc
OBJECTS_DIR = $$OUT_PWD/obj
RESOURCES_DIR = $$PWD/../Resources

# Copy needed libraries
win32 {
    WINDEPLOY_COMMAND = $$(QTDIR)\bin\windeployqt
    QMAKE_POST_LINK += "$$WINDEPLOY_COMMAND $$EXE_PATH"
}

# Copy database ini file
win32 {
    DB_INI_PATH = $$RESOURCES_DIR\db_config.ini
    QMAKE_POST_LINK += && "xcopy $$shell_path($$DB_INI_PATH) $$shell_path($$DESTDIR) /Y"
}

RESOURCES += \
    ../Resources/resources.qrc
