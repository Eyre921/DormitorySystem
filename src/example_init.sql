-- 插入宿舍楼数据
INSERT INTO dormitories (name, sex, position)
VALUES ('Building A', 'Male', 'North Campus'),
       ('Building B', 'Female', 'South Campus'),
       ('Building C', 'Male', 'East Campus'),
       ('Building D', 'Female', 'West Campus');

-- 插入房间数据
INSERT INTO rooms (dormitoryID, roomNumber, capacity, occupied, living_status, repair_status)
VALUES (1, '101', 4, 2, '未满', '正常'),
       (1, '102', 4, 4, '已满', '正常'),
       (1, '103', 4, 0, '未满', '维修中'),
       (2, '201', 4, 3, '未满', '正常'),
       (2, '202', 4, 4, '已满', '正常'),
       (3, '301', 6, 5, '未满', '正常'),
       (3, '302', 6, 0, '未满', '正常'),
       (4, '401', 4, 4, '已满', '正常'),
       (4, '402', 4, 2, '未满', '正常');

-- 插入用户数据（学生）
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin)
VALUES ('S1001', 'Alice', 'Female', 'password123', '123456789', 1, 0),
       ('S1002', 'Bob', 'Male', 'password456', '987654321', 1, 0),
       ('S1003', 'Charlie', 'Male', 'password789', '456789123', 1, 0),
       ('S1004', 'David', 'Male', 'password101', '123123123', 1, 0),
       ('S1005', 'Eve', 'Female', 'password202', '234234234', 1, 0),
       ('S1006', 'Frank', 'Male', 'password303', '345345345', 0, 0),
       ('S1007', 'Grace', 'Female', 'password404', '456456456', 1, 0),
       ('S1008', 'Hank', 'Male', 'password505', '567567567', 0, 0),
       ('S1009', 'Ivy', 'Female', 'password606', '678678678', 1, 0),
       ('S1010', 'Jack', 'Male', 'password707', '789789789', 1, 0);

-- 插入学生与房间的关系数据（学生入住的房间）
INSERT INTO student_rooms (studentID, roomID)
VALUES ('S1001', 1), -- Alice 在 Building A 的 101 房间
       ('S1002', 1), -- Bob 在 Building A 的 101 房间
       ('S1003', 2), -- Charlie 在 Building A 的 102 房间
       ('S1004', 2), -- David 在 Building A 的 102 房间
       ('S1005', 3), -- Eve 在 Building B 的 201 房间
       ('S1006', 4), -- Frank 在 Building B 的 202 房间
       ('S1007', 5), -- Grace 在 Building C 的 301 房间
       ('S1008', 6), -- Hank 在 Building C 的 302 房间
       ('S1009', 7), -- Ivy 在 Building D 的 401 房间
       ('S1010', 8); -- Jack 在 Building D 的 402 房间
