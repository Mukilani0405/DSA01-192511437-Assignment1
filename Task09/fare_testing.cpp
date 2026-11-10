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
    return 0;
}
