#include "operators.h"

std::vector<QString> Operators::names() const
{
    return _names;
}

Operators::Operators(QObject *parent) : QObject(parent)
{

}

void Operators::init()
{
    _names.push_back("Petrov A.D.");
}

void Operators::add(QString name)
{
    _names.push_back(name);
    emit operatorsListChanged();
}

void Operators::remove(QString name)
{
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
