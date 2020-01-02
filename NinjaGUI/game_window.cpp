#include <stdexcept>

#include <QDebug>
#include <QFileInfo>

#include "game_window.h"
#include "ui_game_window.h"

static QString inputFolderPath()
{
    QString current = QDir::currentPath();
    qDebug() << current;
    QDir input(current + "/../../NinjaGame/input/maps");
    if (input.exists())
        return input.canonicalPath();
    else
        return current;
}

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    m_fileSystemModel(new QFileSystemModel(this))
{
    ui->setupUi(this);

    // Set up the tree view
    QString dir = inputFolderPath();
    qDebug() << "Input folder path:" << dir;
    m_fileSystemModel->setRootPath("");
    m_fileSystemModel->setFilter(QDir::AllEntries | QDir::QDir::NoDot);
    ui->fileListView->setModel(m_fileSystemModel.get());

    if (!dir.isEmpty())
    {
        const QModelIndex rootIndex =
            m_fileSystemModel->index(QDir::cleanPath(dir));
        if (rootIndex.isValid())
            ui->fileListView->setRootIndex(rootIndex);
        ui->pathEdit->setText(dir);
    }
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::outputLine(QString line)
{
    ui->outputText->moveCursor(QTextCursor::End);
    ui->outputText->insertPlainText(line + '\n');
}

void GameWindow::on_fileOpenButton_clicked()
{
    auto index = ui->fileListView->currentIndex();
    if (m_fileSystemModel->fileInfo(index).isFile())
    {
        openFile(m_fileSystemModel->filePath(index));
    }
}

void GameWindow::on_fileReloadButton_clicked()
{
    QString path = ui->mapLabel->text();

    if (QFileInfo(path).isFile())
    {
        openFile(ui->mapLabel->text());
    }
}

void GameWindow::on_fileListView_doubleClicked(const QModelIndex &index)
{
    QString path = QDir::cleanPath(m_fileSystemModel->filePath(index));
    qDebug() << path;

    if (m_fileSystemModel->fileInfo(index).isDir())
    {
        ui->pathEdit->setText(path);
        const QModelIndex rootIndex = m_fileSystemModel->index(path);
        if (rootIndex.isValid())
            ui->fileListView->setRootIndex(rootIndex);
    }
    else
    {
        openFile(path);
    }
}

void GameWindow::on_pathEdit_returnPressed()
{
    QString path = ui->pathEdit->text();
    qDebug() << path;

    if (QFileInfo(path).isDir())
    {
        const QModelIndex rootIndex = m_fileSystemModel->index(path);
        if (rootIndex.isValid())
            ui->fileListView->setRootIndex(rootIndex);
    }
}

void GameWindow::openFile(QString filename)
{
    ui->outputText->clear();

    try
    {
        m_simulation.reset(new NinjaSim::Simulation(filename, this));
        ui->mapLabel->setText(filename);
        outputLine(QString("Map opened: %1").arg(filename));

        updatePlayerStats();
        ui->gameView->setSimulation(m_simulation.get());
        resize(700 + ui->gameView->width(), height());
    }
    catch (std::exception& e)
    {
        qWarning("Exception: %s", e.what());
        outputLine(QString("Exception: %1").arg(e.what()));

        ui->mapLabel->setText("<None>");
        ui->gameView->setSimulation(nullptr);
        m_simulation.clear();
    }

    ui->gameView->update();
}

void GameWindow::updatePlayerStats()
{
    if (!m_simulation)
        return;

    auto player = m_simulation->primaryPlayer();
    QString state = player->breakerMode() ? "ON" : "OFF";
    ui->breakerLabel->setText(QString("Breaker: %1").arg(state));
    quint32 shurikens = player->shurikens();
    ui->shurikenLabel->setText(QString("Shurikens: %1").arg(shurikens));
    int steps = player->actionList().size();
    ui->stepsLabel->setText(QString("Steps: %1").arg(steps));
}

void GameWindow::on_runSingleButton_clicked()
{
    if (!m_simulation || !m_simulation->canProceed())
        return;

    QString action = m_simulation->runSingleStep();
    if (!action.isEmpty()) outputLine(action);
    if (m_simulation->completed())
        outputLine("GAME OVER");
    if (m_simulation->loopDetected())
        outputLine("LOOP");

    updatePlayerStats();
    ui->gameView->update();
}

void GameWindow::on_runFullButton_clicked()
{
    if (!m_simulation || !m_simulation->canProceed())
        return;

    bool completed = m_simulation->runFullGame();

    if (completed)
    {
        // If the game has been completed, we will display all actions of
        // the primary player
        auto player = m_simulation->primaryPlayer();
        ui->outputText->setText(player->actionList().join("\n"));
    }
    else
    {
        // Otherwise just display a single line to indicate a loop
        ui->outputText->setText("LOOP");
    }

    updatePlayerStats();
    ui->gameView->update();
}
