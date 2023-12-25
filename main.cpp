#include <iostream>
#include <iomanip>

#include<array>
#include<vector>
#include<string>

// A little "library" by Vincent Godin that allows the use of color in cout:
// https://www.codeproject.com/Articles/16431/Add-color-to-your-std-cout
// From the .h file, we can see that the available colors are blue, red, green, yellow and white
#include "ConsoleColor.h"

using std::cout;
using std::endl;
using std::cerr;
using std::cin;
using std::vector;
using std::string;
using std::left;
using std::right;
using std::to_string;
using std::setw;
using std::stoi;

class Card {
public:
    // Default constructor: defines the card with random values if no values are provided
    Card() {
        faceValueString = generateRandomCardValueString();
        symbolString = generateRandomCardSymbolString();
    }

    // constructor for value and symbol definitions
    Card(string faceValueString_, string symbolString_) {
        errorCheckCardValue(faceValueString_);
        errorCheckCardSymbol(symbolString_);
        faceValueString = faceValueString_;
        symbolString = symbolString_;
    }

    // Modifying the face value of a card
    void setFaceValue(string newFaceValue) {
        errorCheckCardValue(newFaceValue);
        faceValueString = newFaceValue;
    }

    string getFaceValue() {
        return faceValueString;
    }

    void setSymbol(string newSymbol) {
        errorCheckCardSymbol(newSymbol);
        symbolString = newSymbol;
    }

    string getSymbol() {
        return symbolString;
    }

    void redefine(string newFaceValue, string newSymbol) {
        errorCheckCardValue(newFaceValue);
        errorCheckCardSymbol(newSymbol);
        faceValueString = newFaceValue;
        symbolString = newSymbol;
    }

    int faceValueStringToGameValue(string faceValueStringToConvert) {
        // Check if  faceValueString is between "2" and "10"
        if (faceValueStringToConvert >= "2" && faceValueStringToConvert <= "9") {
            // Using string to int (stoi) to convert the 1-digit number in the string to an int
            // Function found on https://cplusplus.com/reference/string/stoi/
            return stoi(faceValueStringToConvert);
        } else if (faceValueStringToConvert == "10" || faceValueStringToConvert == "J" ||
                   faceValueStringToConvert == "Q" ||
                   faceValueStringToConvert == "K") {
            return 10;
        } else if (faceValueStringToConvert == "A") {
            return 11;
        } else {
            return 0;
        }
    }

    char cardSymbolStringToIconChar(string stringCardSymbol) {
        if (stringCardSymbol == "hearts") {
            return hearts;
        } else if (stringCardSymbol == "diamonds") {
            return diamonds;
        } else if (stringCardSymbol == "clubs") {
            return clubs;
        } else if (stringCardSymbol == "spades") {
            return spades;
        }
    }

    int getGameValue() {
        return faceValueStringToGameValue(faceValueString);
    }

    bool isAce() {
        if (faceValueString == "A") {
            return true;
        } else {
            return false;
        }
    }

    void printCard() {
        cout << "+----------+" << endl;

        // Printing the top row with value
        cout << "| ";
        // The color is based on the symbol
        // if the symbol is red, then the text is printed in red, else in white/black
        if (symbolString == "hearts" || symbolString == "diamonds") {
            cout << red << left << setw(2) << faceValueString << white << "       |";
        } else {
            cout << left << setw(2) << faceValueString << "       |";
        }
        cout << endl;

        // Printing the top row with symbol
        // in order to get to the symbols and not the card cardsData
        char symbolIcon = cardSymbolStringToIconChar(symbolString);

        // Printing the left border of the card in white/black
        cout << "| ";
        // If the symbol is hearts or diamonds, print it in red and else in white/black
        if (symbolString == "hearts" || symbolString == "diamonds") {
            cout << red << symbolIcon << white;
        } else {
            cout << symbolIcon;
        }
        // Printing the right border of the card in white/black
        cout << "        |" << endl;

        // Printing the empty middle row of a card
        cout << "|          |" << endl;

        // Printing the bottom row with symbol
        cout << "|        ";
        // if the symbol is hearts or diamonds, print it in red and else in white/black
        if (symbolString == "hearts" || symbolString == "diamonds") {
            cout << red << symbolIcon << white;
        } else {
            cout << symbolIcon;
        }
        cout << " |" << endl;

        // Printing the bottom row(s) with value(s)
        cout << "|       ";
        // The color is based on the symbol, which is i+1 in the vector
        // If the symbol is red, then the text is printed in red, else in white/black
        if (symbolString == "hearts" || symbolString == "diamonds") {
            cout << red << right << setw(2) << faceValueString << white;
        } else {
            cout << right << setw(2) << faceValueString;
        }
        cout << " |" << endl;

        // Printing the bottom border
        cout << "+----------+" << endl;
    }

private:
    // the face value is the value as printed on a card, being 2-10, A, J, Q or K
    string faceValueString;
    string symbolString;

    // Defining the card symbol characters based on this online forum discussion:
    // https://www.daniweb.com/programming/software-development/threads/296311/can-i-get-the-cards-suit-symbols-as-a-character
    const char hearts = '\x03';  //♥
    const char diamonds = '\x04';  //♦
    const char clubs = '\x05';  //♣
    const char spades = '\x06';  //♠

    string generateRandomCardValueString() {
        int randomValue = rand() % 13 + 1;

        if (randomValue == 1) {
            return "A";
        } else if (randomValue == 11) {
            return "J";
        } else if (randomValue == 12) {
            return "Q";
        } else if (randomValue == 13) {
            return "K";
        } else {
            return to_string(randomValue);
        }
    }

    string generateRandomCardSymbolString() {
        int randomNumber = rand() % 4;
        if (randomNumber == 0)
            return "hearts";
        else if (randomNumber == 2)
            return "diamonds";
        else if (randomNumber == 3)
            return "clubs";
        else
            return "spades";
    }

    void errorCheckCardValue(const string &faceValueStringToCheck) {
        if (faceValueStringToGameValue(faceValueStringToCheck) == 0) {
            std::cerr << "Error: card value is not 2-10 or A, J, Q or K" << endl;
            exit(-1);
        }
    }

    void errorCheckCardSymbol(const string &symbolString_) {
        if (symbolString_ != "hearts" && symbolString_ != "diamonds" && symbolString_ != "clubs" &&
            symbolString_ != "spades") {
            // According to internet research, a " can be printed as a string by writing \" 'to escape the characters'
            std::cerr << "Error: the card symbol is not \"hearts\", \"diamonds\", \"clubs\" or \"spades\"" << endl;
            exit(-1);
        }
    }
};

class Hand {
public:
    // Default constructor for an empty hand
    Hand() {}

    void addCard(const Card &cardToAdd) {
        cardsInHand.push_back(cardToAdd);
    }

    void removeLastCard() {
        cardsInHand.pop_back();
    }

    void printVertical() {
        // Ranged based for loop to go through the cards in the vector of the hand
        for (Card cardToPrint: cardsInHand) {
            cardToPrint.printCard();
        }
    }

    // TODO: if more than x cards, print in two rows
    void printHorizontal() {
        // Printing the top borders
        for (Card cardToPrint: cardsInHand) {
            cout << "+----------+" << '\t';
        }
        cout << endl;

        // Printing the top row(s) with value(s)
        for (Card cardToPrint: cardsInHand) {
            cout << "| ";
            // The color is based on the symbol
            // if the symbol is red, then the text is printed in red, else in white/black
            if (cardToPrint.getSymbol() == "hearts" || cardToPrint.getSymbol() == "diamonds") {
                cout << red << left << setw(2) << cardToPrint.getFaceValue() << white << "       |" << '\t';
            } else {
                cout << left << setw(2) << cardToPrint.getFaceValue() << "       |" << '\t';
            }
        }
        cout << endl;

        // Printing the top row(s) with symbol(s)
        // Going through the vector starting at the 2nd value (i=1) and skipping every other value
        // in order to get to the symbols and not the card cardsData
        for (Card cardToPrint: cardsInHand) {
            char symbol = cardToPrint.cardSymbolStringToIconChar(cardToPrint.getSymbol());

            // Printing the left border of the card in white/black
            cout << white << "| ";
            // If the symbol is hearts or diamonds, print it in red and else in white/black
            if (cardToPrint.getSymbol() == "hearts" || cardToPrint.getSymbol() == "diamonds") {
                cout << red << symbol << white;
            } else {
                cout << symbol;
            }
            // Printing the right border of the card in white/black
            cout << "        |" << '\t';
        }
        cout << endl;

        // Printing the empty middle row of a card
        for (Card cardToPrint: cardsInHand) {
            cout << "|          |" << '\t';
        }
        cout << endl;

        // Printing the bottom row(s) with symbol(s)
        // Going through the vector starting at the 2nd value (i = 1) and skipping every other value
        // in order to get to the symbols and not the card cardsData
        for (Card cardToPrint: cardsInHand) {
            char symbol = cardToPrint.cardSymbolStringToIconChar(cardToPrint.getSymbol());

            cout << white << "|        ";
            // if the symbol is hearts or diamonds, print it in red and else in white/black
            if (cardToPrint.getSymbol() == "hearts" || cardToPrint.getSymbol() == "diamonds") {
                cout << red << symbol << white;
            } else {
                cout << symbol;
            }
            cout << " |" << '\t';
        }
        cout << endl;

        // Printing the bottom row(s) with value(s)
        // Converting 1, 11, 12 and 13 into their respective letters for Ace, Jack, Queen and King for printing
        for (Card cardToPrint: cardsInHand) {
            string thisCardsValue = cardToPrint.getFaceValue();

            cout << "|       ";
            // The color is based on the symbol, which is i+1 in the vector
            // If the symbol is red, then the text is printed in red, else in white/black
            if (cardToPrint.getSymbol() == "hearts" || cardToPrint.getSymbol() == "diamonds") {
                cout << red << right << setw(2) << thisCardsValue << white;
            } else {
                cout << right << setw(2) << thisCardsValue;
            }
            cout << " |" << '\t';
        }
        cout << endl;

        // Printing the bottom borders
        for (Card cardToPrint: cardsInHand) {
            cout << "+----------+" << '\t';
        }
        cout << endl;
    }

    int sumOptimal() {
        int sum = 0;
        int numberOfAcesInHand = 0;

        for (Card cardToSum: cardsInHand) {
            sum += cardToSum.getGameValue();

            // Count the amount of aces, in case of going over 21. If the sum is more than 21 (busting/game over),
            // their values can later be reduced from 11 to 1 to reduce the sum.
            if (cardToSum.isAce()) {
                numberOfAcesInHand++;
            }
        }

        // While the sum is more than 21, reduce the sum by 10 for every ace in the hand to avoid busting if possible
        while (sum > 21 && numberOfAcesInHand > 0) {
            sum -= 10;
            numberOfAcesInHand--;
        }

        return sum;
    }

private:
    vector<Card> cardsInHand;

};

int main() {
    // Seed the random number generator
    srand(time(0));

    // How to define a card:
    // ♥ = "hearts"
    // ♦ = "diamonds"
    // ♣ = "clubs"
    // ♠ = "spades"
    // Ace = "A"
    // Jack = "J"
    // Queen = "Q"
    // King = "K"

    Hand player1hand;

    for (int i = 0; i < 4; ++i) {
        player1hand.addCard(Card());
    }
    player1hand.printHorizontal();
    cout << player1hand.sumOptimal();

    return 0;
}