#include "messagemodel.h"

MessageModel::MessageModel(QObject *parent)
    : QStringListModel{parent}
{
    socket.connectToHost("127.0.0.1", 1234);
    connect(&socket, &QTcpSocket::readyRead, this, &MessageModel::onReadyRead);
}

void MessageModel::sendMessage()
{
    qDebug()<<m_currentMessage;
    if (m_currentMessage.isEmpty()) return;

    socket.write((m_currentMessage).toUtf8());

    if (!insertRow(rowCount()))
        qWarning()<<"MessageModel::sendMessage:: Insert row failed";
    else if (!setData(index(rowCount()-1), "ME:" + m_currentMessage))
        qWarning()<<"MessageModel::sendMessage:: setData failed";
    else return;
}

QString MessageModel::currentMessage() const
{
    return m_currentMessage;
}

void MessageModel::setCurrentMessage(const QString &newCurrentMessage)
{
    if (m_currentMessage == newCurrentMessage)
        return;
    m_currentMessage = newCurrentMessage;
    emit currentMessageChanged();
}

void MessageModel::onReadyRead()
{
    QByteArray buffer = socket.readAll();
    qDebug()<<"Recieved:"<<buffer;
    QString newMessage = QString::fromUtf8(buffer);
    if (!insertRow(rowCount()))
        qWarning()<<"MessageModel::onReadyRead:: Insert row failed";
    else if (!setData(index(rowCount()-1), "OT:" + newMessage))
        qWarning()<<"MessageModel::onReadyRead:: setData failed";
    else return;
}
