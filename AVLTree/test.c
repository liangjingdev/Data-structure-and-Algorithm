#include <stdio.h>
#include "core.h"

//函数声明
void InOrderTraverse(BiTree T);

int Height(BiTree T);

void print(BiTree T, int data, int direction);

int main() {
    int i;
    int a[16] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
    BiTree T = NULL;
    int taller;
    for (i = 0; i < 16; i++) {
        InsertAVL(&T, a[i], &taller);
    }
    printf("对该AVL树进行中序遍历，结果为：");
    InOrderTraverse(T);
    printf("\n");
    printf("AVL树的高度为:%d", Height(T));
    printf("\n");
    printf("下面打印AVL树的详细信息：\n");
    print(T, T->data, 0);
    return 0;
}


/**
 * function:对二叉排序树进行中序遍历
 * @param T
 */
void InOrderTraverse(BiTree T) {

    if (T == NULL) {
        return;
    }
    InOrderTraverse(T->lchild);
    printf("%d ", T->data);
    InOrderTraverse(T->rchild);
}

/**
 * function:求二叉树高度
 * @param T
 * @return
 */
int Height(BiTree T) {
    int L, R;
    if (NULL == T)
        return 0;
    else {
        L = Height(T->lchild);
        R = Height(T->rchild);
        return L > R ? L + 1 : R + 1;
    }
}

/**
 * function:打印详细信息--递归实现
 *
 * T       -- AVL树的节点
 * data        -- 节点的键值
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 * @param T
 */
void print(BiTree T, int data, int direction) {

    if (T != NULL) {
        if (direction == 0)    // T是根节点
            printf("%2d is root\n", T->data);
        else                // T是分支节点
            printf("%2d is %2d's %6s child\n", T->data, data, direction == 1 ? "right" : "left");

        print(T->lchild, T->data, -1);
        print(T->rchild, T->data, 1);
    }
}