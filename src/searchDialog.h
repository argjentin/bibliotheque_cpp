#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSqlTableModel>
#include <QTableView>
#include <QtWidgets>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr);

signals:
    void actualiserListeLivres();

private slots:
    void lancerRecherche();
    void annulerRecherche();
    void actualiserRecherche();

private:
    void afficherResultats(QString titre);

    QLineEdit *m_rechercheEdit;
    QSqlTableModel *m_tableLivres;
    QTableView *m_tableView;

};
#endif // SEARCHDIALOG_H
