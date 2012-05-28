#include <stdio.h>
#include <stdlib.h>
#include "conn.h"

/*
  help function
*/

conns_t make_conns()
{
    conns_t conns = {NULL, 0, 0, {-1}, 0};
    return conns;
}

void conns_extend(conns_t *conns, int count)
{
    conns_cut(conns);
    int conn_info_t_size = sizeof(conn_info_t);

    void *p = realloc(
        conns->conn_info, 
        conns->total * conn_info_t_size + count * conn_info_t_size);

    if(p == NULL) {
        printf("realloc error");
        exit(-1);
    }

    conns->total += count;
}

void conns_cut(conns_t *conns)
{
    int i;

    for(i = 0; i < conns->deleted_conns_count; i++) {
        conns->deleted_conns_idx[i] = -1;
    }

    conns->deleted_conns_count = 0;
}

void conn_add(conns_t *conns, int fd, int slave_id)
{
    
    if(conns->count < conns->total) {
        conns->conn_info[conns->count].fd = fd;
        conns->conn_info[conns->count].slave_id = slave_id;
        conns->count++;
    }
    
    else if(conns->total == 0) {
        conns->conn_info = malloc(INIT_CONN_COUNT * sizeof(conn_info_t));
        conns->conn_info[0].fd = fd;
        conns->conn_info[0].slave_id = slave_id;
        conns->count = 1;
        conns->total = INIT_CONN_COUNT;
    }
    
    else {
        conns_extend(conns, EXTEND_CONN_COUNT);
        conn_add(conns, fd, slave_id);
    }
}

void conn_del(conns_t *conns, int fd)
{
    int i;

    if(conns->deleted_conns_count == DELETED_CONN_HOLD_COUNT)
        conns_cut(conns);

    for(i = 0; i < conns->total; i++) {
        if(conns->conn_info[i].fd == fd) {
            conns->deleted_conns_idx[conns->deleted_conns_count] = fd;
            conns->count--;
            break;
        }
    }

    if(conns->deleted_conns_count == DELETED_CONN_HOLD_COUNT)
        conns_cut(conns);

}
