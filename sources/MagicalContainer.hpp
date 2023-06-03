#ifndef MAGICALCONTAINER_H
#define MAGICALCONTAINER_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdexcept>
using namespace std;

namespace ariel
{
    class MagicalContainer
    {
    private:
        std::vector<int> elements;

    public:
        bool operator!=(const MagicalContainer &other) const;
        void addElement(int element);    // Add an int number to the container
        void removeElement(int element); // Remove the inputed number from the container
        size_t size() const;             // Return the number of elements in the container

        // Getters
        std::vector<int> getElements() const;
        int getElementAt(size_t possition) const;

        // Iterator classes
        class AscendingIterator;
        class SideCrossIterator;
        class PrimeIterator;
    };

    class MagicalContainer::AscendingIterator
    {
    private:
        MagicalContainer &container;
        size_t position; // cell index position is the container

    public:
        AscendingIterator(MagicalContainer &cont, size_t pos = 0); // Constructor
        AscendingIterator(const AscendingIterator &other);         // Copy constructor
        ~AscendingIterator();                                      // Destructor
        AscendingIterator(AscendingIterator &&other) noexcept;     // Move constructor
        AscendingIterator &operator=(const AscendingIterator &other);
        AscendingIterator &operator=(AscendingIterator &&other) noexcept;

        AscendingIterator &operator++();
        bool operator==(const AscendingIterator &other) const;
        bool operator!=(const AscendingIterator &other) const;
        bool operator>(const AscendingIterator &other) const;
        bool operator<(const AscendingIterator &other) const;
        int operator*() const;

        AscendingIterator begin(); // Returns an AscendingIterator pointing to the first element of the container
        AscendingIterator end();   // Returns an AscendingIterator pointing one position past the last element of the container
    };

    class MagicalContainer::SideCrossIterator
    {
    private:
        MagicalContainer &container;
        size_t left;      // The current left cell postion
        size_t right;     // The current right cell position
        bool leftToRight; // if true - point at a left cell, else - point at a right cell

    public:
        SideCrossIterator(MagicalContainer &cont); // Constructor
        SideCrossIterator(MagicalContainer &cont, size_t newLeft, size_t newRight, bool lToR = true);
        SideCrossIterator(const SideCrossIterator &other);     // Copy constructor
        ~SideCrossIterator();                                  // Destructor
        SideCrossIterator(SideCrossIterator &&other) noexcept; // Move constructor
        SideCrossIterator &operator=(const SideCrossIterator &other);
        SideCrossIterator &operator=(SideCrossIterator &&other) noexcept;

        SideCrossIterator &operator++();
        bool operator==(const SideCrossIterator &other) const;
        bool operator!=(const SideCrossIterator &other) const;
        bool operator>(const SideCrossIterator &other) const;
        bool operator<(const SideCrossIterator &other) const;
        int operator*() const;

        SideCrossIterator begin(); // Returns an SideCrossIterator pointing to the first element of the container
        SideCrossIterator end();   // Returns an SideCrossIterator pointing one position past the last element of the container
    };

    class MagicalContainer::PrimeIterator
    {
    private:
        MagicalContainer &container;
        size_t position; // cell index position is the container

        bool isPrime(int number) const; // Returns true if number is prime and false otherwise

    public:
        PrimeIterator(MagicalContainer &cont, size_t pos = 0); // Constructor
        PrimeIterator(const PrimeIterator &other);             // Copy constructor
        ~PrimeIterator();                                      // Destructor
        PrimeIterator(PrimeIterator &&other) noexcept;         // Move constructor
        PrimeIterator &operator=(const PrimeIterator &other);
        PrimeIterator &operator=(PrimeIterator &&other) noexcept;

        PrimeIterator &operator++();
        bool operator==(const PrimeIterator &other) const;
        bool operator!=(const PrimeIterator &other) const;
        bool operator>(const PrimeIterator &other) const;
        bool operator<(const PrimeIterator &other) const;
        int operator*() const;

        PrimeIterator begin(); // Returns an PrimeIterator pointing to the first element of the container
        PrimeIterator end();   // Returns an PrimeIterator pointing one position past the last element of the container
    };
};

#endif