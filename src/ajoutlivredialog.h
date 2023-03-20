#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include "livre.h"

class AjoutLivreDialog : public QDialog
{
    Q_OBJECT

public:
    AjoutLivreDialog(QWidget *parent = nullptr);

private slots:
    void ajouterLivre();

private:
    QLineEdit *m_titreLineEdit;
    QLineEdit *m_auteurLineEdit;
    QSpinBox *m_anneeSpinBox;
};

AjoutLivreDialog::AjoutLivreDialog(QWidget *parent)
    : QDialog(parent), m_titreLineEdit(new QLineEdit), m_auteurLineEdit(new QLineEdit), m_anneeSpinBox(new QSpinBox)
{
    // Définition du formulaire
    QLabel *titreLabel = new QLabel(tr("Titre :"));
    QLabel *auteurLabel = new QLabel(tr("Auteur :"));
    QLabel *anneeLabel = new QLabel(tr("Année :"));

    m_titreLineEdit = new QLineEdit;
    m_auteurLineEdit = new QLineEdit;
    m_anneeSpinBox = new QSpinBox;
    m_anneeSpinBox->setRange(0, 2100);

    QPushButton *ajouterButton = new QPushButton(tr("Ajouter"));
    QPushButton *annulerButton = new QPushButton(tr("Annuler"));

    // Layout
    QFormLayout *layout = new QFormLayout;
    layout->addRow(titreLabel, m_titreLineEdit);
    layout->addRow(auteurLabel, m_auteurLineEdit);
    layout->addRow(anneeLabel, m_anneeSpinBox);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(ajouterButton);
    buttonLayout->addWidget(annulerButton);
    layout->addRow(buttonLayout);
    setLayout(layout);

    // Connexion des signaux et des slots
    connect(ajouterButton, &QPushButton::clicked, this, &AjoutLivreDialog::ajouterLivre);
    connect(annulerButton, &QPushButton::clicked, this, &AjoutLivreDialog::reject);
}

void AjoutLivreDialog::ajouterLivre()
{
    // Création d'un objet Livre
    Livre livre(m_titreLineEdit->text(), m_auteurLineEdit->text(), m_anneeSpinBox->value());

    // Ajout du livre à la base de données
    livre.ajouter();

    // Fermeture de la fenêtre
    accept();
}

