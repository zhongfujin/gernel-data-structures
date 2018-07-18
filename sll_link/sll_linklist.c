#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklist.h"

/**********************************************
 *author: zhongfujin
 *brief：链表初始化
 *param:链表地址
***********************************************/
int sll_link_list_init(SLL_LINK_LIST_BASE *list)
{
    list = malloc(sizeof(SLL_LINK_LIST_BASE));
    if(NULL == list)
    {
        printf("malloc failed!\n");
        assert(0);
        return RET_ERROR;
    }
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    return RET_SUCCESS;
}

/**********************************************
 *author: zhongfujin
 *brief：链表头插节点
 *param:链表地址
 *param:添加节点
***********************************************/
int sll_link_list_insert_at_head(SLL_LINK_LIST_BASE *list,void *p_node)
{
    if(list == NULL || p_node == NULL)
    {
        printf("param error!\n");
        assert(0);
        return RET_ERROR;
    }
    SLL_LINK_LIST_NODE *node = (SLL_LINK_LIST_NODE *)p_node;
    node->next = list->head;
    list->head = node;
    if(list->tail == NULL)
    {
        list->tail = node;
    }
    list->len++;
    return RET_SUCCESS;

}

/**********************************************
 *author: zhongfujin
 *brief：链表随查插节点
 *param:链表地址
 *param:添加节点
 *param:添加位置
***********************************************/
int sll_link_list_insert_at_index(SLL_LINK_LIST_BASE *list,void *p_node,int index)
{
    long i = 1;
    SLL_LINK_LIST_NODE *node = (SLL_LINK_LIST_NODE *)p_node;
    if(list->len < index)
    {
        printf("index is invailed!\n");
        assert(0);
        return RET_ERROR;
    }
    SLL_LINK_LIST_NODE *tmp_head = NULL;

    tmp_head = list->head;
    while(tmp_head && i < index)
    {
        tmp_head = tmp_head->next;
        i++;
    }

    if(tmp_head)
    {
        node->next = tmp_head->next;
        tmp_head->next = node;
        list->len++;
    }
    return RET_SUCCESS;
}

/**********************************************
 *author: zhongfujin
 *brief：链表尾插节点
 *param:链表地址
 *param:添加节点
***********************************************/
int sll_link_list_insert_at_tail(SLL_LINK_LIST_BASE *list,void *p_node)
{
    SLL_LINK_LIST_NODE *node = (SLL_LINK_LIST_NODE *)p_node;
    if(NULL != list->tail)
    {

        list->tail->next = node;
    }
    else
    {
        list->head = node;
    }
    list->len++;
    list->tail = node;
    node->next = NULL;
    return RET_SUCCESS;
}

/**********************************************
 *author: zhongfujin
 *brief：判断链表是否为空
 *param:链表地址
***********************************************/
BOOL sll_link_list_empty(SLL_LINK_LIST_BASE *list)
{
    if(list->head == NULL || list->len == 0)
    {
        return TRUE;
    }
    return FALSE;
}

/**********************************************
 *author: zhongfujin
 *brief：获取头节点
 *param:链表地址
***********************************************/
void *sll_link_list_get_head(SLL_LINK_LIST_BASE *list)
{
    if(list == NULL)
    {
        printf("invailed list\n");
        assert(0);
        return NULL;
    }
    if(sll_link_list_empty(list))
    {
        return NULL;
    }
    return list->head;
}


void *sll_link_list_get_tail(SLL_LINK_LIST_BASE *list)
{
    if(list == NULL)
    {
        printf("invailed list\n");
        assert(0);
        return NULL;
    }
    if(sll_link_list_empty(list))
    {
        return NULL;
    }
    SLL_LINK_LIST_NODE *tmp_node = NULL;
    tmp_node = list->head;
    while(tmp_node->next)
    {
        tmp_node = tmp_node->next;
    }
    return tmp_node;
}

/**********************************************
 *author: zhongfujin
 *brief：获取索引为index的节点
 *param:链表地址
 *param:获取位置的索引
***********************************************/
void *sll_link_list_get_index(SLL_LINK_LIST_BASE *list,int index)
{
    if(index > list->len)
    {
        return NULL;
    }
    int i = 1;
    SLL_LINK_LIST_NODE *node = list->head;
    if(index == 1)
    {
        return list->head;
    }
    for(i = 1; i < index; i++)
    {
        node = node->next;
    }
    return node;
}

/**********************************************
 *author: zhongfujin
 *brief：移除头节点
 *param:链表地址
***********************************************/
int sll_link_list_head_remove(SLL_LINK_LIST_BASE * list)
{
    if(sll_link_list_empty(list))
    {
        printf("empty list\n");
        assert(0);
        return RET_ERROR;
    }
    SLL_LINK_LIST_NODE *node = list->head;
    list->head = list->head->next;
    list->len--;
    free(node);
    node = NULL;
    return RET_SUCCESS;
}

/**********************************************
 *author: zhongfujin
 *brief：移除尾节点
 *param:链表地址
***********************************************/
int sll_link_list_tail_remove(SLL_LINK_LIST_BASE *list)
{
    if(sll_link_list_empty(list))
    {
        printf("empty list\n");
        assert(0);
        return RET_ERROR;
    }
    SLL_LINK_LIST_NODE *node = list->head;
    SLL_LINK_LIST_NODE *pre_node = NULL;
    while(node->next)
    {
        pre_node = node;
        node = node->next;
    }
    pre_node->next = NULL;
    list->len--;
    free(node);
    node = NULL;
    return RET_SUCCESS;
}

/**********************************************
 *author: zhongfujin
 *brief：移除node节点
 *param:链表地址
 *param:需移除的节点地址
***********************************************/
int sll_link_list_node_remove(SLL_LINK_LIST_BASE *list,void *node)
{
    if(sll_link_list_empty(list))
    {
        printf("list is empty\n");
        assert(0);
        return RET_ERROR;
    }
    SLL_LINK_LIST_NODE *sllnode = (SLL_LINK_LIST_NODE *)node;
    SLL_LINK_LIST_NODE *p_node = list->head;

    if(node == list->head)
    {
        sll_link_list_head_remove(list);
        return RET_SUCCESS;
    }
    if(node == sll_link_list_get_tail(list))
    {
        sll_link_list_tail_remove(list);
        return RET_SUCCESS;
    }
    while(p_node)
    {
        if(p_node->next == sllnode)
        {
            p_node->next = sllnode->next;
            free(sllnode);
            node = NULL;
            return RET_SUCCESS;
        }
        p_node = p_node->next;
    }
    printf("no such node : %p\n",sllnode);
    return RET_ERROR;
}

/**********************************************
 *author: zhongfujin
 *brief：链表删除
 *param:链表地址
***********************************************/
void sll_link_list_destory(SLL_LINK_LIST_BASE *list)
{
    if(list->head == NULL || list->len == 0)
    {
        free(list);
        return;
    }
    SLL_LINK_LIST_NODE *node = list->head;
    while(node)
    {
        node = node->next;
        free(node);
        node = NULL;
    }
    free(list);
    return;
}

int main()
{
    SLL_LINK_LIST_BASE *list_base = NULL;
    TEST_NODE *node = NULL;
    TEST_NODE *node1 = NULL;
    TEST_NODE *node2 = NULL;
    int i = 0;
    list_base = malloc(sizeof(SLL_LINK_LIST_BASE));
    if(list_base == NULL)
    {
        assert(0);
        return RET_ERROR;
    }
    sll_link_list_init(list_base);
    node = malloc(sizeof(TEST_NODE));
    if(node == NULL)
    {
        assert(0);
        return RET_ERROR;
    }
    memset(node,0,sizeof(TEST_NODE));

    node1 = malloc(sizeof(TEST_NODE));
    if(node1 == NULL)
    {
        assert(0);
        return RET_ERROR;
    }
    memset(node1,0,sizeof(TEST_NODE));
    node2 = malloc(sizeof(TEST_NODE));
    if(node2 == NULL)
    {
        assert(0);
        return RET_ERROR;
    }
    memset(node2,0,sizeof(TEST_NODE));

    strcpy(node->buf,"this is test");
    strcpy(node1->buf,"this is test1");
    strcpy(node2->buf,"this is test2");
    sll_link_list_insert_at_head(list_base,node);
    sll_link_list_insert_at_tail(list_base,node2);
    sll_link_list_insert_at_index(list_base,node1,1);
    printf("list num:%d\n",list_base->len);
    TEST_NODE *p_node = NULL;
    for( i = 1; i <= list_base->len;i++)
    {
        p_node = sll_link_list_get_index(list_base,i);
        printf("head_data:%s\n",p_node->buf);
    }

    sll_link_list_head_remove(list_base);
    for( i = 1; i <= list_base->len;i++)
    {
        p_node = sll_link_list_get_index(list_base,i);
        printf("head_data:%s\n",p_node->buf);
    }

    sll_link_list_tail_remove(list_base);
    for( i = 1; i <= list_base->len;i++)
    {
        p_node = sll_link_list_get_index(list_base,i);
        printf("head_data:%s\n",p_node->buf);
    }

    //printf("head_data:%s\n",p_node->buf);
    sll_link_list_destory(list_base);
    return 1;

}


