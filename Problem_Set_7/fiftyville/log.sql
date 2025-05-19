-- Keep a log of any SQL queries you execute as you solve the mystery.

-- The theft took place on July 28, 2024
-- It took place on Humphrey Street
-- Authorities believe that the thief took a flight out of town with the help of an accomplice

-- 1. Check crime_scene_reports
SELECT description FROM crime_scene_reports
    WHERE year = 2024
    AND month = 7
    AND day = 28
    AND street = 'Humphrey Street';
-- Time: 10:15am
-- Place: Humphrey Street bakery
-- Interview: 'bakery'

-- 2. Check interviews
SELECT name, transcript FROM interviews
    WHERE year = 2024
    AND month = 7
    AND day = 28
    AND transcript LIKE '%bakery%';
-- Ruth: Within 10 minutes, the thief get into a car and drive away (security footage from the bakery parking lot)
-- Eugene: ATM on Leggett Street in the morning, the thief withdrew some money (ATM)
-- Raymond: During leaving, call accomplice for less then 1 minute take the earliest flight the next day (phone call)

-- 3. Check atm_transactions
SELECT account_number, transaction_type, amount FROM atm_transactions
    WHERE year = 2024
    AND month = 7
    AND day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw';

-- 4. Check bank_account with account_number in 3
SELECT person_id, creation_year FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
            WHERE year = 2024
            AND month = 7
            AND day = 28
            AND atm_location = 'Leggett Street'
            AND transaction_type = 'withdraw'
    );

-- 5. Check people and combine with 4
SELECT name, phone_number, passport_number, license_plate FROM people
    WHERE id IN (
        SELECT person_id FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number FROM atm_transactions
                    WHERE year = 2024
                    AND month = 7
                    AND day = 28
                    AND atm_location = 'Leggett Street'
                    AND transaction_type = 'withdraw'
            )
    );
-- Shrink down the scope to eight people

-- 6. Check bakery_security_logs
SELECT minute, activity, license_plate FROM bakery_security_logs
    WHERE year = 2024
    AND month = 7
    AND day = 28
    AND hour = 10
    AND activity = 'exit';
-- 9 different license plates

-- 7. Combine 5 and 6
SELECT name, phone_number, passport_number, license_plate FROM people
    WHERE id IN (
        SELECT person_id FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number FROM atm_transactions
                    WHERE year = 2024
                    AND month = 7
                    AND day = 28
                    AND atm_location = 'Leggett Street'
                    AND transaction_type = 'withdraw'
            )
    )
    AND license_plate IN (
        SELECT license_plate FROM bakery_security_logs
            WHERE year = 2024
            AND month = 7
            AND day = 28
            AND hour = 10
            AND activity = 'exit'
    );
-- Narrow down to 5 suspects

-- 8. Check phone_calls
SELECT caller, receiver, duration FROM phone_calls
    WHERE year = 2024
    AND month = 7
    AND day = 28
    AND duration <= 60;

-- 9. Combine 7 and 8
SELECT name, phone_number, passport_number, license_plate FROM people
    WHERE id IN (
        SELECT person_id FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number FROM atm_transactions
                    WHERE year = 2024
                    AND month = 7
                    AND day = 28
                    AND atm_location = 'Leggett Street'
                    AND transaction_type = 'withdraw'
            )
    )
    AND license_plate IN (
        SELECT license_plate FROM bakery_security_logs
            WHERE year = 2024
            AND month = 7
            AND day = 28
            AND hour = 10
            AND activity = 'exit'
    )
    AND phone_number IN (
        SELECT caller FROM phone_calls
            WHERE year = 2024
            AND month = 7
            AND day = 28
            AND duration <= 60
    );
-- Narrow down to three suspects

-- 10. Check flights
SELECT id, origin_airport_id, destination_airport_id, MIN(hour), minute FROM flights
    WHERE year = 2024
    AND month = 7
    AND day = 29;
-- Confirm the earliest flight_id is 36

-- 11. Find out the destination of the flight
SELECT city, MIN(hour) FROM airports
    JOIN flights ON airports.id = flights.destination_airport_id
    WHERE year = 2024
    AND month = 7
    AND day = 29;
-- Confirm the destination is New York City

-- 12. Check passengers
SELECT name FROM passengers
    JOIN people ON passengers.passport_number = people.passport_number
    WHERE passengers.passport_number IN (
        SELECT passport_number FROM people
            WHERE id IN (
                SELECT person_id FROM bank_accounts
                    WHERE account_number IN (
                        SELECT account_number FROM atm_transactions
                            WHERE year = 2024
                            AND month = 7
                            AND day = 28
                            AND atm_location = 'Leggett Street'
                            AND transaction_type = 'withdraw'
                    )
            )
            AND license_plate IN (
                SELECT license_plate FROM bakery_security_logs
                    WHERE year = 2024
                    AND month = 7
                    AND day = 28
                    AND hour = 10
                    AND activity = 'exit'
            )
            AND phone_number IN (
                SELECT caller FROM phone_calls
                    WHERE year = 2024
                    AND month = 7
                    AND day = 28
                    AND duration <= 60
            )
    )
    AND flight_id = 36;
-- The two suspects left are Bruce and Taylor

-- 13. Combine 8 and 12
-- We know that Bruce is the thief

-- 14. Find out the accomplice
SELECT name FROM people WHERE phone_number = '(375) 555-8161';
-- The accomplice is Robin
