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
    QByteArray set_name_message(QString my_name, QString name);

    QByteArray set_init_sending_file_message(QString filename);
    QByteArray set_accept_file_message();
    QByteArray set_reject_file_message();

    QByteArray set_init_sending_file_message_client(QString sender, QString ID, QString receiver, QString filename);
    QByteArray set_accept_file_message_client(QString receiver, int port);
    QByteArray set_reject_file_message_client(QString sender, QString receiver);

    QByteArray set_file_message(QString filename);
    QByteArray set_file_message_client(QString filename, QString sender);

    QByteArray set_login_message(QString ID);

    QByteArray set_added_you_message(QString name, QString ID, QString receiver);

    QByteArray set_lookup_friend_message(QString ID);

    QByteArray set_create_conversation_message(QString participant1, int participant1_ID, QString participant2, int participant2_ID);
    QByteArray set_save_message_message(QString sender, QString receiver, QString content);

    void load_data(QByteArray data);

    message_type type() const;
    const QString &message() const;
    const QString &name() const;

    const QString &file_name() const;
    const qint64 &file_size() const;
    const QByteArray &file_data() const;

    const QString &file_name_client() const;
    const qint64 &file_size_client() const;
    const QByteArray &file_data_client() const;

    const QString &receiver() const;
    const QString &sender() const;
    const QString &sender_file() const;

    const int &port() const;
    const int &port_transfer() const;

    const QString &client_name() const;

    const QString &old_name() const;
    const QString &my_name() const;

    const QString &my_ID() const;
    const QString &clients_ID() const;

    const QString &full_name() const;

    const QHash<QString, int> &friend_list() const;

private:
    QByteArray get_data(message_type type, QString data);

    message_type _type;
    QString _message;
    QString _name;

    int _port;
    int _port_transfer;

    QString _file_name;
    qint64 _file_size;
    QByteArray _file_data;

    QString _file_name_client;
    qint64 _file_size_client;
    QByteArray _file_data_client;

    QString _client_name;
    QString _receiver;
    QString _sender;
    QString _sender_file;

    QString _old_name;

    QString _my_name;

    QString _full_name;
    QString _my_ID;
    QHash<QString, int> _friend_list;

    QString _client_ID;
};