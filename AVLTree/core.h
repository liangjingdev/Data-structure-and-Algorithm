//
// Created by 梁竞 on 2017/12/4.
//

#ifndef AVLTREE_CORE_H
#define AVLTREE_CORE_H

#endif //AVLTREE_CORE_H

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status; //Status是函数的类型，其值是函数结果状态嘛


//二叉树（二叉排序树）的二叉链表结点结构定义
typedef struct BiTNode {
    int data; //结点的数据
    int bf; //结点的平衡因子
    struct BiTNode *lchild, *rchild; //左右孩子指针
} BiTNode, *BiTree;


/**
 * function:作简单右旋处理
 *          对以p为根的二叉排序树作右旋处理，处理之后p指向新的树根结点，即旋转处理之前的左子树的根结点
 * @param p
 */
void R_Rotate(BiTree *p) {
    BiTree L;
    L = (*p)->lchild; // L指向p的左子树根结点
    (*p)->lchild = L->rchild; //需要进行右旋处理的结点在旋转后，其左孩子为原本它的左子树根结点的有孩子。
    L->rchild = (*p); //作右旋处理后，结点p现在为结点L的右子树根结点了，而L作为它们新的根结点。
    *p = L; //最后需要让p指向新的根结点
}


/**
 * function:作简单左旋处理
 *          对以p为根的二叉排序树作左旋处理，处理之后p指向新的树根结点，即旋转处理之前的右子树的根结点
 * @param p
 */
void L_Rotate(BiTree *p) {
    BiTree R;
    R = (*p)->rchild; //R指向p的右子树根结点
    (*p)->rchild = R->lchild; //R的左子树挂接为p的右子树
    R->lchild = (*p);
    *p = R; //p指向新的根结点
}


#define LH +1 //左高
#define EH 0 //等高
#define RH -1 //右高


/**
 * function:对以指针T所指结点为根的二叉树作左平衡旋转处理
 *          处理结束后，指针T指向新的根结点
 *
 * @param T T为最小不平衡子树的根结点
 */
void LeftBalance(BiTree *T) {
    BiTree L, Lr;
    L = (*T)->lchild; //L指向T的左子树根结点
    //L->bf => L的平衡因子 =>目的是检查是否发生一正一负的情况，这关系到是否能够直接旋转。
    switch (L->bf) {
        //检查T的左子树的平衡度，并作相应平衡处理
        case LH://第一种情况：新结点是插入在T的左孩子的左子树上的，所以只需要作单右旋处理即可。
            (*T)->bf = L->bf = EH; //作单右旋处理后，结点T（原需要进行单右旋处理的根结点）和结点L（结点T的左子树根结点）的平衡因子将变为0
            R_Rotate(T);
            break;

        case RH: //第二种情况，新结点是插入在T的左孩子的右子树上的，即发生了一正一负的情况，所以需要作双旋处理
            Lr = L->rchild; //Lr指向T的左孩子的右子树根结点
            switch (Lr->bf) {
                //修改T及其左孩子的平衡因子
                case LH: //第一种情形，Lr的左子树比右子树高,最终处理结果是：传入的结点T的平衡因子变为RH,而结点T的左子树根结点L的平衡因子为EH
                    (*T)->bf = RH;
                    L->bf = EH;
                    break;
                case EH://第二种情形，Lr的左子树与右子树等高,最终处理结果是：传入的结点T的平衡因子变为EH,结点T的左子树根结点L的平衡因子也同为EH
                    (*T)->bf = L->bf = EH;
                    break;
                case RH://第三种情形，Lr的左子树比右子树低,最终处理结果是：传入的结点T的平衡因子变为EH,而结点T的左子树根结点L的平衡因子为LH
                    (*T)->bf = EH;
                    L->bf = LH;
                    break;
            }
            Lr->bf = EH; //最终Lr的平衡因子为EH
            L_Rotate(&(*T)->lchild); // 首先对T的左子树作左旋平衡处理
            R_Rotate(T); // 然后再对T作右旋平衡处理
    }
}


/*  对以指针T所指结点为根的二叉树作右平衡旋转处理， */
/*  本算法结束时，指针T指向新的根结点 */
//与左平衡旋转处理同理
void RightBalance(BiTree *T) {
    BiTree R, Rl;
    R = (*T)->rchild; /*  R指向T的右子树根结点 */
    switch (R->bf) { /*  检查T的右子树的平衡度，并作相应平衡处理 */
        case RH: /*  新结点插入在T的右孩子的右子树上，要作单左旋处理 */
            (*T)->bf = R->bf = EH;
            L_Rotate(T);
            break;
        case LH: /*  新结点插入在T的右孩子的左子树上，要作双旋处理 */
            Rl = R->lchild; /*  Rl指向T的右孩子的左子树根 */
            switch (Rl->bf) { /*  修改T及其右孩子的平衡因子 */
                case RH:
                    (*T)->bf = LH;
                    R->bf = EH;
                    break;
                case EH:
                    (*T)->bf = R->bf = EH;
                    break;
                case LH:
                    (*T)->bf = EH;
                    R->bf = RH;
                    break;
            }
            Rl->bf = EH;
            R_Rotate(&(*T)->rchild); /*  对T的右子树作右旋平衡处理 */
            L_Rotate(T); /*  对T作左旋平衡处理 */
    }
}


/**
 * function:若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个
 *          数据元素为e的新结点，并返回1，否则返回0。若因插入而使二叉排序树
 *          失去平衡，则作平衡旋转处理，布尔变量taller反映T是否长高.
 *
 *          注意：二叉排序树的插入操作一定是发生在叶子结点上的
 *          重点：递归的实现，最底层运行完之后还会由内而外继而运行，如if (!InsertAVL(&(*T)->lchild, e, taller))和if (!InsertAVL(&(*T)->rchild, e, *taller))
 *               这两行代码，执行到这两行代码的时候将会进入递归遍历，当找到相对应的插入点进行插入并且进行下面代码的处理完之后，就会跳到外面一层
 *               即其对应上一个结点继而继续下面代码的运行，若找到最小不平衡子树的话就会跳到相应的函数进行处理。以此类推。--重要是对递归的理解
 *               然后还需要注意的是向函数LeftBalance(BiTree *T)和函数RightBalance(BiTree *T)传入的那个结点是最小不平衡子树的根结点。
 * @param T
 * @param e
 * @param taller
 * @return
 */
Status InsertAVL(BiTree *T, int e, Status *taller) {

    //指针的值为空,即表示此处不存在结点（已遍历到叶子结点了）
    if (!*T) {
        //插入新结点，树"长高"，则置taller为TRUE
        *T = (BiTree) malloc(sizeof(BiTNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL; //左右子树均置为空
        (*T)->bf = EH; //平衡因子为EH
        *taller = TRUE;
    } else {

        if (e == (*T)->data) {
            //二叉排序树中已存在和e有相同关键字的结点则不再插入
            *taller = FALSE;
            return FALSE;
        }

        //如果e小于当前结点的数据值，则应该在其左子树中继续进行搜索
        if (e < (*T)->data) {
            if (!InsertAVL(&(*T)->lchild, e, taller)) {
                //未插入
                return FALSE;
            }

            if (*taller) //表示已插入到T的左子树中且左子树长高
                switch ((*T)->bf) { //检查T的平衡度
                    case LH:
                        //表示未插入之前T的左子树就比右子树要高，所以现在需要作左平衡处理,处理完成之后整棵树不长高
                        LeftBalance(T);
                        *taller = FALSE;
                        break;
                    case EH:
                        //表示未插入之前T的左子树和右子树等高，现因左子树增高而使树增高
                        (*T)->bf = LH;
                        *taller = TRUE;
                        break;
                    case RH:
                        //表示未插入之前T的左子树比右子树要低，插入之后左、右子树等高，整棵树不长高
                        (*T)->bf = EH;
                        *taller = FALSE;
                        break;
                }
        } else {
            //应继续在T的右子树中进行搜索
            if (!InsertAVL(&(*T)->rchild, e, taller))
                //未插入
                return FALSE;

            if (*taller) {
                switch ((*T)->bf) {
                    case LH:
                        (*T)->bf = EH;
                        *taller = FALSE;
                        break;
                    case EH:
                        (*T)->bf = RH;
                        *taller = TRUE;
                        break;
                    case RH:
                        RightBalance(T);
                        *taller = FALSE;
                        break;
                }
            }
        }
    }
    return TRUE;
}