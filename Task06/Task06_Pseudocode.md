# Task 06 – Fare Computation Pseudocode

## Aim
To design the decision-making and looping logic for calculating metro fares and processing a day's journeys.

## Algorithm

**Input:**
- Passenger's zone
- Peak-hour status
- Smart-card balance
- Journey details

**Output:**
- Calculated fare
- Journey approval or denial
- Remaining card balance

## Pseudocode

```text
BEGIN

    SET BASE_FARE[0] = 1000
    SET BASE_FARE[1] = 2000
    SET BASE_FARE[2] = 3000

    SET PEAK_SURCHARGE_PERCENT = 20
    SET MINIMUM_BALANCE = 5000

    SET balance = 10000

    FOR each journey in journey_list

        READ journey zone
        READ peak-hour status

        SET baseFare = 0

        SWITCH journey zone

            CASE Inner:
                SET baseFare = BASE_FARE[0]
                BREAK

            CASE Middle:
                SET baseFare = BASE_FARE[1]
                BREAK

            CASE Outer:
                SET baseFare = BASE_FARE[2]
                BREAK

            DEFAULT:
                DISPLAY "Invalid zone"
                CONTINUE

        END SWITCH

        IF journey is during peak hour THEN
            SET fare = baseFare +
                       (baseFare * PEAK_SURCHARGE_PERCENT / 100)
        ELSE
            SET fare = baseFare
        END IF

        IF balance - fare >= MINIMUM_BALANCE THEN

            SET balance = balance - fare

            DISPLAY calculated fare
            DISPLAY remaining balance

        ELSE

            DISPLAY "Denied (low balance)"

        END IF

    END FOR

END
```

## Explanation

1. The base fare is selected using a switch statement according to the journey zone.
2. A 20% surcharge is added during peak hours.
3. The minimum remaining card balance must be ₹50.
4. The for loop processes each journey in the list.
5. The continue statement skips an invalid journey.
6. The break statement prevents execution from falling into another switch case.

## Conclusion

The pseudocode provides a structured approach to calculating fares, checking card balances and processing multiple metro journeys before implementing the logic in C++.