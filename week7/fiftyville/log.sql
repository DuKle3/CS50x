-- Keep a log of any SQL queries you execute as you solve the mystery.
-- info : theft took place on July 28, 2021 and that it took place on Humphrey Street.
-- take a look of TABLE structure
.schema

-- crime_scene_reports
-- interviews
-- atm_transactions
-- bank_accounts
-- flights
-- passengers
-- phone_calls
-- people
-- bakery_security_logs

-- search the crime_scene_reports
SELECT *
  FROM crime_scene_reports
 WHERE street = 'Humphrey Street'
   AND year = 2021
   AND month = 7
   AND day = 28;

-- 10:15am,
-- three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- search the interview
SELECT *
  FROM interviews
 WHERE transcript LIKE '%bakery%'
   AND year = 2021
   AND month = 7
   AND day = 28;

-- 1. bakery parking lot, cars tha left the parking lot in that time frame (Sometime within ten minutes of the theft, drive away)
-- 2. Earlier this morning, on Leggett Street, thief was withdrawing money (ATM)
-- 3. phone call (less a minute) when leaving bakery, asked accomplice to take the earliest flight out of Fiftyville tomorrow, purchase the flight ticket.

-- search the bakery_security_logs
-- about 10:15am, focus on
SELECT *
  FROM bakery_security_logs
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND hour = 10
   AND minute > 15
   AND minute < 25;
/*+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
+-----+------+-------+-----+------+--------+----------+---------------+*/

-- search the ATM
SELECT *
  FROM atm_transactions
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND atm_location = 'Leggett Street';

/*
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
*/

-- search the name in these transaction
SELECT people.*
  FROM people, bank_accounts, atm_transactions
 WHERE people.id = bank_accounts.person_id
   AND bank_accounts.account_number = atm_transactions.account_number
   AND bank_accounts.account_number IN
        (SELECT account_number
           FROM atm_transactions
          WHERE year = 2021
            AND month = 7
            AND day = 28
            AND atm_location = 'Leggett Street')
GROUP BY people.name;
/*
+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
| 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| 948985 | Kaelyn  | (098) 555-1164 | 8304650265      | I449449       |
| 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
+--------+---------+----------------+-----------------+---------------+
*/

-- 3. phone call when leaving bakery, asked accomplice to take the earliest flight out of Fiftyville tomorrow, purchase the flight ticket.
-- search the phone_calls
-- search the flight
SELECT *
  FROM phone_calls
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND duration < 70;
/*+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
| 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
| 234 | (609) 555-5876 | (389) 555-5198 | 2021 | 7     | 28  | 60       |
| 240 | (636) 555-4198 | (670) 555-8598 | 2021 | 7     | 28  | 69       |
| 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
| 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
| 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
| 260 | (669) 555-6918 | (971) 555-6468 | 2021 | 7     | 28  | 67       |
| 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
| 271 | (751) 555-6567 | (594) 555-6254 | 2021 | 7     | 28  | 61       |
| 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
| 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
+-----+----------------+----------------+------+-------+-----+----------+
*/

-- combine the atm_withdrawer and these phone-call number
SELECT people.*
  FROM people, bank_accounts, atm_transactions, phone_calls
 WHERE people.id = bank_accounts.person_id
   AND bank_accounts.account_number = atm_transactions.account_number
   AND people.phone_number = phone_calls.caller
   AND bank_accounts.account_number IN
        (SELECT account_number
           FROM atm_transactions
          WHERE year = 2021
            AND month = 7
            AND day = 28
            AND atm_location = 'Leggett Street')
   AND people.phone_number IN
        (SELECT caller
           FROM phone_calls
          WHERE year = 2021
            AND month = 7
            AND day = 28
            AND duration < 70)
GROUP BY people.name;

-- These people had withdraw money and phone_call
/*+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
+--------+---------+----------------+-----------------+---------------+
*/

-- search the flight
SELECT *
  FROM flights
 WHERE year = 2021
   AND month = 7
   AND day = 29
   AND hour < 12
   AND origin_airport_id =
        (SELECT id
           FROM airports
          WHERE city = 'Fiftyville');
/*+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
| 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     |
+----+-------------------+------------------------+------+-------+-----+------+--------+*/

SELECT people.*
  FROM people, bank_accounts, atm_transactions, phone_calls, passengers, flights, bakery_security_logs
 WHERE people.id = bank_accounts.person_id
   AND bank_accounts.account_number = atm_transactions.account_number
   AND people.phone_number = phone_calls.caller
   AND people.passport_number = passengers.passport_number
   AND people.license_plate = bakery_security_logs.license_plate
   AND passengers.flight_id = flights.id
   AND bank_accounts.account_number IN
        (SELECT account_number
           FROM atm_transactions
          WHERE year = 2021
            AND month = 7
            AND day = 28
            AND atm_location = 'Leggett Street')
   AND people.phone_number IN
        (SELECT caller
           FROM phone_calls
          WHERE year = 2021
            AND month = 7
            AND day = 28
            AND duration < 70)
   AND flights.id IN
        (SELECT id
           FROM flights
          WHERE year = 2021
            AND month = 7
            AND day = 29
            AND hour < 12
            AND origin_airport_id =
                (SELECT id
                   FROM airports
                  WHERE city = 'Fiftyville'))
   AND people.license_plate IN
        (SELECT license_plate
           FROM bakery_security_logs
          WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute > 15
            AND minute < 25)
GROUP BY people.name;

/*+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+-------+----------------+-----------------+---------------+*/

-- Thief is Bruce
-- Now, search the accomplice

SELECT people.name
  FROM people, phone_calls
 WHERE people.phone_number = phone_calls.receiver
   AND phone_calls.caller = '(367) 555-5533'
   AND year = 2021
   AND month = 7
   AND day = 28
   AND duration < 60;

/*+-------+
| name  |
+-------+
| Robin |
+-------+*/

-- Robin is accomplice

-- Now search the city where they escaped to
SELECT city
  FROM airports, flights, passengers, people
 WHERE airports.id = flights.destination_airport_id
   AND flights.id = passengers.flight_id
   AND passengers.passport_number = people.passport_number
   AND people.name = 'Bruce';

/*+---------------+
|     city      |
+---------------+
| New York City |
+---------------+*/