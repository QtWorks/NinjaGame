#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QSharedPointer>
#include <QTextStream>

#include <iostream>
#include <stdexcept>

#include "ninjasim/simulation.h"

void runSimulation(QString path)
{
    try
    {
        // Create a simulation using the given map file
        NinjaSim::Simulation simulation(path);

        // Run the full simulation
        bool completed = simulation.runFullGame();

        // Check if the game has been completed
        if (completed)
        {
            // Print all actions of the primary player
            auto player = simulation.primaryPlayer();
            QTextStream(stdout) << player->actionList().join("\n") << endl;
        }
        else
        {
            // Otherwise just print a single line to indicate that a loop
            // has been detected
            QTextStream(stdout) << "LOOP" << endl;
        }
    }
    catch (std::exception& e)
    {
        qWarning("Exception: %s", e.what());
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("NinjaCLI Application");
    parser.addHelpOption();

    parser.addPositionalArgument(
        "input", "The input file that contains a list of filenames.");
    parser.process(app);

    // If the input argument is missing, print the usage text and exit!
    if (parser.positionalArguments().isEmpty())
    {
        parser.showHelp(1);
    }

    QString listPath = parser.positionalArguments().first();

    if (!QFileInfo(listPath).isFile())
    {
        qWarning() << "Missing input file:" << listPath;
        return 1;
    }

    QFile listFile(listPath);
    if (!listFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Cannot open file:" << listPath;
        return 1;
    }

    // Get the path to the base folder to handle relative paths
    QString basePath = QFileInfo(listPath).dir().path();

    QTextStream stream(&listFile);
    while (!stream.atEnd())
    {
        QString path = stream.readLine();

        QTextStream(stdout) << "----------------------------" << endl;
        QTextStream(stdout) << "Opening map file: " << path << endl;

        // Calculate the relative path to the map file
        path = basePath + '/' + path;

        if (QFileInfo(path).isFile())
        {
            runSimulation(path);
        }
        else
        {
            qWarning() << "Missing map file:" << path;
        }
    }

    return 0;
}
