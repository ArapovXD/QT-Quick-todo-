#ifndef AUTHHANDLER_H
#define AUTHHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>

class AuthHandler : public QObject
{
    Q_OBJECT
public:
    explicit AuthHandler(QObject *parent = nullptr);
    ~AuthHandler();
    void setAPIKey( const QString & apiKey );
    Q_INVOKABLE void signUserUp( const QString &emailAddress, const QString &password );
    Q_INVOKABLE void signUserIn( const QString &emailAddress, const QString &password );
    Q_INVOKABLE QString getUserEmail();


public slots:
    void networkReplyReadyRead();

signals:
    void userSignedIn();
private:
    void performPOST( const QString & url, const QJsonDocument & payload );
    void parseResponse( const QByteArray & reponse );
    QString m_userEmail;
    QString m_apiKey;
    QNetworkAccessManager * m_networkAccessManager;
    QNetworkReply * m_networkReply;
    QString m_idToken;
};

#endif // AUTHHANDLER_H
