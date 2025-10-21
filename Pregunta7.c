#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int vertex;
typedef struct node *link;
typedef struct node
{
    vertex w;
    link next;
} Node;
typedef struct graph
{
    int V, A;
    link *adj;
} *Graph;

static link NEWnode(vertex w, link next)
{
    link x = malloc(sizeof *x);
    x->w = w;
    x->next = next;
    return x;
}
Graph GRAPHinit(int V)
{
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = calloc(V, sizeof(link));
    return G;
}
void GRAPHinsertArc(Graph G, vertex v, vertex w)
{
    for (link a = G->adj[v]; a; a = a->next)
        if (a->w == w)
            return;
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

static bool hasArc(Graph G, vertex v, vertex w)
{
    for (link a = G->adj[v]; a; a = a->next)
        if (a->w == w)
            return true;
    return false;
}

bool GRAPHundir(Graph G)
{
    for (vertex v = 0; v < G->V; v++)
    {
        for (link a = G->adj[v]; a; a = a->next)
        {
            vertex w = a->w;
            if (!hasArc(G, w, v))
                return false;
        }
    }
    return true;
}

void GRAPHshow(Graph G)
{
    for (vertex v = 0; v < G->V; v++)
    {
        printf("%d:", v);
        for (link a = G->adj[v]; a; a = a->next)
            printf(" %d", a->w);
        printf("\n");
    }
}

int main()
{
    Graph G = GRAPHinit(5);
    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 1, 0);
    GRAPHinsertArc(G, 2, 3);
    GRAPHinsertArc(G, 3, 2);
    GRAPHinsertArc(G, 1, 2);
    GRAPHinsertArc(G, 2, 1);
    printf("Grafo inicial:\n");
    GRAPHshow(G);
    printf("Es no dirigido? %s\n", GRAPHundir(G) ? "si" : "no");
    GRAPHinsertArc(G, 0, 2);
    printf("Agrego arco 0->2:\n");
    GRAPHshow(G);
    printf("Es no dirigido? %s\n", GRAPHundir(G) ? "si" : "no");
    GRAPHinsertArc(G, 2, 0);
    printf("Agrego arco simetrico 2->0:\n");
    GRAPHshow(G);
    printf("Es no dirigido? %s\n", GRAPHundir(G) ? "si" : "no");
    return 0;
}