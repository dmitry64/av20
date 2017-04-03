#ifndef OPERATORS_H
#define OPERATORS_H

#include <QString>
#include <QObject>
#include <vector>
#include "filesystem.h"


class Operators : public QObject
{
    Q_OBJECT

    QString _filePath;
    std::vector<QString> _names;
    QDomDocument generateXML();
    void parseXML(const QDomDocument &doc);
    void saveToFile();
    void loadFromFile();
public:
    explicit Operators(QObject *parent = 0);
    ~Operators();
    void init(Filesystem *fs);
    void add(const QString & name);
    void remove(const QString & name);
    std::vector<QString> names() const;
signals:
    void operatorsListChanged();
};

#endif // OPERATORS_H
