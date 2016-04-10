#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <map>
#include <stdlib.h>
#include "time.h"

/*
#include<limits>
const int INT_INF = std::numeric_limits<int>::max();
*/
#define  MAX_INT_NUM 0x7fffffff
struct gNode{
	int vert;
	int weight;
	gNode *next;
	gNode(int v, int w, gNode *t){
		vert = v;
		weight = w;
		next = t;
	}
};
typedef gNode* gLink;
class Graph{
	int vertCount;
	int edgeCount;
	bool digraph;
	//int minCost;
	//bool debug; //debug决定是否输出一些中间过程
	//clock_t startTime;
	std::vector<bool> visited;
	//std::vector<int> bestPath; // 最优路径的顶点序列
	//std::vector<int> bestEdgePath; // 最优路径的边序列
	//std::map<int ,int > vertIdMap;// source Id -> Graph Id
	//int edgeId[MAX_VERT_NUM][MAX_VERT_NUM]; // store the map between edge id and id; do not use at now.
	std::vector<gLink> adj;

	//std::vector<int> passVert; //demand 顶点序列
public:
	Graph():
		vertCount(0), edgeCount(0), digraph(false){}
	Graph(int V, bool dig = false);
	Graph(bool dig = false) { digraph = dig; vertCount = 0;edgeCount =0; }
	int get_vertexCount(){ return vertCount;}
	void set_vertexCount(int vert){ vertCount = vert;}
	int get_edgeCount(){ return edgeCount;}
	void set_edgeCount(int edge){ edgeCount = edge;}
	int get_digraph(){ return digraph;}
	void set_digraph(bool dig) { digraph = dig;}
	int get_visited(int vert){ return visited[vert];}
	void set_visited(int vert){ visited[vert] = true;}
	gLink get_adj(int vert){ return adj[vert];};

	gLink FindFirstAdj(int vert) { return adj[vert]->next;}
	gLink FindNextAdj(int v, int w);

	void insert(int v, int w, int weight = 1);

	bool CheckEdge(int v, int w) ;

	void clear_visited(){ visited.assign(vertCount, false);}

	void DFS(int vert = 0);
	void BFS(int vert = 0);
	std::vector<int> TopoSort();

	void printAllEdge();

};

#endif
