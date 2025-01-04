create table check_in_out_records
(
    recordID   INTEGER
        primary key autoincrement,
    studentID  TEXT    not null
        references users,
    roomID     INTEGER not null
        references rooms,
    eventTime  DATETIME default CURRENT_TIMESTAMP,
    recordType TEXT    not null,
    note       TEXT,
    check (recordType IN ('入住', '退宿'))
);

INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (1, '1000', 6, '2024-12-25 15:25:40', '退宿', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (2, '1000', 6, '2024-12-25 15:26:05', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (3, '1001', 1, '2024-12-25 15:26:17', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (4, '1002', 1, '2024-12-25 15:26:29', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (5, '1000', 6, '2024-12-25 15:26:45', '退宿', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (6, '1001', 1, '2024-12-26 15:06:58', '退宿', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (7, '1001', 6, '2024-12-26 15:16:16', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (8, '1001', 6, '2024-12-26 15:20:52', '退宿', '申请的换宿');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (9, '1001', 1, '2024-12-26 15:20:52', '入住', '申请的换宿');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (10, 'T1', 9, '2024-12-26 16:38:06', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (11, 'T2', 9, '2024-12-26 16:39:48', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (12, 't1', 5, '2024-12-27 07:27:32', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (13, 't1', 5, '2024-12-27 07:32:43', '退宿', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (14, 't1', 5, '2024-12-27 07:34:41', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (15, 't2', 5, '2024-12-27 08:14:01', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (16, '2024', 9, '2024-12-30 14:07:28', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (17, '2025', 3, '2024-12-30 14:07:45', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (18, '2027', 6, '2024-12-30 14:08:04', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (19, '20231003', 9, '2024-12-30 14:08:38', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (20, '1000', 1, '2024-12-30 14:09:07', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (21, '222', 5, '2024-12-30 14:09:27', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (22, '0002', 2, '2024-12-31 02:27:43', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (23, '0002', 2, '2024-12-31 02:28:13', '退宿', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (24, '0002', 2, '2024-12-31 10:34:19', '入住', '');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (25, '0002', 2, '2025-01-02 15:31:46', '退宿', '申请的退宿');
INSERT INTO check_in_out_records (recordID, studentID, roomID, eventTime, recordType, note) VALUES (26, '123456789', 17, '2025-01-02 15:32:16', '入住', '');
