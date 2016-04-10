
#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <iostream>
#include "graph.h"
#include "graph_future.h"
#include <vector>
void getEdgeInfo(char *edge, int a[4]);
std::vector<int> getPassVert(char *demand);
//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
    GraphFuture G(true);
    G.set_debug(false);
    // unsigned short result[] = {2, 6, 3};//示例中的一个解
    if(G.get_debug()){
        for(int i =0; i<edge_num; i++){
            for(int j=0; *(topo[i] + j) !='\0'; j++)
            	std::cout<<topo[i][j];
            //
        }
        std::cout<<"\n\n";
    }

    int edge[4];
    //std::cout<<"hello"<<std::endl;
    for(int i = 0; i < edge_num; i++){
    	getEdgeInfo(topo[i], edge);
    	G.insertVertId(edge[1]);
    	G.insertVertId(edge[2]);
    	//G.insert(edge);
    }

    if(G.get_debug()) std::cout<<"VertNum: "<<G.get_vertexCount()<<"\n\n";

    G.initAdj();
    for(int i = 0; i < edge_num; i++){
    	getEdgeInfo(topo[i], edge);
    	G.insert(edge);
    }

    G.initPassVert(getPassVert(demand));

    if(G.get_debug()){
        std::cout<<"All edge list below: \n";
        G.printAllEdge();
        std::cout<<"pass vert: ";
        G.printPassVert();
    }

    //G.BruteForceBFS();

    if(G.get_debug()){
        std::cout<<"bestEdgePath: ";
        G.printBestEdgePath();
        std::cout<<"Time: "<<(double)(clock()-G.get_startTime())/ CLOCKS_PER_SEC<<"s\n";
    }

    //G.reset_startTime();
    G.BruteForceDFS();

    if(G.get_debug()){
        std::cout<<"bestEdgePath: ";
        G.printBestEdgePath();
        std::cout<<"Time: "<<(double)(clock()-G.get_startTime())/ CLOCKS_PER_SEC<<"s\n";
    }

    std::vector<int> res = G.get_bestEdgePath();
    for (unsigned int i = 0; i < res.size(); i++)
        record_result(res[i]);
}

void getEdgeInfo(char *edge, int a[4]){
	int num = 0;
	int i = 0, j = 0;
	while(j < 4){
		num = 0;
		while(edge[i]!='\0' && edge[i]!=',' && edge[i]!='\n' && edge[i]!=-1){

			num = num*10 + edge[i] - '0';
			//std::cout<<edge[i]<<"\n";
			i++;
		}
		i++;
		//std::cout<<num<<" ";
		a[j] = num;
		j++;
	}
	//std::cout<<std::endl;
}

std::vector<int> getPassVert(char *demand){
    int i = 0;
    std::vector<int> passVert;
    while(demand[i]!='\0'){
        int num = 0;
        while(demand[i]!='\0' && demand[i]!=',' && demand[i]!='|'
            && demand[i]!='\n' && demand[i]!=-1){
            num = num*10 + demand[i++] - '0';
        }
        //std::cout<<"num: "<<num<<" ";
        passVert.push_back(num);
        if(demand[i]=='\n' || demand[i] == -1)
            break;
        else
            i++;
    }
    return passVert;
}
