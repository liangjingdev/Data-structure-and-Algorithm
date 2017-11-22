//
// Created by 梁竞 on 2017/11/21.
//

#ifndef UNDIRECTEDGRAPH_ADJACENCYLIST_H
#define UNDIRECTEDGRAPH_ADJACENCYLIST_H

#endif //UNDIRECTEDGRAPH_ADJACENCYLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <MacTypes.h>

typedef char VertexType;  //顶点类型(可自定义)
typedef int EdgeType;  //边上的权值类型(可自定义)
typedef int Status;
#define TRUE 1;
#define FALSE 0;

//边表结点
typedef struct EdgeNode {

    int adjvex; //邻接点域，存储该顶点在顶点表中对应的下标值
    EdgeType info; //用于存储权值，对于非网可不需要
    struct EdgeNode *next; //链域，指向下一个邻接点
} EdgeNode;


//顶点表结点
typedef struct VertexNode {
    VertexType data; //顶点域，存储顶点信息
    EdgeNode *firstEdge; //边表头指针
} VertexNode, AdjList[100];

//图的邻接表存储结构
typedef struct {
    AdjList adjList;
    int numNodes, numEdges; //图中当前顶点数和边数
} GraphAdjList;


void printVertexNode(GraphAdjList *G);

void createALGraph(GraphAdjList *G);


/**
 * function:建立图的邻接表结构
 */
void createALGraph(GraphAdjList *G) {

    int i, j, k, w;
    EdgeNode *e;
    printf("请输入顶点数和边数：\n");
    scanf("%d,%d", &G->numNodes, &G->numEdges);//输入顶点数和边数
    getchar();

    //读入顶点信息，建立顶点表
    for (i = 0; i < G->numNodes; i++) {
        printf("请输入顶点：");
        scanf("%c", &G->adjList[i].data);  //输入顶点信息
        getchar();
        G->adjList[i].firstEdge = NULL;  //起始时，将边表置为空表
    }


    //打印当前顶点表信息
    printVertexNode(G);
    printf("\n");

    //建立边表
    for (k = 0; k < G->numEdges; k++) {
        printf("请输入边(vi,vj)的顶点序号以及权值w：");
        scanf("%d,%d,%d", &i, &j, &w);    //输入边(vi,vj)上的顶点序号

        //判断输入的i和j的值是否超过图当前的顶点数,考虑到代码的健壮性
        if (i >= G->numNodes || j >= G->numNodes) {
            printf("输入顶点的序号有误，请重新输入:");
            scanf("%d,%d,%d", &i, &j, &w);    //输入边(vi,vj)上的顶点序号
        }


        //顶点i的边表(头插法)
        e = (EdgeNode *) malloc(sizeof(EdgeNode)); //向内存申请空间，生成边表结点
        e->adjvex = j;  //邻接序号为j
        e->info = w;
        e->next = G->adjList[i].firstEdge; //1、将e的next指针指向当前顶点i的边表头指针所指向的结点
        G->adjList[i].firstEdge = e;  //2、然后将当前顶点i的边表头指针指向e


        //顶点j的边表--由于是无向图。(所以一条边对应的是两个顶点)
        e = (EdgeNode *) malloc(sizeof(EdgeNode)); //向内存申请空间，生成边表结点
        e->adjvex = i;  //邻接序号为j
        e->info = w;
        e->next = G->adjList[j].firstEdge; //1、将e的next指针指向当前顶点i的边表头指针所指向的结点
        G->adjList[j].firstEdge = e;  //2、然后将当前顶点i的边表头指针指向e
    }

};


/**
 * function:打印顶点表信息
 */
void printVertexNode(GraphAdjList *G) {
    printf("当前的顶点表信息：");
    //打印目前的顶点
    for (int i = 0; i < G->numNodes; i++) {
        printf("v%d=%c ", i, G->adjList[i].data);
    }
}


/**
 * function:判断两个顶点之间是否存在边,若存在则返回1且打印出权值。若不存在则返回0.
 * @param i
 * @param j
 * @return
 */
Status judgeEdge(int i, int j, GraphAdjList *G) {

    EdgeNode *e;
    e = (EdgeNode *) malloc(sizeof(EdgeNode));
    e = G->adjList[i].firstEdge;

    while (e != NULL) {
        if (e->adjvex == j) {
            printf("该两顶点间存在边且权值为：%d\n", e->info);
            //释放内存空间
            free(e);
            return TRUE;
        }
        e = e->next;
    }

    //释放内存空间
    free(e);
    printf("该两顶点间不存在边。\n");
    return FALSE;
}













