#include "triDialog.h"
#include "connexion.h"

TriDialog::TriDialog(QWidget *parent)
    : QDialog(parent),
      m_colonneLabel(new QLabel(tr("Trier par colonne :"))),
      m_ordreLabel(new QLabel(tr("Ordre de tri :"))),
      m_ordreAnneeLabel(new QLabel(tr("Ordre de tri (année) :"))),
      m_colonneComboBox(new QComboBox),
      m_ordreComboBox(new QComboBox),
      m_ordreAnneeComboBox(new QComboBox),
      m_okButton(new QPushButton(tr("OK"))),
      m_cancelButton(new QPushButton(tr("Annuler")))
{
    // Remplir la liste des colonnes
    m_colonneComboBox->addItem(tr("Genre"));
    m_colonneComboBox->addItem(tr("Titre"));
    m_colonneComboBox->addItem(tr("Année"));
    m_colonneComboBox->addItem(tr("Disponible"));

    // Remplir la liste des ordres
    m_ordreComboBox->addItem(tr(""));
    m_ordreComboBox->addItem(tr("Croissant"));
    m_ordreComboBox->addItem(tr("Décroissant"));

    // Remplir la liste des ordres pour l'année
    m_ordreAnneeComboBox->addItem(tr(""));
    m_ordreAnneeComboBox->addItem(tr("Croissant"));
    m_ordreAnneeComboBox->addItem(tr("Décroissant"));

    // Création du layout
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(m_colonneLabel, 0, 0);
    layout->addWidget(m_colonneComboBox, 0, 1);
    layout->addWidget(m_ordreLabel, 1, 0);
    layout->addWidget(m_ordreComboBox, 1, 1);
    layout->addWidget(m_ordreAnneeLabel, 2, 0);
    layout->addWidget(m_ordreAnneeComboBox, 2, 1);
    layout->addWidget(m_okButton, 3, 0);
    layout->addWidget(m_cancelButton, 3, 1);

    setLayout(layout);

    // Connexion des signaux et des slots
    connect(m_okButton, &QPushButton::clicked, this, &TriDialog::onOkButtonClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

int TriDialog::getColonne() const
{
    return m_colonneComboBox->currentIndex();
}

Qt::SortOrder TriDialog::getOrdre() const
{
    return m_ordreComboBox->currentIndex() == 0 ? Qt::AscendingOrder : (m_ordreComboBox->currentIndex() == 1 ? Qt::AscendingOrder : Qt::DescendingOrder);
}

Qt::SortOrder TriDialog::getOrdreAnnee() const
{
    return m_ordreAnneeComboBox->currentIndex() == 0 ? Qt::AscendingOrder : (m_ordreAnneeComboBox->currentIndex() == 1 ? Qt::AscendingOrder : Qt::DescendingOrder);
}

void TriDialog::onOkButtonClicked()
{
    emit trierLivres(getColonne(), getOrdre(), getOrdreAnnee());
    accept();
}