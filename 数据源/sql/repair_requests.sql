create table repair_requests
(
    repairID    INTEGER
        primary key autoincrement,
    studentID   TEXT    not null
        references users,
    roomID      INTEGER not null
        references rooms,
    description TEXT    not null,
    repairTime  DATETIME,
    repairType  TEXT    not null,
    status      TEXT default '未处理',
    handleTime  DATETIME,
    check (repairType IN ('泥', '木', '水', '电', '设备', '其它')),
    check (status IN ('未处理', '已处理'))
);

INSERT INTO repair_requests (repairID, studentID, roomID, description, repairTime, repairType, status, handleTime) VALUES (1, '1002', 1, '', '2024-12-27 14:36:22', '泥', '已处理', '2024-12-27 15:11:25');
INSERT INTO repair_requests (repairID, studentID, roomID, description, repairTime, repairType, status, handleTime) VALUES (2, '1002', 1, 'da', '2024-12-27 14:39:19', '水', '已处理', '2024-12-27 15:06:33');
INSERT INTO repair_requests (repairID, studentID, roomID, description, repairTime, repairType, status, handleTime) VALUES (3, '1001', 1, '的', '2024-12-27 15:12:07', '其它', '已处理', '2024-12-27 15:12:47');
INSERT INTO repair_requests (repairID, studentID, roomID, description, repairTime, repairType, status, handleTime) VALUES (4, '1001', 1, '大', '2024-12-27 15:12:35', '泥', '已处理', '2024-12-27 15:13:26');
INSERT INTO repair_requests (repairID, studentID, roomID, description, repairTime, repairType, status, handleTime) VALUES (5, '1002', 1, '坏了', '2024-12-31 02:46:54', '泥', '未处理', null);
INSERT INTO repair_requests (repairID, studentID, roomID, description, repairTime, repairType, status, handleTime) VALUES (6, '1002', 1, '断电了', '2024-12-31 02:47:25', '电', '未处理', null);
INSERT INTO repair_requests (repairID, studentID, roomID, description, repairTime, repairType, status, handleTime) VALUES (10, '0002', 2, '没水了', '2024-12-31 11:30:33', '水', '已处理', '2025-01-02 15:30:55');
INSERT INTO repair_requests (repairID, studentID, roomID, description, repairTime, repairType, status, handleTime) VALUES (11, '0002', 2, '坏了', '2025-01-02 15:20:45', '泥', '已处理', '2025-01-02 15:31:07');
INSERT INTO repair_requests (repairID, studentID, roomID, description, repairTime, repairType, status, handleTime) VALUES (12, '0002', 2, '坏了', '2025-01-02 15:20:54', '水', '已处理', '2025-01-02 15:31:25');
