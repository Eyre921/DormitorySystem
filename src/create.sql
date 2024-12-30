-- 创建用户表
CREATE TABLE users
(
    userID      TEXT PRIMARY KEY,                             -- 用户ID（学号或用户名），作为主键唯一标识用户
    name        TEXT                                NOT NULL, -- 姓名，不能为空，表示学生或用户的名字
    gender      TEXT CHECK (gender IN ('男', '女')) NOT NULL, -- 性别，检查是否为 '男' 或 '女'，不能为空
    password    TEXT                                NOT NULL, -- 密码，不能为空，用于用户登录验证
    contactInfo TEXT,                                         -- 联系方式，可选，用于存储学生的联系信息
    isCheckedIn INTEGER DEFAULT 0,                            -- 是否入住（0表示没有，1表示有），默认为0
    isAdmin     INTEGER DEFAULT 0                             -- 是否为管理员（0表示学生，1表示管理员），默认为0
);

-- 创建宿舍楼表
CREATE TABLE dormitories
(
    dormitoryID INTEGER PRIMARY KEY AUTOINCREMENT, -- 宿舍楼ID（自增），唯一标识宿舍楼
    name        TEXT NOT NULL UNIQUE,              -- 宿舍楼名称，不能为空，且必须唯一
    sex         TEXT NOT NULL,                     -- 性别，表示宿舍楼的性别要求（男/女）
    position    TEXT                               -- 位置，表示宿舍楼的具体位置（可选）
);

-- 创建房间表
CREATE TABLE rooms
(
    roomID        INTEGER PRIMARY KEY AUTOINCREMENT,                                   -- 房间ID（自增），唯一标识房间
    dormitoryID   INTEGER                                                    NOT NULL, -- 所属宿舍楼ID（外键），关联到宿舍楼表
    roomNumber    TEXT                                                       NOT NULL, -- 房间号，不能为空，表示房间的编号
    capacity      INTEGER                                                    NOT NULL, -- 房间容量，表示房间可容纳的人数
    occupied      INTEGER                                          DEFAULT 0 NOT NULL, -- 已入住人数，默认为0
    repair_status TEXT CHECK (repair_status IN ('维修中', '正常')) DEFAULT '正常',     -- 房间状态（正常、维修中），默认为 '正常'
    FOREIGN KEY (dormitoryID) REFERENCES dormitories (dormitoryID)                     -- 外键，关联宿舍楼表
);

-- 创建学生房间关联表
CREATE TABLE student_rooms
(
    studentID TEXT    NOT NULL,                        -- 学生ID（外键），关联到用户表
    roomID    INTEGER NOT NULL,                        -- 房间ID（外键），关联到房间表
    PRIMARY KEY (studentID, roomID),                   -- 组合主键，确保每个学生在一个房间内只能有一个记录
    FOREIGN KEY (studentID) REFERENCES users (userID), -- 外键，关联到用户表
    FOREIGN KEY (roomID) REFERENCES rooms (roomID)     -- 外键，关联到房间表
);

-- 创建入住/退宿记录表
CREATE TABLE check_in_out_records
(
    recordID   INTEGER PRIMARY KEY AUTOINCREMENT,                    -- 记录ID（自增），唯一标识每条记录
    studentID  TEXT                                        NOT NULL, -- 学生ID（外键），关联到用户表
    roomID     INTEGER                                     NOT NULL, -- 房间ID（外键），关联到房间表
    eventTime  DATETIME DEFAULT CURRENT_TIMESTAMP,                   -- 事件时间，默认为当前时间
    recordType TEXT CHECK (recordType IN ('入住', '退宿')) NOT NULL, -- 记录类型（入住或退宿），不能为空
    note       TEXT,                                                 -- 备注，可选，存储任何附加信息
    FOREIGN KEY (studentID) REFERENCES users (userID),               -- 外键，关联到用户表
    FOREIGN KEY (roomID) REFERENCES rooms (roomID)                   -- 外键，关联到房间表
);

-- 创建报修请求表
CREATE TABLE repair_requests
(
    repairID    INTEGER PRIMARY KEY AUTOINCREMENT,                                            -- 报修ID（自增），唯一标识每条报修记录
    studentID   TEXT                                                                NOT NULL, -- 学生ID（外键），关联到用户表
    roomID      INTEGER                                                             NOT NULL, -- 房间ID（外键），关联到房间表
    description TEXT                                                                NOT NULL, -- 详细描述，说明问题内容
    repairTime  DATETIME                                    DEFAULT CURRENT_TIMESTAMP,        -- 报修时间，默认为当前时间
    repairType  TEXT CHECK (repairType IN ('泥', '木', '水', '电', '设备', '其它')) NOT NULL, -- 报修类型，限定为固定值（如泥、水、电等）
    status      TEXT CHECK (status IN ('未处理', '已处理')) DEFAULT '未处理',                 -- 报修状态（未处理、已处理），默认为 '未处理'
    approveTime DATETIME,                                                                     -- 审批时间，默认为 NULL
    handleTime  DATETIME                                    DEFAULT CURRENT_TIMESTAMP,        -- 处理时间，默认为当前时间
    FOREIGN KEY (studentID) REFERENCES users (userID),                                        -- 外键，关联到用户表
    FOREIGN KEY (roomID) REFERENCES rooms (roomID)                                            -- 外键，关联到房间表
);



-- CREATE TABLE notifications
-- (
--     notificationID INTEGER PRIMARY KEY AUTOINCREMENT, -- 通知ID（自增）
--     userID         TEXT NOT NULL,                     -- 用户ID（外键）
--     message        TEXT NOT NULL,                     -- 通知内容
--     dateSent       TEXT DEFAULT CURRENT_TIMESTAMP,    -- 发送时间（默认当前时间）
--     FOREIGN KEY (userID) REFERENCES users (userID)
-- );

