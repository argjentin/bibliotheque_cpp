#ifndef CONNEXION_H
#define CONNEXION_H

#include <QtSql>

class Connexion {
public:
    // Constructeur et destructeur
    Connexion();
    ~Connexion();

    // Méthodes publiques
    bool ouvrir();
    void fermer();

private:
    // Attributs privés
    QSqlDatabase db;
};

#endif // CONNEXION_H
