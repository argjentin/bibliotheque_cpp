TEMPLATE = app
TARGET = bibliotheque
INCLUDEPATH += .

QT += sql
QT += widgets

LIBS += -lmysqlclient

HEADERS += src/connexion.h src/livre.h src/livrewidget.h src/ajoutlivredialog.h src/triDialog.h src/empruntDialog.h src/searchDialog.h
SOURCES += src/connexion.cpp src/livre.cpp src/livrewidget.cpp src/main.cpp src/ajoutlivredialog.cpp src/triDialog.cpp src/empruntDialog.cpp src/searchDialog.cpp
