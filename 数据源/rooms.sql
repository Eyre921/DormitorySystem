create table rooms
(
    roomID        INTEGER
        primary key autoincrement,
    dormitoryID   INTEGER not null
        references dormitories,
    roomNumber    TEXT    not null,
    capacity      INTEGER not null,
    occupied      INTEGER default 0,
    repair_status TEXT    default '正常'
);

INSERT INTO rooms (roomID, dormitoryID, roomNumber, capacity, occupied, repair_status) VALUES (1, 1, '101', 4, 4, '正常');
INSERT INTO rooms (roomID, dormitoryID, roomNumber, capacity, occupied, repair_status) VALUES (2, 1, '102', 4, 2, '正常');
INSERT INTO rooms (roomID, dormitoryID, roomNumber, capacity, occupied, repair_status) VALUES (3, 2, '201', 4, 2, '正常');
INSERT INTO rooms (roomID, dormitoryID, roomNumber, capacity, occupied, repair_status) VALUES (4, 2, '202', 4, 1, '正常');
INSERT INTO rooms (roomID, dormitoryID, roomNumber, capacity, occupied, repair_status) VALUES (5, 3, '301', 4, 3, '正常');
INSERT INTO rooms (roomID, dormitoryID, roomNumber, capacity, occupied, repair_status) VALUES (6, 3, '302', 4, 4, '正常');
INSERT INTO rooms (roomID, dormitoryID, roomNumber, capacity, occupied, repair_status) VALUES (9, 5, 'N1', 5, 4, '正常');
INSERT INTO rooms (roomID, dormitoryID, roomNumber, capacity, occupied, repair_status) VALUES (16, 8, 'N1', 3, 0, '正常');
INSERT INTO rooms (roomID, dormitoryID, roomNumber, capacity, occupied, repair_status) VALUES (17, 8, 'N2', 3, 0, '正常');
