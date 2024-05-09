#pragma once

#include "client_manager.h"
#include "chat_line.h"

#include <QtWidgets>
#include <QtCore>
#include <QtMultimedia>

class client_chat_window : public QMainWindow
{
    Q_OBJECT
public:
    client_chat_window(QString my_ID, QWidget *parent = nullptr);
    client_chat_window(QString destinator, QString name, int conversation_ID, QWidget *parent = nullptr);

    void window_name(QString name);

    QString my_name();
    void set_name(QString insert_name);

    void set_up_window();

    void message_received(QString message);

    void add_file(QString path, bool is_mine = false, QString date_time = "");

    void add_audio(const QUrl &source, bool is_mine = false, QString date_time = "");

    void add_friend(QString ID);

    void retrieve_conversation(std::vector<std::string> messages);

    void ask_microphone_permission();

    bool is_recording = false;

    bool is_playing = false;

    int paused_position = 0;

private:
    QStatusBar *_status_bar;

    static client_manager *_client;

    QString _destinator_name;
    int _conversation_ID;

    QString _destinator = "Server";
    QString _window_name = "Server";

    QString _my_ID;

    static QString _my_name;
    static QString _insert_name;

    QLineEdit *_insert_message;

    QPushButton *_send_file_button;

    QLabel *_duration_label;

    QSlider *_slider;

    QPoint _drag_start_position;
    bool _dragging = false;

    std::vector<int> _conversation_list;

    QPushButton *_button_file;
    QPushButton *_audio;

    QListWidget *_list;

    QHBoxLayout *_hbox;
    QDir _dir;

    QMediaCaptureSession *_session;
    QAudioInput *_audio_input;
    QMediaRecorder *_recorder;

    QMediaPlayer *_player;
    QAudioOutput *_audio_output;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void
    client_name_changed(QString old_name, QString client_name);
    void client_disconnected(QString client_name);

    void text_message_received(QString sender, QString message);
    void is_typing_received(QString sender);

    void socket_disconnected();

    void update_button_file();

    void data_received_sent(QString client_name);

    void swipe_right();

    void client_added_you(QString name, QString ID, int conversation_ID);

    void lookup_friend_result(QString name, int conversation_ID);

    void friend_list(QHash<int, QHash<QString, int>> list);

private slots:
    void send_message();

    void send_file();
    void send_file_client();

    void folder();

    void on_init_receiving_file(QString file_name, qint64 file_size);
    void on_init_receiving_file_client(QString sender, QString ID, QString file_name, qint64 file_size);

    void on_file_saved(QString path);

    void start_recording();

    void on_duration_changed(qint64 duration);

    void play_audio(const QUrl &source);
};