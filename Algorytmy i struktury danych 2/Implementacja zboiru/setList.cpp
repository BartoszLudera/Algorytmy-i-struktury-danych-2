#include "setList.h"
#include <iostream>
#include <vector>

using namespace std;

int setList::getSize() {
    return vec.size();
}

void setList::printSet() {
    std::cout << "{ ";
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "}" << std::endl;
}

void setList::insert(int x) {
    if (!isInSet(x)) {
        vec.push_back(x);
    }
}

void setList::withdraw(int x) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == x) {
            vec.erase(vec.begin() + i);
            break;
        }
    }
}

bool setList::isInSet(int x) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == x) {
            return true;
        }
    }
    return false;
}

setList setList::operator+(setList& obj) {
    setList result;
    for (int i = 0; i < vec.size(); i++) {
        result.insert(vec[i]);
    }
    for (int i = 0; i < obj.vec.size(); i++) {
        result.insert(obj.vec[i]);
    }
    return result;
}

setList setList::operator*(setList& obj) {
    setList result;
    for (int i = 0; i < vec.size(); i++) {
        if (obj.isInSet(vec[i])) {
            result.insert(vec[i]);
        }
    }
    return result;
}

setList setList::operator-(setList& obj) {
    setList result;
    for (int i = 0; i < vec.size(); i++) {
        if (!obj.isInSet(vec[i])) {
            result.insert(vec[i]);
        }
    }
    return result;
}

bool setList::operator==(setList& obj) {
    if (vec.size() != obj.vec.size()) {
        return false;
    }
    for (int i = 0; i < vec.size(); i++) {
        if (!obj.isInSet(vec[i])) {
            return false;
        }
    }
    return true;
}

bool setList::operator<=(setList& obj) {
    for (int i = 0; i < vec.size(); i++) {
        if (!obj.isInSet(vec[i])) {
            return false;
        }
    }
    return true;
}


int main()
{
    setList A;
    setList B;

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

    setList C = A + B;
    std::cout << "A + B: ";
    C.printSet();

    setList D = A * B;
    std::cout << "A * B: ";
    D.printSet();

    setList E = A - B;
    std::cout << "A - B: ";
    E.printSet();

    bool isEqual = A == B;
    std::cout << "A == B: " << isEqual << std::endl;

    bool isSubset = A <= B;
    std::cout << "A <= B: " << isSubset << std::endl;
}
