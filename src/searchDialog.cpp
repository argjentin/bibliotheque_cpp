#include "searchDialog.h"
#include <QtWidgets>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

SearchDialog::SearchDialog(QWidget *parent)
    : QDialog(parent), m_rechercheEdit(new QLineEdit),
      m_tableView(new QTableView), m_tableLivres(new QSqlTableModel)
{
    setWindowTitle(tr("Recherche de livres"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_rechercheEdit);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(new QLabel(tr("Titre")));
    layout->addLayout(hLayout);

    QPushButton *lancerRechercheButton = new QPushButton(tr("Lancer la recherche"));
    connect(lancerRechercheButton, &QPushButton::clicked, this, &SearchDialog::lancerRecherche);
    layout->addWidget(lancerRechercheButton);

    m_tableLivres->setTable("livres");
    m_tableLivres->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_tableLivres->select();

    m_tableView->setModel(m_tableLivres);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_tableView->setColumnHidden(0, true);

    m_tableLivres->setHeaderData(1, Qt::Horizontal, tr("Genre"));
    m_tableLivres->setHeaderData(2, Qt::Horizontal, tr("Titre"));
    m_tableLivres->setHeaderData(3, Qt::Horizontal, tr("Auteur"));
    m_tableLivres->setHeaderData(4, Qt::Horizontal, tr("Année"));
    m_tableLivres->setHeaderData(5, Qt::Horizontal, tr("Disponibilité"));
    m_tableLivres->setHeaderData(6, Qt::Horizontal, tr("Nom"));
    m_tableLivres->setHeaderData(7, Qt::Horizontal, tr("Prénom"));
    m_tableLivres->setHeaderData(8, Qt::Horizontal, tr("Date d'emprunt"));
    m_tableLivres->setHeaderData(9, Qt::Horizontal, tr("Date de retour"));
    m_tableView->resizeColumnsToContents();

    layout->addWidget(m_tableView);

    QPushButton *annulerButton = new QPushButton(tr("Annuler la recherche"));
    connect(annulerButton, &QPushButton::clicked, this, &SearchDialog::annulerRecherche);
    layout->addWidget(annulerButton);

    setLayout(layout);
}

void SearchDialog::lancerRecherche()
{
    QString titre = m_rechercheEdit->text();

    if (titre.isEmpty()) {
        QMessageBox::information(this, tr("Recherche de livres"), tr("Entrez un titre à rechercher."));
        return;
    }

    afficherResultats(titre);
}

void SearchDialog::annulerRecherche()
{
    m_rechercheEdit->clear();
    m_tableLivres->setFilter("");
    m_tableLivres->select();

    m_tableView->clearSelection();

    // Désélectionner toutes les lignes de la vue de la table
    // QModelIndexList selectedIndexList = m_tableView->selectionModel()->selectedIndexes();
    // foreach (QModelIndex selectedIndex, selectedIndexList) {
    //     m_tableView->selectionModel()->select(selectedIndex, QItemSelectionModel::Deselect);
    // }
}

void SearchDialog::actualiserRecherche()
{
    QString titre = m_rechercheEdit->text();

    QSqlQuery query;
    query.prepare("SELECT titre FROM livres WHERE titre LIKE :titre");
    query.bindValue(":titre", QString("%%1%").arg(titre));
    query.exec();

    if (query.next()) {
        afficherResultats(titre);
    }

    else {
        QMessageBox::information(this, tr("Recherche de livres"), tr("Aucun livre ne correspond à votre recherche."));
    }

    emit actualiserListeLivres();
}

void SearchDialog::afficherResultats(QString titre)
{
    m_tableLivres->setFilter(QString("titre LIKE '%1%'").arg(titre));
    m_tableLivres->select();

    if (m_tableLivres->rowCount() == 0) {
        QMessageBox::information(this, tr("Recherche de livres"), tr("Aucun livre ne correspond à votre recherche."));
    }

    else {
        QMessageBox::information(this, tr("Recherche de livres"), tr("%1 livre(s) correspond(ent) à votre recherche.").arg(m_tableLivres->rowCount()));
    }
}

