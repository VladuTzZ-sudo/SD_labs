#include "graph.h"

Edge **createEdges(int type, int nodes, int edges, FILE *file)
{
	Edge **adj = malloc(nodes * sizeof(Edge *));
	if (adj == NULL)
		return NULL;
	for (int i = 0; i < nodes; i++)
	{
		adj[i] = malloc((nodes + 1) * sizeof(int));
		if (adj[i] == NULL)
		{
			for (int j = 0; j < i; j++)
			{
				free(adj[j] - 1);
			}
			free(adj);
			return NULL;
		}
		adj[i] = adj[i] + 1; /* offset: adj[i][-1] number of nodes */
		adj[i][NR_NEIGHBOURS].n = 0;
		adj[i][NR_NEIGHBOURS].w = 0;
	}
	for (int i = 0; i < edges; i++)
	{
		int u, v, w;
		fscanf(file, "%d%d%d", &u, &v, &w);
		adj[u][adj[u][NR_NEIGHBOURS].n].n = v;
		adj[u][adj[u][NR_NEIGHBOURS].n].w = w;
		adj[u][NR_NEIGHBOURS].n++;
		if (type == TYPE_UNDIRECTED)
		{
			adj[v][adj[v][NR_NEIGHBOURS].n].n = u;
			adj[v][adj[v][NR_NEIGHBOURS].n].w = w;
			adj[v][NR_NEIGHBOURS].n++;
		}
	}
	return adj;
}

void destroyEdges(int nodes, Edge **adj)
{
	for (int i = 0; i < nodes; i++)
	{
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
	/* TODO 1 */
	Queue *q = createQueue();
	int *visited = calloc(graph->nodes, sizeof(int));
	visited[n] = 1;
	enqueue(q, n);
	while (!isEmptyQueue(q))
	{
		n = dequeue(q);
		printf("%d ", n);
		for (int i = 0; i < graph->adj[n][NR_NEIGHBOURS].n; i++)
		{
			if (visited[graph->adj[n][i].n])
				continue;
			visited[graph->adj[n][i].n] = 1;
			enqueue(q, graph->adj[n][i].n);
		}
	}
	printf("\n");
	free(visited);
	destroyQueue(q);
}

void dfs(Graph *graph, int n)
{
	/* TODO 2 */
	Stack *s = createStack();
	int *visited = calloc(graph->nodes, sizeof(int));
	visited[n] = 1;
	push(s, n);
	while (!isEmptyStack(s))
	{
		n = pop(s);
		printf("%d ", n);
		for (int i = 0; i < graph->adj[n][NR_NEIGHBOURS].n; i++)
		{
			if (visited[graph->adj[n][i].n])
				continue;
			visited[graph->adj[n][i].n] = 1;
			push(s, graph->adj[n][i].n);
		}
	}
	printf("\n");
	free(visited);
	destroyStack(s);
}

void dfs_util(Graph *graph, int n, int *visited)
{
	printf("%d ", n);
	//for (int i = 0; i < graph->adj[n][NR_NEIGHBOURS].n; i++) {
	for (int i = graph->adj[n][NR_NEIGHBOURS].n - 1; i >= 0; i--)
	{
		if (visited[graph->adj[n][i].n])
			continue;
		visited[graph->adj[n][i].n] = 1;
		dfs_util(graph, graph->adj[n][i].n, visited);
	}
}

void dfs_rec(Graph *graph, int n)
{
	int *visited = calloc(graph->nodes, sizeof(int));
	visited[n] = 1;
	dfs_util(graph, n, visited);
	printf("\n");
	free(visited);
}

void topological(Graph *graph)
{
	Stack *s;
	s = createStack();
	int *visited;
	visited = (int *)calloc(graph->nodes, sizeof(int));
	int i;
	int j;
	for (i = 0; i < graph->nodes; i++)
	{
		if (visited[i] == 0)
		{
			ts(graph, i, visited, s);
		}
	}
	while (isEmptyStack(s) != 1)
	{
		j = pop(s);
		printf("%d", j);
	}
	/* TODO 3 */
}

void dijkstra(Graph *graph, int n)
{
	Heap *MinHeap = createHeap(graph->nodes);
	int *distanta;
	Queue *coada;
	coada = createQueue();
	distanta = malloc(graph->nodes*sizeof(int));

	// INSERARE IN MINHEAP - primul element;
	distanta[n] = 0;
	insert(MinHeap, distanta[n], n);

	// INSERARE IN MINHEAP - restul de elemente;
	for (int i = 0; i < graph->nodes; ++i)
	{
		if (n != i)
		{
			distanta[i] = 3000;
			insert(MinHeap, distanta[i], i);
		}
	}
	// MAIN - DIJKSTRA
	while (isEmptyHeap(MinHeap) == 0)
	{
		int element;
		element = extract(MinHeap);
		//
		int cost;
		int j;
		for (j = 0; j < graph->adj[element][NR_NEIGHBOURS].n; ++j)
		{
			//enqueue(coada,element);
			cost = graph->adj[element][j].w;
			if (distanta[graph->adj[element][j].n] > distanta[element] + cost)
			{
				//enqueue(coada,element);
				distanta[graph->adj[element][j].n] = distanta[element] + cost;
				insert(MinHeap, distanta[graph->adj[element][j].n], graph->adj[element][j].n);
			}
		}
	}

	int p;
	printf("Distante Dijkstra:\n");
	for (int i = 0; i < graph->nodes; i++)
	{
		printf("%d  ->  %d  =  %d\n", n, i, distanta[i]);
		/*while (isEmptyQueue(coada) == 0)
		{
			p = dequeue(coada);
			printf("%d ", p);
		}
		printf("\n");*/
	}
	destroyQueue(coada);
}

int degree(Graph *graph, int node)
{
	/* TODO 0.a */
	return graph->adj[node][NR_NEIGHBOURS].n;
}

int indegree(Graph *graph, int node)
{
	/* TODO 0.b */
	int in_d = 0;
	for (int j = 0; j < graph->nodes; j++)
	{
		if (j == node)
			continue;
		for (int i = 0; i < graph->adj[j][NR_NEIGHBOURS].n; i++)
		{
			if (graph->adj[j][i].n == node)
			{
				in_d++;
				break;
			}
		}
	}
	return in_d;
}

int outdegree(Graph *graph, int node)
{
	/* TODO 0.c */
	return graph->adj[node][NR_NEIGHBOURS].n;
}

void ts(Graph *Graph, int v, int *visited, Stack *s)
{
	visited[v] = 1;
	for (int w = 1; w <= Graph->nodes; w++)
	{
		if (arc(Graph, v, w) && !visited[w])
		{
			ts(Graph, w, visited, s);
		}
		//push(s,v);
	}
	push(s, v);
}

int arc(Graph *g, int v, int w)
{
	int i;
	int nr;
	nr = g->adj[v][NR_NEIGHBOURS].n;
	for (i = 0; i < nr; i++)
	{
		if (g->adj[v][i].n == w)
			return 1;
	}
	return 0;
}
