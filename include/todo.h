#ifndef TODO_H
#define TODO_H
#include <QObject>


class ToDo
{
public:
    ToDo(QString text, QString id);
    QString getText() const;
    QString getId() const;

private:
    QString text;
    QString id;
};

#endif // TODO_H
