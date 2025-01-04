create table users
(
    userID      TEXT
        primary key,
    name        TEXT not null,
    gender      TEXT not null,
    password    TEXT not null,
    contactInfo TEXT,
    isCheckedIn INTEGER default 0,
    isAdmin     INTEGER default 0
);

INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('20231001', '张三', '男', 'password123', '13288888855', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('20231002', '李四', '女', 'password456', '13099999999', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('20231003', '王五', '男', 'password789', '13099999940', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('20231004', '赵六', '女', 'password101', '13099999935', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('1', '管理员', '男', '1', '13288888888', 1, 1);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('2024', '王中锤', '男', '123456', '13288888889', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('2025', '苏悦', '女', '2025', '13288888810', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('2026', '赵不尤', '男', '2026', '1', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('2027', '甘亮', '男', '2027', '123', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('2028', '赵瓣儿', '女', '2028', '123', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('2029', '王大锤', '男', '2029', '123', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('2030', '王小锤', '男', '123456', '123', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('2031', '顾震', '男', '123456', '123', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('1000', '万福', '男', '123456', '1', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('1001', '赵墨儿', '男', '123456', '1', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('1002', '赵离', '男', '1', '1', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('T1', '张择端', '男', 'T1', '1', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('T2', '宋齐愈', '男', 'T2', '1', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('t1', '姚禾', '男', 't1', '2', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('t2', '狄伦', '男', 't2', '123', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('222', '萧逸水', '男', '222', '123', 1, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('1234567', '栾回', '男', '234567', '1235567', 0, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('admin', '管理员2', '女', 'p@ssw0rd', '1234567', 1, 1);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('2024123101', '测试1', '男', '123456', '1234667788', 0, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('2024123102', '测试2', '女', '123102', '1234567890', 0, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('0002', '测试4', '男', '12345', '123456789', 0, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('0102', 'test1', '男', '0102', '123456', 0, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('0103', 'test2', '女', '0103', '123456', 0, 0);
INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) VALUES ('123456789', 'NAME', '女', '123456', '235', 1, 0);
