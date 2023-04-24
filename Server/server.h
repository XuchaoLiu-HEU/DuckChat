#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
//#include <QAbstractSocket>
#include <QDebug>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    bool Connect(int port);  //监听函数
    QString getContent();
    void setReuseAddress(bool enable);

signals:
    void getMessage(QString);
    void playerConnected();

public slots:
    void sendData(QString);
    void clientDisconnected();
    void receiveData();

protected:
    void incomingConnection(qintptr handle) override;

private:
    QList<QTcpSocket*> m_clients;
    QString m_content;
};

#endif // SERVER_H
