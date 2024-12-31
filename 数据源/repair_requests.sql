create table repair_requests
(
    repairID    INTEGER
        primary key autoincrement,
    studentID   TEXT    not null
        references users,
    roomID      INTEGER not null
        references rooms,
    description TEXT    not null,
    repairTime  DATETIME default CURRENT_TIMESTAMP,
    repairType  TEXT    not null,
    status      TEXT     default '未处理',
    approveTime DATETIME,
    handleTime  DATETIME default CURRENT_TIMESTAMP,
    check (repairType IN ('泥', '木', '水', '电', '设备', '其它')),
    check (status IN ('未处理', '已处理'))
);

INSERT INTO repair_requests (repairID, studentID, roomID, description, repairTime, repairType, status, approveTime, handleTime) VALUES (1, '1002', 1, '', '2024-12-27 14:36:22', '泥', '已处理', null, '2024-12-27 15:11:25');
INSERT INTO repair_requests (repairID, studentID, roomID, description, repairTime, repairType, status, approveTime, handleTime) VALUES (2, '1002', 1, 'da', '2024-12-27 14:39:19', '水', '已处理', null, '2024-12-27 15:06:33');
INSERT INTO repair_requests (repairID, studentID, roomID, description, repairTime, repairType, status, approveTime, handleTime) VALUES (3, '1001', 1, '的', '2024-12-27 15:12:07', '其它', '已处理', null, '2024-12-27 15:12:47');
INSERT INTO repair_requests (repairID, studentID, roomID, description, repairTime, repairType, status, approveTime, handleTime) VALUES (4, '1001', 1, '大', '2024-12-27 15:12:35', '泥', '已处理', null, '2024-12-27 15:13:26');
