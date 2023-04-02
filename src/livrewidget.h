#ifndef LIVREWIDGET_H
#define LIVREWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QtWidgets>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

class LivreWidget : public QWidget
{
    Q_OBJECT // Macro pour utiliser les slots et signaux

public:
    LivreWidget(QWidget *parent = nullptr); // Constructeur

public slots: // Déclaration des slots
    void ajouterLivre();
    void supprimerLivre();
    void emprunterLivre();
    void rendreLivre();
    void trierLivres();
    void actualiserListeLivres();
    void exportToTxtMenu();
    void setFullScreenMenu();
    void setNormalScreenMenu();
    void afficherSearchDialog();

private:
    QTableView *m_tableView; // Pointeur vers un QTableView
    QSqlTableModel *m_tableLivres; // Pointeur vers un QSqlTableModel
};

#endif // LIVREWIDGET_H
