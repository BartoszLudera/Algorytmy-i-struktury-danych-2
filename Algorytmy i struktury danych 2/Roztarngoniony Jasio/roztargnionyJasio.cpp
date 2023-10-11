#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

int main()
{
    ifstream input("Input.txt");

    int n;
    input >> n;

    vector<int> keys(n + 1);
    for (int i = 1; i <= n; i++)
    {
        input >> keys[i];
    }

    vector<bool> visited(n + 1, false);
    int num_components = 0;
    vector<int> smashed;

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            num_components++;
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while (!q.empty())
            {
                int curr = q.front();
                q.pop();

                int neighbor = keys[curr];
                if (!visited[neighbor])
                {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }

    int num_smashed = n - num_components;
    cout << "Minimalna ilość skarbonek do rozbicia: " << num_smashed << endl;

    input.close();
}
