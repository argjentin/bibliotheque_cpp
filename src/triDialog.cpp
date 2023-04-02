#include "triDialog.h"
#include "connexion.h"
TriDialog::TriDialog(QWidget *parent)
    : QDialog(parent),
      m_colonneLabel(new QLabel(tr("Trier par colonne :"))),
      m_ordreLabel(new QLabel(tr("Ordre de tri :"))),
      m_colonneComboBox(new QComboBox),
      m_ordreComboBox(new QComboBox),
      m_okButton(new QPushButton(tr("OK"))),
      m_cancelButton(new QPushButton(tr("Annuler")))
{
    // Remplir la liste des colonnes
    m_colonneComboBox->addItem(tr("Genre"));
    m_colonneComboBox->addItem(tr("Titre"));
    m_colonneComboBox->addItem(tr("Année"));
    m_colonneComboBox->addItem(tr("Disponible"));

    // Remplir la liste des ordres
    m_ordreComboBox->addItem(tr("Croissant"));
    m_ordreComboBox->addItem(tr("Décroissant"));

    // Création du layout
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(m_colonneLabel, 0, 0);
    layout->addWidget(m_colonneComboBox, 0, 1);
    layout->addWidget(m_ordreLabel, 1, 0);
    layout->addWidget(m_ordreComboBox, 1, 1);
    layout->addWidget(m_okButton, 2, 0);
    layout->addWidget(m_cancelButton, 2, 1);

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
    return m_ordreComboBox->currentIndex() == 0 ? Qt::AscendingOrder : Qt::DescendingOrder;
}

void TriDialog::onOkButtonClicked()
{
    emit trierLivres(getColonne(), getOrdre());
    accept();
}

