// connexion à la base de données

#include "connexion.h"
#include "livrewidget.h"
#include "livre.h"
#include "ajoutlivredialog.h"
#include <QtWidgets>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QX11Info>



LivreWidget::LivreWidget(QWidget *parent) // Constructeur
    : QWidget(parent), m_tableView(new QTableView), m_tableModel(new QSqlTableModel) 
{
    QVBoxLayout *layout = new QVBoxLayout; // Création d'un layout vertical
    layout->addWidget(m_tableView);
    setLayout(layout);

    m_tableModel->setTable("livres"); // Définition de la table à utiliser
    m_tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_tableModel->select(); // Sélection des données de la table
    m_tableView->setModel(m_tableModel); // Définition du modèle à utiliser

    QMenu *menu = new QMenu(this);
    QAction *action = new QAction(tr("Quitter"), this);
    connect(action, &QAction::triggered, qApp, &QApplication::quit);
    menu->addAction(action);

    QPushButton *menuButton = new QPushButton(tr("Menu"));
    menuButton->setMenu(menu);

    // the menu is't visible
    menuButton->showMenu();
    


    m_tableView->setColumnHidden(0, true); // Masquer la colonne 0



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
    m_tableModel->setSort(3, Qt::AscendingOrder);
    m_tableModel->select();
}



void LivreWidget::actualiserListeLivres()
{
    m_tableModel->select();
}


