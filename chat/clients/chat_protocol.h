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
        file
    };

    QByteArray set_text_message(QString message);
    QByteArray set_is_typing_message();
    QByteArray set_name_message(QString name);

    void load_data(QByteArray data);

    message_type type() const;
    const QString &message() const;
    const QString &name() const;

private:
    QWidget *central_widget;
    QByteArray get_data(message_type type, QString data);

    message_type _type;
    QString _message;
    QString _name;
    QString _is_typing;
};