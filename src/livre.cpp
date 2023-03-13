#include "livre.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QX11Info>

Livre::Livre(const QString& titre, const QString& auteur, int annee, bool disponible) // Constructeur
    : m_titre(titre), m_auteur(auteur), m_annee(annee), m_disponible(disponible) // Initialisation des attributs
{
}

bool Livre::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO livres (titre, auteur, annee, disponible) VALUES (:titre, :auteur, :annee, :disponible)");
    query.bindValue(":titre", m_titre);
    query.bindValue(":auteur", m_auteur);
    query.bindValue(":annee", m_annee);
    query.bindValue(":disponible", m_disponible);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout d'un livre:" << query.lastError().text();
        return false;
    }

    return true;
}

bool Livre::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM livres WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression d'un livre:" << query.lastError().text();
        return false;
    }

    return true;
}

bool Livre::emprunter(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE livres SET disponible = 0 WHERE id = :id AND disponible = 1");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'emprunt d'un livre:" << query.lastError().text();
        return false;
    }

    if (query.numRowsAffected() == 0) {
        qDebug() << "Impossible d'emprunter le livre avec l'ID" << id;
        return false;
    }

    return true;
}

bool Livre::rendre(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE livres SET disponible = 1 WHERE id = :id AND disponible = 0");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la restitution d'un livre:" << query.lastError().text();
        return false;
    }

    if (query.numRowsAffected() == 0) {
        qDebug() << "Impossible de rendre le livre avec l'ID" << id;
        return false;
    }

    return true;
}
