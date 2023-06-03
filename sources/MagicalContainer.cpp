#include "MagicalContainer.hpp"

namespace ariel
{
    // --------------------------------------
    //          MagicalContainer
    // --------------------------------------
    bool MagicalContainer::operator!=(const MagicalContainer &other) const
    {
        return this->elements != other.elements;
    }

    void MagicalContainer::addElement(int element)
    {
        if (this->elements.empty())
        {
            this->elements.push_back(element); // Add the first element
        }
        else
        {
            // Find the position to insert the element using binary search
            int left = 0;
            int right = this->elements.size() - 1;
            int mid = 0;

            while (left <= right)
            {
                mid = (left + right) / 2;

                if (element == this->elements.at(static_cast<std::vector<int>::size_type>(mid)))
                {
                    // Element already exists in the vector, no need to insert
                    return;
                }
                else if (element < this->elements.at(static_cast<std::vector<int>::size_type>(mid)))
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }

            // Insert the element at the appropriate position
            this->elements.insert(this->elements.begin() + left, element);
        }
    }

    void MagicalContainer::removeElement(int element)
    {
        auto it = std::find(this->elements.begin(), this->elements.end(), element);

        if (it == this->elements.end())
        {
            throw std::runtime_error("Element not found in the container.");
        }
        this->elements.erase(std::remove(this->elements.begin(), this->elements.end(), element), this->elements.end());
    }

    size_t MagicalContainer::size() const
    {
        return this->elements.size();
    }

    std::vector<int> MagicalContainer::getElements() const
    {
        return this->elements;
    }

    int MagicalContainer::getElementAt(size_t possition) const
    {
        return this->elements.at(possition);
    }

    // --------------------------------------
    //          AscendingIterator
    // --------------------------------------
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &cont, size_t pos)
        : container(cont), position(pos) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : container(other.container), position(other.position) {}

    MagicalContainer::AscendingIterator::~AscendingIterator() {}

    MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator &&other) noexcept : container(other.container), position(other.position) {}

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        if (this->container != other.container)
        {
            throw std::runtime_error("Can't assign on different container.");
        }

        this->container = other.container;
        this->position = other.position;
        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(AscendingIterator &&other) noexcept
    {
        this->container = other.container;
        this->position = other.position;
        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        if (*this == this->end())
        {
            throw std::runtime_error("Increment beyond the end");
        }
        ++position;
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
    {
        return this->position == other.position;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
    {
        return this->position != other.position;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
    {
        return this->position > other.position;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
    {
        return this->position < other.position;
    }

    int MagicalContainer::AscendingIterator::operator*() const
    {
        if (this->position < this->container.size())
        {
            return this->container.getElementAt(position);
        }
        else
        {
            throw std::out_of_range("Iterator out of range.");
        }
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
    {
        return AscendingIterator(this->container);
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
    {
        return AscendingIterator(this->container, this->container.size());
    }

    // --------------------------------------
    //          SideCrossIterator
    // --------------------------------------
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &cont)
        : container(cont), left(0), right(cont.size() - 1), leftToRight(true)
    {
        if (cont.size() == 0)
        {
            right = 0;
        }
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &cont, size_t newLeft, size_t newRight, bool lToR)
        : container(cont), left(newLeft), right(newRight), leftToRight(lToR) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : container(other.container), left(other.left), right(other.right), leftToRight(other.leftToRight) {}

    MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator &&other) noexcept : container(other.container), left(other.left), right(other.right), leftToRight(other.leftToRight) {}

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
        if (this->container != other.container)
        {
            throw std::runtime_error("Can't assign on different container.");
        }

        this->container = other.container;
        this->left = other.left;
        this->right = other.right;
        return *this;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(SideCrossIterator &&other) noexcept
    {
        this->container = other.container;
        this->left = other.left;
        this->right = other.right;
        return *this;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {
        if (*this == end())
        {
            throw std::runtime_error("Reached to the end");
        }

        if (this->leftToRight)
        {
            this->left++;
        }
        else
        {
            this->right--;
        }

        if (this->right < this->left)
        {
            this->right = this->container.size();
            this->left = 0;
        }
        this->leftToRight = !this->leftToRight;
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
    {
        return (this->left == other.left) && (this->right == other.right);
        ;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        return (this->left > other.left) || (this->right > other.right);
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        return (this->left < other.left) || (this->right < other.right);
    }

    int MagicalContainer::SideCrossIterator::operator*() const
    {
        if (this->leftToRight)
        {
            return this->container.getElementAt(this->left);
        }

        return this->container.getElementAt(this->right);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
    {
        return SideCrossIterator(this->container);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
    {
        return SideCrossIterator(this->container, 0, this->container.size(), true);
    }

    // --------------------------------------
    //          PrimeIterator
    // --------------------------------------
    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &cont, size_t pos)
        : container(cont), position(pos)
    {
        // Looking for the index of the first prime number in the container
        while (position < container.size() && !isPrime(container.getElementAt(position)))
            ++position;
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : container(other.container), position(other.position) {}

    MagicalContainer::PrimeIterator::~PrimeIterator() {}

    MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator &&other) noexcept : container(other.container), position(other.position) {}

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
    {
        if (this->container != other.container)
        {
            throw std::runtime_error("Can't assign on different container.");
        }

        this->container = other.container;
        this->position = other.position;
        return *this;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(PrimeIterator &&other) noexcept
    {
        this->container = other.container;
        this->position = other.position;
        return *this;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        if (*this == this->end())
        {
            throw std::runtime_error("Increment beyond the end");
        }
        ++position;
        // Looking for the index of the next prime number in the container
        while (position < container.size() && !isPrime(container.getElementAt(position)))
            ++position;
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
    {
        return this->position == other.position;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
    {
        return this->position > other.position;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
    {
        return this->position < other.position;
    }

    int MagicalContainer::PrimeIterator::operator*() const
    {
        if (this->position < this->container.size())
            return this->container.elements[this->position];
        else
            throw std::out_of_range("Iterator out of range.");
    }

    // Returns true if number is prime and false otherwise
    bool MagicalContainer::PrimeIterator::isPrime(int number) const
    {
        if (number < 2)
            return false;
        if (number < 4)
            return true;
        if (number % 2 == 0)
            return false;

        int sqrtNumber = static_cast<int>(std::sqrt(number));
        for (int i = 3; i <= sqrtNumber; i += 2)
        {
            if (number % i == 0)
                return false;
        }
        return true;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
    {
        return PrimeIterator(this->container);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
    {
        return PrimeIterator(this->container, this->container.size());
    }
}