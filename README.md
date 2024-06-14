// BELOW ARE ALL THE REQUIREMENTS AND PREPARATIONS FOR THE DATABASE IN ORDER TO USE THIS PROJECT'S CODE. MAKE SURE THAT YOU HAVE MYSQL INSTALLED ON YOUR PC. YOU CAN USE EITHER VSCODE OR MYSQL WORKBENCH TO RUN THESE FOLLOWING QUERIES



    ------ This Project will be a kind of duplication of whatsapp and how I understand it. The outcome will most likely be the same but the logic and implementation are way different.
    ------ I am using C++ along with Qt for the GUI implementation which will allow the app to be cross-platform.
    ------ Within Qt, I am mainly using QtCore and QtWidgets classes which encapsulates QWebSocket and QWebSocketServer for the Network/Web communication part. I Used QtMultimedia for recording audio files and the like.
    ------ All Data serialization (files, voice notes, text messages) are operated using QDataStream (another QtWidgets's class).
    ------ The app uses an hybrid architecture. It uses both the Server--clients and Peer-to-Peer (P2P) Architecture for large (refers to the message's size in byte) voice notes and files.
    ------ Clients'name are dynamic within the interface i.e changing your default name will result in changing it for whoever added your phone_number.
    ------ Clients are bestowed minimal access to the Database for Security's sake. The server handles quasi every Database related query.
    ------ Swipe left to go back Implementation by overriding these 2 functions: mousePressEvent and mouseMoveEvent.
    ------ Voice Notes Feature implemented using QMediaRecorder (class within QtMultimedia).
    ------ On/Offline Status implemented using a green and red dot. 
    ------ Using WebAssembly, it's both a Desktop app and WebApp.
    ------ Store Data using emscripten's IDBFS, then sync it with indexed_DB to make Data consistent. File and Audio retrieval can be done without requesting it from the server.
    ------ Group Chats (Adding people from your friend_list). 
    ------ 
    ------
    ------
    ------

    TO DO
    --- Remove/Add people from/to groups
    --- Message read/unread
    --- Make the GUI more appealing.
    --- Upload Preview here once Finished.


            *************** ALL THE TABLES ***************

            -------accounts
            CREATE TABLE accounts
            (
                phone_number INT PRIMARY KEY,
                first_name VARCHAR(50),
                last_name VARCHAR(50),
                port INT,
                alias VARCHAR(50) DEFAULT NULL
            );

            -------password_security
            CREATE TABLE password_security
            (
                phone_number INT PRIMARY KEY,
                hashed_password VARBINARY(500),
                secret_question VARCHAR(500),
                secret_answer VARCHAR(500)
            );

            -------conversations
            CREATE TABLE conversations 
            (
                conversation_ID INT PRIMARY KEY,
                participant1 VARCHAR(50),
                participant1_ID INT,
                participant2 VARCHAR(50),
                participant2_ID INT,
                start_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            );

            -------messages
            CREATE TABLE messages 
            (
                date_time TIMESTAMP PRIMARY KEY,
                conversation_ID INT,
                sender_ID INT,
                receiver_ID INT,
                content TEXT,
                message_type VARCHAR(25) DEFAULT 'text'
            );


            -------binary_data
            CREATE TABLE binary_data 
            (
                date_time TIMESTAMP PRIMARY KEY,
                conversation_ID INT,
                sender_ID INT,
                receiver_ID INT,
                file_name VARCHAR(255),
                file_data MEDIUMBLOB,
                data_type TEXT
            );

            -------group_memberships
            CREATE TABLE group_memberships 
            (
                group_ID INT,
                group_name TEXT,
                participant_ID INT,
                user_role TEXT,
                PRIMARY KEY (group_ID, participant_ID)
            );

            -------group_messages
            CREATE TABLE group_messages 
            (
                date_time TIMESTAMP PRIMARY KEY,
                group_ID INT,
                sender TEXT,
                content TEXT,
                message_type VARCHAR(25) DEFAULT 'text'
            );

            -------group_binary_data
            CREATE TABLE group_binary_data 
            (
                date_time TIMESTAMP PRIMARY KEY,
                group_ID INT,
                sender TEXT,
                file_name VARCHAR(255),
                file_data MEDIUMBLOB,
                data_type TEXT
            );

  
            *************** ALL THE TRIGGERS ***************

            -------default_alias
            CREATE TRIGGER default_alias BEFORE INSERT ON accounts
            FOR EACH ROW
                BEGIN
                    IF NEW.alias IS NULL THEN 
                        SET NEW.alias = NEW.first_name;
                    END IF;
                END;

            -------add_file_message
            CREATE TRIGGER add_file_message AFTER INSERT ON binary_data 
            FOR EACH ROW 
                BEGIN
                    INSERT INTO messages (date_time, conversation_ID, sender_ID, receiver_ID, content, message_type)
                    VALUES (NEW.date_time, NEW.conversation_ID, NEW.sender_ID, NEW.receiver_ID, NEW.file_name, NEW.data_type);
                END;

            -------update_message_deletion
            CREATE TRIGGER update_message_deletion AFTER DELETE ON messages 
            FOR EACH ROW 
                BEGIN
                    DELETE FROM binary_data WHERE date_time = OLD.date_time AND conversation_ID = OLD.conversation_ID;
                END;

            -------update_group_message_deletion
            CREATE TRIGGER update_group_message_deletion AFTER DELETE ON group_messages 
            FOR EACH ROW 
                BEGIN
                    DELETE FROM group_binary_data WHERE date_time = OLD.date_time AND group_ID = OLD.group_ID;
                END;

            -------add_group_file_message                 
            CREATE TRIGGER add_group_file_message AFTER INSERT ON group_binary_data 
            FOR EACH ROW 
                BEGIN
                    INSERT INTO group_messages (date_time, group_ID, sender, content, message_type)
                    VALUES (NEW.date_time, NEW.group_ID, NEW.sender, NEW.file_name, NEW.data_type);
                END;