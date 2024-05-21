#pragma once

#include <QtWidgets>
#include <QtCore>
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

        client_connected,

        added_you,
        lookup_friend,
        create_conversation,
        save_message,

        audio,
        save_data,
        sign_up,
        login_request
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

    QByteArray set_added_you_message(int conversation_ID, QString name, QString ID, QString receiver);

    QByteArray set_lookup_friend_message(int conversation_ID, QString ID, bool true_or_false);

    QByteArray set_audio_message(QString sender, QString audio_name, QByteArray audio_data);

    QByteArray set_client_connected_message(QString client_name);

    QByteArray set_online_client_message(QList<QString> names);

    QByteArray set_login_message(QString hashed_password, bool true_or_false, QString full_name, int port, QHash<int, QHash<QString, int>> friend_list, QList<QString> online_friends, QHash<int, QVector<QString>> messages, QHash<int, QHash<QString, QByteArray>> binary_data);

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

    const QString &audio_name() const;
    const QString &audio_sender() const;
    const QString &audio_receiver() const;
    const QString &data_type() const;
    const QByteArray &audio_data() const;

    const QString &last_name() const;
    const QString &first_name() const;
    const QString &password() const;
    const QString &secret_question() const;
    const QString &secret_answer() const;

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

    QString _audio_name;
    QString _audio_sender;
    QString _audio_receiver;
    QByteArray _audio_data;
    QString _data_type;

    QString _last_name;
    QString _first_name;
    QString _password;
    QString _secret_question;
    QString _secret_answer;
};