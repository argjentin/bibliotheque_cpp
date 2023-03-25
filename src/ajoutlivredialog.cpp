#include "ajoutlivredialog.h"
#include <QLabel>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QX11Info>

AjoutLivreDialog::AjoutLivreDialog(QWidget *parent)
    : QDialog(parent), m_titreEdit(new QLineEdit), m_auteurEdit(new QLineEdit), m_anneeEdit(new QDateEdit), m_ajouterButton(new QPushButton("Ajouter"))
{
    setWindowTitle("Ajouter un livre");

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Titre", m_titreEdit);
    formLayout->addRow("Auteur", m_auteurEdit);
    formLayout->addRow("Année", m_anneeEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_ajouterButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(m_ajouterButton, &QPushButton::clicked, this, &AjoutLivreDialog::ajouterLivre);
}

void AjoutLivreDialog::ajouterLivre()
{
    QString titre = m_titreEdit->text();
    QString auteur = m_auteurEdit->text();
    int annee = m_anneeEdit->date().year();

    if (titre.isEmpty() || auteur.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs");
        return;
    }

    Livre livre(titre, auteur, annee, true);

    if (!livre.ajouter()) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ajouter le livre");
        return;
    }

    accept();
}

