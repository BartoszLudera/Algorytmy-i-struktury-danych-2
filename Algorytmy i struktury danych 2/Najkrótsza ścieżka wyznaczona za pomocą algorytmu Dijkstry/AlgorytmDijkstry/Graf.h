#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <queue>
#include <list>

#include "edge.h"

const int INF = std::numeric_limits<int>::max();

class Graf
{
    std::vector<std::vector<edge *>> vertexList;
    int numVertices;

public:
    Graf()
    {
        vertexList = std::vector<std::vector<edge *>>();
        numVertices = 0;
    }
    void createVertices(int ile)
    {
        this->numVertices = ile;

        vertexList.resize(numVertices);
        for (int i = 0; i < vertexList.size(); i++)
        {
            for (int j = 0; j < vertexList.size(); j++)
            {
                vertexList[i].push_back(nullptr);
            }
        }
    }

    void addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2, int weight)
    {
        edge *newEdge = new edge(i_Vertex_Index_1, i_Vertex_Index_2, weight);
        vertexList[i_Vertex_Index_1][i_Vertex_Index_2] = newEdge;
        if (i_Vertex_Index_1 != i_Vertex_Index_2)
        {
            vertexList[i_Vertex_Index_1][i_Vertex_Index_2] = newEdge;
        }
    }
    bool removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2)
    {
        bool isRemoved = false;

        if (vertexList[i_Vertex_Index_1][i_Vertex_Index_2] != nullptr)
        {
            delete vertexList[i_Vertex_Index_1][i_Vertex_Index_2];
            isRemoved = true;
            vertexList[i_Vertex_Index_1][i_Vertex_Index_2] = nullptr;
            vertexList[i_Vertex_Index_2][i_Vertex_Index_1] = nullptr;
        }

        return isRemoved;
    }

    Graf(std::string path)
    {

        std::ifstream infile(path);
        if (!infile.is_open())
        {
            std::cout << "Cannot open file: " << path << std::endl;
            return;
        }

        int num_vertices;
        infile >> num_vertices;

        createVertices(num_vertices);

        int vertex1, vertex2, weight;
        while (infile >> vertex1 >> vertex2 >> weight)
        {
            addEdge(vertex1, vertex2, weight);
        }
        infile.close();
    }

    bool checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2)
    {
        return vertexList[i_Vertex_Index_1][i_Vertex_Index_2] != nullptr;
    }
    int vertexDegree(int idx)
    {
        int count = 0;
        for (int i = 0; i < vertexList.size(); i++)
        {
            if (vertexList[idx][i] != nullptr)
            {
                count++;
            }
        }
        return count;
    }

    std::vector<int> getNeighbourIndices(int idx)
    {
        std::vector<int> neighbours;

        for (int i = 0; i < vertexList.size(); i++)
        {
            if (vertexList[idx][i] != nullptr)
            {
                neighbours.push_back(i);
            }
        }
        return neighbours;
    }

    void printNeighbourIndices(int idx)
    {
        std::vector<int> neighbours = getNeighbourIndices(idx);

        for (int i = 0; i < neighbours.size(); i++)
        {
            std::cout << neighbours[i] << " ";
        }
        std::cout << std::endl;
    }

    int getNumberOfEdges()
    {
        int count = 0;
        for (int i = 0; i < vertexList.size(); i++)
        {
            for (int j = 0; j < vertexList.size(); j++)
            {
                if (vertexList[i][j] != nullptr)
                {
                    count++;
                }
            }
        }
        return count / 2;
    }

    int getEdgeValue(int i, int j)
    {
        edge *e = vertexList[i][j];
        if (e == nullptr)
        {
            return -1;
        }
        return e->waga;
    }

    int getSize()
    {
        return numVertices;
    }
};

void dijkstra(Graf &graf, int source, int destination)
{
    int graphSize = graf.getSize();
    int *distance = new int[graphSize]();
    int *prev = new int[graphSize]();

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    for (int i = 0; i < graphSize; i++)
    {
        distance[i] = INF;
        prev[i] = -1;
    }

    distance[source] = 0;
    prev[source] = source;

    pq.push({distance[source], source});
    while (!pq.empty())
    {
        int min = pq.top().second;
        pq.pop();
        std::vector<int> neighbours = graf.getNeighbourIndices(min);
        for (int neighbour : neighbours)
        {
            if (distance[neighbour] > distance[min] + graf.getEdgeValue(min, neighbour))
            {
                distance[neighbour] = distance[min] + graf.getEdgeValue(min, neighbour);
                pq.push({distance[neighbour], neighbour});
                prev[neighbour] = min;
            }
        }
    }

    for (int i = 0; i < graphSize; i++)
    {
        std::cout << i << " : " << ((distance[i] == INF) ? -1 : distance[i]) << std::endl;
    }
    std::cout << std::endl;

    std::list<int> answer;
    int last = destination;

    do
    {
        last = prev[last];
        answer.push_front(last);
    } while (last != source);

    std::cout << "Droga od" << source << " do " << destination << ": ";
    for (int e : answer)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    std::cout << "Koszt od " << source << " do " << destination << " wynosi: " << distance[destination] << std::endl;
}
