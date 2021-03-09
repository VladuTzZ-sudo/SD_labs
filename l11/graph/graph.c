#include "graph.h"

Edge **createEdges(int type, int nodes, int edges, FILE *file)
{
	Edge **adj = malloc(nodes * sizeof(Edge *));
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
		adj[i][NR_NEIGHBOURS].n = 0;
		adj[i][NR_NEIGHBOURS].w = 0;
	}
	for (int i = 0; i < edges; i++) {
		int u, v, w;
		fscanf(file, "%d%d%d", &u, &v, &w);
		adj[u][adj[u][NR_NEIGHBOURS].n].n = v;
		adj[u][adj[u][NR_NEIGHBOURS].n].w = w;
		adj[u][NR_NEIGHBOURS].n++;
		if (type == TYPE_UNDIRECTED) {
			adj[v][adj[v][NR_NEIGHBOURS].n].n = u;
			adj[v][adj[v][NR_NEIGHBOURS].n].w = w;
			adj[v][NR_NEIGHBOURS].n++;
		}
	}
	return adj;
}

void destroyEdges(int nodes, Edge **adj)
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
	graph->edges = edges;
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
	while (!isEmptyQueue(q)) {
		n = dequeue(q);
		printf("%d ", n);
		for (int i = 0; i < graph->adj[n][NR_NEIGHBOURS].n; i++) {
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
	while (!isEmptyStack(s)) {
		n = pop(s);
		printf("%d ", n);
		for (int i = 0; i < graph->adj[n][NR_NEIGHBOURS].n; i++) {
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
	for (int i = graph->adj[n][NR_NEIGHBOURS].n - 1; i >= 0; i--) {
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

/*
6 6
5 2 1
5 0 1
4 0 1
4 1 1
2 3 1
3 1 1
*/
void topological_util(Graph *graph, int n, int *visited, Stack *s)
{
	for (int i = 0; i < graph->adj[n][NR_NEIGHBOURS].n; i++) {
		if (visited[graph->adj[n][i].n])
			continue;
		visited[graph->adj[n][i].n] = 1;
		topological_util(graph, graph->adj[n][i].n, visited, s);
	}
	push(s, n);
}

void topological(Graph *graph)
{
	/* TODO 3 */
	Stack *s = createStack();
	int *visited = calloc(graph->nodes, sizeof(int));
	for (int i = 0; i < graph->nodes; i++) {
		if (!visited[i]) {
			visited[i] = 1;
			topological_util(graph, i, visited, s);
		}
	}
	while (!isEmptyStack(s)) {
		printf("%d ", pop(s));
	}
	printf("\n");
}

void printPath(int *parent, int n)
{
	if (parent[n] == NO) {
		printf("%d ", n);
		return;
	}
	printPath(parent, parent[n]);
	printf("%d ", n);
}

void dijkstra(Graph *graph, int n)
{
	/* TODO 4.a */
	Heap *h = createHeap(graph->nodes);
	int *parent = malloc(graph->nodes * sizeof(int));
	int *dist = malloc(graph->nodes * sizeof(int));
	parent[n] = NO;
	dist[n] = 0;
	insert(h, dist[n], n);
	for (int i = 0; i < graph->nodes; i++) {
		if (i == n)
			continue;
		parent[i] = NO;
		dist[i] = INF;
		insert(h, dist[i], i);
	}
	while (!isEmptyHeap(h)) {
		n = extract(h);
		for (int i = 0; i < graph->adj[n][NR_NEIGHBOURS].n; i++) {
			if (inHeap(h, graph->adj[n][i].n) && dist[n] != INF &&
				graph->adj[n][i].w + dist[n] < dist[graph->adj[n][i].n]) {
				parent[graph->adj[n][i].n] = n;
				dist[graph->adj[n][i].n] = dist[n] + graph->adj[n][i].w;
				decreasePriority(h, dist[graph->adj[n][i].n], graph->adj[n][i].n);
			}
		}
	}
	/* TODO 4.b */
	for (int i = 0; i < graph->nodes; i++) {
		printf("%d (%d): ", i, dist[i]);
		printPath(parent, i);
		printf("\n");
	}
	printf("\n");
	free(parent);
	free(dist);
	destroyHeap(h);
}

void prim(Graph *graph)
{
	/* TODO 5.a */
	Heap *h = createHeap(graph->nodes);
	int *parent = malloc(graph->nodes * sizeof(int));
	int *key = malloc(graph->nodes * sizeof(int));
	int n = 0;
	parent[n] = NO;
	key[n] = 0;
	insert(h, key[n], n);
	for (int i = 0; i < graph->nodes; i++) {
		if (i == n)
			continue;
		parent[i] = NO;
		key[i] = INF;
		insert(h, key[i], i);
	}
	while ( !isEmptyHeap(h) ) {
		n = extract(h);
		for ( int i = 0 ; i < graph->adj[n][NR_NEIGHBOURS].n; i++ ) {
			if ( inHeap(h, graph->adj[n][i].n) &&
			graph->adj[n][i].w < key[graph->adj[n][i].n]){
				parent[graph->adj[n][i].n] = n;
				key[graph->adj[n][i].n] = graph->adj[n][i].w;
				decreasePriority(h,key[graph->adj[n][i].n], graph->adj[n][i].n);
			}
		}
	}
	/* TODO 5.b */
	/* print minimum spanning tree */
	printf("PRIM\n");
	for ( int i = 0 ; i < graph->nodes ; i++ ){
		printf("%d - %d\n", parent[i], i);
	}
	printf("\n");
	free(parent);
	free(key);
	destroyHeap(h);
}

typedef struct 
{
	int s, d, w;
} NewEdge;


int compareEdge(const void *e1, const void *e2)
{
	return (*(NewEdge *) e1).w - (*(NewEdge *) e2).w;
}

typedef struct 
{
	int p;
	int r;
} Subset;

int find(Subset *subsets, int n) {
	if ( subsets[n].p != n){
		subsets[n].p = find(subsets, subsets[n].p);
	}
	return subsets[n].p;
}

void Union(Subset *subsets, int n1, int n2) {
	int r1 = find(subsets, n1);
	int r2 = find(subsets, n2);

	if (subsets[r1].r < subsets[r2].r)
		subsets[r1].p = r2;
	else if (subsets[r1].r > subsets[r2].r)
		subsets[r2].p = r1; 
	else  {
		subsets[r2].p = r1;
		subsets[r1].r++;
	}
}

void kruskal(Graph *graph)
{
	NewEdge *edges = malloc(graph->edges * sizeof(NewEdge));
	NewEdge *result = malloc(graph->nodes * sizeof(NewEdge));
	Subset *subsets = malloc(graph->nodes * sizeof(Subset));
	int e = 0;
	for ( int n = 0 ; n < graph->nodes ; n++ ){
		for ( int i = 0 ; i < graph->adj[n][NR_NEIGHBOURS].n; i++ ){
			edges[e].s = n;
			edges[e].d = graph->adj[n][i].n;
			edges[e].w = graph->adj[n][i].w;
			e++;
  		}
		subsets[n].p = n;
		subsets[n].r = 0;
 	}
	qsort(edges, e, sizeof(NewEdge), compareEdge);
	e = 0;
	for ( int i = 0 ; i < graph->edges && e < graph->nodes ; i++){
		int x = find(subsets, edges[i].s);
		int y = find(subsets, edges[i].d);
		if ( x != y) {
			result[e] = edges[i];
			Union(subsets, x ,y);
			e++;
		}
	}
	printf("KRUSKAL\n");
	for ( int i = 0; i < e ; i++ ){
		printf("%d - %d\n", result[i].s, result[i].d);
	}
	printf("\n");
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
	for (int j = 0; j < graph->nodes; j++) {
		if (j == node)
			continue;
		for (int i = 0; i < graph->adj[j][NR_NEIGHBOURS].n; i++) {
			if (graph->adj[j][i].n == node) {
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
