#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent): QWidget(parent), ui(new Ui::Client) {
    ui->setupUi(this);
    this->setWindowTitle("DuckChat客户端");
    connect(ui->ip, &QLineEdit::returnPressed, this, [=](){ui->port->setFocus();});
//    connect(ui->port, &QLineEdit::returnPressed, this,[=](){ui->connectButton->setFocus();});
    connect(ui->connectButton, &QPushButton::clicked, this, &Client::connectToServer);
    connect(ui->nameEdit, &QLineEdit::returnPressed, this, [=](){ui->send->setFocus();});
    connect(ui->send, &QLineEdit::returnPressed, this, &Client::sendMessage);
}


Client::~Client()
{
    delete ui;
}


void Client::connectToServer()
{
    if(ui->ip->text().isEmpty() || ui->port->text().isEmpty()) {
        QMessageBox::warning(this, "连接失败", "IP地址或端口号不能为空！");
        return;
    }
    socket.connectToHost(ui->ip->text(), ui->port->text().toInt());
    if(socket.waitForConnected(1000)) {
        ui->nameEdit->setFocus();
        text += "成功连接聊天室...\n";
    } else {
        text += "连接失败...\n";
    }
    ui->receive->setText(text);
    connect(&socket, &QTcpSocket::readyRead, this, &Client::receiveData);
}

void Client::receiveData()
{
    QByteArray message = socket.readAll();
    text += message;
    ui->receive->setText(text);
}


void Client::sendMessage()
{
    QString username = ui->nameEdit->text().trimmed();
//    if (username.isEmpty() || username.length() > 20) {
//        QMessageBox::warning(this, "用户名错误", "用户名不能为空且长度不能超过20个字符。");
//        return;
//    }
    QString message = ui->send->text().trimmed();
//    if (message.isEmpty() || message.length() > 200) {
//        QMessageBox::warning(this, "消息错误", "消息不能为空且长度不能超过200个字符。");
//        return;
//    }
//    if (message.contains("@")) {
//        QMessageBox::warning(this, "消息错误", "消息中不能包含@字符。");
//        return;
//    }

    QString new_text = username + ": " + message + "\n";
    text += new_text;
    ui->receive->setText(text);
    socket.write(new_text.toUtf8());
    ui->send->clear();
    ui->send->setFocus();
}

