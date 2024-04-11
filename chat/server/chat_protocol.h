#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QByteArray>

class chat_protocol : public QMainWindow
{
    Q_OBJECT
public:
    chat_protocol(QWidget *parent = nullptr);

    enum message_type
    {
        text,
        is_typing,
        set_name,
        init_sending_file,
        accept_sending_file,
        reject_sending_file,
        send_file,
        new_client,
        clients_list,
        client_new_name,
        client_disconnected,
        disconnected_from
    };

    QByteArray set_text_message(QString sender, QString receiver, QString message);
    QByteArray set_is_typing_message(QString sender, QString receiver);
    QByteArray set_name_message(QString name);

    QByteArray set_init_sending_file_message(QString filename);
    QByteArray set_accept_file_message();
    QByteArray set_reject_file_message();
    QByteArray set_file_message(QString filename);

    QByteArray set_new_client_message(QString client_name);
    QByteArray set_clients_list_message(QString client_name, QStringList other_clients);
    QByteArray set_client_name_message(QString old_name, QString client_name);
    QByteArray set_client_disconnected_message(QString client_name);

    QByteArray set_disconnected_from_message(QString sender, QString receiver);

    void load_data(QByteArray data);

    message_type type() const;
    const QString &message() const;
    const QString &name() const;
    const QString &file_name() const;
    const qint64 &file_size() const;
    const QByteArray &file_data() const;

    const QString &client_name() const;
    const QStringList &other_clients() const;

    const QString &receiver() const;
    const QString &sender() const;

private:
    QWidget *central_widget;
    QByteArray get_data(message_type type, QString data);

    message_type _type;
    QString _message;
    QString _name;
    QString _is_typing;

    QString _file_name;
    qint64 _file_size;
    QByteArray _file_data;

    QString _client_name;
    QString _receiver;
    QString _sender;
    QStringList _other_clients;
};