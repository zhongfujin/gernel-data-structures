#include "linklist.h"

#include <stdio.h>


int sll_list_test()
{
	SLL_LIST_T list_base;
    SLL_TEST_NODE *node = NULL;
    SLL_TEST_NODE *node1 = NULL;
    SLL_TEST_NODE *node2 = NULL;
	SLL_TEST_NODE *sllnode = NULL;
    int i = 0;
    
    SLL_LIST_INIT(list_base);
    node = malloc(sizeof(SLL_TEST_NODE));
    if(node == NULL)
    {
        assert(0);
        return RET_ERROR;
    }
    memset(node,0,sizeof(SLL_TEST_NODE));

    node1 = malloc(sizeof(SLL_TEST_NODE));
    if(node1 == NULL)
    {
        assert(0);
        return RET_ERROR;
    }
    memset(node1,0,sizeof(SLL_TEST_NODE));
    node2 = malloc(sizeof(SLL_TEST_NODE));
    if(node2 == NULL)
    {
        assert(0);
        return RET_ERROR;
    }
    memset(node2,0,sizeof(SLL_TEST_NODE));

    strcpy(node->buf,"this is test");
    strcpy(node1->buf,"this is test1");
    strcpy(node2->buf,"this is test2");
    SLL_LIST_INSERT_HEAD(list_base,node->node);
    SLL_LIST_INSERT_TAIL(list_base,node2->node);
    SLL_LIST_INSERT_TAIL(list_base,node1->node);
    printf("list num:%ld\n",list_base.len);
    SLL_TEST_NODE *p_node = NULL;
	sllnode = SLL_LIST_NEXT(node2->node,offsetof(SLL_TEST_NODE,node));
	printf("next:%s\n",sllnode->buf);
	SLL_LIST_FOR_EACH(list_base,sllnode,offsetof(SLL_TEST_NODE,node))
    {
    	//sllnode = SLL_LIST_GET_INDEX(list_base, i, offsetof(SLL_TEST_NODE,node));
        printf("cyc head_data:%s\n",sllnode->buf);
    }

    sllnode = SLL_LIST_HEAD_REMOVE(list_base,offsetof(SLL_TEST_NODE,node));
	printf("del head:%s\n",sllnode->buf);
   /* for( i = 1; i <= list_base.len;i++)
    {
        p_node = SLL_LIST_GET_INDEX(list_base,i,offsetof(SLL_TEST_NODE,node));
        printf("head_data:%s\n",p_node->buf);
    }*/

    sllnode = SLL_LIST_TAIL_REMOVE(list_base,offsetof(SLL_TEST_NODE,node));
   	
	printf("del tail:%s\n",sllnode->buf);
    for( i = 1; i <= list_base.len;i++)
    {
        p_node = SLL_LIST_GET_INDEX(list_base,i,offsetof(SLL_TEST_NODE,node));
        printf("head_data:%s\n",p_node->buf);
    }

    return 1;
}



int dll_list_test()
{
	DLL_LIST_T list_base;
    DLL_TEST_NODE *node = NULL;
    DLL_TEST_NODE *node1 = NULL;
    DLL_TEST_NODE *node2 = NULL;
	DLL_TEST_NODE *sllnode = NULL;
	DLL_TEST_NODE *in_ne = NULL;
	DLL_TEST_NODE *in_af = NULL;
    int i = 0;
    
    DLL_LIST_INIT(list_base);
    node = malloc(sizeof(DLL_TEST_NODE));
    if(node == NULL)
    {
        assert(0);
        return RET_ERROR;
    }
    memset(node,0,sizeof(DLL_TEST_NODE));

    node1 = malloc(sizeof(DLL_TEST_NODE));
    if(node1 == NULL)
    {
        assert(0);
        return RET_ERROR;
    }
    memset(node1,0,sizeof(DLL_TEST_NODE));
    node2 = malloc(sizeof(DLL_TEST_NODE));
    if(node2 == NULL)
    {
        assert(0);
        return RET_ERROR;
    }
    memset(node2,0,sizeof(DLL_TEST_NODE));


    in_ne = malloc(sizeof(DLL_TEST_NODE));
    if(in_ne == NULL)
    {
        assert(0);
        return RET_ERROR;
    }
    memset(in_ne,0,sizeof(DLL_TEST_NODE));

	in_af = malloc(sizeof(DLL_TEST_NODE));
    if(in_af == NULL)
    {
        assert(0);
        return RET_ERROR;
    }
    memset(in_af,0,sizeof(DLL_TEST_NODE));



	printf("dll test!!!!!!!!!!!!!\n");
    strcpy(node->buf,"this is test");
    strcpy(node1->buf,"this is test1");
    strcpy(node2->buf,"this is test2");
	strcpy(in_ne->buf,"this is in ne test");
	strcpy(in_af->buf,"this is in af test");
	
    DLL_LIST_INSERT_HEAD(list_base,node->node);
    DLL_LIST_INSERT_HEAD(list_base,node2->node);
    DLL_LIST_INSERT_HEAD(list_base,node1->node);
	DLL_LIST_INSERT_BEFORE(node2->node, in_ne->node);
	DLL_LIST_INSERT_AFTER(node2->node, in_af->node);

	printf("insert success!\n");

	DLL_LIST_FOR_EACH(list_base,sllnode,offsetof(DLL_TEST_NODE,node))
	{
		printf("haha:%s\n",sllnode->buf);
	}

	DLL_TEST_NODE *tmp = NULL;


	
    sllnode = (DLL_TEST_NODE *)DLL_LIST_HEAD(list_base, offsetof(DLL_TEST_NODE,node));
	printf("head:%s\n",sllnode->buf);
	
	sllnode = (DLL_TEST_NODE *)DLL_LIST_TAIL(list_base, offsetof(DLL_TEST_NODE,node));
	printf("tail:%s\n",sllnode->buf);
		
	
	//DLL_LIST_FOR_EACH(list_base,sllnode,offsetof(DLL_TEST_NODE,node))
	int offset = offsetof(DLL_TEST_NODE,node);

	/*for((sllnode = DLL_LIST_HEAD(list_base,offset)); (sllnode != NULL && list_base.head != sllnode->node.next); (sllnode = DLL_LIST_NEXT(*(DLL_NODE_T *)((void *)sllnode + offset),offset)))
    {
        printf("cyc head_data:%s\n",sllnode->buf);
    }*/

	DLL_LIST_FOR_EACH_SAFE(list_base, sllnode, tmp, offsetof(DLL_TEST_NODE,node))
	{
		if(sllnode != NULL)
		{
			DLL_LIST_NODE_REMOVE(sllnode->node);
			printf("del node:%s\n",sllnode->buf);
		}
	}
		
    /*sllnode = DLL_LIST_HEAD_REMOVE(list_base,offsetof(DLL_TEST_NODE,node));
	printf("del head:%s\n",sllnode->buf);

    sllnode = DLL_LIST_TAIL_REMOVE(list_base,offsetof(SLL_TEST_NODE,node));
   	
	printf("del tail:%s\n",sllnode->buf);*/
   
    return 1;
}


int main()
{
    sll_list_test();
	printf("---------------\n");
	dll_list_test();

}

