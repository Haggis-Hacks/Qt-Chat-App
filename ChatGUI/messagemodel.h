#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QObject>
#include <QStringListModel>
#include <QTcpSocket>

class MessageModel : public QStringListModel
{
    Q_OBJECT

    Q_PROPERTY(QString currentMessage READ currentMessage WRITE setCurrentMessage NOTIFY currentMessageChanged FINAL);

public:
    explicit MessageModel(QObject *parent = nullptr);

    Q_INVOKABLE void sendMessage();

    QString currentMessage() const;
    void setCurrentMessage(const QString &newCurrentMessage);

signals:
    void currentMessageChanged();

private slots:
    void onReadyRead();

private:
    QTcpSocket socket;
    QString m_currentMessage;
};

#endif // MESSAGEMODEL_H
