#pragma once

#include <QMainWindow>
#include <QFileSystemModel>
#include <QSharedPointer>

#include "simulation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void updatePlayerStats();
    
private:
    void openFile(QString filename);

    void outputLine(QString line);

private slots:
    void on_fileOpenButton_clicked();

    void on_fileListView_doubleClicked(const QModelIndex &index);

    void on_pathEdit_returnPressed();

    void on_fileReloadButton_clicked();

    void on_runSingleButton_clicked();

    void on_runFullButton_clicked();

private:
    Ui::GameWindow *ui;

    QSharedPointer<QFileSystemModel> m_fileSystemModel;
    QSharedPointer<Simulation> m_simulation;
};

