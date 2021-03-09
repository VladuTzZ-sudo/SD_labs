#include "graph.h"

int **createEdges(int type, int nodes, int edges, FILE *file)
{
	int **adj = malloc(nodes * sizeof(int *));
	if (adj == NULL)
		return NULL;
	for (int i = 0; i < nodes; i++) {
		adj[i] = malloc((nodes + 1) * sizeof(int));
		if (adj[i] == NULL) {
			for (int j = 0; j < i; j++) {
				free(adj[j] - 1);
			}
			free(adj);
			return NULL;
		}
		adj[i] = adj[i] + 1; /* offset: adj[i][-1] number of nodes */
		adj[i][NR_NEIGHBOURS] = 0;
	}
	for (int i = 0; i < edges; i++) {
		int u, v;
		fscanf(file, "%d%d", &u, &v);
		adj[u][adj[u][NR_NEIGHBOURS]] = v;
		adj[u][NR_NEIGHBOURS]++;
		if (type == TYPE_UNDIRECTED) {
			adj[v][adj[v][NR_NEIGHBOURS]] = u;
			adj[v][NR_NEIGHBOURS]++;
		}
	}
	return adj;
}

void destroyEdges(int nodes, int **adj)
{
	for (int i = 0; i < nodes; i++) {
		free(adj[i] - 1); /* offset: adj[i][-1] number of nodes */
	}
	free(adj);
}

Graph *createGraph(int type, int nodes, int edges, FILE *file)
{
	Graph *graph = malloc(sizeof(Graph));
	if (graph == NULL)
		return NULL;
	graph->type = type;
	graph->nodes = nodes;
	graph->adj = createEdges(type, nodes, edges, file);
	return graph;
}

void destroyGraph(Graph *graph)
{
	destroyEdges(graph->nodes, graph->adj);
	free(graph);
}

void bfs(Graph *graph, int n)
{
	Queue *v = createQueue();
	int i;
	int *visited = calloc(graph->nodes, sizeof(int));
	visited[n] = 1;
	enqueue(v, n);
	while(!isEmptyQueue(v))
	{
		n = dequeue(v);
		printf("%d ", n);
		for(i = 0; i < graph->adj[n][NR_NEIGHBOURS]; i++)
		{
			if(visited[graph->adj[n][i]])
				continue;
			visited[graph->adj[n][i]] = 1;
			enqueue(v, graph->adj[n][i]);
		}
	}
	printf("\n");
	free(visited);
	destroyQueue(v);
}

void dfs(Graph *graph, int n)
{
	Stack *s = createStack();
	int i;
	int *visited = calloc(graph->nodes, sizeof(int));
	visited[n] = 1;
	push(s, n);
	while(!isEmptyStack(s))
	{
		n = pop(s);
		printf("%d ", n);
		for(i = 0; i < graph->adj[n][NR_NEIGHBOURS]; i++)
		{
			if(visited[graph->adj[n][i]])
				continue;
			visited[graph->adj[n][i]] = 1;
			push(s, graph->adj[n][i]);
		}
	}
	printf("\n");
	free(visited);
	destroyStack(s);
}

int degree(Graph *graph, int node)
{
	return graph->adj[node][NR_NEIGHBOURS];
}

int indegree(Graph *graph, int node)
{
	int contor = 0;
	int j,i;
	for (j = 0; j < graph->nodes; j++)
	{
		if(j == node)
			continue;
		for(i = 0; i < graph->adj[j][NR_NEIGHBOURS]; i++)
		{
			if(graph->adj[j][i] == node)
			{
				contor++;
				break;
			}
		}
	}
	return contor;
}

int outdegree(Graph *graph, int node)
{
	return graph->adj[node][NR_NEIGHBOURS];
}
