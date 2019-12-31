#pragma once

#include <QString>
#include <QMap>

namespace NinjaSim
{
// A ninja name generator
class NameGenerator
{
public:
    NameGenerator();

    QString generateNinjaName(QString familyName, QString givenName);

private:

    QString generateComponent(QString inputName, int lettersToUse);

private:

    QMap<QChar, QString> m_fragments;
    void generateComponent();
};
}

