SELECT M.Timestamp,
    CASE
        WHEN M.sender_ID = C.participant1_ID THEN A1.first_name
        ELSE A2.first_name
    END AS sender,
    CASE
        WHEN M.ReceiverID = C.participant1_ID THEN A1.first_name
        ELSE A2.first_name
    END AS receiver,
    M.content
FROM messages M
    JOIN conversations C ON M.conversation_ID = C.conversation_ID
    JOIN accounts A1 ON C.participant1_ID = A1.phone_number
    JOIN accounts A2 ON C.participant2_ID = A2.phone_number
WHERE C.conversation_ID = ?
ORDER BY M.Timestamp;