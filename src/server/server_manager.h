#pragma once

#include "chat_protocol.h"
#include "database.h"
class server_manager : public QMainWindow
{
    Q_OBJECT
public:
    server_manager(QSqlDatabase &db_connection, QWidget *parent = nullptr);
    server_manager(QWebSocket *client, QWidget *parent = nullptr);

    static QSqlDatabase _db_connection;

    void disconnect_from_host();
    void disconnect_all_clients();

    void is_typing_for_other_clients(const QString &sender, const QString &receiver);

    void send_text(const QString &text, const QString &time);
    void send_is_typing(const QString &sender);

    void notify_other_clients(const QString &old_name, const QString &client_name);

    void file_received(const QString &sender, const QString &receiver, const QString &file_name, const QByteArray &file_data, const QString &time);

    QString name() const;

    void create_conversation(const int &conversation_ID, const QString &participant1, const int &participant1_ID, const QString &participant2, const int &participant2_ID);
    void save_conversation_message(const int &conversation_ID, const QString &sender, const QString &receiver, const QString &content, const QString &time);
    void lookup_friend(const QString &ID);

    void audio_received(const QString &sender, const QString &receiver, const QString &audio_name, const QByteArray &audio_data, const QString &time);
    void save_data(const int &conversation_ID, const QString &sender, const QString &receiver, const QString &file_name, const QByteArray &file_data, const QString &data_type, const QString &time);

    void sign_up(const QString &phone_number, const QString &first_name, const QString &last_name, const QString &password, const QString &secret_question, const QString &secret_answer);

    void login_request(const QString &phone_number, const QString &password);
    void new_password_requested(const QString &phone_number);
    void update_password(const QString &phone_number, const QString &new_password);

    void delete_message(const int &conversation_ID, const QString &sender, const QString &receiver, const QString &time);
    void delete_group_message(const int &conversation_ID, const QString &group_name, const QString &time);

    void create_new_group(const QString &adm, const QStringList &members, const QString &group_name);

    void group_is_typing_received(const int &group_ID, const QString &group_name, const QString &sender);
    void group_text_received(const int &group_ID, const QString &group_name, const QString &sender, const QString &message, const QString &time);
    void group_file_received(const int &group_ID, const QString &group_name, const QString &sender, const QString &file_name, const QByteArray &file_data, const QString &time);
    void group_audio_received(const int &group_ID, const QString &group_name, const QString &sender, const QString &audio_name, const QByteArray &audio_data, const QString &time);

    void new_group_member(const int &group_ID, const QString &group_name, const QString &adm, const QString &group_member);
    void remove_group_member(const int &group_ID, const QString &group_name, const QString &adm, const QString &group_member);

    void data_requested(const int &conversation_ID, const QString &date_time, const QString &type);

    void delete_account(const QString &phone_number);

    void update_last_message_read(const int &conversation_ID, const QString &client_ID, const QString &time);
    void update_group_last_message_read(const int &group_ID, const QString &client_ID, const QString &time);

    static QHash<QString, QWebSocket *> _clients;
    static QHash<QString, QString> _time_zone;

    QWebSocket *_socket{};

private:
    QWidget *central_widget{};

    QWebSocketServer *_server{};
    chat_protocol *_protocol{};

    QString _file_name{};

    QHostAddress _ip = QHostAddress::LocalHost;
    int _port{12345};

signals:
    void new_client_connected(QWebSocket *client);
    void new_client_disconnected(QWebSocket *client);

    void text_message_received(const QString &message, const QString &time);
    void client_name_changed(const QString &original_name, const QString &old_name, const QString &name);
    void is_typing_received(const QString &sender, const QString &receiver);

    void after_login(const QString &old_name, const QString &name);

    void file_saved(const QString &path, bool is_mine, const QString &time);

private slots:
    void on_new_connection();
    void on_client_disconnected();

    void on_binary_message_received(const QByteArray &message);

    void message_received(const QString &sender, const QString &receiver, const QString &message, const QString &time);
};