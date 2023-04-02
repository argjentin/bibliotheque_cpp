#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

#include "livrewidget.h"
#include "connexion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set the eglfs platform plugin
    // QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    // QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    // QCoreApplication::setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents);
    // QCoreApplication::setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents);
    // QCoreApplication::setAttribute(Qt::AA_EnableTouchPadMovement);

    // Connect to the database
    Connexion connexion;
    if (!connexion.ouvrir())
    {
        qDebug() << "Erreur lors de la connexion à la base de données";
        return 1;
    }

    // Create the main widget
    LivreWidget w;
    w.show();

    return a.exec();
}
