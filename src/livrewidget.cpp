#include "connexion.h"
#include "livrewidget.h"
#include "livre.h"
#include "ajoutlivredialog.h"
#include "triDialog.h"
#include "empruntDialog.h"
#include "searchDialog.h"
#include <QtWidgets>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QX11Info>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>


LivreWidget::LivreWidget(QWidget *parent)
    : QWidget(parent), m_tableView(new QTableView), m_tableLivres(new QSqlTableModel)
{
    QVBoxLayout *layout = new QVBoxLayout; // Création d'un layout vertical
    layout->addWidget(m_tableView);
    setLayout(layout);

    // Création du modèle de données
    m_tableLivres->setTable("livres");
    m_tableLivres->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_tableLivres->select();

    // Création de la vue
    m_tableView->setModel(m_tableLivres);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // taille minimale de la fenêtre
    setMinimumSize(915, 600);

    // cacher colonnes de l'id
    m_tableView->setColumnHidden(0, true);

    // renommer les colonnes
    m_tableLivres->setHeaderData(1, Qt::Horizontal, tr("Genre"));
    m_tableLivres->setHeaderData(2, Qt::Horizontal, tr("Titre"));
    m_tableLivres->setHeaderData(3, Qt::Horizontal, tr("Auteur"));
    m_tableLivres->setHeaderData(4, Qt::Horizontal, tr("Année"));
    m_tableLivres->setHeaderData(5, Qt::Horizontal, tr("Disponibilité"));
    m_tableLivres->setHeaderData(6, Qt::Horizontal, tr("Nom"));
    m_tableLivres->setHeaderData(7, Qt::Horizontal, tr("Prénom"));
    m_tableLivres->setHeaderData(8, Qt::Horizontal, tr("Date d'emprunt"));
    m_tableLivres->setHeaderData(9, Qt::Horizontal, tr("Date de retour"));
    m_tableView->resizeColumnsToContents(); // ajuster la taille des colonnes

    // création du menu
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu(tr("Fichier"));
    QMenu *viewMenu = menuBar->addMenu(tr("Affichage"));

    // Ajout des actions au menu Fichier
    QAction *exportToTxtAction = fileMenu->addAction(tr("Exporter en .txt"));
    connect(exportToTxtAction, &QAction::triggered, this, &LivreWidget::exportToTxtMenu);
    QAction *quitAction = fileMenu->addAction(tr("Quitter"));
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

    // Ajout des actions au menu Affichage
    QAction *fullScreenAction = viewMenu->addAction(tr("Plein écran"));
    connect(fullScreenAction, &QAction::triggered, this, &LivreWidget::setFullScreenMenu);
    QAction *normalScreenAction = viewMenu->addAction(tr("Affichage normal"));
    connect(normalScreenAction, &QAction::triggered, this, &LivreWidget::setNormalScreenMenu);

    layout -> setMenuBar(menuBar);

    QPushButton *ajouterButton = new QPushButton(tr("Ajouter"));
    connect(ajouterButton, &QPushButton::clicked, this, &LivreWidget::ajouterLivre);

    QPushButton *supprimerButton = new QPushButton(tr("Supprimer"));
    connect(supprimerButton, &QPushButton::clicked, this, &LivreWidget::supprimerLivre);

    QPushButton *emprunterButton = new QPushButton(tr("Emprunter"));
    connect(emprunterButton, &QPushButton::clicked, this, &LivreWidget::emprunterLivre);

    QPushButton *rendreButton = new QPushButton(tr("Rendre"));
    connect(rendreButton, &QPushButton::clicked, this, &LivreWidget::rendreLivre);

    QPushButton *trierButton = new QPushButton(tr("Trier"));
    connect(trierButton, &QPushButton::clicked, this, &LivreWidget::trierLivres);

    QPushButton *rechercherButton = new QPushButton(tr("Rechercher"));
    connect(rechercherButton, &QPushButton::clicked, this, &LivreWidget::afficherSearchDialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(ajouterButton);
    buttonLayout->addWidget(supprimerButton);
    buttonLayout->addWidget(emprunterButton);
    buttonLayout->addWidget(rendreButton);
    buttonLayout->addWidget(trierButton);
    buttonLayout->addWidget(rechercherButton);

    layout->addLayout(buttonLayout);
}

void LivreWidget::exportToTxtMenu()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exporter la liste des livres"), QDir::homePath(), tr("Fichiers texte (*.txt)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);

        // Ouvrir le fichier en écriture
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            // Écrire les en-têtes de colonnes
            out << "ID\tType\tTitre\tAuteur\tAnnée\tDisponible\tEmprunté par\tDate d'emprunt\tDate de retour";

            // Parcourir les données du modèle de la table
            if (m_tableLivres) {
                int rows = m_tableLivres->rowCount();
                int cols = m_tableLivres->columnCount();
                for (int i = 0; i < rows; i++) {
                    out << '\n';
                    for (int j = 0; j < cols; j++) {
                        out << m_tableLivres->data(m_tableLivres->index(i, j)).toString() << '\t';
                    }
                }
            }

            file.close();
            QMessageBox::information(this, tr("Exporter la liste des livres"), tr("La liste des livres a été exportée avec succès dans le fichier : ") + fileName);
        } else {
            QMessageBox::critical(this, tr("Exporter la liste des livres"), tr("Impossible d'ouvrir le fichier de sauvegarde."));
        }
    }
}

void LivreWidget::setFullScreenMenu()
{
    this->showFullScreen();
}

void LivreWidget::setNormalScreenMenu()
{
    this->showNormal();
}

void LivreWidget::ajouterLivre()
{
    AjoutLivreDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        m_tableLivres->select();
    }
}

void LivreWidget::supprimerLivre()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Supprimer un livre"), tr("Êtes-vous sûr de vouloir supprimer ce livre ?"), QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        int row = m_tableView->currentIndex().row();
        if (row >= 0) {
            int id = m_tableLivres->data(m_tableLivres->index(row, 0)).toInt();
            if (Livre::supprimer(id)) {
                m_tableLivres->select();
            } else {
                QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer le livre."));
            }
        }
    }
}

void LivreWidget::emprunterLivre()
{
    int row = m_tableView->currentIndex().row();
    if (row >= 0) {
        int id = m_tableLivres->data(m_tableLivres->index(row, 0)).toInt();
        if (Livre::estEmprunte(id)) {
            QMessageBox::critical(this, tr("Erreur"), tr("Le livre est déjà emprunté."));
            return;
        }
    }
    EmpruntDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        int row = m_tableView->currentIndex().row();
        if (row >= 0) {
            int id = m_tableLivres->data(m_tableLivres->index(row, 0)).toInt();
            if (Livre::emprunter(id, dialog.getNom(), dialog.getPrenom(), dialog.getDateEmprunt())) {
                m_tableLivres->select();
            } else {
                QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'emprunter le livre."));
            }
        }
    }
}

void LivreWidget::rendreLivre()
{   
    int row = m_tableView->currentIndex().row();
    if (row >= 0) {
        int id = m_tableLivres->data(m_tableLivres->index(row, 0)).toInt();
        if (!Livre::estEmprunte(id)) {
            QMessageBox::critical(this, tr("Erreur"), tr("Le livre n'est pas emprunté."));
            return;
        }
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Rendre un livre"), tr("Êtes-vous sûr de vouloir rendre ce livre ?"), QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        int row = m_tableView->currentIndex().row();
        if (row >= 0) {
            int id = m_tableLivres->data(m_tableLivres->index(row, 0)).toInt();
            if (Livre::rendre(id)) {
                m_tableLivres->select();
            } else {
                QMessageBox::critical(this, tr("Erreur"), tr("Impossible de rendre le livre."));
            }
        }
    }
}

void LivreWidget::trierLivres()
{
    TriDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        m_tableLivres->setSort(dialog.getColonne(), dialog.getOrdre());
        m_tableLivres->select();
    }
}

void LivreWidget::afficherSearchDialog()
{
    SearchDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        m_tableLivres->select();
    }
}


void LivreWidget::actualiserListeLivres()
{
    m_tableLivres->select();
}