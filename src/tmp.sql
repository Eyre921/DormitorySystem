SELECT r.roomID, r.roomNumber, r.capacity, r.occupied
FROM rooms r
         JOIN dormitories d ON r.dormitoryID = d.dormitoryID
WHERE d.name = 'Building A'
  AND r.occupied < r.capacity;
