SELECT CASE
        WHEN participant1_ID = ? THEN participant2
        ELSE participant1
    END AS other_participant,
    CASE
        WHEN participant1_ID = ? THEN participant2_ID
        ELSE participant1_ID
    END AS other_participant_ID,
    conversation_ID
FROM conversations
WHERE participant1_ID = ?
    OR participant2_ID = ?;