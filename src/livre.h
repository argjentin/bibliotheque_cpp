#ifndef LIVRE_H
#define LIVRE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QX11Info>

class Livre
{
public:
    Livre(const QString& titre = "", const QString& auteur = "", int annee = 0, bool disponible = true); // Constructeur

    bool ajouter(); 
    static bool supprimer(int id);
    static bool emprunter(int id);
    static bool rendre(int id);

private: // Attributs privés
    QString m_titre; 
    QString m_auteur;
    int m_annee;
    bool m_disponible;
};

#endif 