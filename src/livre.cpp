#include "livre.h"

Livre::Livre(const QString& type,const QString& titre, const QString& auteur, int annee, bool disponible, QString nom, QString prenom, QDate dateEmprunt, QDate dateRetour)
    : m_type(type),m_titre(titre), m_auteur(auteur), m_annee(annee), m_disponible(disponible), m_nom(nom), m_prenom(prenom), m_dateEmprunt(dateEmprunt), m_dateRetour(dateRetour)
{
}

bool Livre::ajouter()
{
    // Vérification de l'existence du livre
    QSqlQuery query;
    query.prepare("SELECT id FROM livres WHERE titre = :titre AND auteur = :auteur AND annee = :annee");
    query.bindValue(":titre", m_titre);
    query.bindValue(":auteur", m_auteur);
    query.bindValue(":annee", m_annee);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la vérification de l'existence d'un livre:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        qDebug() << "Le livre existe déjà";
        return false;
    }

    query.prepare("INSERT INTO livres (type,titre, auteur, annee, disponible) VALUES (:type,:titre, :auteur, :annee, :disponible)");
    query.bindValue(":type", m_type);
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

bool Livre::estEmprunte(int id)
{
    QSqlQuery query;
    query.prepare("SELECT disponible FROM livres WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la vérification de l'emprunt d'un livre:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        return !query.value(0).toBool();
    }

    return false;
}

bool Livre::emprunter(int id, QString nom, QString prenom, QDate date)
{
    QSqlQuery query;
    query.prepare("UPDATE livres SET disponible = 0, personne_nom = :nom, personne_prenom = :prenom, date_emprunt = :date, date_retour = :dateRetour WHERE id = :id AND disponible = 1");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date", date);
    query.bindValue(":dateRetour", date.addDays(15));

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
    query.prepare("UPDATE livres SET disponible = 1, personne_nom = '', personne_prenom = '', date_emprunt = NULL, date_retour = NULL WHERE id = :id AND disponible = 0");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors du retour d'un livre:" << query.lastError().text();
        return false;
    }

    if (query.numRowsAffected() == 0) {
        qDebug() << "Impossible de rendre le livre avec l'ID" << id;
        return false;
    }

    return true;
}
