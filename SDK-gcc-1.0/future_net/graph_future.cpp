#include "graph_future.h"
#include <queue>
#include <algorithm>
#include <iostream>
#include <stack>

void printVec(std::vector<int> v);
void printPath(Path & pa);

void GraphFuture::insertVertId(int num){
	if(vertIdMap.find(num) == vertIdMap.end()){
		vertIdMap[num] = get_vertexCount();
		set_vertexCount(get_vertexCount()+1);
	}
}


void GraphFuture::initAdj(){
	adj.clear();
	for(int i=0; i < get_vertexCount(); i++){
		gNodeFuture* node = new gNodeFuture(-1, i, 0, NULL);
		adj.push_back(node);
	}
}

void GraphFuture::initPassVert(std::vector<int> v){
	passVert.clear();
	for(unsigned int i = 0; i < v.size(); i++){
		passVert.push_back(getVertId(v[i]));
	}
}

/*
void GraphFuture::insert(int id, int v, int w, int weight){
	adj[v]->next = new gNodeFuture(id, w, weight, adj[v]->next);
	set_edgeCount(get_edgeCount()+1);
	if(!get_digraph()) adj[w]->next = new gNodeFuture(id, v, weight, adj[w]->next);
}*/

void GraphFuture::insert(int id, int v, int w, int weight){
    gNodeFuture *g = adj[v]->next,  *q = adj[v];
    while(g && weight > g->weight) {q =g; g = g->next;}
    q->next = new gNodeFuture(id, w, weight, g);
	set_edgeCount(get_edgeCount()+1);
	if(!get_digraph()) {
        insert(id, w, v, weight);
        set_edgeCount(get_edgeCount()-1);
    }
}

void GraphFuture::insert(int edge[4]){
	insert(edge[0], getVertId(edge[1]), getVertId(edge[2]), edge[3]);
}
int GraphFuture::FindEdgeId(int v, int w){
	gLinkFuture g = adj[v]->next;
	while(g!=NULL && g->vert !=w) g = g->next;
	return g ? g->edgeId : -1;
}

void GraphFuture::set_bestEdgePath(){
	bestEdgePath.clear();
	for(unsigned int i = 0; i < bestPath.size()-1; i++){
		bestEdgePath.push_back(FindEdgeId(bestPath[i], bestPath[i+1]));
	}
}

void GraphFuture::BruteForceBFS(){
    initBestPath();
    std::queue<Path> que;
    Path first;
    first.path.push_back(passVert[0]);
    first.passCnt = 1;
    que.push(first);
    while(!que.empty() && ((double)(clock() - startTime) / CLOCKS_PER_SEC) <MAX_RUNNING_TIME){
        Path pa = que.front();
        //printVec(pa.path);
        //printPath(pa);
        for(gLinkFuture g = adj[pa.path.back()]->next; g!=NULL; g=g->next){
            Path newPa(pa);
            if(std::find(newPa.path.begin(), newPa.path.end(), g->vert) != newPa.path.end())
                continue; // Loop
            if(g->vert == passVert[1] && newPa.passCnt != passVert.size()-1)
                continue; // go to end without enough pass vert.
            if(std::find(passVert.begin(), passVert.end(), g->vert) != passVert.end())
                newPa.passCnt++;
            newPa.cost = newPa.cost + g->weight;
            newPa.path.push_back(g->vert);
            //std::cout<<"passcnt: "<<newPa.passCnt<<"\n";
            if(newPa.passCnt == passVert.size()){
                if(newPa.cost < minCost){
                    if(debug){
                        std::cout<<"find better path:\n";
                        printPath(newPa);
                    }
                    minCost = newPa.cost;
                    bestPath = newPa.path;
                }
                continue; // if all pass, don't find more.
            }
            que.push(newPa);
        }
        que.pop();
    }

    set_bestEdgePath();
}

void GraphFuture::BruteForceDFS(){
    initBestPath();
    Path first;
    first.path.push_back(passVert[0]);
    first.passCnt = 1;
    std::stack<Path> st;
    st.push(first);
    while(!st.empty() && ((double)(clock() - startTime) / CLOCKS_PER_SEC) <MAX_RUNNING_TIME ) {
        Path pa = st.top();
        st.pop();
        for(gLinkFuture g = adj[pa.path.back()]->next; g!=NULL; g=g->next){
            Path newPa(pa);
            if(std::find(newPa.path.begin(), newPa.path.end(), g->vert) != newPa.path.end())
                continue; // Loop
            if(g->vert == passVert[1] && newPa.passCnt != passVert.size()-1)
                continue; // go to end without enough pass vert.
            if(std::find(passVert.begin(), passVert.end(), g->vert) != passVert.end())
                newPa.passCnt++;
            newPa.cost = newPa.cost + g->weight;
            newPa.path.push_back(g->vert);
            //std::cout<<"passcnt: "<<newPa.passCnt<<"\n";
            if(newPa.passCnt == passVert.size()){
                if(newPa.cost < minCost){
                    if(debug){
                        std::cout<<"find better path:\n";
                        printPath(newPa);
                    }
                    minCost = newPa.cost;
                    bestPath = newPa.path;
                }
                continue; // if all pass, don't find more.
            }
            st.push(newPa);
        }

    }
    //BruteForceDFS(first);
    set_bestEdgePath();
}

// 递归式深度搜索，未完成
void GraphFuture::BruteForceDFS(Path & pa){
    if(((double)(clock() - startTime) / CLOCKS_PER_SEC) <MAX_RUNNING_TIME)
        return;
    if(pa.passCnt == passVert.size()){
        if(pa.cost < minCost){
            if(debug){
                std::cout<<"find better path:\n";
                printPath(pa);
            }
            minCost = pa.cost;
            bestPath = pa.path;
        }
        return;
    }
    for(gLinkFuture g = adj[pa.path.back()]->next; g!=NULL; g=g->next){
    }
}

void GraphFuture::printPassVert(){
	for(unsigned int i = 0; i < passVert.size(); i++)
		std::cout<<passVert[i]<<" ";
	std::cout<<"\n\n";
}

void GraphFuture::printBestEdgePath(){
	for(unsigned int i = 0; i < bestEdgePath.size(); i++)
		std::cout<<bestEdgePath[i]<<" ";
	std::cout<<"\n\n";
}

void GraphFuture::printAllEdge(){
	for(unsigned int i = 0; i < adj.size(); i++){
		gLinkFuture g = adj[i]->next;
		std::cout<<i<<":";
		while(g!=NULL){
			std::cout<<g->vert<<" ";
			g = g->next;
		}
		std::cout<<"\n";
	}
    std::cout<<"\n";
}

void printVec(std::vector<int> v){
    for(unsigned int i =0; i< v.size(); i++)
        std::cout<<v[i]<<" ";
    std::cout<<"\n";
}

void printPath(Path & pa){
    std::cout<<"Path: ";
    for(unsigned int i =0; i< pa.path.size(); i++)
        std::cout<<pa.path[i]<<" ";
    std::cout<<"\n";
    std::cout<<"cost: "<<pa.cost<<"\n";
    std::cout<<"passCnt: "<<pa.passCnt<<"\n\n";
}
