#include "Graf.h"

void test()
{

    Graf graf("./GrafD.txt");
    dijkstra(graf, 7, 6);
}

int main()
{
    test();
}
