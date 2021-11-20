-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM crime_scene_reports;

-----

SELECT * FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28 AND street = 'Chamberlin Street';

-----

SELECT * FROM interviews
WHERE transcript LIKE '%courthouse%' AND year >= 2020 AND month >= 7 AND day >= 28;

-----

SELECT * FROM phone_calls
WHERE duration <= 60 AND year = 2020 AND month = 7 AND day = 28;

-----

SELECT caller, receiver FROM phone_calls
WHERE duration <= 60 AND year = 2020 AND month = 7 AND day = 28;

-----

SELECT license_plate FROM courthouse_security_logs
WHERE minute <= 25 AND minute >= 15 AND year = 2020 AND month = 7 AND day = 28;

-----

SELECT account_number FROM atm_transactions
WHERE atm_location = 'Fifer Street' AND transaction_type = 'withdraw' AND year = 2020 AND month = 7 AND day = 28;

-----

SELECT * FROM flights
WHERE year = 2020 AND month = 7 AND day = 29
ORDER BY hour, minute ASC;

-----

SELECT * FROM passengers
WHERE flight_id = 36;

-----

SELECT DISTINCT people.*

FROM (((people
INNER JOIN passengers ON people.passport_number = passengers.passport_number)
INNER JOIN phone_calls ON people.phone_number = phone_calls.caller)
INNER JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate)

WHERE 

passengers.flight_id = 36 

AND phone_calls.duration <= 60 AND phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28

AND courthouse_security_logs.minute <= 25 AND courthouse_security_logs.minute >= 15 AND courthouse_security_logs.year = 2020 AND courthouse_security_logs.month = 7 AND courthouse_security_logs.day = 28

ORDER BY people.name;

-----

SELECT DISTINCT people.*, phone_calls.receiver

FROM (people
INNER JOIN phone_calls ON people.phone_number = phone_calls.receiver)

WHERE 
phone_calls.duration <= 60 AND phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28
AND phone_calls.caller = '(367) 555-5533'

ORDER BY people.name;
