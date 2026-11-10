#include <iostream>
using namespace std;
class SmartCard
{
private:
    long long balance;
    static constexpr long long MIN_BALANCE = 5000;
public:
    SmartCard(long long initialBalance)
    {
        balance = initialBalance;
    }
    // Check whether the journey is allowed
    bool canTravel(long long fare) const
    {
        return fare >= 0 && balance - fare >= MIN_BALANCE;
    }
    // Deduct fare only when the journey is allowed
    bool deduct(long long fare)
    {
        if (canTravel(fare))
        {
            balance -= fare;
            return true;
        }
        return false;
    }
    // Return the current balance
    long long getBalance() const
    {
        return balance;
    }
};
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
        fare += fare * 20 / 100;
    return fare;
}
int main()
{
    SmartCard card(10000);
    int zones[] = {1, 3, 2};
    bool peakHours[] = {false, true, false};
    for (int i = 0; i < 3; i++)
    {
        long long fare = calculateFare(zones[i], peakHours[i]);
        if (card.deduct(fare))
        {
            cout << "Fare Rs " << fare / 100 << "."
                 << (fare % 100 < 10 ? "0" : "")
                 << fare % 100;
        }
        else
        {
            cout << "Denied (low balance)";
        }
        cout << " balance Rs " << card.getBalance() / 100 << endl;
    }
    return 0;
}
