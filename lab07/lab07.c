#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct NoGrafo
{
    char Nome;
    int x, y, NumAdj;
    double *Adj;
} NodeGrafo;

typedef struct Grafo
{
    NodeGrafo *Node;
    int NumNode;
} Grafo;

Grafo *LeGrafo (char *nomearq)
{
    int NumNode, x, y;
    char Nome;

    FILE *fp = fopen(nomearq, "r");
    Grafo *G = (Grafo*)calloc(1, sizeof(Grafo));
    
    fscanf(fp, "%d\n", &NumNode);
    G->Node = (NodeGrafo*)calloc(NumNode, sizeof(NodeGrafo));
    G->NumNode = NumNode;

    for (int i = 0; i < NumNode; i++)
    {
        fscanf(fp, "%c %d %d\n", &G->Node[i].Nome, &G->Node[i].x, &G->Node[i].y);
        G->Node[i].Adj = (double*)calloc(NumNode, sizeof(double));
        
        for (int j = 0; j < NumNode; j++)
            G->Node[i].Adj[j] = 0;
    }

    return G;
}

double DistanciaEuclidiana(int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void AchaAdj(NodeGrafo **Grafo, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                double Distancia = DistanciaEuclidiana((*Grafo)[i].x, (*Grafo)[i].y, (*Grafo)[j].x, (*Grafo)[j].y);
                if (Distancia <= 2.0)
                    (*Grafo)[i].Adj[j] = Distancia;
            }

        }
    }
}

void PrintGrafoMatriz(Grafo** Grafo, int NumNode) {
    printf("Matriz de adjacencia:\n\t");
    
    for (int i = 0; i < NumNode; i++) 
        printf("%c\t", (*Grafo)->Node[i].Nome);
    printf("\n");

    for (int i = 0; i < NumNode; i++) 
    {
        printf("%c\t", (*Grafo)->Node[i].Nome);
        for (int j = 0; j < NumNode; j++) 
        {
            if ((*Grafo)->Node[i].Adj[j] == 0)
                printf("0\t");
            else
                printf("%.3f\t", (*Grafo)->Node[i].Adj[j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    Grafo *Grafo = LeGrafo(argv[1]);
    AchaAdj(&Grafo->Node, Grafo->NumNode);
    PrintGrafoMatriz(&Grafo, Grafo->NumNode);
    
    return 0;
}