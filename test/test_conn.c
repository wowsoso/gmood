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
    conns_t conns = make_conns();
    conns_extend(&conns, 2);
    
    assert(conns.total == 2);
}

static void test_conn_del() {
    conns_t conns = make_conns();
    conn_add(&conns, 1, 101);
    conn_add(&conns, 2, 102);
    conn_add(&conns, 3, 103);
    conn_del(&conns, 1);
    conn_del(&conns, 3);

    assert(conns.count == 1);
    assert(conns.deleted_conns_idx[0] = 1);
    assert(conns.deleted_conns_idx[1] = 3);
    assert(conns.deleted_conns_count = 2);
}

static void test_conns_cut() {
    conns_t conns = make_conns();
    conn_add(&conns, 1, 101);
    conn_add(&conns, 2, 102);
    conn_add(&conns, 3, 103);
    conn_del(&conns, 1);
    conns_cut(&conns);

    assert(conns.count == 2);
    assert(conns.deleted_conns_count == 0);
}


int main() {
    test_make_conns();
    test_conn_extend();
    test_conns_cut();
    test_conn_add();
    printf("ok\n");
    return 0;
}
