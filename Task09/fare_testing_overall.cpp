#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
const int BASE_FARES[] = {1000, 2000, 3000};
const int PEAK_SURCHARGE = 20;
bool isPeakHour(int hour)
{
    return (hour >= 8 && hour < 10) ||
           (hour >= 17 && hour < 20);
}
long long calculateFare(int zone, int hour)
{
    if (zone < 1 || zone > 3 || hour < 0 || hour > 23)
        return -1;

    long long fare = BASE_FARES[zone - 1];

    if (isPeakHour(hour))
        fare += fare * PEAK_SURCHARGE / 100;
    return fare;
}

bool canTravel(long long balance, long long fare)
{
    const long long MINIMUM_BALANCE = 5000;

    return balance >= 0 &&
           fare >= 0 &&
           balance - fare >= MINIMUM_BALANCE;
}

bool isValidRecharge(long long amount)
{
    return amount >= 0;
}

bool isValidHourInput(const string& input)
{
    if (input.empty())
        return false;

    for (char ch : input)
    {
        if (ch < '0' || ch > '9')
            return false;
    }

    int hour = stoi(input);
    return hour >= 0 && hour <= 23;
}


int main()
{
    cout << "===== METRO FARE TESTING =====\n\n";
    cout << left << setw(10) << "Zone"
         << setw(10) << "Hour"
         << setw(15) << "Fare (Rs)" << '\n';
    cout << "-----------------------------------\n";
    for (int zone = 1; zone <= 3; zone++)
    {
        for (int hour : {7, 9, 10, 17, 20})
        {
            long long fare = calculateFare(zone, hour);
            cout << left << setw(10) << zone
                 << setw(10) << hour
                 << fixed << setprecision(2)
                 << setw(15) << static_cast<double>(fare) / 100
                 << '\n';
        }
    }
    cout << "\n\n===== MINIMUM BALANCE TEST =====\n";

long long balance = 6200;
long long fare = calculateFare(1, 9);
long long remaining = balance - fare;

cout << "Initial Balance: Rs. "
     << balance / 100.0 << '\n';

cout << "Fare: Rs. "
     << fare / 100.0 << '\n';

cout << "Remaining Balance: Rs. "
     << remaining / 100.0 << '\n';

if (canTravel(balance, fare))
    cout << "Result: Travel Allowed\n";
else
    cout << "Result: Travel Denied\n";
    
cout << "\n\n===== INVALID INPUT TESTS =====\n";

long long recharge = -10000;

cout << "Negative Recharge (-Rs. 100): ";

if (isValidRecharge(recharge))
    cout << "Accepted\n";
else
    cout << "Rejected\n";

string invalidHour = "abc";

cout << "Alphabetic Hour Input (abc): ";

if (isValidHourInput(invalidHour))
    cout << "Accepted\n";
else
    cout << "Rejected\n";
    
cout << "\n\n===== FIVE JOURNEY TOTAL =====\n";

int journeyZones[] = {1, 1, 2, 2, 3};
int journeyHours[] = {7, 9, 7, 9, 7};

long long totalFare = 0;

for (int i = 0; i < 5; i++)
{
    long long fare = calculateFare(
        journeyZones[i], journeyHours[i]
    );

    totalFare += fare;

    cout << "Journey " << i + 1
         << ": Rs. " << fare / 100.0 << '\n';
}

cout << "Total Fare: Rs. "
     << totalFare / 100.0 << '\n';


    return 0;
}
