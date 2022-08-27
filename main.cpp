// Typed By: Jaya Krishna Soganur; Date: August 27, 2022
// A simple C++ application which uses Luhns' Algorithm to validate the credit card number.
// It does not check whether the credit card number is legal and usable.
// It just checks if it is a valid number for a credit card.

#include <iostream>
using namespace std;

// returns 'true' if all characters are digits, else 'false'
bool isNumber(const string& ccNumber) {
    for(const char& digit : ccNumber)
        if(digit < '0' or digit > '9')
            return false;
    return true;
}

// getName() : getCreditCardCompanyName()
string getName(const string& ccNumber) {
    // major credit cards company follows a start pattern
    // Visa - 4, MasterCard - 5, AmericanExpress - 37, Discover - 6
    switch(ccNumber[0]) {
        case '4':
            return "Visa";
        case '5':
            return "MasterCard";
        case '6':
            return "Discover";
        case '3':
            if(ccNumber[1] == '7')
                return "American Express";
    }
    return "Not Recognizable";
}

// isValid() : isValidCreditCardNumber(), ccNumber : creditCardNumber
// returns 'true' if a ccNumber is valid, else 'false'
bool isValid(const string& ccNumber) {
    // typical ccNumber from major credit card companies
    // like Visa(16), MasterCard(16), AmericanExpress(15), Discover(16)
    // have 13 to 16 digits in them, if not they are not valid ccNumbers
    if(ccNumber.length() < 13 or ccNumber.length() > 16) {
        cout << "Invalid Input: The Input Contains More/Less Digits Than Acceptable\n";
        return false;
    }
    // check if all entered characters are digits, if not return 'false'
    if(!isNumber(ccNumber)) {
        cout << "Invalid Input: The Input Contains Characters Other Than Digits\n";
        return false;
    }
    // we can validate whether a ccNumber is valid or not by Luhns' Algorithm
    // Luhns' Algorithm:
    // 1. double the even place digits from the right of the ccNumber i.e., last digits
    // 2. if doubling results in 2-digit number, add both digits
    // 3. add the all even place - doubled numbers to a variable sum
    // 4. add the all odd place numbers to the same variable sum
    // 5. is sum is a multiple of 10, it is valid, if not, not valid
    int sum = 0;
    for(int i = ccNumber.length()-2; i >= 0; i -= 2) {
        int doubleDigit = (ccNumber[i]-'0') * 2; // step 1
        if(doubleDigit > 9) // step 2
            doubleDigit = doubleDigit/10 + doubleDigit%10;
        sum += doubleDigit; // step 3
    }
    // step 4
    for(int i = ccNumber.length()-1; i >= 0; i -= 2)
        sum += (ccNumber[i]-'0');
    return (sum % 10 == 0); // step 5
}


int main() {
    string ccNumber;
    cout << "Validate The Credit Card Number\n";
    cout << "Enter The Credit Card Number:";
    cin >> ccNumber;
    if(isValid(ccNumber)) {
        cout << "The Credit Card " + ccNumber + " Is Valid\n";
        cout << "It Is Issued By " + getName(ccNumber) << "\n";
    }
    else
        cout << "The Credit Card " + ccNumber + " Is NOT Valid\n";
    return 0;
}
