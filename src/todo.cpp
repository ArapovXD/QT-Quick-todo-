#include "./include/todo.h"

ToDo::ToDo(QString text, QString id) :
    text {std::move(text)},
    id {std::move(id)}
{

}

QString ToDo::getText() const
{
    return text;
}

QString ToDo::getId() const
{
    return id;
}


void ToDo::setText(const QString &newText)
{
    text = newText;
}
