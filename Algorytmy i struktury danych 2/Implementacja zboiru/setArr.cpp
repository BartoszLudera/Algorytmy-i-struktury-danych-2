#include "setArr.h"
#include <iostream>

using namespace std;

setArr::setArr()
{
    size = 0;
    table = new bool[universeSize];
    for (int i = 0; i < universeSize; i++)
    {
        table[i] = false;
    }
}

bool setArr::checkRangeCorrectness(int x)
{
    if (x < 0 || x >= universeSize)
    {
        std::cout << "Error: index out of range" << std::endl;
        return false;
    }
    return true;
}

void setArr::insert(int x)
{
    if (checkRangeCorrectness(x) && !table[x])
    {
        table[x] = true;
        size++;
    }
}

void setArr::withdraw(int x)
{
    if (checkRangeCorrectness(x) && !table[x])
    {
        table[x] = true;
        size--;
    }
}

bool setArr::isInSet(int i)
{
    if (checkRangeCorrectness(i))
    {
        return table[i];
    }
    return false;
}

int setArr::getSize()
{
    return size;
}

void setArr::clearSet()
{
    for (int i = 0; i < size; i++)
    {
        table[i] = false;
    }
    size = 0;
}

void setArr::printSet()
{
    std::cout << "{ ";
    for (int i = 0; i < universeSize; i++)
    {
        if (table[i])
        {
            std::cout << i << " ";
        }
    }
    std::cout << "}" << std::endl;
}

setArr setArr::operator+(setArr &object)
{
    setArr result;
    for (int i = 0; i < universeSize; i++)
    {
        result.table[i] = table[i] || object.table[i];
        if (result.table[i])
        {
            result.size++;
        }
    }
    return result;
}

setArr setArr::operator*(setArr &object)
{
    setArr result;
    for (int i = 0; i < universeSize; i++)
    {
        result.table[i] = table[i] && object.table[i];
        if (result.table[i])
        {
            result.size++;
        }
    }
    return result;
}

setArr setArr::operator-(setArr &object)
{
    setArr result;
    for (int i = 0; i < universeSize; i++)
    {
        result.table[i] = table[i] && !object.table[i];
        if (result.table[i])
        {
            result.size++;
        }
    }
    return result;
}

bool setArr::operator==(setArr &object)
{
    for (int i = 0; i < universeSize; i++)
    {
        if (table[i] != object.table[i])
        {
            return false;
        }
    }
    return true;
}

bool setArr::operator<=(setArr &object)
{
    for (int i = 0; i < universeSize; i++)
    {
        if (table[i] && !object.table[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    setArr A;
    setArr B;

    A.insert(5);
    A.insert(7);
    A.insert(10);

    B.insert(2);
    B.insert(5);
    B.insert(7);

    std::cout << "A: ";
    A.printSet();
    std::cout << "B: ";
    B.printSet();

    setArr C = A + B;
    std::cout << "A + B: ";
    C.printSet();

    setArr D = A * B;
    std::cout << "A * B: ";
    D.printSet();

    setArr E = A - B;
    std::cout << "A - B: ";
    E.printSet();

    bool isEqual = A == B;
    std::cout << "A == B: " << isEqual << std::endl;

    bool isSubset = A <= B;
    std::cout << "A <= B: " << isSubset << std::endl;

    A.clearSet();
    B.clearSet();
}
