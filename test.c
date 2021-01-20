#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>

#include"xr_quee.h"

int main(void)
{
    XR_NODE node = init_node("hello");
    // node.data = "123456";
    XR_NODE nodes[5] = {};

    XR_QUEE quee;
    init_quee(&quee, NULL, 0);

    for(int i=0; i<1000; i++)
    {
        xr_quee_append(&quee, &node);
        printf("append node\n");
    }
    printf("waitting\n");
    // sleep(10);

    printf("%d\n", quee.length);

    XR_NODE tmp_node;

    for(int i=0; i<500; i++)
    {
        xr_quee_pop(&tmp_node, &quee);
        printf("%s", (unsigned char *)(tmp_node.data));
    }

    xr_quee_distroy(&quee);
    printf("over l: %d\n", quee.length);

    // sleep(10);

    printf("%s\n", node.data);

    return 0;
}
