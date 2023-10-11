#include <array>
#include <iostream>
#include "priorityQueue.h"

using namespace std;

PriorityQueue::PriorityQueue()
{
    size = 0;
}

void PriorityQueue::insert(int x)
{
    if (size == MAX_SIZE)
    {
        cout << "Error: Priority queue is full." << endl;
        return;
    }

    heap[size] = x;
    heapify_up(size);
    size++;
}

int PriorityQueue::removeRootElem()
{
    if (size == 0)
    {
        cout << "Error: Priority queue is empty." << endl;
        return -1;
    }

    int root_elem = heap[0];
    size--;
    heap[0] = heap[size];
    heapify_down(0);

    return root_elem;
}

void PriorityQueue::heapify_up(int i)
{
    if (i == 0)
    {
        return;
    }

    int parent = (i - 1) / 2;

    if (heap[i] > heap[parent])
    {
        swap(heap[i], heap[parent]);
        heapify_up(parent);
    }
}

void PriorityQueue::heapify_down(int i)
{
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;
    int largest = i;

    if (left_child < size && heap[left_child] > heap[largest])
    {
        largest = left_child;
    }

    if (right_child < size && heap[right_child] > heap[largest])
    {
        largest = right_child;
    }

    if (largest != i)
    {
        swap(heap[i], heap[largest]);
        heapify_down(largest);
    }
}

void PriorityQueue::print()
{
    for (int i = 0; i < size; i++)
    {
        cout << heap[i] << " ";
    }
    cout << endl;
}

int PriorityQueue::getRootElem()
{
    if (size == 0)
    {
        cout << "Error: Priority queue is empty." << endl;
        return -1;
    }

    return heap[0];
}

int main()
{
    PriorityQueue pq;

    // Insert elements into the priority queue
    pq.insert(5);
    pq.insert(10);
    pq.insert(3);
    pq.insert(8);

    // Print the priority queue
    pq.print();

    // Get the root element
    int root = pq.getRootElem();
    cout << "Root element: " << root << endl;

    // Remove the root element
    int removed = pq.removeRootElem();
    cout << "Removed element: " << removed << endl;

    // Print the priority queue again
    pq.print();
}