-- 1. 插入宿舍楼数据
INSERT INTO dormitories (name, sex, position)
VALUES ('东区1号楼', '男', '东区'),
       ('东区2号楼', '女', '东区'),
       ('西区1号楼', '男', '西区'),
       ('西区2号楼', '女', '西区');

-- 2. 插入房间数据
-- 东区1号楼
INSERT INTO rooms (dormitoryID, roomNumber, capacity, occupied)
VALUES (1, '101', 4, 2),
       (1, '102', 4, 3);

-- 东区2号楼
INSERT INTO rooms (dormitoryID, roomNumber, capacity, occupied)
VALUES (2, '201', 4, 1),
       (2, '202', 4, 0);

-- 西区1号楼
INSERT INTO rooms (dormitoryID, roomNumber, capacity, occupied)
VALUES (3, '301', 4, 3),
       (3, '302', 4, 0);

-- 西区2号楼
INSERT INTO rooms (dormitoryID, roomNumber, capacity, occupied)
VALUES (4, '401', 4, 0),
       (4, '402', 4, 2);

-- 3. 插入学生数据
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin)
VALUES ('20231001', '张三', '男', 'password123', '1234567890', 1, 0),
       ('20231002', '李四', '女', 'password456', '0987654321', 1, 0),
       ('20231003', '王五', '男', 'password789', '1122334455', 0, 0),
       ('20231004', '赵六', '女', 'password101', '2233445566', 1, 0);

-- 4. 插入学生与房间的关系数据
INSERT INTO student_rooms (studentID, roomID)
VALUES ('20231001', 1), -- 张三入住东区1号楼101房间
       ('20231002', 4), -- 李四入住东区2号楼201房间
       ('20231004', 6);
-- 赵六入住西区2号楼402房间

-- 5. 插入入住记录到 check_in_out_records 表
INSERT INTO check_in_out_records (studentID, roomID, eventTime, recordType, note)
VALUES ('20231001', 1, CURRENT_TIMESTAMP, '入住', '初次入住'),
       ('20231002', 4, CURRENT_TIMESTAMP, '入住', '初次入住'),
       ('20231004', 6, CURRENT_TIMESTAMP, '入住', '初次入住');
