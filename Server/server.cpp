#include "server.h"

Server::Server(QObject *parent) : QTcpServer{parent}
{
}

// 开启服务端口
bool Server::Connect(int port)
{
    qDebug() << "监听";
    if(listen(QHostAddress::Any, port))// 开启端口，监听任意IP地址和指定端口
        return true;
}

// 接收新的连接请求，并处理
void Server::incomingConnection(qintptr handle)
{
    // 新建一个socket，并与新的客户端连接关联
    QTcpSocket *socket = new QTcpSocket(this);
    if(socket->setSocketDescriptor(handle)){

        connect(socket, &QTcpSocket::readyRead, this, &Server::receiveData);            // 服务器数据可读
        connect(socket, &QTcpSocket::disconnected, this, &Server::clientDisconnected);  // 客户端断开

        m_clients.append(socket);
        emit playerConnected();

        socket->setParent(this);  // 内存管理
    }
}

// 接收客户端发送过来的消息
void Server::receiveData()
{
    // 获取发送消息的QTcpSocket对象
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket)
    {
        // 读取socket中的消息，转换为QString类型
        QString str = QString::fromUtf8(socket->readAll());
        m_content = str;
        // 发射getMessage信号，将接收到的消息发送到UI界面显示
        emit getMessage(str);
    }
}

// 向所有客户端发送消息
void Server::sendData(QString text)
{
    for (QTcpSocket *socket : m_clients)
    {
        // 将消息转换为QByteArray类型，并发送到每个客户端
        socket->write(text.toUtf8());
    }
}

// 获取服务端已接收到的所有消息
QString Server::getContent()
{
    return m_content;
}

// 客户端断开连接处理
void Server::clientDisconnected()
{
    // 获取发送断开连接信号的QTcpSocket对象
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket)
    {
        m_clients.removeOne(socket);
        socket->deleteLater();
    }
}
