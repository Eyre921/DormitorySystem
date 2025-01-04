create table dormitories
(
    dormitoryID INTEGER
        primary key autoincrement,
    name        TEXT not null
        unique,
    sex         TEXT not null,
    position    TEXT
);

INSERT INTO dormitories (dormitoryID, name, sex, position) VALUES (1, '三区一栋', '男', '三区');
INSERT INTO dormitories (dormitoryID, name, sex, position) VALUES (2, '三区二栋', '女', '三区');
INSERT INTO dormitories (dormitoryID, name, sex, position) VALUES (3, '二区一栋', '男', '二区');
INSERT INTO dormitories (dormitoryID, name, sex, position) VALUES (5, '三区十九栋', '男', '三区');
INSERT INTO dormitories (dormitoryID, name, sex, position) VALUES (8, '二区二栋', '女', '二区');
