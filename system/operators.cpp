#include "operators.h"

std::vector<QString> Operators::names() const
{
    return _names;
}

QDomDocument Operators::generateXML()
{
    QDomDocument doc;

    QDomNode xmlNode = doc.createProcessingInstruction("xml",
                       "version=\"1.0\" encoding=\"UTF-8\" ");
    doc.insertBefore(xmlNode, doc.firstChild());
    QDomElement operators = doc.createElement("operators");

    for(auto it=_names.begin(); it!=_names.end(); it++) {
        QDomElement op = doc.createElement("operator");
        QDomElement name = doc.createElement("name");
        name.appendChild(doc.createTextNode(it.operator*()));
        op.appendChild(name);
        operators.appendChild(op);
    }

    doc.appendChild(operators);
    return doc;
}

void Operators::parseXML(QDomDocument doc)
{
    QDomNode operators = doc.firstChildElement("operators");
    auto ops = operators.childNodes();
    for(int i=0; i<ops.size(); i++) {
        QDomNode op = ops.at(i);
        QDomNode name = op.firstChildElement("name");
        QString nameStr = name.toElement().text();
        _names.push_back(nameStr);
    }
}

void Operators::saveToFile()
{
    logEvent("Operators","Saving to file");
    QFile outFile(_filePath);
    outFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QDomDocument doc = generateXML();
    QTextStream stream(&outFile);
    stream << doc.toString();
    outFile.close();
}

void Operators::loadFromFile()
{
    logEvent("Operators","Loading from file");
    QDomDocument doc;
    QFile inputFile(_filePath);
    if (!inputFile.open(QIODevice::ReadOnly) || !doc.setContent(&inputFile)) {
        qDebug() << "Cannot read file" << _filePath;
        return;
    }
    inputFile.close();
    parseXML(doc);
}

Operators::Operators(QObject *parent) : QObject(parent)
{

}

Operators::~Operators()
{
    saveToFile();
}

void Operators::init(Filesystem * fs)
{
    _filePath = fs->getOperatorsPath() + "/operators.xml";
    _names.clear();
    loadFromFile();
    saveToFile();

}

void Operators::add(QString name)
{
    _names.push_back(name);
    saveToFile();
    emit operatorsListChanged();
}

void Operators::remove(QString name)
{
    if(!_names.empty()) {
        auto remove = _names.end();
        for(auto it=_names.begin(); it!=_names.end(); it++) {
            QString op = it.operator*();
            if(name.compare(op) == 0) {
                remove = it;
            }
        }
        _names.erase(remove);
        emit operatorsListChanged();
    }
    saveToFile();
}
