create table student_rooms
(
    studentID TEXT    not null
        references users,
    roomID    INTEGER not null
        references rooms,
    primary key (studentID, roomID)
);

INSERT INTO student_rooms (studentID, roomID) VALUES ('20231001', 1);
INSERT INTO student_rooms (studentID, roomID) VALUES ('20231002', 4);
INSERT INTO student_rooms (studentID, roomID) VALUES ('20231004', 6);
INSERT INTO student_rooms (studentID, roomID) VALUES ('2026', 6);
INSERT INTO student_rooms (studentID, roomID) VALUES ('2028', 3);
INSERT INTO student_rooms (studentID, roomID) VALUES ('2029', 2);
INSERT INTO student_rooms (studentID, roomID) VALUES ('2030', 2);
INSERT INTO student_rooms (studentID, roomID) VALUES ('2031', 6);
INSERT INTO student_rooms (studentID, roomID) VALUES ('1002', 1);
INSERT INTO student_rooms (studentID, roomID) VALUES ('1001', 1);
INSERT INTO student_rooms (studentID, roomID) VALUES ('T1', 9);
INSERT INTO student_rooms (studentID, roomID) VALUES ('T2', 9);
INSERT INTO student_rooms (studentID, roomID) VALUES ('t1', 5);
INSERT INTO student_rooms (studentID, roomID) VALUES ('t2', 5);
INSERT INTO student_rooms (studentID, roomID) VALUES ('2024', 9);
INSERT INTO student_rooms (studentID, roomID) VALUES ('2025', 3);
INSERT INTO student_rooms (studentID, roomID) VALUES ('2027', 6);
INSERT INTO student_rooms (studentID, roomID) VALUES ('20231003', 9);
INSERT INTO student_rooms (studentID, roomID) VALUES ('1000', 1);
INSERT INTO student_rooms (studentID, roomID) VALUES ('222', 5);
INSERT INTO student_rooms (studentID, roomID) VALUES ('123456789', 17);
