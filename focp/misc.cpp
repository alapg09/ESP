#include <string>
#include <iostream>
#include <limits>
#include "misc.h"
#include "color.h"

using namespace std;

char get_validated_input(const string &prompt, const string &validOptions)
{
    char input;
    while (true)
    {
        cout << GREEN << prompt << RESET;
        cin >> input;

        // validates only single characteredi innputs
        if (cin.fail() || (cin.peek() != '\n' && cin.peek() != EOF))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << GREEN "Invalid input! Please enter a single character." << endl
                 << RESET;
            continue;
        }

        input = tolower(input);

        // Check against valid options
        if (validOptions.find(input) != string::npos) // checks if entered options are among the ones allowed
        {
            return input;
        }

        cout << GREEN << "Invalid input! Please enter one of the following: " << validOptions << endl
             << RESET;
    }
}
