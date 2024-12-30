create table accommodation_requests
(
    requestID     INTEGER
        primary key autoincrement,
    studentID     TEXT not null
        references users,
    dormitoryName TEXT,
    roomNumber    TEXT,
    requestType   TEXT not null,
    requestTime   DATETIME default CURRENT_TIMESTAMP,
    approveTime   DATETIME default NULL,
    status        TEXT     default '待审批',
    note          TEXT,
    check (requestType IN ('入住', '换宿', '退宿')),
    check (status IN ('待审批', '已审批', '已拒绝'))
);

INSERT INTO accommodation_requests (requestID, studentID, dormitoryName, roomNumber, requestType, requestTime, approveTime, status, note) VALUES (1, '1000', null, null, '入住', '2024-12-25 15:27:08', '2024-12-26 14:58:58', '已拒绝', null);
INSERT INTO accommodation_requests (requestID, studentID, dormitoryName, roomNumber, requestType, requestTime, approveTime, status, note) VALUES (2, '1001', null, null, '退宿', '2024-12-25 15:28:55', '2024-12-26 15:00:23', '已审批', null);
INSERT INTO accommodation_requests (requestID, studentID, dormitoryName, roomNumber, requestType, requestTime, approveTime, status, note) VALUES (3, '1001', '西区1号楼', '301', '换宿', '2024-12-25 15:29:07', '2024-12-26 14:59:55', '已审批', '');
INSERT INTO accommodation_requests (requestID, studentID, dormitoryName, roomNumber, requestType, requestTime, approveTime, status, note) VALUES (4, '1001', null, null, '退宿', '2024-12-26 12:50:51', '2024-12-26 15:00:52', '已拒绝', null);
INSERT INTO accommodation_requests (requestID, studentID, dormitoryName, roomNumber, requestType, requestTime, approveTime, status, note) VALUES (5, '1001', '东区1号楼', '102', '换宿', '2024-12-26 12:51:02', '2024-12-26 15:00:45', '已拒绝', '');
INSERT INTO accommodation_requests (requestID, studentID, dormitoryName, roomNumber, requestType, requestTime, approveTime, status, note) VALUES (6, '1001', null, null, '退宿', '2024-12-26 15:02:01', '2024-12-26 15:06:58', '已审批', null);
INSERT INTO accommodation_requests (requestID, studentID, dormitoryName, roomNumber, requestType, requestTime, approveTime, status, note) VALUES (7, '1001', null, null, '入住', '2024-12-26 15:09:17', '2024-12-26 15:16:16', '已审批', null);
INSERT INTO accommodation_requests (requestID, studentID, dormitoryName, roomNumber, requestType, requestTime, approveTime, status, note) VALUES (8, '1001', '东区1号楼', '101', '换宿', '2024-12-26 15:20:34', '2024-12-26 15:20:52', '已审批', '');
INSERT INTO accommodation_requests (requestID, studentID, dormitoryName, roomNumber, requestType, requestTime, approveTime, status, note) VALUES (9, 't1', null, null, '入住', '2024-12-27 07:27:04', '2024-12-27 07:27:32', '已审批', null);
INSERT INTO accommodation_requests (requestID, studentID, dormitoryName, roomNumber, requestType, requestTime, approveTime, status, note) VALUES (10, 't1', null, null, '入住', '2024-12-27 07:33:20', '2024-12-27 07:34:41', '已审批', null);
INSERT INTO accommodation_requests (requestID, studentID, dormitoryName, roomNumber, requestType, requestTime, approveTime, status, note) VALUES (11, 't2', null, null, '入住', '2024-12-27 08:13:34', '2024-12-27 08:14:01', '已审批', null);
INSERT INTO accommodation_requests (requestID, studentID, dormitoryName, roomNumber, requestType, requestTime, approveTime, status, note) VALUES (12, '1001', '西区1号楼', '301', '换宿', '2024-12-27 12:04:43', null, '待审批', '');
