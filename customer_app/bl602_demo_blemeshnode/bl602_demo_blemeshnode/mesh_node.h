#ifndef  __MESH_NODE__
#define  __MESH_NODE__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define LED_RED_PIN         (17)
#define LED_GREEN_PIN       (14)
#define LED_BLUE_PIN        (11)

int blemesh_node(void);
void mesh_node_open(void);
void mesh_node_reset(void);
#endif // __ZB_NOTIFY__