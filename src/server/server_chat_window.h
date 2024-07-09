#pragma once

#include "chat_protocol.h"
#include "server_manager.h"
#include "chat_line.h"
class server_chat_window : public QMainWindow
{
    Q_OBJECT
public:
    server_chat_window(QWebSocket *client, QWidget *parent = nullptr);

    void disconnect_from_host();

    void add_file(const QString &path, bool is_mine, const QString &time);

private:
    QListWidget *_list{};

    QLineEdit *_insert_message{};
    QPushButton *_send_button{};
    QPushButton *_send_file_button{};

    server_manager *_client{};
    chat_protocol *_protocol{};

    QPushButton *_file{};

    QDir _dir{};

signals:
    void client_name_changed(const QString &original_name, const QString &old_name, const QString &name);
    void is_typing_received(const QString &sender, const QString &receiver);

    void text_for_other_client(const QString &sender, const QString &receiver, const QString &message);
    void file_for_other_client(const QString &sender, const QString &receiver, const QString &file_name);

    void reject_receiving_file_for_other_clients(const QString &sender, const QString &receiver);

private slots:
    void on_client_name_changed(const QString &original_name, const QString &old_name, const QString &name);

    void send_message();

    void folder();

    void on_text_message_received(const QString &message, const QString &time);

    void send_file();
};

class SeparatorDelegate : public QStyledItemDelegate
{
private:
    QListWidget *m_parent;

public:
    explicit SeparatorDelegate(QListWidget *parent) : QStyledItemDelegate(parent), m_parent(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        painter->save();

        QRect rect = option.rect.adjusted(2, 2, -2, -2);

        painter->setBrush(QBrush(Qt::white));
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(rect, 50, 50);

        QStyleOptionViewItem adjustedOption = option;
        adjustedOption.rect = rect;
        adjustedOption.displayAlignment = Qt::AlignCenter;
        QStyledItemDelegate::paint(painter, adjustedOption, index);

        painter->restore();
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QSize size = QStyledItemDelegate::sizeHint(option, index);
        size.setHeight(size.height() + 2);

        return size;
    }
};