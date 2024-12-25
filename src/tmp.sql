SELECT u.userID                        AS 学号,     -- 学生学号
       u.name                          AS 姓名,     -- 学生姓名
       u.gender                        AS 性别,     -- 学生性别
       COALESCE(u.password, 'NULL')    AS 密码,     -- 学生密码，若为空则显示NULL
       COALESCE(u.contactInfo, 'NULL') AS 联系方式, -- 学生联系方式，若为空则显示NULL
       COALESCE(d.name, 'NULL')        AS 宿舍楼,   -- 宿舍楼名称，若为空则显示NULL
       COALESCE(r.roomNumber, 'NULL')  AS 房间号    -- 房间号，若为空则显示NULL
FROM users u
         LEFT JOIN
     student_rooms sr ON u.userID = sr.studentID -- 连接学生表与学生房间关系表（使用 LEFT JOIN 保证即使学生未入住也能查询到）
         LEFT JOIN
     rooms r ON sr.roomID = r.roomID -- 连接房间表
         LEFT JOIN
     dormitories d ON r.dormitoryID = d.dormitoryID -- 连接宿舍楼表
WHERE u.name = '1'; -- 查询指定姓名的学生
