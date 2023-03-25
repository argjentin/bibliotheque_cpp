#ifndef LIVREWIDGET_H
#define LIVREWIDGET_H

#include <QWidget>
#include <QX11Info>
#include <QSqlTableModel>
#include <QTableView>

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

private:
    QTableView *m_tableView; // Pointeur vers un QTableView
    QSqlTableModel *m_tableModel; // Pointeur vers un QSqlTableModel
};

#endif // LIVREWIDGET_H
