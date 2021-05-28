-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Read crime scene reports on July 28, 2020 from Chamberlin Street and interviews
SELECT description FROM crime_scene_reports WHERE day = "28" AND month = "7" AND year = "2020" AND street = "Chamberlin Street";
SELECT name, transcript FROM interviews WHERE day = "28" AND month = "7" AND year = "2020";


-- //SOLUTION//


-- Print suspect thief names
SELECT * FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit")
AND account_number IN
(SELECT account_number FROM atm_transactions WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street" GROUP BY account_number)
AND phone_number IN
(SELECT caller FROM phone_calls WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60");
-- results 2 persons
-- id | name | phone_number | passport_number | license_plate | account_number | person_id | creation_year
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X | 49610011 | 686048 | 2010
-- 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE | 26013199 | 514354 | 2012


-- Check suspect accopmplice name
SELECT * FROM people
WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60" AND caller IN
    (SELECT phone_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
    WHERE license_plate IN
    (SELECT license_plate FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit")
    AND account_number IN
    (SELECT account_number FROM atm_transactions WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street" GROUP BY account_number)
    AND phone_number IN
    (SELECT caller FROM phone_calls WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60"))
);
-- results 2 persons
-- id | name | phone_number | passport_number | license_plate
-- 847116 | Philip | (725) 555-3243 | 3391710505 | GW362R6
-- 864400 | Berthold | (375) 555-8161 |  | 4V16VO0


-- Print ESCAPED TO city from Fiftyville airport
SELECT * FROM airports WHERE id IN (
SELECT destination_airport_id FROM flights WHERE year = "2020" AND month = "7" AND day = "29" AND hour < "12" AND origin_airport_id = "8"
AND id IN (SELECT flight_id FROM passengers WHERE passport_number IN
(SELECT passport_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
    WHERE license_plate IN
    (SELECT license_plate FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit")
    AND account_number IN
    (SELECT account_number FROM atm_transactions WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street" GROUP BY account_number)
    AND phone_number IN
    (SELECT caller FROM phone_calls WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60"))
));
-- only one flight is on July, 29 morning
-- Escaped city is London


-- Check our suspect person with flights
SELECT * FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE year = "2020" AND month = "7" AND day = "29" AND hour < "12" AND origin_airport_id = "8"
AND id IN (SELECT flight_id FROM passengers WHERE passport_number IN
(SELECT passport_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
    WHERE license_plate IN
    (SELECT license_plate FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit")
    AND account_number IN
    (SELECT account_number FROM atm_transactions WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street" GROUP BY account_number)
    AND phone_number IN
    (SELECT caller FROM phone_calls WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60"))
))
AND passport_number IN
(SELECT passport_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
    WHERE license_plate IN
    (SELECT license_plate FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit")
    AND account_number IN
    (SELECT account_number FROM atm_transactions WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street" GROUP BY account_number)
    AND phone_number IN
    (SELECT caller FROM phone_calls WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60"))
;
-- 36 | 5773159633 | 4A
-- Our thief is person with passport number 5773159633


-- //RESULTS//


-- Result single query to find THIEF
SELECT name AS THIEF FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE year = "2020" AND month = "7" AND day = "29" AND hour < "12" AND origin_airport_id = "8"
AND id IN (SELECT flight_id FROM passengers WHERE passport_number IN
(SELECT passport_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
    WHERE license_plate IN
    (SELECT license_plate FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit")
    AND account_number IN
    (SELECT account_number FROM atm_transactions WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street" GROUP BY account_number)
    AND phone_number IN
    (SELECT caller FROM phone_calls WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60"))
))
AND passport_number IN
(SELECT passport_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
    WHERE license_plate IN
    (SELECT license_plate FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit")
    AND account_number IN
    (SELECT account_number FROM atm_transactions WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street" GROUP BY account_number)
    AND phone_number IN
    (SELECT caller FROM phone_calls WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60"))
);


-- Result single query to find ACCOMPLICE
SELECT name AS ACCOMPLICE FROM people
WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60" AND caller IN
(SELECT phone_number FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE year = "2020" AND month = "7" AND day = "29" AND hour < "12" AND origin_airport_id = "8"
AND id IN (SELECT flight_id FROM passengers WHERE passport_number IN
(SELECT passport_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
    WHERE license_plate IN
    (SELECT license_plate FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit")
    AND account_number IN
    (SELECT account_number FROM atm_transactions WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street" GROUP BY account_number)
    AND phone_number IN
    (SELECT caller FROM phone_calls WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60"))
))
AND passport_number IN
(SELECT passport_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
    WHERE license_plate IN
    (SELECT license_plate FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit")
    AND account_number IN
    (SELECT account_number FROM atm_transactions WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street" GROUP BY account_number)
    AND phone_number IN
    (SELECT caller FROM phone_calls WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60"))
)));


-- Result single query to find ESCAPE TO city
SELECT city AS ESCAPE_TO FROM airports WHERE id IN (
SELECT destination_airport_id FROM flights WHERE year = "2020" AND month = "7" AND day = "29" AND hour < "12" AND origin_airport_id = "8"
AND id IN (SELECT flight_id FROM passengers WHERE passport_number IN
(SELECT passport_number FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE year = "2020" AND month = "7" AND day = "29" AND hour < "12" AND origin_airport_id = "8"
AND id IN (SELECT flight_id FROM passengers WHERE passport_number IN
(SELECT passport_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
    WHERE license_plate IN
    (SELECT license_plate FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit")
    AND account_number IN
    (SELECT account_number FROM atm_transactions WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street" GROUP BY account_number)
    AND phone_number IN
    (SELECT caller FROM phone_calls WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60"))
))
AND passport_number IN
(SELECT passport_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
    WHERE license_plate IN
    (SELECT license_plate FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit")
    AND account_number IN
    (SELECT account_number FROM atm_transactions WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street" GROUP BY account_number)
    AND phone_number IN
    (SELECT caller FROM phone_calls WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60"))
))));