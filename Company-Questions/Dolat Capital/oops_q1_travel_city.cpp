/*
Question 1: Travel Expense (Object-Oriented Programming)
Problem Statement:
You are required to calculate the travel expense for different cities based on the mode of transportation available in that city. Use Object-Oriented Programming (OOP) concepts, specifically polymorphism, to implement this functionality.

Each mode of transport has a fixed cost associated with it:

Bus: 30.50

Taxi: 55.20

Metro: 25.75

Class Design Requirements:

Create a base class City with the following methods:

String getName(): Returns the name of the city.

double calculateTravelExpense(): Calculates and returns the total expense based on the transport (this should be overridden by subclasses).

Create three subclasses representing cities with specific transports (e.g., a City with a Bus, a City with a Taxi, etc.).

Each subclass must have a constructor that takes the city's name (as a string) as a parameter.

Each subclass must override the calculateTravelExpense() method to return the fixed cost of its respective transport.

Example:

Input: Bus NewYork

Output: NY : 30.50 (Note: The problem description shows NY as shorthand in the output, but fundamentally requires printing the city name/identifier and the fixed double value).

*/

#include <iostream>
#include <string>
using namespace std;

// Abstract Base Class
class City
{
protected:
    string name;

public:
    City(string n) : name(n) {}

    string getName()
    {
        return name;
    }

    // Pure virtual function to achieve polymorphism
    virtual double calculateTravelExpense() = 0;

    virtual ~City() {} // Virtual destructor for safe memory management
};

class BusCity : public City
{
public:
    BusCity(string n) : City(n) {}
    double calculateTravelExpense() override
    {
        return 30.50;
    }
};

class TaxiCity : public City
{
public:
    TaxiCity(string n) : City(n) {}
    double calculateTravelExpense() override
    {
        return 55.20;
    }
};

class MetroCity : public City
{
public:
    MetroCity(string n) : City(n) {}
    double calculateTravelExpense() override
    {
        return 25.75;
    }
};

int main()
{
    string transport, cityName;
    // Example Input: Bus NewYork
    if (cin >> transport >> cityName)
    {
        City *city = nullptr;

        if (transport == "Bus")
            city = new BusCity(cityName);
        else if (transport == "Taxi")
            city = new TaxiCity(cityName);
        else if (transport == "Metro")
            city = new MetroCity(cityName);

        if (city)
        {
            // Output: NY : 30.50 (Formatting as requested)
            // Note: The example maps 'NewYork' to 'NY'. In a real scenario,
            // you'd likely just print city->getName().
            cout << city->getName() << " : " << city->calculateTravelExpense() << endl;
            delete city;
        }
    }
    return 0;
}