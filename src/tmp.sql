SELECT d.name   AS 宿舍楼名称,
       -- 统计当前月已入住的学生人数，确保每个学生只计算一次
       COUNT(DISTINCT CASE
                          WHEN strftime('%Y-%m', co.eventTime) = strftime('%Y-%m', 'now')
                              AND co.recordType = '入住'
                              THEN co.studentID
           END) AS 当前月已入住人数,
       -- 通过子查询单独计算宿舍楼的总房间容量，避免因JOIN导致的重复计算
       rc.总房间容量,
       -- 计算入住率：已入住人数 / 总房间容量，并保留两位小数
       ROUND(
               COUNT(DISTINCT CASE
                                  WHEN strftime('%Y-%m', co.eventTime) = strftime('%Y-%m', 'now')
                                      AND co.recordType = '入住'
                                      THEN co.studentID
                   END) * 1.0 / rc.总房间容量,
               2
       )        AS 入住率
FROM dormitories d
         -- 子查询：计算每个宿舍楼的总房间容量
         LEFT JOIN (SELECT dormitoryID,
                           SUM(capacity) AS 总房间容量
                    FROM rooms
                    GROUP BY dormitoryID) rc ON d.dormitoryID = rc.dormitoryID
    -- 连接 rooms 和 check_in_out_records 表，用于统计入住人数
         LEFT JOIN rooms r ON d.dormitoryID = r.dormitoryID
         LEFT JOIN check_in_out_records co ON r.roomID = co.roomID
GROUP BY d.dormitoryID; -- 按宿舍楼分组，确保宿舍楼数据汇总