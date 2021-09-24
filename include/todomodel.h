#ifndef TODOMODEL_H
#define TODOMODEL_H
#include "todo.h"
#include <QAbstractListModel>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>

class ToDoModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ToDoModel(const QString url_p = "",
                       const QString add_p = "",
                       const QString del_p = "",
                       const QString update_p = "",
                       const QString get_p = "",
                       QObject *parent = nullptr);
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& parent = {}) const override;
    QVariant data(const QModelIndex& index = {}, int role = Qt::DisplayRole) const override;
    ~ToDoModel();

signals:


public slots:
    void initData(const QString &email);
    void addTodo(const QString &email, const QString &text);
    void updateToDo(const QString &newText, const int& index = {});
    void deleteTodo(const int& index);
    void initReplyReadyRead();
    void addReplyReadyRead();

private:
    QString m_baseUrl;
    QString m_addPrefix;
    QString m_deletePrefix;
    QString m_updatePrefix;
    QString m_getPrefix;
    QNetworkAccessManager *m_networkManeger;
    QNetworkReply *m_networkReply;
    std::vector<ToDo> m_todos;

    enum todosRoles { ToDoText, Id };
    void parseResponse(const QByteArray &response);
};

#endif // TODOMODEL_H
