#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtMultimedia>

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
        init_sending_file_client,

        accept_sending_file,
        accept_sending_file_client,

        reject_sending_file,
        reject_sending_file_client,

        send_file,
        send_file_client,

        client_new_name,
        client_disconnected,

        log_in,
        added_you,
        lookup_friend,
        create_conversation,
        save_message
    };

    QByteArray set_text_message(QString sender, QString receiver, QString message);
    QByteArray set_is_typing_message(QString sender, QString receiver);
    QByteArray set_name_message(QString name);

    QByteArray set_init_sending_file_message(QString filename);
    QByteArray set_init_sending_file_message_client(QString sender, QString ID, QString filename, qint64 file_size);

    QByteArray set_accept_file_message();
    QByteArray set_accept_file_message_client(int port);

    QByteArray set_reject_file_message();
    QByteArray set_reject_file_message_client(QString sender, QString receiver);

    QByteArray set_file_message(QString filename);
    QByteArray set_file_message_client(int port);

    QByteArray set_client_name_message(QString old_name, QString client_name);
    QByteArray set_client_disconnected_message(QString client_name);

    QByteArray set_login_message(QString full_name, int port, QHash<int, QHash<QString, int>> friend_list);
    QByteArray set_added_you_message(QString name, QString ID, QString receiver, int conversation_ID);

    QByteArray set_lookup_friend_message(QString ID, int conversation_ID);

    void load_data(QByteArray data);

    message_type type() const;
    const QString &message() const;
    const QString &name() const;
    const QString &original_name() const;
    const QString &file_name() const;
    const QString &file_name_client() const;
    const qint64 &file_size() const;
    const qint64 &file_size_client() const;
    const QByteArray &file_data() const;

    const QString &client_name() const;
    const QHash<QString, QString> &other_clients() const;

    const QString &receiver() const;
    const QString &sender() const;

    const QString &receiver_typing() const;
    const QString &sender_typing() const;

    const int &port() const;

    const QString &clients_ID() const;

    const QString &participant1() const;
    const int &participant1_ID() const;
    const QString &participant2() const;
    const int &participant2_ID() const;

    const int &conversation_ID() const;

private:
    QByteArray get_data(message_type type, QString data);

    message_type _type;
    QString _message;
    QString _name;
    QString _is_typing;

    int _port;

    QString _file_name;
    QString _file_name_client;
    qint64 _file_size;
    qint64 _file_size_client;
    QByteArray _file_data;

    QString _client_name;
    QString _receiver;
    QString _sender;
    QString _receiver_typing;
    QString _sender_typing;
    QString _original_name;
    QHash<QString, QString> _other_clients;

    QString _client_ID;

    QString _participant1;
    int _participant1_ID;
    QString _participant2;
    int _participant2_ID;

    int _conversation_ID;
};