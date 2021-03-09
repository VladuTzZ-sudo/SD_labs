#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>


#define INF 10000
#define NO -1

#include "../queue/queue.h"
#include "../stack/stack.h"
#include "../heap/heap.h"

#define NR_NEIGHBOURS -1

#define TYPE_UNDIRECTED 0
#define TYPE_DIRECTED 1

typedef struct {
	int n;
	int w;
} Edge;

typedef struct {
	int type;
	int nodes;
	Edge **adj;
	int edges;
} Graph;

Edge **createEdges(int type, int nodes, int edges, FILE *file);

void destroyEdges(int nodes, Edge **adj);

Graph *createGraph(int type, int nodes, int edges, FILE *file);

void destroyGraph(Graph *graph);

void bfs(Graph *graph, int n);

void dfs(Graph *graph, int n);

void dfs_rec(Graph *graph, int n);

void topological(Graph *graph);

void dijkstra(Graph *graph, int n);

void prim(Graph *graph);

void kruskal(Graph *graph);

int degree(Graph *graph, int node);

int indegree(Graph *graph, int node);

int outdegree(Graph *graph, int node);

#endif // GRAPH_H_INCLUDED
