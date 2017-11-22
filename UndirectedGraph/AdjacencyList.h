//
// Created by 梁竞 on 2017/11/21.
//

#ifndef UNDIRECTEDGRAPH_ADJACENCYLIST_H
#define UNDIRECTEDGRAPH_ADJACENCYLIST_H

#endif //UNDIRECTEDGRAPH_ADJACENCYLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef char VertexType;  //顶点类型(可自定义)
typedef int EdgeType;  //边上的权值类型(可自定义)
typedef int Status;
typedef int Boolean;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROE 0
#define MAXSIZE 10 //存储空间初始分配量

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
} VertexNode, AdjList[10];

//图的邻接表存储结构
typedef struct {
    AdjList adjList;
    int numNodes, numEdges; //图中当前顶点数和边数
} GraphAdjList;

//邻接表的广度优先遍历算法需要利用到的队列结构(循环队列的顺序存储结构)
typedef struct {
    int data[10];
    int front;  //头指针
    int rear;   //尾指针，若队列不为空，指向队尾元素的下一个位置
} Queue;


void printVertexNode(GraphAdjList *G);

void createALGraph(GraphAdjList *G);

Status judgeEdge(int i, int j, GraphAdjList *G);

void DFS(GraphAdjList *G, int i);

void DFSTraverse(GraphAdjList G);

void BFSTraverse(GraphAdjList G);

Status initQueue(Queue *Q);

Status QueueEmpty(Queue Q);

Status EnQueue(Queue *Q, int e);

Status DeQueue(Queue *Q, int *e);


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


//访问标志的数组
Boolean visited[100];

/**
 * function:邻接表的深度优先递归算法
 * @param G
 */
void DFS(GraphAdjList *G, int i) {

    EdgeNode *p;
    visited[i] = TRUE;
    //打印顶点
    printf("%c", G->adjList[i].data);
    p = G->adjList[i].firstEdge;
    while (p) {
        if (!visited[p->adjvex]) {
            DFS(G, p->adjvex);      //对未访问的邻接顶点递归调用进行访问
        }
        p = p->next;
    }
}


/**
 * function:邻接表的深度优先遍历操作
 * @param G
 */
void DFSTraverse(GraphAdjList G) {

    int i;

    //初始所有顶点都是未访问状态
    for (i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
    }


    for (i = 0; i < G.numNodes; i++) {
        if (!visited[i]) {
            //对未访问过的顶点调用DFS，若是连通图，则只会执行一次
            DFS(&G, i);
        }
    }

}


/**
 * function:邻接表的广度优先遍历算法
 * @param G
 */
void BFSTraverse(GraphAdjList G) {

    int i;
    EdgeNode *p;
    Queue Q;

    //初始所有顶点都是未访问状态
    for (i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
    }

    //初始化队列
    initQueue(&Q);
    for (i = 0; i < G.numNodes; i++) {

        //如果未被访问过
        if (!visited[i]) {
            visited[i] = TRUE;
            printf("%c", G.adjList[i].data); //打印顶点
            EnQueue(&Q, i);
            while (!QueueEmpty(Q)) {
                DeQueue(&Q, &i);
                p = G.adjList[i].firstEdge; //找到出队列的那个元素顶点的边表链表头指针
                while (p) {

                    //若该顶点没有被访问过
                    if (!visited[p->adjvex]) {
                        visited[p->adjvex] = TRUE;
                        printf("%c ", G.adjList[p->adjvex].data); //打印该顶点
                        EnQueue(&Q, p->adjvex);  //将此顶点进入队列
                    }
                    p = p->next; //指针指向下一个邻接点
                }
            }
        }
    }
}

/**
 * function:初始化一个空队列
 * @param Q
 * @return
 */
Status initQueue(Queue *Q) {
    Q->front = 0;
    Q->rear = 0;
    return OK;
}


/**
 * function:若队列Q为空队列，则返回TRUE，否则返回FALSE
 * @param Q
 * @return
 */
Status QueueEmpty(Queue Q) {

    //队列为空的标志
    if (Q.front == Q.rear) {
        return TRUE;
    } else {
        return FALSE;
    }

}


/**
 * function:若队列未满，则插入元素e为Q新的队尾元素
 * @param Q
 * @param e
 * @return
 */
Status EnQueue(Queue *Q, int e) {

    //队列满的判断(保留一个元素空间，也就是说，当队列满时，数组中还有一个空闲单元。此时就认为队列已经满了)
    if ((Q->rear + 1) % MAXSIZE == Q->front)
        return ERROE;

    Q->data[Q->rear] = e; //将元素e赋值给队尾
    Q->rear = (Q->rear + 1) % MAXSIZE; //rear指针向后移一位置.若到最后则转到数组头部o
    return OK;
}


/**
 * function:若队列不为空，则删除Q中队头元素，用e返回其值
 * @param Q
 * @param e
 * @return
 */
Status DeQueue(Queue *Q, int *e) {

    //队列空的判断
    if (Q->front == Q->rear)
        return ERROE;
    *e = Q->data[Q->front];  //将队头元素赋值给e
    Q->front = (Q->front + 1) % MAXSIZE; //front指针向后移一位。若到最后则会转到数组头部
    return OK;
}



