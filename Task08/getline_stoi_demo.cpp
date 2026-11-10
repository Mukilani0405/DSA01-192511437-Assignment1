#include <iostream>
#include <string>
using namespace std;
int main()
{
    string input;
    int value;
    cout << "Enter a number: ";
    getline(cin, input);
    try
    {
        size_t position;
        value = stoi(input, &position);
        if (position != input.find_last_not_of(" \t") + 1)
        {
            throw invalid_argument("Extra characters");
        }
        cout << "Valid number: " << value << '\n';
    }
    catch (const exception&)
    {
        cout << "Invalid input! Please enter a valid integer.\n";
    }
    return 0;
}
