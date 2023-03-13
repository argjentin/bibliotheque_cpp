#include "connexion.h"

// Constructeur
Connexion::Connexion() {
    // Définition des paramètres de connexion
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("biblio");
    db.setUserName("akorbi");
    db.setPassword("0325");
}

// Destructeur
Connexion::~Connexion() {
    fermer();
}

// Méthode pour ouvrir la connexion à la base de données
bool Connexion::ouvrir() {
    bool ok = db.open();
    if (!ok) {
        qDebug() << "Erreur de connexion : " << db.lastError().text();
    }
    return ok;
}

// Méthode pour fermer la connexion à la base de données
void Connexion::fermer() {
    db.close();
}
