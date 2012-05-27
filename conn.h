typedef struct conns_s        conns_t;
typedef struct conn_info_s    conn_info_t;

#define INIT_CONN_COUNT 5
#define EXTEND_CONN_COUNT 5
#define DELETED_CONN_HOLD_COUNT 2

struct conn_info_s {
    int fd;
    int slave_id;
};

struct conns_s {
    conn_info_t        *conn_info;
    int                count;
    int                total;
    int                deleted_conns[DELETED_CONN_HOLD_COUNT];
};

conns_t make_conns();
conns_t conn_add(conns_t conns, int fd, int slave_no);
conns_t conn_delete(conns_t conns, int fd);
conns_t conns_extend(conns_t conns, int size);
