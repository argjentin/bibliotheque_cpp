#ifndef TRIDIALOG_H
#define TRIDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QString>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

class TriDialog : public QDialog
{
    Q_OBJECT

public:
    TriDialog(QWidget *parent = nullptr);
    int getColonne() const;
    Qt::SortOrder getOrdre() const;
    Qt::SortOrder getOrdreAnnee() const;

signals:
    void trierLivres(int colonne, Qt::SortOrder ordre, Qt::SortOrder ordreAnnee);

private slots:
    void onOkButtonClicked();

private:
    QLabel *m_colonneLabel;
    QLabel *m_ordreLabel;
    QLabel *m_ordreAnneeLabel;
    QComboBox *m_colonneComboBox;
    QComboBox *m_ordreComboBox;
    QComboBox *m_ordreAnneeComboBox;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
};

#endif // TRIDIALOG_H