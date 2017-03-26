#ifndef PHP_PANDA_RESOURCE_H
#define PHP_PANDA_RESOURCE_H

#define PANDA_RESOURCE_TYPE_MYSQL "mysql"
#define PANDA_RESOURCE_TYPE_MEMCACHE "memcache"
#define PANDA_RESOURCE_TYPE_REDIS "redis"

#define PANDA_NODE_RESOURCE "resource"
#define PANDA_NODE_RESOURCE_SQLS "sqls"
#define PANDA_NODE_RESOURCE_MAPS "maps"
#define PANDA_NODE_RESOURCE_MAPS_HOST "host"
#define PANDA_NODE_RESOURCE_MAPS_PORT "port"

int panda_resource_compose_node(TSRMLS_D);
int panda_resource_init_globals(TSRMLS_D);
int panda_resource_destroy_globals(TSRMLS_D);
int panda_resource_set_resource(const char *type, char *host, int port TSRMLS_DC);
int panda_resource_get_resource_last_insert_id(const char *type, int *resource_id TSRMLS_DC);
int panda_resource_get_resource_id_with_hashkey(ulong hash, int *resource_id TSRMLS_DC);
int panda_resource_set_resource_id_with_hashkey(ulong hash, int resource_id TSRMLS_DC);
int panda_resource_set_resource_id_with_instance_id(ulong instance_id, int resource_id TSRMLS_DC);
int panda_resource_get_resource_id_with_instance_id(ulong instance_id, int *resource_id TSRMLS_DC);
int panda_resource_set_last_instance_id(const char* type, int resource_id TSRMLS_DC);
int panda_resource_get_last_instance_id( const char* type, int *resource_id TSRMLS_DC);
int panda_resource_set_sql(const char *type, char *sql TSRMLS_DC);
int panda_resource_get_sql_last_id(const char *type, int *resource_id TSRMLS_DC);
int panda_resource_set_db_with_instance_id(ulong instance_id, const char *db TSRMLS_DC);
int panda_resource_get_db_with_instance_id(ulong instance_id, char **db TSRMLS_DC);
int panda_resource_set_prepare_sql_with_stmt_id(ulong stmt_id, char *prepare_sql TSRMLS_DC);
int panda_resource_get_prepare_sql_with_stmt_id(ulong stmt_id, char **prepare_sql TSRMLS_DC);
int panda_resource_set_instance_id_with_stmt_id(ulong stmt_id, int instance_id TSRMLS_DC);
int panda_resource_get_instance_id_with_stmt_id(ulong stmt_id, int *instance_id TSRMLS_DC);
int panda_resource_set_url_entity_with_instance_id(int instance_id, panda_url_entity_t *url_entity TSRMLS_DC);
int panda_resource_get_url_entity_with_instance_id(int instance_id, panda_url_entity_t  **url_entity TSRMLS_DC);
int panda_resource_set_child_instances_with_instance_id(int instance_id, zval *child_instances TSRMLS_DC);
int panda_resource_get_child_instances_with_instance_id(int instance_id, zval **child_instances TSRMLS_DC);
#endif
