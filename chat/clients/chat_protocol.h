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
        file,
        is_typing,
        set_name
    };

    QByteArray text_message(QString message);
    QByteArray is_typing_func();
    QByteArray set_name_func(QString message);

    void laod_data(QByteArray data);

    message_type G_type() const;
    const QString &G_message() const;
    const QString &G_set_name() const;
    const QString &G_is_typing() const;

private:
    QWidget *central_widget;
    QByteArray get_data(message_type type, QString message);

    message_type _type;
    QString _message;
    QString _set_name;
    QString _is_typing;
};