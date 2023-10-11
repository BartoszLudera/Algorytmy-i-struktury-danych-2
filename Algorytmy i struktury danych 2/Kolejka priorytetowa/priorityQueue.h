#pragma once
#include <iostream>
#include <array>

const int MAX_SIZE = 100;

class PriorityQueue
{
private:
    std::array<int, MAX_SIZE> heap;
    int size;

    void heapify_up(int i);
    void heapify_down(int i);

public:
    PriorityQueue();
    void insert(int x);
    int removeRootElem();
    void print();
    int getRootElem();
};