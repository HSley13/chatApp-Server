#include "database.h"

QSqlDatabase connection_setup(const connection_details &details)
{
    try
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(details.server);
        db.setPort(details.port);
        db.setDatabaseName(details.schema);
        db.setUserName(details.user);
        db.setPassword(details.password);

        if (!db.open())
        {
            qDebug() << "connection_setup() --> SQL ERROR:" << db.lastError().text();
            return QSqlDatabase();
        }

        return db;
    }
    catch (const std::exception &e)
    {
        qDebug() << "connection_setup() --> ERROR:" << e.what();
        return QSqlDatabase();
    }
}

QString Security::generate_random_salt(std::size_t len)
{
    const QString valid_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789@#&?!~^-$%*+";
    QString salt;

    for (size_t i = 0; i < len; ++i)
    {
        int index = QRandomGenerator::global()->bounded(valid_chars.size());
        salt.append(valid_chars.at(index));
    }

    return salt;
}

QString Security::hashing_password(const QString &password)
{
    const size_t SALT_LENGTH = 32;
    QString salt = generate_random_salt(SALT_LENGTH);

    QByteArray salted_password = salt.toUtf8() + password.toUtf8();
    QByteArray hash = QCryptographicHash::hash(salted_password, QCryptographicHash::Sha256);

    return salt + QString::fromUtf8(hash.toHex());
}

bool Security::verifying_password(const QString &password, const QString &hashed_password)
{
    const uint32_t hash_length = 64; // Length of SHA-256 hash in hex representation
    const size_t SALT_LENGTH = hashed_password.length() - hash_length;

    QString salt = hashed_password.left(SALT_LENGTH);
    QString original_hash = hashed_password.mid(SALT_LENGTH, hash_length);

    QByteArray salted_password = salt.toUtf8() + password.toUtf8();
    QByteArray hash = QCryptographicHash::hash(salted_password, QCryptographicHash::Sha256);

    return original_hash == QString::fromUtf8(hash.toHex());
}

QString Security::retrieve_hashed_password(QSqlDatabase &db, const int &phone_number)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("SELECT hashed_password FROM password_security WHERE phone_number = ?");
        query.addBindValue(phone_number);

        if (!query.exec())
        {
            qDebug() << "retrieve_hashed_password() ---> SQL ERROR:" << query.lastError().text();
            return QString();
        }

        QString hashed_password = QString();
        if (query.next())
            hashed_password = query.value("hashed_password").toString();

        return hashed_password;
    }
    catch (const std::exception &e)
    {
        qDebug() << "retrieve_hashed_password() ---> ERROR:" << e.what();
        return QString();
    }
}

void Account::create_account(QSqlDatabase &db, const int &phone_number, const QString &first_name, const QString &last_name, const QString &secret_question, const QString &secret_answer, const QString &password)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("INSERT INTO accounts (phone_number, first_name, last_name) VALUES (?, ?, ?);");
        query.addBindValue(phone_number);
        query.addBindValue(first_name);
        query.addBindValue(last_name);

        if (!query.exec())
        {
            qDebug() << "create_account() 1 ---> SQL ERROR:" << query.lastError().text();
            return;
        }

        QString hashed_password = Security::hashing_password(password);

        query.prepare("INSERT INTO password_security VALUES (?, ?, ?, ?);");
        query.addBindValue(phone_number);
        query.addBindValue(hashed_password);
        query.addBindValue(secret_question);
        query.addBindValue(secret_answer);

        if (!query.exec())
            qDebug() << "create_account() 2 ---> SQL ERROR:" << query.lastError().text();
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
    }
}

QStringList Account::retrieve_conversation(QSqlDatabase &db, const int &conversation_ID, const int &client_ID, const QString &timeZone_ID)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("SELECT messages.sender_ID, messages.receiver_ID, messages.content, messages.date_time, messages.message_type, "
                      "CASE WHEN conversations.participant1_ID = ? THEN conversations.last_message_read1 ELSE conversations.last_message_read2 END AS last_message_read "
                      "FROM messages "
                      "JOIN conversations ON messages.conversation_ID = conversations.conversation_ID "
                      "WHERE messages.conversation_ID = ? "
                      "ORDER BY messages.date_time;");
        query.addBindValue(client_ID);
        query.addBindValue(conversation_ID);

        if (!query.exec())
        {
            qDebug() << "retrieve_conversation() ---> SQL ERROR:" << query.lastError().text();
            return {};
        }

        QStringList messages = {};
        int count = 0;
        QString last_message_read = QString();

        while (query.next())
        {
            if (last_message_read.isEmpty())
                last_message_read = UTC_to_timeZone(query.value("last_message_read").toString(), timeZone_ID);

            QString date_time = UTC_to_timeZone(query.value("date_time").toString(), timeZone_ID);

            QDateTime dt1 = QDateTime::fromString(date_time, "yyyy-MM-dd HH:mm:ss");
            QDateTime dt2 = QDateTime::fromString(last_message_read, "yyyy-MM-dd HH:mm:ss");

            if (dt1 > dt2)
                count++;

            QString message = QString("%1/%2/%3/%4/%5/%6")
                                  .arg(query.value("sender_ID").toString())
                                  .arg(query.value("receiver_ID").toString())
                                  .arg(query.value("content").toString())
                                  .arg(date_time)
                                  .arg(query.value("message_type").toString())
                                  .arg(QString::number(count));

            messages << message;
        }

        return messages;
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
        return {};
    }
}

QHash<int, QHash<QString, QString>> Account::retrieve_friend_list(QSqlDatabase &db, const int &phone_number)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("SELECT CASE WHEN participant1_ID = ? THEN participant2 ELSE participant1 END AS other_participant, "
                      "CASE WHEN participant1_ID = ? THEN participant2_ID ELSE participant1_ID END AS other_participant_ID, "
                      "conversation_ID FROM conversations WHERE participant1_ID = ? OR participant2_ID = ?;");
        query.addBindValue(phone_number);
        query.addBindValue(phone_number);
        query.addBindValue(phone_number);
        query.addBindValue(phone_number);

        if (!query.exec())
        {
            qDebug() << "retrieve_friend_list() ---> SQL ERROR:" << query.lastError().text();
            return {};
        }

        QHash<int, QHash<QString, QString>> friend_list_pack = {};

        while (query.next())
        {
            QHash<QString, QString> friend_list = {};

            QString participant2_ID = query.value("other_participant_ID").toString();
            QString participant2 = query.value("other_participant").toString();

            friend_list.insert(participant2_ID, participant2);

            int conversation_ID = query.value("conversation_ID").toInt();

            friend_list_pack.insert(conversation_ID, friend_list);
        }

        return friend_list_pack;
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
        return {};
    }
}

void Account::save_text_message(QSqlDatabase &db, const int &conversation_ID, const int &sender_ID, const int &receiver_ID, const QString &content, const QString &time)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("INSERT IGNORE INTO messages (conversation_ID, sender_ID, receiver_ID, content, date_time) VALUES (?, ?, ?, ?, ?);");
        query.addBindValue(conversation_ID);
        query.addBindValue(sender_ID);
        query.addBindValue(receiver_ID);
        query.addBindValue(content);
        query.addBindValue(time);

        if (!query.exec())
            qDebug() << "save_text_message() ---> SQL ERROR:" << query.lastError().text();
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
    }
}

void Account::create_conversation(QSqlDatabase &db, const int &conversation_ID, const QString &participant1, const int &participant1_ID, const QString &participant2, const int &participant2_ID)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("INSERT IGNORE INTO conversations (conversation_ID, participant1, participant1_ID, participant2, participant2_ID) "
                      "VALUES (?, ?, ?, ?, ?);");
        query.addBindValue(conversation_ID);
        query.addBindValue(participant1);
        query.addBindValue(participant1_ID);
        query.addBindValue(participant2);
        query.addBindValue(participant2_ID);

        if (!query.exec())
            qDebug() << "create_conversation() ---> SQL ERROR:" << query.lastError().text();
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
    }
}

QString Account::retrieve_alias(QSqlDatabase &db, const int &phone_number)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("SELECT alias FROM accounts WHERE phone_number = ?");
        query.addBindValue(phone_number);

        if (!query.exec())
        {
            qDebug() << "retrieve_alias() ---> SQL ERROR:" << query.lastError().text();
            return QString();
        }

        QString name = QString();
        if (query.next())
            name = query.value("alias").toString();

        return name;
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
        return QString();
    }
}

void Account::update_alias(QSqlDatabase &db, const int &phone_number, const QString &name)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("UPDATE accounts SET alias = ? WHERE phone_number = ?");
        query.addBindValue(name);
        query.addBindValue(phone_number);

        if (!query.exec())
        {
            qDebug() << "update_alias() ---> SQL ERROR:" << query.lastError().text();
            return;
        }

        QSqlQuery query_conversation(db);
        query_conversation.prepare("UPDATE conversations SET participant1 = CASE WHEN participant1_ID = ? THEN ? ELSE participant1 END, "
                                   "participant2 = CASE WHEN participant2_ID = ? THEN ? ELSE participant2 END "
                                   "WHERE participant1_ID = ? OR participant2_ID = ?");
        query_conversation.addBindValue(phone_number);
        query_conversation.addBindValue(name);
        query_conversation.addBindValue(phone_number);
        query_conversation.addBindValue(name);
        query_conversation.addBindValue(phone_number);
        query_conversation.addBindValue(phone_number);

        if (!query_conversation.exec())
            qDebug() << "update_alias() ---> SQL ERROR:" << query_conversation.lastError().text();
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
    }
}

void Account::save_binary_data(QSqlDatabase &db, const int &conversation_ID, const int &sender_ID, const int &receiver_ID, const QString &data_name, const QByteArray &data_data, const QString &type, const QString &time)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("INSERT IGNORE INTO binary_data (conversation_ID, sender_ID, receiver_ID, file_name, file_data, data_type, date_time) "
                      "VALUES (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(conversation_ID);
        query.addBindValue(sender_ID);
        query.addBindValue(receiver_ID);
        query.addBindValue(data_name);
        query.addBindValue(data_data);
        query.addBindValue(type);
        query.addBindValue(time);

        if (!query.exec())
            qDebug() << "save_binary_data() ---> SQL ERROR:" << query.lastError().text();
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
    }
}

QHash<QString, QByteArray> Account::retrieve_binary_data(QSqlDatabase &db, const int &conversation_ID, const QString &date_time)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("SELECT file_data, data_type FROM binary_data WHERE conversation_ID = ? AND date_time = ?");
        query.addBindValue(conversation_ID);
        query.addBindValue(date_time);

        if (!query.exec())
        {
            qDebug() << "retrieve_binary_data() ---> SQL ERROR:" << query.lastError().text();
            return {};
        }

        QHash<QString, QByteArray> binary_data = {};

        if (query.next())
        {
            QByteArray file_data = query.value("file_data").toByteArray();
            QString data_type = query.value("data_type").toString();

            binary_data.insert(data_type, file_data);
        }

        return binary_data;
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
        return {};
    }
}

void Account::delete_message(QSqlDatabase &db, const int &conversation_ID, const QString &time)
{
    try
    {
        QString date_time = (time.length() < 10) ? QDate::currentDate().toString("yyyy-MM-dd") + " " + time : time;

        QSqlQuery query(db);
        query.prepare("DELETE FROM messages WHERE conversation_ID = ? AND date_time = ?");
        query.addBindValue(conversation_ID);
        query.addBindValue(date_time);

        if (!query.exec())
            qDebug() << "delete_message() ---> SQL ERROR:" << query.lastError().text();
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
    }
}

void Account::delete_group_message(QSqlDatabase &db, const int &group_ID, const QString &time)
{
    try
    {
        QString date_time = (time.length() < 10) ? QString("%1 %2").arg(QDate::currentDate().toString("yyyy-MM-dd"), time) : time;

        QSqlQuery query(db);
        query.prepare("DELETE FROM group_messages WHERE group_ID = ? AND date_time = ?");
        query.addBindValue(group_ID);
        query.addBindValue(date_time);

        if (!query.exec())
            qDebug() << "delete_group_message() ---> SQL ERROR:" << query.lastError().text();
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
    }
}

void Account::add_to_group(QSqlDatabase &db, const int &group_ID, const QString &group_name, const int &phone_number, const QString &user_role)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("INSERT INTO group_memberships (group_ID, group_name, participant_ID, user_role) VALUES (?, ?, ?, ?)");
        query.addBindValue(group_ID);
        query.addBindValue(group_name);
        query.addBindValue(phone_number);
        query.addBindValue(user_role);

        if (!query.exec())
            qDebug() << "add_to_group() ---> SQL ERROR:" << query.lastError().text();
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
    }
}

QStringList Account::retrieve_group_members(QSqlDatabase &db, const int &group_ID)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("SELECT participant_ID FROM group_memberships WHERE group_ID = ?");
        query.addBindValue(group_ID);

        if (!query.exec())
        {
            qDebug() << "retrieve_group_members() ---> SQL ERROR:" << query.lastError().text();
            return {};
        }

        QStringList members = {};

        while (query.next())
            members << query.value("participant_ID").toString();

        return members;
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
        return {};
    }
}

QHash<int, QHash<int, QString>> Account::retrieve_group_list(QSqlDatabase &db, const int &phone_number)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("SELECT group_ID, group_name FROM group_memberships WHERE participant_ID = ?");
        query.addBindValue(phone_number);

        if (!query.exec())
        {
            qDebug() << "retrieve_group_list() ---> SQL ERROR:" << query.lastError().text();
            return {};
        }

        QHash<int, QHash<int, QString>> group_list = {};

        while (query.next())
        {
            int group_ID = query.value("group_ID").toInt();
            QString group_name = query.value("group_name").toString();

            QSqlQuery admin_query(db);
            admin_query.prepare("SELECT participant_ID FROM group_memberships WHERE user_role = 'admin' AND group_ID = ?");
            admin_query.addBindValue(group_ID);

            if (!admin_query.exec())
            {
                qDebug() << "retrieve_group_list() ---> SQL ERROR:" << admin_query.lastError().text();
                continue;
            }

            QHash<int, QString> group_name_and_admin = {};
            while (admin_query.next())
            {
                int admin = admin_query.value("participant_ID").toInt();
                group_name_and_admin.insert(admin, group_name);
            }

            group_list.insert(group_ID, group_name_and_admin);
        }

        return group_list;
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
        return {};
    }
}

void Account::save_group_text_message(QSqlDatabase &db, const int &group_ID, const QString &sender, const QString &content, const QString &time)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("INSERT IGNORE INTO group_messages (group_ID, sender, content, date_time) VALUES (?, ?, ?, ?)");
        query.addBindValue(group_ID);
        query.addBindValue(sender);
        query.addBindValue(content);
        query.addBindValue(time);

        if (!query.exec())
            qDebug() << "save_group_text_message() ---> SQL ERROR:" << query.lastError().text();
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
    }
}

void Account::save_group_binary_data(QSqlDatabase &db, const int &group_ID, const QString &sender, const QString &data_name, const QByteArray &data_data, const QString &type, const QString &time)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("INSERT IGNORE INTO group_binary_data (group_ID, sender, file_name, file_data, data_type, date_time) VALUES (?, ?, ?, ?, ?, ?)");
        query.addBindValue(group_ID);
        query.addBindValue(sender);
        query.addBindValue(data_name);
        query.addBindValue(data_data);
        query.addBindValue(type);
        query.addBindValue(time);

        if (!query.exec())
            qDebug() << "save_group_binary_data() ---> SQL ERROR:" << query.lastError().text();
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
    }
}

QStringList Account::retrieve_group_conversation(QSqlDatabase &db, const int &group_ID, const int &client_ID, const QString &timeZone_ID)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("SELECT gm.sender, gm.content, gm.date_time, gm.message_type, "
                      "(SELECT last_message_read FROM group_memberships WHERE group_ID = gm.group_ID AND participant_ID = ?) AS last_message_read "
                      "FROM group_messages gm WHERE gm.group_ID = ? ORDER BY gm.date_time;");
        query.addBindValue(client_ID);
        query.addBindValue(group_ID);

        if (!query.exec())
        {
            qDebug() << "retrieve_group_conversation() ---> SQL ERROR:" << query.lastError().text();
            return {};
        }

        QStringList messages = {};
        int count = 0;
        QString last_message_read = QString();

        while (query.next())
        {
            if (last_message_read.isEmpty())
                last_message_read = UTC_to_timeZone(query.value("last_message_read").toString(), timeZone_ID);

            QString date_time = UTC_to_timeZone(query.value("date_time").toString(), timeZone_ID);

            QDateTime dt1 = QDateTime::fromString(date_time, "yyyy-MM-dd HH:mm:ss");
            QDateTime dt2 = QDateTime::fromString(last_message_read, "yyyy-MM-dd HH:mm:ss");

            if (dt1 > dt2)
                count++;

            QString message = QString("%1/%2/%3/%4/%5")
                                  .arg(query.value("sender").toString())
                                  .arg(query.value("content").toString())
                                  .arg(date_time)
                                  .arg(query.value("message_type").toString())
                                  .arg(QString::number(count));

            messages << message;
        }

        return messages;
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
        return {};
    }
}

QHash<QString, QByteArray> Account::retrieve_group_binary_data(QSqlDatabase &db, const int &group_ID, const QString &date_time)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("SELECT file_data, data_type FROM group_binary_data WHERE group_ID = ? AND date_time = ?");
        query.addBindValue(group_ID);
        query.addBindValue(date_time);

        if (!query.exec())
        {
            qDebug() << "retrieve_group_binary_data() ---> SQL ERROR:" << query.lastError().text();
            return {};
        }

        QHash<QString, QByteArray> binary_data = {};

        if (query.next())
        {
            QByteArray file_data = query.value("file_data").toByteArray();
            QString data_type = query.value("data_type").toString();

            binary_data.insert(data_type, file_data);
        }

        return binary_data;
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
        return {};
    }
}

void Account::remove_from_group(QSqlDatabase &db, const int &group_ID, const int &phone_number)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("DELETE FROM group_memberships WHERE group_ID = ? AND participant_ID = ?");
        query.addBindValue(group_ID);
        query.addBindValue(phone_number);

        if (!query.exec())
            qDebug() << "remove_from_group() ---> SQL ERROR:" << query.lastError().text();
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
    }
}

void Account::delete_account(QSqlDatabase &db, const int &phone_number)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("DELETE FROM accounts WHERE phone_number = ?");
        query.addBindValue(phone_number);

        if (!query.exec())
            qDebug() << "delete_account() ---> SQL ERROR:" << query.lastError().text();
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
    }
}

void Account::update_last_message_read(QSqlDatabase &db, const int &conversation_ID, const int &client_ID, const QString &time)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("UPDATE conversations SET last_message_read1 = CASE WHEN participant1_ID = ? THEN ? ELSE last_message_read1 END, "
                      "last_message_read2 = CASE WHEN participant2_ID = ? THEN ? ELSE last_message_read2 END "
                      "WHERE conversation_ID = ? AND (participant1_ID = ? OR participant2_ID = ?)");
        query.addBindValue(client_ID);
        query.addBindValue(time);
        query.addBindValue(client_ID);
        query.addBindValue(time);
        query.addBindValue(conversation_ID);
        query.addBindValue(client_ID);
        query.addBindValue(client_ID);

        if (!query.exec())
            qDebug() << "update_last_message_read() ---> SQL ERROR:" << query.lastError().text();
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
    }
}

void Account::update_group_last_message_read(QSqlDatabase &db, const int &group_ID, const int &client_ID, const QString &time)
{
    try
    {
        QSqlQuery query(db);
        query.prepare("UPDATE group_memberships SET last_message_read = ? WHERE group_ID = ? AND participant_ID = ?");
        query.addBindValue(time);
        query.addBindValue(group_ID);
        query.addBindValue(client_ID);

        if (!query.exec())
            qDebug() << "update_group_last_message_read() ---> SQL ERROR:" << query.lastError().text();
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
    }
}

QString Account::UTC_to_timeZone(const QString &UTC_time, const QString &timeZone_ID)
{
    QDateTime UTC_dateTime = QDateTime::fromString(UTC_time);
    if (!UTC_dateTime.isValid())
    {
        qDebug() << "Invalid UTC time format:" << UTC_time;
        return QString();
    }

#ifdef __EMSCRIPTEN__
    return QString();

    // FIXME: find a way to fix this
#else
    QTimeZone targetTimeZone(timeZone_ID.toUtf8());
    if (!targetTimeZone.isValid())
    {
        qDebug() << "Invalid time zone ID:" << timeZone_ID;
        return QString();
    }

    QDateTime localDateTime = UTC_dateTime.toTimeZone(targetTimeZone);

    return localDateTime.toString("yyyy-MM-dd HH:mm:ss");
#endif
}