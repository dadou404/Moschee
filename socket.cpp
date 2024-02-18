#include "socket.h"
#include<QDebug>
SocketTest::SocketTest(QObject *parent) :
    QObject(parent)

{


        QObject::connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
        if(!server->listen(QHostAddress::Any, 44092))
            {
                qDebug() << "Server could not start";
            }
            else
            {
                qDebug() << "Server started!";
            }

}


void SocketTest::onNewConnection()
{
    //qDebug()<<server->serverAddress();
    //qDebug()<<server->serverPort();
   QTcpSocket *clientSocket = server->nextPendingConnection();
   connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
   connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));
     qDebug()<<"The Connection is working On New Connection"<<endl;
   /* _sockets.push_back(clientSocket);
    for (QTcpSocket* socket : _sockets) {
        socket->write(QByteArray::fromStdString(clientSocket->peerAddress().toString().toStdString() + " connected to server !\n"));
    }*/
}

void SocketTest::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        _sockets.removeOne(sender);
         qDebug()<<"The Connection is working OnSocket"<<endl;
    }
}

void SocketTest::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray datas = sender->readAll();
    qDebug()<<"The Connection is working On Ready Read"<<endl;


    /*for (QTcpSocket* socket : _sockets) {
        if (socket != sender)
            socket->write(QByteArray::fromStdString(sender->peerAddress().toString().toStdString() + ": " + datas.toStdString()));
    }
    */
}
