#include "name_generator.h"

namespace NinjaSim
{

NameGenerator::NameGenerator()
{
    // Fill the map of Japanese name fragments
    m_fragments['a'] = "ka";
    m_fragments['b'] = "zu";
    m_fragments['c'] = "mi";
    m_fragments['d'] = "te";
    m_fragments['e'] = "ku";
    m_fragments['f'] = "lu";
    m_fragments['g'] = "ji";
    m_fragments['h'] = "ri";
    m_fragments['i'] = "ki";

    m_fragments['j'] = "zu";
    m_fragments['k'] = "me";
    m_fragments['l'] = "ta";
    m_fragments['m'] = "rin";
    m_fragments['n'] = "to";
    m_fragments['o'] = "mo";
    m_fragments['p'] = "no";
    m_fragments['q'] = "ke";
    m_fragments['r'] = "shi";

    m_fragments['s'] = "ari";
    m_fragments['t'] = "chi";
    m_fragments['u'] = "do";
    m_fragments['v'] = "ru";
    m_fragments['w'] = "mei";
    m_fragments['x'] = "na";
    m_fragments['y'] = "fu";
    m_fragments['z'] = "zi";
}

QString NameGenerator::generateComponent(QString inputName, int lettersToUse)
{
    QString name;
    for (int i = 0; i < lettersToUse && i < inputName.size(); i++)
    {
        QChar letter = inputName.at(i).toLower();
        if (m_fragments.contains(letter))
            name += m_fragments.value(letter);
    }
    // Capitalize the first letter
    if (name.size() > 0)
        name[0] = name[0].toUpper();

    return name;
}

QString NameGenerator::generateNinjaName(QString familyName, QString givenName)
{
    // Use the first 3 letters of the family name
    QString first = generateComponent(familyName, 3);

    // Use the first 4 letters of the given name
    QString last = generateComponent(givenName, 4);

    // Return the combined ninja name
    return first + " " + last;
}

}
