#ifndef LIVRE_H
#define LIVRE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QX11Info>
#include <QDate>

class Livre
{
public:
    Livre(const QString& type = "",const QString& titre = "", const QString& auteur = "", int annee = 0, bool disponible = true, QString nom = "", QString prenom = "", QDate dateEmprunt = QDate(), QDate dateRetour = QDate()); // Constructeur                                                                                                                                                                                                       

    bool ajouter(); 
    static bool supprimer(int id);
    static bool emprunter(int id, QString nom, QString prenom, QDate date);
    static bool rendre(int id);
    static bool estEmprunte(int id);

private: // Attributs privés
    QString m_type;
    QString m_titre; 
    QString m_auteur;
    int m_annee;
    bool m_disponible;
    QString m_nom;
    QString m_prenom;
    QDate m_dateEmprunt;
    QDate m_dateRetour;
};

#endif 