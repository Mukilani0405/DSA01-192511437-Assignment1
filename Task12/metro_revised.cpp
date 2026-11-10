#include <iostream>
#include <string>
using namespace std;

enum class Zone {
    Inner,
    Middle,
    Outer,
    Airport
};

const int BASE_FARES[] = {10, 20, 30, 60};

// Calculate fare based on zone, time and day
int calculateFare(Zone zone, int hour, bool isWeekend) {

    int fare = BASE_FARES[static_cast<int>(zone)];

    // Weekend discount takes priority over peak surcharge
    if (isWeekend) {
        fare = fare * 90 / 100;
    }
    else if ((hour >= 8 && hour < 10) ||
             (hour >= 17 && hour < 20)) {
        fare = fare * 120 / 100;
    }

    return fare;
}
// Monthly pass for two selected zones
class MonthlyPass {
private:
    Zone zone1;
    Zone zone2;
    int daysRemaining;

public:
    MonthlyPass(Zone z1, Zone z2, int days) {
        zone1 = z1;
        zone2 = z2;
        daysRemaining = days;
    }

    bool covers(Zone zone) {
        return daysRemaining > 0 &&
               (zone == zone1 || zone == zone2);
    }

    void showStatus() {
        cout << "Pass validity: " << daysRemaining
             << " days remaining" << endl;
    }
};
// Smart card manages passenger balance and journeys
class SmartCard {
private:
    int balance;

public:
    SmartCard(int initialBalance) {
        balance = initialBalance;
    }

    void processJourney(Zone zone, int hour,
                        bool isWeekend, MonthlyPass* pass) {

        cout << "\nProcessing journey..." << endl;

        // Check monthly pass first
        if (pass != nullptr && pass->covers(zone)) {
            cout << "Monthly pass accepted!" << endl;
            cout << "Journey is FREE." << endl;
            return;
        }

        // Calculate and deduct normal fare
        int fare = calculateFare(zone, hour, isWeekend);

        if (balance - fare >= 50) {
            balance -= fare;
            cout << "Fare deducted: Rs. " << fare << endl;
            cout << "Remaining balance: Rs. "
                 << balance << endl;
        }
        else {
            cout << "Insufficient balance!" << endl;
            cout << "Minimum Rs. 50 must remain." << endl;
        }
    }

    void showBalance() {
        cout << "Card balance: Rs. " << balance << endl;
    }
};

int main() {

    cout << "===== METRO SMART CARD SYSTEM =====" << endl;

    SmartCard card(500);

    // Monthly pass covers Inner and Middle zones
    MonthlyPass activePass(Zone::Inner, Zone::Middle, 30);

    // Expired monthly pass
    MonthlyPass expiredPass(Zone::Inner, Zone::Middle, 0);

    // Test 1: Airport weekday off-peak
    cout << "\nTEST 1: Airport - Weekday Off-Peak" << endl;
    card.processJourney(Zone::Airport, 11, false, nullptr);

    // Test 2: Airport weekday peak
    cout << "\nTEST 2: Airport - Weekday Peak" << endl;
    card.processJourney(Zone::Airport, 9, false, nullptr);

    // Test 3: Airport weekend during peak hours
    cout << "\nTEST 3: Airport - Weekend Peak Hour" << endl;
    card.processJourney(Zone::Airport, 9, true, nullptr);

    // Test 4: Journey covered by monthly pass
    cout << "\nTEST 4: Middle Zone - Valid Monthly Pass" << endl;
    card.processJourney(Zone::Middle, 12, false, &activePass);

    // Test 5: Journey outside the pass zones
    cout << "\nTEST 5: Airport - Outside Pass Zones" << endl;
    card.processJourney(Zone::Airport, 11, false, &activePass);

    // Test 6: Journey with expired pass
    cout << "\nTEST 6: Inner Zone - Expired Monthly Pass" << endl;
    card.processJourney(Zone::Inner, 12, false, &expiredPass);

    cout << "\n===== FINAL CARD STATUS =====" << endl;
    card.showBalance();

    return 0;
}