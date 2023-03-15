
#include <limits.h>
#include <stdio.h>

// Anzahl der Knoten im Graphen
#define V 4

// Eine Hilfsfunktion, um den Knoten mit dem minimalen Distanzwert zu finden, 
// von der Menge der Knoten, die noch nicht im kürzesten Pfadbaum enthalten sind
int minDistance(int dist[], bool sptSet[])
{
    // Initialisiere den minimalen Wert
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Eine Hilfsfunktion zum Drucken des konstruierten Distanzarrays
void printSolution(int dist[], int n)
{
    printf("Knoten   Entfernung vom Ursprung\n");
    for (int i = 0; i < V; i++){
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

// Funktion, die den Dijkstra-Algorithmus zur Berechnung des kürzesten Pfads von einer Quelle aus 
// auf einem Graphen mit Adjazenzmatrixdarstellung implementiert
void dijkstra(int graph[V][V], int src)
{
    int dist[V]; // Das Ausgabearray. dist[i] wird den kürzesten Abstand von src zu i halten

    bool sptSet[V]; // sptSet[i] wird true sein, wenn der Knoten i im kürzesten Pfadbaum enthalten ist 
                    // oder der kürzeste Abstand von src zu i finalisiert ist

    // Initialisiere alle Distanzen als UNENDLICH und sptSet[] als falsch
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Der Abstand des Ursprungsknotens von sich selbst ist immer 0
    dist[src] = 0;

    // Finde den kürzesten Pfad für alle Knoten
    for (int count = 0; count < V - 1; count++) {
        // Wähle den Knoten mit der minimalen Distanz aus der Menge der Knoten aus, die noch nicht verarbeitet wurden. 
        // In der ersten Iteration ist u immer gleich src.
        int u = minDistance(dist, sptSet);

        // Markiere den ausgewählten Knoten als verarbeitet
        sptSet[u] = true;

        // Aktualisiere den dist-Wert der benachbarten Knoten des ausgewählten Knotens.
        for (int v = 0; v < V; v++)

            // Aktualisiere dist[v] nur, wenn er nicht in sptSet enthalten ist, es eine Kante von u nach v gibt 
            // und das Gesamtgewicht des Pfads von src nach v durch u kleiner ist als der aktuelle Wert von dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // Drucke das konstruierte Distanzarray
    printSolution(dist, V);
}

int main()
{
    int INF = 1e9;

    int graph[V][V] = { { 0,    1,  4,  INF},
                        { 1,    0,  INF,10},
                        { 4,    INF,0,  5},
                        { INF,    10,  5,  0}};
 
    dijkstra(graph, 0);
 
    return 0;
}