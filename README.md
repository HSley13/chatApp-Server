// BELOW ARE ALL THE REQUIREMENTS AND PREPARATIONS FOR THE DATABASE IN ORDER TO USE THIS PROJECT'S CODE. MAKE SURE THAT YOU HAVE MYSQL INSTALLED ON YOUR PC. YOU CAN USE EITHER VSCODE OR MYSQL WORKBENCH TO RUN THESE FOLLOWING QUERIES


/* 

    ------ This Project will be a kind of duplication of whatsapp and how I understand it. The outcome will most likely be the same but the logic and implementation are way different.
    ------ I am using C++ along with Qt for the GUI implementation which will allow the app to be cross-platform.
    ------ Within Qt, I am mainly using QtWidgets and QtCore classes which encapsulates QTcpSocket and QTcpSocket for the Network communication part.
    ------ All Data serialization (files, voice notes, text messages) are operated using QDataStream (another QtWidgets's class)
    ------ The app uses an hybrid architecture. It uses both the Server--clients and Peer-to-Peer (P2P) Architecture for large (refers to the message's size in byte) voice notes and files.
    ------ 
    ------
    ------
    ------
    ------
    ------
    ------
    ------
    ------
    ------
    ------
    ------

    TO DO
    --- voice notes implementation
    --- List sent File and Audio in the conversation
    --- client authentification
    --- finish the database's configuration
    --- store conversations in the database
    --- Implement database conversation retrieve 
    --- 
    --- 
    --- Make the GUI more appealing 


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
                start_time DATETIME DEFAULT CURRENT_TIMESTAMP
            );


            -------messages
            CREATE TABLE messages 
            (
                message_id INT AUTO_INCREMENT PRIMARY KEY,
                conversation_ID INT,
                sender_ID INT,
                receiver_ID INT,
                content TEXT, 
                date_time DATETIME DEFAULT CURRENT_TIMESTAMP
            )AUTO_INCREMENT = 1;




            *************** ALL THE TRIGGERS ***************

            -------default_alias
            CREATE TRIGGER default_alias BEFORE INSERT ON accounts
            FOR EACH ROW
                BEGIN
                    IF NEW.alias IS NULL THEN 
                        SET NEW.alias = NEW.first_name;
                    END IF;
                END;
*/



