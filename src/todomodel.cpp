#include "include/todomodel.h"
#include <QNetworkRequest>
#include <QVariantMap>
#include <QMap>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <typeinfo>

ToDoModel::ToDoModel(const QString url,
                     const QString add_p,
                     const QString del_p,
                     const QString update_p,
                     const QString get_p,
                     QObject *parent) : QAbstractListModel(parent),
    m_baseUrl {std::move(url)},
    m_addPrefix {std::move(add_p)},
    m_deletePrefix {std::move(del_p)},
    m_updatePrefix {std::move(update_p)},
    m_getPrefix {std::move(get_p)}
{
   m_networkManeger = new QNetworkAccessManager( this );

/*
   ToDo one("gogo", "1");
   ToDo two("go", "2");

   m_todos.push_back(one);
   m_todos.push_back(two);
*/
}

ToDoModel::~ToDoModel()
{
    m_networkManeger->deleteLater();
    delete m_networkManeger;
    delete m_networkReply;
}

QVariant ToDoModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() > rowCount(index)) {
        return {};
    }

    const ToDo& todo = m_todos.at(index.row());

    switch (role) {
        case todosRoles::ToDoText: {
            return QVariant::fromValue(todo.getText());
        }
        case todosRoles::Id: {
            return QVariant::fromValue(todo.getId());
        }
        default: {
            return {};
        }
    }
}


QHash<int, QByteArray> ToDoModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ToDoModel::ToDoText] = "text";
    return roles;
}

int ToDoModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_todos.size());
}

void ToDoModel::initData(const QString &email)
{
    QString url = m_baseUrl + m_getPrefix + "/" + email;

    m_networkReply = m_networkManeger->get(QNetworkRequest(QUrl(url)));
    connect( m_networkReply, &QNetworkReply::readyRead, this, &ToDoModel::initReplyReadyRead);
}

void ToDoModel::addTodo(const QString &email, const QString &text)
{
    QVariantMap data;
    data["email"] = email;
    data["todo"] = text;
    QJsonDocument jsonPayload = QJsonDocument::fromVariant(data);

    QNetworkRequest newRequest( (QUrl( m_baseUrl + m_addPrefix )) );
    newRequest.setHeader( QNetworkRequest::ContentTypeHeader, QString( "application/json"));
    m_networkReply = m_networkManeger->post( newRequest, jsonPayload.toJson());
    connect( m_networkReply, &QNetworkReply::readyRead, this, &ToDoModel::addReplyReadyRead);
}

void ToDoModel::updateToDo(const QString &newText, const int& index)
{
    m_todos.at(index).setText(newText);

    QModelIndex mIndex = createIndex(index, 0, static_cast<void *>(0));
    emit dataChanged(mIndex, mIndex);

    QVariantMap data;
    data["id"] = m_todos.at(index).getId();
    data["todo"] = newText;
    QJsonDocument jsonPayload = QJsonDocument::fromVariant(data);

    QNetworkRequest newRequest( (QUrl( m_baseUrl + m_updatePrefix )) );
    newRequest.setHeader( QNetworkRequest::ContentTypeHeader, QString( "application/json"));
    m_networkManeger->post( newRequest, jsonPayload.toJson());
}

void ToDoModel::deleteTodo(const int &index)
{
    QVariantMap data;
    data["id"] = m_todos.at(index).getId();
    QJsonDocument jsonPayload = QJsonDocument::fromVariant(data);

    beginRemoveRows(QModelIndex(), index, index);
    m_todos.erase(m_todos.begin() + index);
    endRemoveRows();

    QNetworkRequest newRequest( (QUrl( m_baseUrl + m_deletePrefix )) );
    newRequest.setHeader( QNetworkRequest::ContentTypeHeader, QString( "application/json"));
    m_networkManeger->post( newRequest, jsonPayload.toJson());
}

void ToDoModel::initReplyReadyRead()
{
    QByteArray response = m_networkReply->readAll();

    m_networkReply->deleteLater();
    parseResponse(response);
}

void ToDoModel::addReplyReadyRead()
{

    QByteArray response = m_networkReply->readAll();
    m_networkReply->deleteLater();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(response);
    QJsonObject obj = jsonDocument.object();

    QString text = obj["todo"].toString();
    QString id = obj["id"].toString();

    beginInsertRows(QModelIndex(), m_todos.size(), m_todos.size());
    ToDo todo(text, id);
    m_todos.push_back(todo);
    endInsertRows();
}


void ToDoModel::parseResponse(const QByteArray &response)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(response);
    QJsonArray jsonArray = jsonDocument.array();

    if (jsonArray.size() == 0) return;

    beginInsertRows(QModelIndex(), m_todos.size(), m_todos.size() + jsonArray.size() - 1);
    for (auto it: jsonArray){
        QJsonObject obj = it.toObject();
        QString text = obj["todo"].toString();
        QString id = obj["id"].toString();

        ToDo todo(text, id);

        m_todos.push_back(todo);
    }

    endInsertRows();
}
