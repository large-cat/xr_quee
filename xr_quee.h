#include<stddef.h>
#include<stdlib.h>
#include<string.h>


struct  XR_NODE{
    char* data;
    struct XR_NODE* next ;
} ;

 struct XR_QUEE{
    struct XR_NODE* head;
    struct XR_NODE* tail;
    int length;
} ;


typedef struct XR_NODE XR_NODE;
typedef struct XR_QUEE XR_QUEE;



// 功能： 初始化一个节点变量
// 参数：{data： 该节点携带的字符串数据。}
XR_NODE init_node(char* data)
{
    XR_NODE result_node;

    if(data != NULL)
    {
        result_node.data = (char *)malloc(strlen(data) + 1);
        strcpy(result_node.data, data);
    }
    
    result_node.next = NULL;

    return result_node;

}


// 功能：深拷贝节点
// 说明： 将源节点深拷贝到目标节点
// 参数：{gol_node：目标节点指针，source_node：源节点指针}
int cp_node(XR_NODE* gol_node, XR_NODE* source_node)
{
    if(source_node == NULL || source_node->data == NULL) return -1;

    gol_node->data = (char *) malloc(strlen(source_node->data) + 1);
    strcpy(gol_node->data ,  source_node->data);

    return 0;
}


// 功能：初始化队列
// 参数：{result_quee：待初始化的队列的指针，不能为空， nodes：要保存到队列的节点的数组， 
//               quee_length：队列的长度，要和节点数组长度对应}
int init_quee(XR_QUEE* result_quee, XR_NODE* nodes,  int quee_length)
{
    if( result_quee == NULL) return -1;

    if(nodes != NULL && quee_length > 0)
    {
        result_quee->head = (XR_NODE *)malloc(sizeof(XR_NODE));
        cp_node(result_quee->head, nodes);

        XR_NODE *last_node_point = result_quee->head;
        result_quee->length = 1;

        if(quee_length == 1)
        {
            result_quee->tail = result_quee->head;
            result_quee->tail->next = NULL;
            return 0;
        }

        for(int i=1; i< quee_length; i++)
        {
            last_node_point->next = (XR_NODE *)malloc(sizeof(XR_NODE));
            cp_node(last_node_point->next, ++nodes);
            
            last_node_point = last_node_point->next;
            result_quee->length++;
        }

        result_quee->tail = (XR_NODE *)malloc(sizeof(XR_NODE));
        cp_node(result_quee->tail, nodes);

        result_quee->tail->next = NULL;
        return 0;
    }
    
    if(quee_length == 0 && nodes == NULL) 
    {
        result_quee->head = NULL;
        result_quee->tail = NULL;
        result_quee->length = 0;

        return 0;
    }

    return -1;
}


// 功能：往队列追加节点
// 说明：追加的节点是深拷贝到队列中的
// 参数：{quee：待操作的队列的指针，node：待插入到队列的节点的指针}
int xr_quee_append(XR_QUEE* quee, XR_NODE* node)
{
    if(quee == NULL || node == NULL || quee->length < 0) return -1;

    if(quee->length == 0)
    {
        quee->head = (XR_NODE *)malloc(sizeof(XR_NODE));
        cp_node(quee->head, node);

        quee->tail = quee->head;
        quee->head->next = quee->tail;
        quee->length = 1;
        
    }
    else
    {
        quee->tail->next = (XR_NODE *)malloc(sizeof(XR_NODE));
        cp_node(quee->tail->next, node);

        quee->tail = quee->tail->next;
        quee->length++;
        quee->tail->next = NULL;
    }

    return 0;
}


// 功能：从队列的头部弹出节点
// 参数：{result_node：用来保存当前队列头部节点的节点指针，
//                quee：待弹出头部节点的队列}
int xr_quee_pop(XR_NODE* result_node, XR_QUEE *quee)
{
    if(quee == NULL || quee->length == 0 || result_node == NULL) return -1;

    XR_NODE* tmp_node = quee->head;
    cp_node(result_node , quee->head);

    if(quee->length == 1)
    {
        quee->head = NULL;
        quee->tail = NULL;
    }
    else
    {
        quee->head = quee->head->next;
    }

    quee->length--;
    free(tmp_node->data);
    free(tmp_node);

    return 0;
}


// 功能：释放队列资源
// 参数：{quee：待销毁的队列的指针}
int xr_quee_distroy(XR_QUEE* quee)
{
    XR_NODE* tmp_node;

    if(quee->length == 1)
    {
        free(quee->head->data);
        free(quee->head);
        quee->head = NULL;
        quee->tail = NULL;

        return 0;
    }

    while (quee->head != NULL)
    {
        tmp_node = quee->head;

        quee->head = quee->head->next;
        quee->length--;

        free(tmp_node->data);
        free(tmp_node);
    }

    quee->tail = NULL;
    return 0;
    
}
