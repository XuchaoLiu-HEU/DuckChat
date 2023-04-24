#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("DuckChat服务端"));
    connect(&server, &Server::playerConnected, this, &Widget::playerConnected);  // 客户端连接
    connect(&server, &Server::getMessage, this, &Widget::getMessage);            // 服务端接收到客户端消息

    connect(ui->send, &QLineEdit::returnPressed, this, &Widget::on_pushButton_clicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::on_pushButton_clicked);
    connect(ui->port, &QLineEdit::returnPressed, this, &Widget::on_startButton_clicked);
//    connect(ui->startButton, &QPushButton::clicked, this, &Widget::on_startButton_clicked);
    connect(ui->nameEdit, &QLineEdit::returnPressed, this, &Widget::next);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::playerConnected()
{
    text.append(tr("一只鸭子加入聊天室...\n"));
    ui->textEdit->setText(text);
}

void Widget::getMessage()
{
    text.append(server.getContent());
    ui->textEdit->setText(text);
}

void Widget::on_pushButton_clicked()
{
    QString name = ui->nameEdit->text();
//    QString message = ui->send->text().trimmed(); // 去除前后空格
    QString message = ui->send->text() + "\n";

    if (name.isEmpty() || message.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("请填写昵称和消息内容！"));
        return;
    }

    text.append(name + ": " + message);
    ui->textEdit->setText(text);

    server.sendData(name + ": " + message);
    ui->send->clear();
}

void Widget::on_startButton_clicked()
{
    QString portText = ui->port->text().trimmed(); // 去除前后空格

    bool isNumber;
    int port = portText.toInt(&isNumber);

    if (!isNumber || port < 1024 || port > 65535) {
        QMessageBox::warning(this, tr("警告"), tr("请填写正确的端口号（1024-65535）！"));
        return;
    }

    if (server.Connect(port)) {
        text += QString(tr("PORT:%1\n聊天室创建成功...\n")).arg(portText);
        ui->textEdit->setText(text);
    }
//    else {
//        QMessageBox::warning(this, tr("警告"), tr("启动服务失败，请检查端口是否被占用！"));
//    }

    ui->nameEdit->setFocus();
}

void Widget::next()
{
    ui->send->setFocus();
}
