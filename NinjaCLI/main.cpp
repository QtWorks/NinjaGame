#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QSharedPointer>
#include <QDebug>

#include <iostream>

#include "simulation.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("NinjaCLI Application");
    parser.addHelpOption();
//    QCommandLineOption op1("c", "Option1");
//    parser.addOption(op1);
//    parser.addPositionalArgument("directory", "The directory to start in.");
    parser.process(app);
//    const QString rootPath = parser.positionalArguments().isEmpty()
//        ? QString() : parser.positionalArguments().first();

    QSharedPointer<Simulation> sim(new Simulation());

    //qDebug() << sim->getName();

    return 0;
}
