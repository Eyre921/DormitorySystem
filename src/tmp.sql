-- 删除原表 check_in_out_records
DROP TABLE IF EXISTS check_in_out_records;

-- 删除原表 accommodation_requests
DROP TABLE IF EXISTS accommodation_requests;


CREATE TABLE check_in_out_records
(
    recordID       INTEGER PRIMARY KEY AUTOINCREMENT,                                                   -- 记录ID（自增）
    studentID      TEXT                                        NOT NULL,                                -- 学生ID（外键）
    roomID         INTEGER                                     NOT NULL,                                -- 房间ID（外键）
    eventTime      DATETIME                                                  DEFAULT CURRENT_TIMESTAMP, -- 事件时间（无论是入住还是退宿）
    recordType     TEXT CHECK (recordType IN ('入住', '退宿')) NOT NULL,                                -- 记录类型（入住或退宿）
    approvalStatus TEXT CHECK (approvalStatus IN ('未审批', '通过', '拒绝')) DEFAULT '未审批',          -- 审批状态
    note           TEXT,                                                                                -- 备注（可选，存储任何附加信息）
    FOREIGN KEY (studentID) REFERENCES users (userID),                                                  -- 外键关联到用户表
    FOREIGN KEY (roomID) REFERENCES rooms (roomID)                                                      -- 外键关联到房间表
);

CREATE TABLE accommodation_requests
(
    recordID       INTEGER PRIMARY KEY AUTOINCREMENT,                                                   -- 记录ID（自增）
    studentID      TEXT                                         NOT NULL,                               -- 学生ID（外键）
    roomID         INTEGER                                      NOT NULL,                               -- 房间ID（外键）
    eventTime      DATETIME                                                  DEFAULT CURRENT_TIMESTAMP, -- 事件时间（无论是入住还是退宿）
    requestType    TEXT CHECK (requestType IN ('入住', '退宿')) NOT NULL,                               -- 记录类型（入住或退宿）
    approvalStatus TEXT CHECK (approvalStatus IN ('未审批', '通过', '拒绝')) DEFAULT '未审批',          -- 审批状态
    approvalTime   DATETIME,                                                                            -- 审批时间（默认NULL）
    note           TEXT,                                                                                -- 备注（可选，存储任何附加信息）
    FOREIGN KEY (studentID) REFERENCES users (userID),                                                  -- 外键关联到用户表
    FOREIGN KEY (roomID) REFERENCES rooms (roomID)                                                      -- 外键关联到房间表
);


