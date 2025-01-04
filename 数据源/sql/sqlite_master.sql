create table sqlite_master
(
    type     TEXT,
    name     TEXT,
    tbl_name TEXT,
    rootpage INT,
    sql      TEXT
);

INSERT INTO sqlite_master (type, name, tbl_name, rootpage, sql) VALUES ('table', 'users', 'users', 2, 'CREATE TABLE users
(
    userID      TEXT PRIMARY KEY,  -- 用户ID（学号或用户名）
    name        TEXT NOT NULL,     -- 姓名
    gender      TEXT NOT NULL,     -- 性别
    password    TEXT NOT NULL,     -- 密码
    contactInfo TEXT,              -- 联系方式
    isCheckedIn INTEGER DEFAULT 0, -- 是否入住（0表示没有，1表示有）
    isAdmin     INTEGER DEFAULT 0  -- 是否为管理员（0表示学生，1表示管理员）
)');
INSERT INTO sqlite_master (type, name, tbl_name, rootpage, sql) VALUES ('index', 'sqlite_autoindex_users_1', 'users', 3, null);
INSERT INTO sqlite_master (type, name, tbl_name, rootpage, sql) VALUES ('table', 'dormitories', 'dormitories', 4, 'CREATE TABLE dormitories
(
    dormitoryID INTEGER PRIMARY KEY AUTOINCREMENT, -- 宿舍楼ID（自增）
    name        TEXT NOT NULL UNIQUE,              -- 宿舍楼名称
    sex         TEXT NOT NULL,                     -- 性别
    position    TEXT
)');
INSERT INTO sqlite_master (type, name, tbl_name, rootpage, sql) VALUES ('index', 'sqlite_autoindex_dormitories_1', 'dormitories', 5, null);
INSERT INTO sqlite_master (type, name, tbl_name, rootpage, sql) VALUES ('table', 'sqlite_sequence', 'sqlite_sequence', 6, 'CREATE TABLE sqlite_sequence(name,seq)');
INSERT INTO sqlite_master (type, name, tbl_name, rootpage, sql) VALUES ('table', 'student_rooms', 'student_rooms', 8, 'CREATE TABLE student_rooms
(
    studentID TEXT    NOT NULL,      -- 学生ID（外键）
    roomID    INTEGER NOT NULL,      -- 房间ID（外键）
    PRIMARY KEY (studentID, roomID), -- 组合主键，确保每个学生在一个房间内只能有一个记录
    FOREIGN KEY (studentID) REFERENCES users (userID),
    FOREIGN KEY (roomID) REFERENCES rooms (roomID)
)');
INSERT INTO sqlite_master (type, name, tbl_name, rootpage, sql) VALUES ('index', 'sqlite_autoindex_student_rooms_1', 'student_rooms', 9, null);
INSERT INTO sqlite_master (type, name, tbl_name, rootpage, sql) VALUES ('table', 'rooms', 'rooms', 11, 'CREATE TABLE "rooms" (
                           roomID INTEGER PRIMARY KEY AUTOINCREMENT,
                           dormitoryID INTEGER NOT NULL,
                           roomNumber TEXT NOT NULL,
                           capacity INTEGER NOT NULL,
                           occupied INTEGER DEFAULT 0,
                           repair_status TEXT DEFAULT ''正常'',
                           FOREIGN KEY (dormitoryID) REFERENCES dormitories (dormitoryID)
)');
INSERT INTO sqlite_master (type, name, tbl_name, rootpage, sql) VALUES ('table', 'accommodation_requests', 'accommodation_requests', 10, 'CREATE TABLE accommodation_requests
(
    requestID     INTEGER PRIMARY KEY AUTOINCREMENT,                                               -- 申请ID（自增）
    studentID     TEXT                                                 NOT NULL,                   -- 学生ID（外键）
    dormitoryName TEXT,                                                                            -- 申请宿舍楼名称（用于换宿）
    roomNumber    TEXT,                                                                            -- 申请房间号（用于换宿）
    requestType   TEXT CHECK (requestType IN (''入住'', ''换宿'', ''退宿'')) NOT NULL,                   -- 申请类型（入住、换宿、退宿）
    requestTime   DATETIME                                              DEFAULT CURRENT_TIMESTAMP, -- 申请时间（默认当前时间）
    approveTime   DATETIME                                              DEFAULT NULL,
    status        TEXT CHECK (status IN (''待审批'', ''已审批'', ''已拒绝'')) DEFAULT ''待审批'',          -- 申请状态（待审批、已审批、已拒绝）
    note          TEXT,                                                                            -- 备注（可选，存储任何附加信息）
    FOREIGN KEY (studentID) REFERENCES users (userID)                                              -- 外键关联到用户表
)');
INSERT INTO sqlite_master (type, name, tbl_name, rootpage, sql) VALUES ('table', 'check_in_out_records', 'check_in_out_records', 15, 'CREATE TABLE "check_in_out_records" (
                                          recordID   INTEGER PRIMARY KEY AUTOINCREMENT,                    -- 记录ID（自增）
                                          studentID  TEXT NOT NULL,                                         -- 学生ID（外键）
                                          roomID     INTEGER NOT NULL,                                      -- 房间ID（外键）
                                          eventTime  DATETIME DEFAULT CURRENT_TIMESTAMP,                    -- 默认使用当前时间
                                          recordType TEXT CHECK (recordType IN (''入住'', ''退宿'')) NOT NULL,  -- 记录类型（入住或退宿）
                                          note       TEXT,                                                  -- 备注（可选，存储任何附加信息）
                                          FOREIGN KEY (studentID) REFERENCES users (userID),               -- 外键关联到用户表
                                          FOREIGN KEY (roomID) REFERENCES rooms (roomID)                   -- 外键关联到房间表
)');
INSERT INTO sqlite_master (type, name, tbl_name, rootpage, sql) VALUES ('trigger', 'set_eventTime_before_insert', 'check_in_out_records', 0, 'CREATE TRIGGER set_eventTime_before_insert
    BEFORE INSERT ON "check_in_out_records"
    FOR EACH ROW
BEGIN
    -- 如果没有提供 eventTime，则使用本地时间
    UPDATE "check_in_out_records"
    SET eventTime = datetime(''now'', ''localtime'')
    WHERE rowid = NEW.rowid AND NEW.eventTime IS NULL;
END');
INSERT INTO sqlite_master (type, name, tbl_name, rootpage, sql) VALUES ('table', 'repair_requests', 'repair_requests', 14, 'CREATE TABLE "repair_requests"
(
    repairID    INTEGER PRIMARY KEY AUTOINCREMENT,                                            -- 报修ID（自增）
    studentID   TEXT                                                                NOT NULL, -- 学生ID（外键，关联users表）
    roomID      INTEGER                                                             NOT NULL, -- 房间ID（外键，关联rooms表）
    description TEXT                                                                NOT NULL, -- 详细描述
    repairTime  DATETIME,                                                                     -- 报修时间（不设置默认值，使用触发器自动填充）
    repairType  TEXT CHECK (repairType IN (''泥'', ''木'', ''水'', ''电'', ''设备'', ''其它'')) NOT NULL, -- 报修类型
    status      TEXT CHECK (status IN (''未处理'', ''已处理'')) DEFAULT ''未处理'',                 -- 报修状态（未处理、已处理）
    handleTime  DATETIME,                                                                     -- 处理时间，默认为NULL
    FOREIGN KEY (studentID) REFERENCES users (userID),                                        -- 外键关联到用户表
    FOREIGN KEY (roomID) REFERENCES rooms (roomID)                                            -- 外键关联到房间表
)');
INSERT INTO sqlite_master (type, name, tbl_name, rootpage, sql) VALUES ('trigger', 'set_repairTimes_before_insert', 'repair_requests', 0, 'CREATE TRIGGER set_repairTimes_before_insert
    BEFORE INSERT
    ON "repair_requests"
    FOR EACH ROW
BEGIN
    -- 如果没有提供 repairTime，则使用当前时间
    UPDATE "repair_requests"
    SET repairTime = datetime(''now'', ''localtime'')
    WHERE rowid = NEW.rowid
      AND NEW.repairTime IS NULL;

    -- 如果没有提供 handleTime，则使用当前时间
    UPDATE "repair_requests"
    SET handleTime = datetime(''now'', ''localtime'')
    WHERE rowid = NEW.rowid
      AND NEW.handleTime IS NULL;
END');
