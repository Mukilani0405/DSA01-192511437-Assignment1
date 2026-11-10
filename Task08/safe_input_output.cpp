#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;
// Read an integer safely
int readInteger(string message)
{
    int value;
    while (true)
    {
        cout << message;
        cin >> value;
        if (cin.fail())
        {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}
// Calculate fare based on zone and peak hour
long long calculateFare(int zone, int hour)
{
    long long fare;
    if (zone == 1)
        fare = 1000;
    else if (zone == 2)
        fare = 2000;
    else if (zone == 3)
        fare = 3000;
    else
        return -1;
    bool peak = (hour >= 8 && hour < 10) ||
                (hour >= 17 && hour < 20);
    if (peak)
        fare += fare * 20 / 100;
    return fare;
}
int main()
{
    cout << "===== METRO SMART CARD GATE =====\n";
    int zone = readInteger("Enter zone (1-Inner, 2-Middle, 3-Outer): ");
    int hour = readInteger("Enter journey hour (0-23): ");
    int balance = readInteger("Enter card balance in rupees: ");
    if (zone < 1 || zone > 3 || hour < 0 ||
        hour > 23 || balance < 0)
    {
        cout << "\nInvalid journey details!\n";
        return 0;
    }
    long long fare = calculateFare(zone, hour);
    long long balancePaise = static_cast<long long>(balance) * 100;
    cout << "\n========== JOURNEY REPORT ==========\n";
    cout << left << setw(22) << "Zone: ";
    if (zone == 1)
        cout << "Inner\n";
    else if (zone == 2)
        cout << "Middle\n";
    else
        cout << "Outer\n";
    cout << left << setw(22) << "Journey hour: " << hour << ":00\n";
    cout << fixed << setprecision(2);
    if (balancePaise - fare >= 5000)
    {
        balancePaise -= fare;
        cout << left << setw(22) << "Fare: "
             << "Rs " << static_cast<double>(fare) / 100 << '\n';
        cout << left << setw(22) << "Status: " << "Approved\n";
    }
    else
    {
        cout << left << setw(22) << "Fare: "
             << "Rs " << static_cast<double>(fare) / 100 << '\n';
        cout << left << setw(22) << "Status: " << "Denied (low balance)\n";
    }
    cout << left << setw(22) << "Remaining balance: "
         << "Rs " << static_cast<double>(balancePaise) / 100 << '\n';
    cout << "====================================\n";
    return 0;
}
