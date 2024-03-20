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
        send_file
    };

    QByteArray set_text_message(QString message);
    QByteArray set_is_typing_message();
    QByteArray set_name_message(QString name);

    QByteArray set_init_sending_file_message(QString filename);
    QByteArray set_accept_file_message();
    QByteArray set_reject_file_message();
    QByteArray set_file_message(QString filename);

    void load_data(QByteArray data);

    message_type type() const;
    const QString &message() const;
    const QString &name() const;
    const QString &file_name() const;
    const qint64 &file_size() const;
    const QByteArray &file_data() const;

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
};