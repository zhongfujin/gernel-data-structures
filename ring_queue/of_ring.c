#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _tag_or_mgr
{
  void *base;
  unsigned int len;
  unsigned int head;
  unsigned int tail;
} OR_MGR;

typedef struct _tag_or_node
{
  unsigned int len;
  char data[0];
} OR_NODE;

OR_MGR *g_om = NULL;

int or_create(unsigned int len)
{
  void *p = malloc(sizeof(OR_MGR) + len);
  if (!p)
    goto LABEL_FAIL;

  g_om = (OR_MGR *)p;
  g_om->base = p + sizeof(OR_MGR);
  g_om->len = len - sizeof(OR_MGR);
  g_om->head = g_om->tail = 0;

  return 0;

LABEL_FAIL:
  if (p)
    free(p);
  printf(" Failed to create offset ring!.");
  return -1;
}

int node_fill(char *ring_addr, char *data, unsigned int len)
{
  OR_NODE *p_node = (OR_NODE *)ring_addr;

  if (!ring_addr || !data)
    return -1;
    
  p_node->len = len;
  memcpy(p_node->data, data, len);

  return 0;
}

int or_add(void *data, unsigned int len)
{
  unsigned int node_len = sizeof(unsigned int) + len;
  unsigned int head_new = g_om->head + node_len;
  OR_NODE *p_node = NULL;
  char *p = NULL;
  int ret = 0;
  
  if (NULL == data)
    goto LABEL_FAIL;

  if (g_om->head >= g_om->tail)
  {
    /*Memory leak in the bottom*/
    if (head_new > g_om->len)
    {
      /*No space in top*/
      if (node_len >= g_om->tail)
        goto LABEL_FULL;
        
      /*No space for length tag*/
      if ((g_om->len - g_om->head) < sizeof(unsigned int))
      {
        ret = node_fill(g_om->base, data, len);
        if (0 != ret)
          goto LABEL_FAIL;
        g_om->head = sizeof(unsigned int) + len;
      }
      else
      {
        /*Length tag first in the bottom*/
        p = g_om->base + g_om->head;
        p_node = (OR_NODE *)p;
        p_node->len = len;

        ret = node_fill(g_om->base, data, len);
        if (0 != ret)
          goto LABEL_FAIL;
        g_om->head = sizeof(unsigned int) + len;
      }
      
    }
    else
    {
      ret = node_fill(g_om->base + g_om->head, data, len);
      if (0 != ret)
        goto LABEL_FAIL;
      g_om->head += sizeof(unsigned int) + len;
    }
  }
  else
  {
    if (head_new >= g_om->tail)
      goto LABEL_FULL;

    ret = node_fill(g_om->base + g_om->head, data, len);
    if (0 != ret)
      goto LABEL_FAIL;
    g_om->head += sizeof(unsigned int) + len;
  }

  return 1;

LABEL_FULL:
  printf(" Ring is full!\n");
  return 0;

LABEL_FAIL:
  printf(" Failed to add node to Ring\n");
  return -1;
}

int or_delete(char **pdata, unsigned int *len)
{
  OR_NODE *p_node = NULL;
  unsigned *p_tmp_len = NULL;
  char *p = NULL;
  
  if (g_om->head == g_om->tail)
    goto LABEL_FAIL;

  /*Bottom detect*/
  if ((g_om->tail + sizeof(unsigned int)) > g_om->len)
  {
    /*No length tag exists*/
    p_node = (OR_NODE *)g_om->base;
    *pdata = p_node->data;
    *len = p_node->len;
    g_om->tail = sizeof(unsigned int) + p_node->len;
  }
  else
  {
    p = g_om->base + g_om->tail;
    p_tmp_len = (unsigned int *)p;

    if ((g_om->tail + sizeof(unsigned int) + *p_tmp_len) > g_om->len)
    {
      /*Length tag exists*/
      p_node = (OR_NODE *)g_om->base;
      *pdata = p_node->data;
      *len = p_node->len;
      g_om->tail = sizeof(unsigned int) + p_node->len;
    }
    else
    {
      p_node = (OR_NODE *)p;
      *pdata = p_node->data;
      *len = p_node->len;
      g_om->tail += sizeof(unsigned int) + p_node->len;
    }
  }
  
  return 1;

LABEL_EMPTY:
  printf(" Ring is empty!\n");
  return 0;

LABEL_FAIL:
  printf(" Failed to remove node from the ring\n");
  return -1;
}

int main(int argc, char **argv)
{
  char mode;
  unsigned int len;
  char *p;
  int ret;
  
  if (argc != 2)
    return -1;

  or_create((unsigned int)atoi(argv[1]));

  while (1)
  {
    scanf("%c", &mode);
    if (mode == '?')
    {
      printf("e - exit\n");
      printf("a - add\n");
      printf("d - delete\n");
      printf("i - info\n");
      printf("? - help\n");
    }
    else if (mode == 'e')
    {
      break;
    }
    else if (mode == 'a')
    {
      printf(" <add> Data length:");
      fflush(NULL);
      scanf("%u", &len);
      p = malloc(len);
      if (!p)
        printf("error\n");
      or_add(p, len);
      free(p);
    }
    else if (mode == 'd')
    {
      len = 0;
      or_delete(&p, &len);
      printf( "<delete> Data length:%d\n", len);
    }
    else if (mode == 'i')
    {
      printf("  len %u\n", g_om->len);
      printf(" head %u\n", g_om->head);
      printf(" tail %u\n", g_om->tail);
    }
  }

  return 0;
}


