#include"graph.h"
#include<iostream>
#include<queue>
#include<list>
Graph::Graph(int V, bool dig){
	vertCount = V;
	edgeCount = 0;
	digraph = dig;
	visited.assign(V,false);
	for(int i=0; i < V; i++){
		gNode* node = new gNode(i, 0, NULL);
		adj.push_back(node);
	}
}

gLink Graph::FindNextAdj(int v, int w){
	gLink g = adj[v]->next;
	while(g!= NULL && g->vert != w ) g = g->next;
	return g ? g->next : g;
}

void Graph::insert(int v, int w, int weight){
	adj[v]->next = new gNode(w, weight, adj[v]->next);
	edgeCount++;
	if(!digraph) adj[w]->next = new gNode(v, weight, adj[w]->next);
}


bool Graph::CheckEdge(int v, int w) {
	for (gLink g = adj[v]->next; g != NULL; g=g->next) {
		if (g->vert == w)
			return true;
	}
	return false;
}

void Graph::DFS(int vert){
	visited[vert] = true;
	// std::cout<<"visit: "<<vert<<std::endl;
	for( gLink g = adj[vert]->next; g!=NULL; g=g->next){
		if(!visited[g->vert])
			DFS(g->vert);
	}
}

void Graph::BFS(int vert){
	visited[vert] = true;
	// std::cout<<"visit: "<<vert<<std::endl;
	std::queue<int> cq;
	cq.push(vert);
	int temp;
	while(!cq.empty()){
		temp = cq.front();
		cq.pop();
		for(gLink g = adj[temp]->next; g!=NULL; g=g->next){
			if(!visited[g->vert]){
				visited[g->vert] = true;
				// std::cout<<"visit: "<<g->vert<<std::endl;
				cq.push(g->vert);
			}
		}
	}
}

std::vector<int> Graph::TopoSort(){
	std::queue<int> cq;
	std::vector<int> degree;
	std::vector<int> topoSeq;
	degree.assign(vertCount, 0);
	for(int i = 0; i < vertCount; i++){
		for(gLink g = adj[i]->next; g!=NULL; g=g->next){
			degree[g->vert]++;
		}
	}
	for(int i = 0; i < vertCount; i++){
		if(degree[i] == 0){
			cq.push(i);
		}
		//std::cout<<"degree: "<<degree[i]<<std::endl;
	}
	int temp;
	while(!cq.empty()){
		temp = cq.front();
		cq.pop();
		topoSeq.push_back(temp);
		//std::cout<<"sort: "<<temp<<std::endl;
		for(gLink g = adj[temp]->next; g != NULL; g=g->next){
			degree[g->vert]--;
			if(degree[g->vert] == 0) cq.push(g->vert);
		}
	}
	return topoSeq;
}

void Graph::printAllEdge(){
	for(unsigned int i = 0; i < adj.size(); i++){
		gLink g = adj[i]->next;
		std::cout<<i<<":";
		while(g!=NULL){
			std::cout<<g->vert<<" ";
			g = g->next;
		}
		std::cout<<"\n";
	}
	std::cout<<"\n";
}
