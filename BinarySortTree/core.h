//
// Created by 梁竞 on 2017/11/17.
//

#ifndef BINARYSORTTREE_CORE_H
#define BINARYSORTTREE_CORE_H

#endif //BINARYSORTTREE_CORE_H

#include <stdio.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0
typedef int Status;   //Status是函数的类型,其值是函数结果状态代码，如TRUE等

/**
 * 二叉树的二叉链表结点结构定义
 */
typedef struct BiTNode {  //结点结构

    int data;   //结点数据

    struct BiTNode *lchild, *rchild;  //左右孩子指针

} BiTNode, *BiTree;

//函数声明(因为在DeleteBST函数中需要调用Delete函数)
Status Delete(BiTree *p);

/**
 * function:递归查找二叉排序树T中是否存在key,
 *          指针f指向T的双亲，其初始调用值为NULL
 *          若查找成功，则指针p指向该数据元素结点，并返回TRUE
 *          否则指针p指向查找路径上访问的最后一个结点并返回FALSE
 * @param T
 * @param key
 * @param f
 * @param p
 * @return
 */
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p) {

    if (!T) {
        *p = f;
        return FALSE;
    } else if (key == T->data) {
        *p = T;
        return TRUE;
    } else if (key < T->data) {
        return SearchBST(T->lchild, key, T, p);  /*  在左子树中继续查找 */
    } else {
        return SearchBST(T->rchild, key, T, p);   /*  在右子树中继续查找 */
    }
}


/**
 * function:当二叉排序树T中不存在关键字等于key的数据元素时，
 *          插入key并返回TRUE，否则返回FALSE
 * @param T
 * @param key
 * @return
 */
Status InsertBST(BiTree *T, int key) {

    BiTree p, s;

    //查找不成功
    if (!SearchBST(*T, key, NULL, &p)) {

        //开辟内存空间
        s = (BiTree) malloc(sizeof(BiTNode));
        s->data = key;
        s->lchild = s->rchild = NULL;
        if (!p) {
            *T = s;   //插入s为新的根结点
        } else if (key < p->data) {
            p->lchild = s;  //插入s为左孩子
        } else {
            p->rchild = s;   //插入s为右孩子
        }

        return TRUE;
    } else {


        return FALSE;  //树中已经有关键字相同的结点，不再插入。
    }

}


/**
 * function: 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点,
 * 并返回TRUE；否则返回FALSE。
 * @param T
 * @param key
 * @return
 */
Status DeleteBST(BiTree *T, int key) {

    //不存在关键字等于key的数据元素（即指针的内容为空，并没有指向某个地址）
    if (!*T) {
        return FALSE;
    } else {
        if (key == (*T)->data) {   //找到关键字等于key的数据元素
            return Delete(T);
        } else if (key < (*T)->data) {
            return DeleteBST(&(*T)->lchild, key);
        } else {
            return DeleteBST(&(*T)->rchild, key);
        }
    }
}

/*
 * function:从二叉排序树中删除结点p，并重接它的左或右子树。
 * @param p
 * @return
 */
Status Delete(BiTree *p) {

    BiTree q, s;
    if ((*p)->rchild == NULL) {   //右子树空则只需重接它的左子树（待删结点是叶子结点也走此分支)
        q = *p;
        *p = (*p)->lchild;
        free(q);
    } else if ((*p)->lchild == NULL) {   //只需重接它的右子树
        q = *p;
        *p = (*p)->rchild;
        free(q);
    } else {   //左右子树均不空
        q = *p;
        s = (*p)->lchild;
        while (s->rchild) {   //转左，然后向右到尽头（找待删结点的前驱）
            q = s;
            s = s->rchild;
        }
        (*p)->data = s->data;    //s指向被删结点的直接前驱（将被删结点前驱的值取代被删结点的值）q指向的结点是s指向的结点的父结点

        //若if语句里面的条件不成立则说明待删除的结点的左子树只有一个结点
        if (q != *p)
            q->rchild = s->lchild;    //重接q的右子树
        else
            q->lchild = s->lchild;    //重接q的左子树
        free(s);
    }

    return TRUE;
}













