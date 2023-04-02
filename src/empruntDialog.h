#ifndef EMPRUNTDIALOG_H
#define EMPRUNTDIALOG_H

#include <QDialog>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDate>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

class EmpruntDialog : public QDialog
{
    Q_OBJECT

public:
    EmpruntDialog(QWidget *parent = nullptr);

    void setLivreId(int id);
    // do getNom(), getPrenom(), getDateEmprunt()
    QString getNom() const;
    QString getPrenom() const;
    QDate getDateEmprunt() const;

private slots:
    void onOkButtonClicked();

private:
    int m_livreId;
    QLabel *m_nomLabel;
    QLabel *m_prenomLabel;
    QLabel *m_dateLabel;
    QLineEdit *m_nomEdit;
    QLineEdit *m_prenomEdit;
    QDateEdit *m_dateEdit;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
};

#endif // EMPRUNTDIALOG_H
