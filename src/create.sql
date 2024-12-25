CREATE TABLE users
(
    userID      TEXT PRIMARY KEY,                             -- 用户ID（学号或用户名）
    name        TEXT                                NOT NULL, -- 姓名
    gender      TEXT CHECK (gender IN ('男', '女')) NOT NULL, -- 性别
    password    TEXT                                NOT NULL, -- 密码
    contactInfo TEXT,                                         -- 联系方式
    isCheckedIn INTEGER DEFAULT 0,                            -- 是否入住（0表示没有，1表示有）
    isAdmin     INTEGER DEFAULT 0                             -- 是否为管理员（0表示学生，1表示管理员）
);
CREATE TABLE dormitories
(
    dormitoryID INTEGER PRIMARY KEY AUTOINCREMENT, -- 宿舍楼ID（自增）
    name        TEXT NOT NULL UNIQUE,              -- 宿舍楼名称
    sex         TEXT NOT NULL,                     -- 性别
    position    TEXT
);
CREATE TABLE rooms
(
    roomID        INTEGER PRIMARY KEY AUTOINCREMENT, -- 房间ID（自增）
    dormitoryID   INTEGER           NOT NULL,        -- 所属宿舍楼ID（外键）
    roomNumber    TEXT              NOT NULL,        -- 房间号
    capacity      INTEGER           NOT NULL,        -- 房间容量
    occupied      INTEGER DEFAULT 0 NOT NULL,        -- 已入住人数
    repair_status TEXT    DEFAULT '正常',            -- 房间状态（正常、维修中）
    FOREIGN KEY (dormitoryID) REFERENCES dormitories (dormitoryID)
);
CREATE TABLE student_rooms
(
    studentID TEXT    NOT NULL,      -- 学生ID（外键）
    roomID    INTEGER NOT NULL,      -- 房间ID（外键）
    PRIMARY KEY (studentID, roomID), -- 组合主键，确保每个学生在一个房间内只能有一个记录
    FOREIGN KEY (studentID) REFERENCES users (userID),
    FOREIGN KEY (roomID) REFERENCES rooms (roomID)
);
CREATE TABLE check_in_out_records
(
    recordID   INTEGER PRIMARY KEY AUTOINCREMENT,                    -- 记录ID（自增）
    studentID  TEXT                                        NOT NULL, -- 学生ID（外键）
    roomID     INTEGER                                     NOT NULL, -- 房间ID（外键）
    eventTime  DATETIME DEFAULT CURRENT_TIMESTAMP,                   -- 事件时间（无论是入住还是退宿）
    recordType TEXT CHECK (recordType IN ('入住', '退宿')) NOT NULL, -- 记录类型（入住或退宿）
    note       TEXT,                                                 -- 备注（可选，存储任何附加信息）
    FOREIGN KEY (studentID) REFERENCES users (userID),               -- 外键关联到用户表
    FOREIGN KEY (roomID) REFERENCES rooms (roomID)                   -- 外键关联到房间表
);



CREATE TABLE accommodation_requests
(
    requestID     INTEGER PRIMARY KEY AUTOINCREMENT,                                               -- 申请ID（自增）
    studentID     TEXT                                                 NOT NULL,                   -- 学生ID（外键）
    dormitoryName TEXT,                                                                            -- 申请宿舍楼名称（用于换宿）
    roomNumber    TEXT,                                                                            -- 申请房间号（用于换宿）
    requestType   TEXT CHECK (requestType IN ('入住', '换宿', '退宿')) NOT NULL,                   -- 申请类型（入住、换宿、退宿）
    requestTime   DATETIME                                              DEFAULT CURRENT_TIMESTAMP, -- 申请时间（默认当前时间）
    approveTime   DATETIME                                              DEFAULT NULL,
    status        TEXT CHECK (status IN ('待审批', '已审批', '已拒绝')) DEFAULT '待审批',          -- 申请状态（待审批、已审批、已拒绝）
    note          TEXT,                                                                            -- 备注（可选，存储任何附加信息）
    FOREIGN KEY (studentID) REFERENCES users (userID)                                              -- 外键关联到用户表
);



-- CREATE TABLE repair_requests
-- (
--     requestID     INTEGER PRIMARY KEY AUTOINCREMENT, -- 请求ID（自增）
--     studentID     TEXT    NOT NULL,                  -- 学生ID（外键）
--     roomID        INTEGER NOT NULL,                  -- 房间ID（外键）
--     description   TEXT    NOT NULL,                  -- 维修描述
--     status        TEXT DEFAULT '待处理',             -- 请求状态（待处理、处理中、已完成）
--     dateSubmitted TEXT DEFAULT CURRENT_TIMESTAMP,    -- 提交日期（默认当前时间）
--     FOREIGN KEY (studentID) REFERENCES users (userID),
--     FOREIGN KEY (roomID) REFERENCES rooms (roomID)
-- );
-- CREATE TABLE notifications
-- (
--     notificationID INTEGER PRIMARY KEY AUTOINCREMENT, -- 通知ID（自增）
--     userID         TEXT NOT NULL,                     -- 用户ID（外键）
--     message        TEXT NOT NULL,                     -- 通知内容
--     dateSent       TEXT DEFAULT CURRENT_TIMESTAMP,    -- 发送时间（默认当前时间）
--     FOREIGN KEY (userID) REFERENCES users (userID)
-- );
-- CREATE TABLE reports
-- (
--     reportID      INTEGER PRIMARY KEY AUTOINCREMENT, -- 报表ID（自增）
--     reportType    TEXT NOT NULL,                     -- 报表类型（如使用率、入住率）
--     content       TEXT NOT NULL,                     -- 报表内容（通常是生成的文件或数据）
--     dateGenerated TEXT DEFAULT CURRENT_TIMESTAMP     -- 生成日期（默认当前时间）
-- );
