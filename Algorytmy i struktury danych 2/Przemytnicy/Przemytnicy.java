import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import java.util.Scanner;

public class Przemytnicy {
    private final int vertices;
    private int[][] graph;

    private final List<Integer> invalidVer = new ArrayList<>();

    public int countNonZeroElements() {
        int count = 0;

        for (int i = 0; i < graph.length; i++) {
            for (int j = 0; j < graph[i].length; j++) {
                if (graph[i][j] != 0) {
                    count++;
                }
            }
        }

        return count;
    }

    public void addEdge(int source, int destination, int weight) {
        graph[source][destination] = weight;
    }

    public Przemytnicy(int vertices) {
        this.vertices = vertices;
        graph = new int[vertices][vertices];

    }


    public void delEdge(int source, int destination, int weight) {
        graph[source][destination] = 0;
    }


    public void reverseGraph() {
        int[][] reversedGraph = new int[vertices][vertices];

        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                reversedGraph[j][i] = graph[i][j];
            }
        }

        graph = reversedGraph;
    }

    public int[] shortestPath(int source) {
        int[] distances = new int[vertices];
        boolean[] visited = new boolean[vertices];

        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[source] = 0;

        for (int count = 0; count < vertices - 1; count++) {
            int minDistance = findMinDistance(distances, visited);
            visited[minDistance] = true;

            for (int vertex = 0; vertex < vertices; vertex++) {
                if (!visited[vertex] && graph[minDistance][vertex] != 0 &&
                        distances[minDistance] != Integer.MAX_VALUE) {
                    distances[vertex] = distances[minDistance] + graph[minDistance][vertex];
                }
            }
        }

        return distances;
    }

    private int findMinDistance(int[] distances, boolean[] visited) {
        int minDistance = Integer.MAX_VALUE;
        int minIndex = -1;

        for (int vertex = 0; vertex < vertices; vertex++) {
            if (!visited[vertex] && distances[vertex] <= minDistance) {
                minDistance = distances[vertex];
                minIndex = vertex;
            }
        }

        return minIndex;
    }

    public static int findSmallestSumByIndex(int[] array1, int[] array2, int[] array3) {
        int smallestSum = Integer.MAX_VALUE;
        int length = Math.min(Math.min(array1.length, array2.length), array3.length);

        for (int i = 0; i < length; i++) {
            int sum = array1[i] + array2[i] + array3[i];
            smallestSum = Math.min(smallestSum, sum);
        }

        return smallestSum;
    }

    public static List<Integer> readNumbersFromFile(String fileName) throws FileNotFoundException {
        List<Integer> numbers = new ArrayList<>();
        File file = new File(fileName);
        Scanner scanner = new Scanner(file);

        while (scanner.hasNextInt()) {
            int number = scanner.nextInt();
            numbers.add(number);
        }

        scanner.close();
        return numbers;
    }



    public static void main(String[] args) throws FileNotFoundException {
        List<Integer> numbers;
        String fileName = "/.../Input.txt"; // enter the path to the file


        numbers = readNumbersFromFile(fileName);
        int vertices = numbers.get(0);
        int[] tax = new int[vertices];
        Przemytnicy dijkstra = new Przemytnicy(vertices);
        for (int i = 1; i <= vertices; i++) {
            tax[i - 1] = numbers.get(i) / 2;
        }
        int edgesNumberIndex = vertices + 1;
        int numberOfEdges = numbers.get(edgesNumberIndex);

        int endIndex = edgesNumberIndex + 1 + numberOfEdges;
        for (int i = edgesNumberIndex + 1; i < numbers.size(); i = i + 3) {
            dijkstra.addEdge(numbers.get(i) - 1, numbers.get(i + 1) - 1, numbers.get(i + 2));
        }

        int source = 0;
        int[] shortestDistances = dijkstra.shortestPath(source);


        dijkstra.reverseGraph();

        int[] reversedShortestDistances = dijkstra.shortestPath(source);


        int result = findSmallestSumByIndex(shortestDistances, reversedShortestDistances, tax);
        if (result > numbers.get(1) || result < 0 || dijkstra.countNonZeroElements() == 0) {
            System.out.println("result: " + numbers.get(1));
        } else {
            System.out.println("result: " + result);
        }
    }
}
