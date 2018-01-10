#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <math.h>
#include <fstream>

using namespace std;

unsigned long long num_input;

vector<unsigned long long> card_number;
/**
 Prompts user for card number input as a string. String converted into usingned long long vector.
 @param card_number a vector which is filled in reverse
 @param num_input user input
 */
void string_convert(vector<unsigned long long>& card_number, unsigned long long num_input)
{
    cout << "Enter your card number (16 digit max): ";
    
    cin >> num_input;
    
    while(num_input >= 1)
    {
        int temp = (fmod(num_input, 10));
        if (num_input >= 1)
        {
            card_number.push_back(temp);
        }
        else
        {
            card_number.push_back(num_input);
        }
        num_input = num_input / 10;
    }
}
/**
 Uses mod 10 to check the sum of all digits after being doubled. If the sum of an even digit location is greater than 10, take sum of constituent digits.
 @return bool true if check true, false if check false.
 */
bool check_sum()
{
    bool check_sum = false;
    int total;
    int running_total = 0;
    
    for (int i = 0; i < card_number.size(); i++)
    {
        if(i%2 != 0)
        {
            if(card_number[i] *2 >= 10)
            {
                int temp = card_number[i] *2;
                total = (temp / 10) + (temp % 10);
            }
            else
            {
                total = card_number[i] * 2;
            }
        }
        else
        {
            total = card_number[i];
        }
        running_total = running_total + total;
    }
    if((running_total % 10 == 0) && (card_number.size() >= 12 && card_number.size() <=16))
    {
        check_sum = true;
    }
    return check_sum;
}
/**
 Checks beginning card digits to determine card type.
 @return string returns the type of card.
 */
string card_type ()
{
    string type;
    if (card_number[card_number.size() - 1] == 4)
    {
        type = "Visa";
    }
    else if ((card_number[card_number.size() - 1] == 6) && (card_number[card_number.size() - 2] == 0))
    {
        type = "Discover";
    }
    else if ((card_number[card_number.size() - 1] == 5) || (card_number[card_number.size() - 1] == 2))
    {
        type = "Master";
    }
    else if ((card_number[card_number.size() - 1] == 3) && ((card_number[card_number.size() - 2] == 7) || (card_number[card_number.size() - 2] == 4)))
    {
        type = "American Express";
    }
    else
    {
        type = "Uknown";
    }
    return type;
}
/***************** MAIN *****************/
int main ()
{
    int count = 0;

    string_convert(card_number, num_input);
    string type = card_type();
    bool check = check_sum();
    cout << endl;

    if(card_number.size() > 16)
    {
        cout << "You've exceeded the 16 digit maximum." << endl;
    }
    else if (check)
    {
        cout << "Card is: VALID" << endl;
        cout << "Card type: " << type << endl;
    }
    else if (((!check) && (type != "Uknown")) && (card_number.size() >= 12))
    {
        cout << "Card is: INVALID" << endl;
        cout << "Card type: " << type << " (possible fradulent card)" << endl;
    }
    else if ((!check) && (card_number.size() < 16))
    {
        cout << "Card is: INVALID" << endl;
        cout << "Only " << card_number.size() << " digits were detected. Please try again." << endl;
    }
   
    else
    {
        cout << "Card is: INVALID" << endl;
        cout << type << endl;
    }
    cout << endl;

    return 0;
}

