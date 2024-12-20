-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 查询犯罪现场报告
SELECT description
FROM crime_scene_reports
WHERE year = 2023
AND month = 7
AND day = 28
AND street = 'Humphrey Street';

-- 查询结果
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time
-- each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No known witnesses.
-- 采访了三个人，都提到面包店，时间16：36

-- 查询采访记录
SELECT name, transcript
FROM interviews
WHERE year = 2023
AND month = 7
AND day = 28
AND transcript LIKE '%bakery%';

-- Ruth
--      Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--      If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- Eugene
--      I don't know the thief's name, but it was someone I recognized.
--      Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- Raymond
--      As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--      In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--      The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- Ruth：
--      在偷窃发生后的十分钟内，我看到小偷在面包店停车场上了一辆车并开走了。
--      如果你有面包店停车场的监控录像，可能需要查看在这个时间段离开停车场的车辆。
-- Eugene：
--      我不知道小偷的名字，但我认得他。
--      今天早上，在我到达艾玛的面包店之前，我走过了莱吉特街的ATM机，看到小偷在那里取钱。
-- Raymond：
--      小偷离开面包店时，打电话给某人，两人通话时间不到一分钟。
--      在通话中，我听到小偷说他们计划明天乘坐最早的航班离开菲夫提镇。 —— 小偷还让电话那头的人帮忙买机票。

-- 至少两个人


--      分析：16：36-16:46 停车场记录，安保日志
SELECT activity, license_plate, minute
FROM bakery_security_logs
WHERE year = 2023
AND month = 7
AND day = 28
AND hour = 16
AND minute >= 36
AND minute <= 50;

-- 查询结果
+----------+---------------+--------+
| activity | license_plate | minute |
+----------+---------------+--------+
| exit     | 4468KVT       | 38     |
| exit     | 207W38T       | 42     |
| exit     | C194752       | 47     |
+----------+---------------+--------+

-- 进一步排查4468KVT、207W38T车主，对C194752持怀疑态度
SELECT name, phone_number, passport_number, license_plate
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND hour = 16
    AND minute >= 36
    AND minute <= 50
    );
-- 查询结果
+-------+----------------+-----------------+---------------+
| name  |  phone_number  | passport_number | license_plate |
+-------+----------------+-----------------+---------------+
| John  | (016) 555-9166 | 8174538026      | 4468KVT       |
| Frank | (356) 555-6641 | 8336437534      | 207W38T       |
+-------+----------------+-----------------+---------------+
-- 得到两名可能目标 John 和 Frank
-- 查询他们的银行账户
SELECT account_number
FROM bank_accounts
WHERE person_id = (
    SELECT id
    FROM people
    WHERE name = 'John'
);
SELECT account_number
FROM bank_accounts
WHERE person_id = (
    SELECT id
    FROM people
    WHERE name = 'Frank'
);
-- John 39774254
-- Frank 62075502


SELECT *
FROM atm_transactions
WHERE year = 2023
AND month = 7
AND day = 28
AND atm_location LIKE '%Leggett%'
AND transaction_type = 'withdraw';
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 | 28500762       | 2023 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2023 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2023 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2023 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2023 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 288 | 25506511       | 2023 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2023 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2023 | 7     | 28  | Leggett Street | withdraw         | 35     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+

SELECT name
FROM people
WHERE ID = (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2023
        AND month = 7
        AND day = 28
        AND atm_location LIKE '%Leggett%'
        AND transaction_type = 'withdraw'
    )
);

--      分析：查询通话时间一分钟内的电话
SELECT caller, receiver
FROM phone_calls
WHERE year = 2023
AND month = 7
AND day = 28
AND duration <= 60;

+----------------+----------------+
|     caller     |    receiver    |
+----------------+----------------+
| (130) 555-0289 | (996) 555-8899 |
| (499) 555-9472 | (892) 555-8872 |
| (367) 555-5533 | (375) 555-8161 |
| (609) 555-5876 | (389) 555-5198 |
| (499) 555-9472 | (717) 555-1342 |
| (286) 555-6063 | (676) 555-6554 |
| (770) 555-1861 | (725) 555-3243 |
| (031) 555-6622 | (910) 555-3251 |
| (826) 555-1652 | (066) 555-9701 |
| (338) 555-6650 | (704) 555-2131 |
+----------------+----------------+

--      分析：明天最早的机票
--      查找Frank的护照航班
SELECT flight_id, passport_number
FROM passengers
WHERE passport_number IN ('8336437534','8174538026');

+-----------+
| flight_id |
+-----------+
| 11        |
| 28        |
| 48        |
+-----------+

-- 查找航班ID

SELECT *
FROM flights
WHERE year = 2023
AND month = 7
AND day = 29
AND ID IN (SELECT flight_id
FROM passengers
WHERE passport_number IN ('8336437534','8174538026'));
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 53 | 8                 | 9                      | 2023 | 7     | 29  | 15   | 20     |
+----+-------------------+------------------------+------+-------+-----+------+--------+

SELECT flight_id, passport_number
FROM passengers
WHERE flight_id = 53
AND passport_number IN ('8336437534','8174538026');

+-----------+-----------------+
| flight_id | passport_number |
+-----------+-----------------+
| 53        | 7894166154      |
| 53        | 6034823042      |
| 53        | 4408372428      |
| 53        | 2312901747      |
| 53        | 1151340634      |
| 53        | 8174538026      |
| 53        | 1050247273      |
| 53        | 7834357192      |
+-----------+-----------------+
+-----------+-----------------+
| flight_id | passport_number |
+-----------+-----------------+
| 53        | 8174538026      |
+-----------+-----------------+
-- John？

SELECT *
FROM airports
WHERE ID IN (8,9);
+----+--------------+-----------------------------+------------+
| id | abbreviation |          full_name          |    city    |
+----+--------------+-----------------------------+------------+
| 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
| 9  | HND          | Tokyo International Airport | Tokyo      |
+----+--------------+-----------------------------+------------+


-- 查查航班上的其他人,
SELECT name, phone_number, passport_number, license_plate
FROM people
WHERE passport_number IN (SELECT passport_number
FROM passengers
WHERE flight_id = 53);
+---------+----------------+-----------------+---------------+
|  name   |  phone_number  | passport_number | license_plate |
+---------+----------------+-----------------+---------------+
| Pamela  | (113) 555-7544 | 1050247273      | 5CIO816       |
| Larry   | (892) 555-8872 | 2312901747      | O268ZZ0       |
| Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
| Melissa | (717) 555-1342 | 7834357192      | NULL          |
| Thomas  | (286) 555-0131 | 6034823042      | WD5M8I6       |
| Steven  | (195) 555-4173 | 1151340634      | 5VFD6G0       |
| John    | (016) 555-9166 | 8174538026      | 4468KVT       |
| Richard | NULL           | 7894166154      | 20Q418R       |
+---------+----------------+-----------------+---------------+

-- 倒查通话记录
SELECT caller, receiver
FROM phone_calls
WHERE year = 2023
AND month = 7
AND day = 28
AND duration <= 60
AND receiver IN
    (SELECT phone_number
    FROM people
    WHERE passport_number IN (SELECT passport_number
    FROM passengers
    WHERE flight_id = 53));
+----------------+----------------+
|     caller     |    receiver    |
+----------------+----------------+
| (499) 555-9472 | (892) 555-8872 |
| (499) 555-9472 | (717) 555-1342 |
+----------------+----------------+

-- (499) 555-9472是谁？
SELECT name, phone_number, passport_number, license_plate
FROM people
WHERE phone_number = '(499) 555-9472';
+--------+----------------+-----------------+---------------+
|  name  |  phone_number  | passport_number | license_plate |
+--------+----------------+-----------------+---------------+
| Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
+--------+----------------+-----------------+---------------+
