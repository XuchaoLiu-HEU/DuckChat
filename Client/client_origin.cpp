/*
#include "client.h"
#include "ui_client.h"

// 这是一个构造函数，它创建了一个名为Client的QWidget。
// 该构造函数需要一个QWidget类型的parent指针，用于指定Client的父对象。
// QWidget(parent)调用QWidget的构造函数来设置Client的父对象。
// 然后，使用new关键字创建了一个名为ui的Ui::Client对象。

Client::Client(QWidget *parent): QWidget(parent), ui(new Ui::Client) {
    ui->setupUi(this);  // 使用ui对象调用setupUi()函数，这个函数是由Qt的UI设计器自动生成的，用于将UI文件中的组件绑定到ui对象上。
    this->setWindowTitle("DuckChat客户端");
    ui->receive->setText(text);
    // returnPressed()表示用户按下回车键时，这个信号会被发出。它表示用户已经完成了在该部件中的编辑操作，想要进行下一步操作。
    connect(ui->ip,SIGNAL(returnPressed()),this,SLOT(next()));
    connect(ui->port,SIGNAL(returnPressed()),this,SLOT(on_connectButton_clicked()));
    connect(ui->nameEdit,SIGNAL(returnPressed()),this,SLOT(next()));
    connect(ui->send,SIGNAL(returnPressed()),this,SLOT(on_sendButton_clicked()));
}

void Client::receiveData()
{
    QByteArray message=socket.readAll();
    text=text+message.data()+"\n";
    ui->receive->setText(text);
}

void Client::on_connectButton_clicked()
{
    socket.connectToHost(ui->ip->text(),ui->port->text().toInt());
    if(socket.waitForConnected(1000)){
        text.append("成功连接聊天室...\n");
        // 作用是将光标移到名为nameEdit的QLineEdit控件中，以便用户可以直接在该控件中输入用户名。
        // 这样做的好处是可以提高用户的输入效率，使得用户可以更快速地完成输入操作。
        ui->nameEdit->setFocus();
    }
    else{
        text.append("连接失败...\n");
    }
    connect(&socket,SIGNAL(readyRead()),this,SLOT(receiveData()));

    ui->receive->setText(text);
}


void Client::on_sendButton_clicked()
{
    //输入校验
    QString username = ui->nameEdit->text().trimmed();
    if (username.isEmpty() || username.length() > 20) {
        QMessageBox::warning(this, "用户名错误", "用户名不能为空且长度不能超过20个字符。");
        return;
    }
    QString message = ui->send->text().trimmed();
    if (message.isEmpty() || message.length() > 200) {
        QMessageBox::warning(this, "消息错误", "消息不能为空且长度不能超过200个字符。");
        return;
    }
    if (message.contains("@")) {
        QMessageBox::warning(this, "消息错误", "消息中不能包含@字符。");
        return;
    }

    QString new_text=ui->nameEdit->text()+": "+ui->send->text();
    text.append(new_text).append("\n");
    ui->receive->setText(text);
    socket.write(new_text.toUtf8());
    ui->send->clear();
    ui->send->setFocus();
}

void Client::next()
{

     * sender() 函数是 Qt 中的一个特殊函数，它返回一个指向发送该信号的对象的指针。
     * 当槽函数被调用时，sender() 函数会自动返回发送该信号的对象的指针，从而使槽函数可以知道是哪个对象触发了信号。
     * 在一个对象与多个对象之间相互通信的场景下，sender() 函数可以帮助我们区分不同的信号来源，从而更方便地进行信号处理。
     * 需要注意的是，sender() 函数只能在槽函数中调用，否则会返回一个空指针。
     * 此外，由于 sender() 函数返回的指针类型为 QObject*，因此在使用时需要进行强制类型转换。
     * 如果发生信号共享的情况，那么需要谨慎使用 sender() 函数，因为此时 sender() 返回的指针可能指向不同的对象。

    QLineEdit *lineEdit = (QLineEdit *)sender();
        if (lineEdit == ui->ip) {
            ui->port->setFocus();
        } else if (lineEdit == ui->nameEdit) {
            ui->send->setFocus();
        }
}

*/
