SELECT r.roomID, r.roomNumber, r.capacity, r.occupied
FROM rooms r
WHERE r.dormitoryID = '5'