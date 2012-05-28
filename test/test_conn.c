#include <stdio.h>
#include <assert.h>
#include "../conn.h"

static void test_make_conns() {
    conns_t conns = make_conns();
    assert(conns.conn_info == NULL);
    assert(conns.count == 0);
    assert(conns.total == 0);
    assert(sizeof(conns.deleted_conns_idx));
}

static void test_conn_add() {
    conns_t conns = make_conns();
    conn_add(&conns, 1, 101);
    conn_add(&conns, 2, 102);

    assert(conns.conn_info[0].fd == 1);
    assert(conns.conn_info[0].slave_id == 101);
    assert(conns.conn_info[1].fd == 2);
    assert(conns.conn_info[1].slave_id == 102);
}

static void test_conn_extend() {
    conns_t conns1 = make_conns();
    conns_extend(&conns1, 2);
    
    assert(conns1.total == 2);
}


int main() {
    test_make_conns();
    test_conn_extend();
    test_conn_add();
    printf("ok\n");
    return 0;
}
