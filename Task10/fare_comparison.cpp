
#include <iostream>
#include <iomanip>
#include <random>
#include <climits>
using namespace std;

const int BASE_FARES[] = {1000, 2000, 3000};

int main()
{
    int journeyCounts[] = {20000, 500000, 3000000};

    mt19937 generator(42);
    uniform_int_distribution<int> zoneDist(0, 2);
    uniform_int_distribution<int> hourDist(0, 23);

    cout << fixed << setprecision(2);
    cout << "===== EXPECTATION VS EXECUTION =====\n\n";

    cout << left
         << setw(15) << "Journeys"
         << setw(20) << "Integer (paise)"
         << setw(20) << "Double (paise)"
         << setw(18) << "Difference"
         << "Int Status\n";

    for (int count : journeyCounts)
    {
        long long exactTotal = 0;
        double doubleTotal = 0.0;
        float floatTotal = 0.0f;

        mt19937 localGenerator(42);
        uniform_int_distribution<int> zone(0, 2);
        uniform_int_distribution<int> hour(0, 23);

        for (int i = 0; i < count; i++)
        {
            int z = zone(localGenerator);
            int h = hour(localGenerator);

            long long fare = BASE_FARES[z];

            bool peak = (h >= 8 && h < 10) ||
                        (h >= 17 && h < 20);

            if (peak)
                fare += fare * 20 / 100;

            exactTotal += fare;
            doubleTotal += static_cast<double>(fare) / 100.0;
            floatTotal += static_cast<float>(fare) / 100.0f;
        }

        double doublePaise = doubleTotal * 100.0;
        double difference =
            doublePaise - static_cast<double>(exactTotal);

        cout << left
             << setw(15) << count
             << setw(20) << exactTotal
             << setw(20) << fixed << setprecision(0)
             << doublePaise
             << setw(18) << setprecision(2)
             << difference;

        if (exactTotal <= INT_MAX)
            cout << "Fits in int\n";
        else
            cout << "OVERFLOW RISK\n";

        cout << "Float total (Rs): "
             << setprecision(2) << floatTotal << "\n\n";
    }

    cout << "INT_MAX: " << INT_MAX << " paise\n";
    cout << "All totals are calculated using the same fixed seed.\n";

    return 0;
}
