#include "chatserver.h"

ChatServer::ChatServer(QObject *parent)
    : QTcpServer{parent}
{
    if (!listen(QHostAddress::Any, 1234))
        qWarning()<<"ChatServer listen has failed";
}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketDescriptor);

    connect(client, &QTcpSocket::readyRead, this, &ChatServer::handleClientReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &ChatServer::handleClientDisconnected);

    clients.append(client);
}

void ChatServer::handleClientReadyRead()
{
    QTcpSocket * senderClient = qobject_cast<QTcpSocket *>(sender());
    if(!senderClient) return;

    QByteArray data = senderClient->readAll();
    qDebug()<<"Forwarding data:" <<data;
    foreach (QTcpSocket *client, clients)
    {
        if (client == senderClient) continue;
        client->write(data);
    }
}

void ChatServer::handleClientDisconnected()
{
    QTcpSocket * senderClient = qobject_cast<QTcpSocket *>(sender());
    if(!senderClient) return;

    clients.removeAll(senderClient);
    senderClient->deleteLater();
}
