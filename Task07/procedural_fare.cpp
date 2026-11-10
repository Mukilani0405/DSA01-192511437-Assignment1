#include <iostream>
using namespace std;
const long long MIN_BALANCE = 5000;
// Calculate fare based on zone and peak hour
long long calculateFare(int zone, bool peak)
{
    long long fare = 0;
    if (zone == 1)
        fare = 1000;
    else if (zone == 2)
        fare = 2000;
    else if (zone == 3)
        fare = 3000;
    else
        return -1;
    if (peak)
        fare = fare + (fare * 20 / 100);
    return fare;
}
// Check whether the journey is allowed
bool canTravel(long long balance, long long fare)
{
    return fare >= 0 && balance - fare >= MIN_BALANCE;
}
// Deduct fare from the balance
void deductFare(long long &balance, long long fare)
{
    if (canTravel(balance, fare))
        balance = balance - fare;
}
int main()
{
    long long balance = 10000;
    int zones[] = {1, 3, 2};
    bool peakHours[] = {false, true, false};
    for (int i = 0; i < 3; i++)
    {
        long long fare = calculateFare(zones[i], peakHours[i]);
        if (canTravel(balance, fare))
        {
            deductFare(balance, fare);
            cout << "Fare Rs " << fare / 100 << "."
                 << (fare % 100 < 10 ? "0" : "")
                 << fare % 100;
        }
        else
        {
            cout << "Denied (low balance)";
        }
        cout << " balance Rs " << balance / 100 << endl;
    }
    return 0;
}
