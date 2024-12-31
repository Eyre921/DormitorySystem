-- 1. 删除已存在的触发器（如果有）
DROP TRIGGER IF EXISTS set_repairTimes_before_insert;

-- 2. 创建新表，修改 repairTime 和 handleTime 的默认值为当前时间
CREATE TABLE repair_requests_new
(
    repairID    INTEGER PRIMARY KEY AUTOINCREMENT,                                            -- 报修ID（自增）
    studentID   TEXT                                                                NOT NULL, -- 学生ID（外键，关联users表）
    roomID      INTEGER                                                             NOT NULL, -- 房间ID（外键，关联rooms表）
    description TEXT                                                                NOT NULL, -- 详细描述
    repairTime  DATETIME,                                                                     -- 报修时间（不设置默认值，使用触发器自动填充）
    repairType  TEXT CHECK (repairType IN ('泥', '木', '水', '电', '设备', '其它')) NOT NULL, -- 报修类型
    status      TEXT CHECK (status IN ('未处理', '已处理')) DEFAULT '未处理',                 -- 报修状态（未处理、已处理）
    handleTime  DATETIME,                                                                     -- 处理时间，默认为NULL
    FOREIGN KEY (studentID) REFERENCES users (userID),                                        -- 外键关联到用户表
    FOREIGN KEY (roomID) REFERENCES rooms (roomID)                                            -- 外键关联到房间表
);

-- 3. 创建触发器，确保 repairTime 和 handleTime 使用本地时间
CREATE TRIGGER set_repairTimes_before_insert
    BEFORE INSERT
    ON repair_requests_new
    FOR EACH ROW
BEGIN
    -- 如果没有提供 repairTime，则使用当前时间
    UPDATE repair_requests_new
    SET repairTime = datetime('now', 'localtime')
    WHERE rowid = NEW.rowid
      AND NEW.repairTime IS NULL;

    -- 如果没有提供 handleTime，则使用当前时间
    UPDATE repair_requests_new
    SET handleTime = datetime('now', 'localtime')
    WHERE rowid = NEW.rowid
      AND NEW.handleTime IS NULL;
END;

-- 4. 将旧表数据插入新表
INSERT INTO repair_requests_new (repairID, studentID, roomID, description, repairTime, repairType, status, handleTime)
SELECT repairID,
       studentID,
       roomID,
       description,
       repairTime,
       repairType,
       status,
       handleTime
FROM repair_requests;

-- 5. 删除旧表
DROP TABLE repair_requests;

-- 6. 重命名新表为原表的名称
ALTER TABLE repair_requests_new
    RENAME TO repair_requests;
UPDATE users
SET password ='2'
WHERE userID = '0002'
UPDATE users SET password = '6' WHERE userID = 0002;