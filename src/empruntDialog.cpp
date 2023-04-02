#include "empruntDialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

EmpruntDialog::EmpruntDialog(QWidget *parent) : QDialog(parent)
{
    // Créer les widgets
    m_nomLabel = new QLabel("Nom");
    m_prenomLabel = new QLabel("Prénom");
    m_dateLabel = new QLabel("Date d'emprunt");
    m_nomEdit = new QLineEdit;
    m_prenomEdit = new QLineEdit;
    m_dateEdit = new QDateEdit;
    m_okButton = new QPushButton("OK");
    m_cancelButton = new QPushButton("Annuler");    

    // Créer le layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *nomLayout = new QHBoxLayout;
    QHBoxLayout *prenomLayout = new QHBoxLayout;
    QHBoxLayout *dateLayout = new QHBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // Ajouter les widgets au layout
    nomLayout->addWidget(m_nomLabel);
    nomLayout->addWidget(m_nomEdit);
    prenomLayout->addWidget(m_prenomLabel);
    prenomLayout->addWidget(m_prenomEdit);
    dateLayout->addWidget(m_dateLabel);
    dateLayout->addWidget(m_dateEdit);
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);    

    // Connexion des signaux et des slots
    connect(m_okButton, &QPushButton::clicked, this, &EmpruntDialog::onOkButtonClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &EmpruntDialog::reject);

    // Ajouter les layouts au layout principal
    mainLayout->addLayout(prenomLayout);
    mainLayout->addLayout(nomLayout);
    mainLayout->addLayout(dateLayout);
    mainLayout->addLayout(buttonLayout);

    // Définir le layout principal
    setLayout(mainLayout);

    // Définir les valeurs par défaut
    m_dateEdit->setDate(QDate::currentDate());

    // Définir le titre de la fenêtre
    setWindowTitle("Emprunt");

    // Définir la taille minimale de la fenêtre
    setMinimumSize(300, 200);
    
}

void EmpruntDialog::setLivreId(int id)
{
    m_livreId = id;
}

QString EmpruntDialog::getNom() const
{
    return m_nomEdit->text();
}

QString EmpruntDialog::getPrenom() const
{
    return m_prenomEdit->text();
}

QDate EmpruntDialog::getDateEmprunt() const
{
    return m_dateEdit->date();
}

void EmpruntDialog::onOkButtonClicked()
{
    if (m_nomEdit->text().isEmpty() || m_prenomEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Le nom et le prénom sont obligatoires");
        return;
    }

    accept();
}


