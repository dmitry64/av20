#ifndef OPERATORS_H
#define OPERATORS_H

#include <QString>
#include <QObject>
#include <vector>

class Operators : public QObject
{
    Q_OBJECT

    std::vector<QString> _names;
public:
    Operators(QObject *parent = 0);
    void init();
    void add(QString name);
    void remove(QString name);
    std::vector<QString> names() const;
signals:
    void operatorsListChanged();
};

#endif // OPERATORS_H
