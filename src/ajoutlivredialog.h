#ifndef AJOUTLIVREDIALOG_H
#define AJOUTLIVREDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QDateEdit>
#include "livre.h"

class AjoutLivreDialog : public QDialog
{
    Q_OBJECT

public:
    AjoutLivreDialog(QWidget *parent = nullptr);

private slots:
    void ajouterLivre();

private:
    QLineEdit *m_titreEdit;
    QLineEdit *m_auteurEdit;
    QDateEdit *m_anneeEdit;
    QPushButton *m_ajouterButton;
};

#endif // AJOUTLIVREDIALOG_H

