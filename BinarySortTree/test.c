#include <stdio.h>
#include "core.h"

void InOrderTraverse(BiTree T);

int main(void) {

    int i;
    int a[10] = {66, 88, 54, 23, 78, 93, 40, 60, 55, 98};
    BiTree tree = NULL;
    BiTree p = (BiTree) malloc(sizeof(BiTNode));

    for (int j = 0; j < 10; j++) {
        InsertBST(&tree, a[j]);
    }


    //中序遍历二叉排序树将会得到一个有序的序列
    printf("未删除前的二叉排序树的有序序列：");
    InOrderTraverse(tree);
    printf("\n");

    //测试查找函数
    int searchKey = 93;
    int result = SearchBST(tree, searchKey, NULL, &p);
    printf("查找结果：%d\n查找key:%d\n", result, p->data);

    //测试删除函数
    int deleteKey = 23;
    result = DeleteBST(&tree, deleteKey);
    printf("删除结果：%d\n删除key:%d\n", result, deleteKey);
    printf("删除后的二叉排序树的有序序列：");
    InOrderTraverse(tree);

    return 0;
}


/**
 * function:二叉树的中序遍历算法
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
