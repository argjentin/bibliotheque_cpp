// connexion à la base de données

#include "connexion.h"
#include "livrewidget.h"
#include "livre.h"
#include "ajoutlivredialog.h"
#include "triDialog.h"
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


LivreWidget::LivreWidget(QWidget *parent) // Constructeur
    : QWidget(parent), m_tableView(new QTableView), m_tableModel(new QSqlTableModel) 
{
    QVBoxLayout *layout = new QVBoxLayout; // Création d'un layout vertical
    layout->addWidget(m_tableView);
    setLayout(layout);
    
    // taille de la fenêtre sans impacter les fonctions de la fenêtre
    setMinimumSize(800, 600);


    m_tableModel->setTable("livres"); // Définition de la table à utiliser
    m_tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_tableModel->select(); // Sélection des données de la table
    m_tableView->setModel(m_tableModel); // Définition du modèle à utiliser

    m_tableView->setColumnHidden(0, true); // Masquer la colonne 0

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

    // set the menu bar to the main window
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


    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(ajouterButton);
    buttonLayout->addWidget(supprimerButton);
    buttonLayout->addWidget(emprunterButton);
    buttonLayout->addWidget(rendreButton);
    buttonLayout->addWidget(trierButton);

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
            out << "ID\tType\tTitre\tAuteur\tAnnée\tDisponible\n";

            // Parcourir les données du modèle de la table
            int rows = m_tableModel->rowCount();
            int cols = m_tableModel->columnCount();
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    out << m_tableModel->data(m_tableModel->index(i, j)).toString() << "\t";
                }
                out << "\n";
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
        m_tableModel->select();
    }
}


void LivreWidget::supprimerLivre()
{
    int row = m_tableView->currentIndex().row();
    if (row >= 0) {
        int id = m_tableModel->data(m_tableModel->index(row, 0)).toInt();
        if (Livre::supprimer(id)) {
            m_tableModel->select();
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer le livre."));
        }
    }
}

void LivreWidget::emprunterLivre()
{
    int row = m_tableView->currentIndex().row();
    if (row >= 0) {
        int id = m_tableModel->data(m_tableModel->index(row, 0)).toInt();
        if (Livre::emprunter(id)) {
            m_tableModel->select();
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'emprunter le livre."));
        }
    }
}

void LivreWidget::rendreLivre()
{
    int row = m_tableView->currentIndex().row();
    if (row >= 0) {
        int id = m_tableModel->data(m_tableModel->index(row, 0)).toInt();
        if (Livre::rendre(id)) {
            m_tableModel->select();
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Impossible de rendre le livre."));
        }
    }
}

void LivreWidget::trierLivres()
{
    TriDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        m_tableModel->setSort(dialog.getColonne(), dialog.getOrdre());
        m_tableModel->select();
    }
}

void LivreWidget::actualiserListeLivres()
{
    m_tableModel->select();
}