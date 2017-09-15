#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_panda.h"
#include "panda_resource.h"

ZEND_EXTERN_MODULE_GLOBALS(panda);
int panda_resource_compose_node(TSRMLS_D)
{
    Z_ADDREF_P(PANDA_G(resources_maps));
    add_assoc_zval(PANDA_G(node_resource), PANDA_NODE_RESOURCE_MAPS, PANDA_G(resources_maps));
    Z_ADDREF_P(PANDA_G(resources_sqls));
    add_assoc_zval(PANDA_G(node_resource), PANDA_NODE_RESOURCE_SQLS, PANDA_G(resources_sqls));
    return SUCCESS;
}

int panda_resource_init_globals(TSRMLS_D)
{
    PANDA_ARRAY_INIT(PANDA_G(node_resource));
    PANDA_ARRAY_INIT(PANDA_G(resources_sqls));
    PANDA_ARRAY_INIT(PANDA_G(resources_maps));
    PANDA_HASHTABLE_INIT(&PANDA_G(resource_index_object_dbs_table));
    PANDA_HASHTABLE_INIT(&PANDA_G(resource_index_object_resources_table));
    PANDA_HASHTABLE_INIT(&PANDA_G(resource_index_object_prepare_sqls_table));
    PANDA_HASHTABLE_INIT(&PANDA_G(resource_index_object_stmt_table));
    PANDA_HASHTABLE_INIT(&PANDA_G(resource_index_hashkey_resources_table));
    PANDA_HASHTABLE_INIT(&PANDA_G(resource_index_last_instances_table));
    PANDA_HASHTABLE_INIT(&PANDA_G(resource_index_curl_entity_table));
    PANDA_HASHTABLE_INIT(&PANDA_G(reosurce_index_object_chilrens_table));
    return SUCCESS;
}

int panda_resource_destroy_globals(TSRMLS_D)
{
    PANDA_ARRAY_DESTROY(PANDA_G(resources_sqls));
    PANDA_ARRAY_DESTROY(PANDA_G(resources_maps));
    PANDA_ARRAY_DESTROY(PANDA_G(node_resource));
    PANDA_HASHTABLE_DESTROY(&PANDA_G(resource_index_object_dbs_table));
    PANDA_HASHTABLE_DESTROY(&PANDA_G(resource_index_object_resources_table));
    PANDA_HASHTABLE_DESTROY(&PANDA_G(resource_index_object_prepare_sqls_table));
    PANDA_HASHTABLE_DESTROY(&PANDA_G(resource_index_object_stmt_table));
    PANDA_HASHTABLE_DESTROY(&PANDA_G(resource_index_hashkey_resources_table));
    PANDA_HASHTABLE_DESTROY(&PANDA_G(resource_index_last_instances_table));
    PANDA_HASHTABLE_DESTROY(&PANDA_G(resource_index_curl_entity_table));
    PANDA_HASHTABLE_DESTROY(&PANDA_G(reosurce_index_object_chilrens_table));
    return SUCCESS;
}

int panda_resource_set_resource(const char *type, char *host, int port, ulong hash TSRMLS_DC)
{
    zval *map = PANDA_G(resources_maps);
    int status = FAILURE;
    zval *new_val;
    do {
        PANDA_ARRAY_INIT(new_val);
        add_assoc_string(new_val, PANDA_NODE_RESOURCE_MAPS_HOST, host, PANDA_TRUE);
        add_assoc_string(new_val, PANDA_NODE_RESOURCE_MAPS_TYPE, (char *)type, PANDA_TRUE);
        add_assoc_long(new_val, PANDA_NODE_RESOURCE_MAPS_PORT, port);
        add_assoc_long(new_val, PANDA_NODE_RESOURCE_MAPS_HASH, hash);
        add_next_index_zval(map, new_val);
        Z_ADDREF_P(new_val);
        PANDA_ARRAY_DESTROY(new_val);
        status = SUCCESS;
    } while (0);
    return status;
}

int panda_resource_get_resource_last_insert_id(const char *type, int *resource_id TSRMLS_DC)
{
    int status = FAILURE;
    zval *map = PANDA_G(resources_maps);
    zval **type_map_p;
    do {
        if (zend_hash_find(Z_ARRVAL_P(map), type, PANDA_STRLEN(type), (void **)&type_map_p) == SUCCESS) {
            *resource_id = (int)PANDA_ARRAY_COUNT(*type_map_p) - 1;
            status = SUCCESS;
        }
    } while(0);
    return status;
}

int panda_resource_get_resource_id_with_hashkey(ulong hash, int *resource_id TSRMLS_DC)
{
    HashTable *ht = &PANDA_G(resource_index_hashkey_resources_table);
    int status = FAILURE;
    do {
        int *data;
        if (zend_hash_index_find(ht, hash, (void **)&data) == SUCCESS) {
            *resource_id = *data;
            status = SUCCESS;
        }
    } while (0);
    return status;
}

int panda_resource_set_resource_id_with_hashkey(ulong hash, int resource_id TSRMLS_DC)
{
    HashTable *ht = &PANDA_G(resource_index_hashkey_resources_table);
    return zend_hash_index_update(ht, hash, (void *)&resource_id, sizeof(int), NULL);
}

int panda_resource_set_resource_id_with_instance_id(ulong instance_id, int resource_id TSRMLS_DC)
{
    HashTable *ht = &PANDA_G(resource_index_object_resources_table);
    return zend_hash_index_update(ht, instance_id, (void *)&resource_id, sizeof(int), NULL);
}

int panda_resource_get_resource_id_with_instance_id(ulong instance_id, int *resource_id TSRMLS_DC)
{
    HashTable *ht = &PANDA_G(resource_index_object_resources_table);
    int status = FAILURE;
    do {
        int *data;
        if (zend_hash_index_find(ht, instance_id, (void **)&data) == SUCCESS) {
              *resource_id = *data;
              status = SUCCESS;
          }
     } while (0);
    return status;
}

int panda_resource_set_last_instance_id(const char* ext, int instance_id TSRMLS_DC)
{
    HashTable *ht = &PANDA_G(resource_index_last_instances_table);
    return zend_hash_update(ht, ext, PANDA_STRLEN(ext), (void *)&instance_id, sizeof(int), NULL);
}

int panda_resource_get_last_instance_id(const char* ext, int *instance_id TSRMLS_DC)
{
    HashTable *ht = &PANDA_G(resource_index_last_instances_table);
    int status = FAILURE;
    do {
        int *data;
        if (zend_hash_find(ht, ext, PANDA_STRLEN(ext), (void **)&data) == SUCCESS) {
            *instance_id = *data;
            status = SUCCESS;
        }
    } while (0);
    return status;
}

int panda_resource_set_sql(const char *type, char *sql TSRMLS_DC)
{
    int status = FAILURE;
    zval **type_map_p;
    zval *maps = PANDA_G(resources_sqls);

    do {
        if (zend_hash_find(Z_ARRVAL_P(maps), type, PANDA_STRLEN(type), (void **)&type_map_p) == FAILURE) {
            zval *new_type_map;
            PANDA_ARRAY_INIT(new_type_map);
            add_index_string(new_type_map, 0, sql, 1);
            add_assoc_zval(maps, type, new_type_map);
            Z_ADDREF_P(new_type_map);
            PANDA_ARRAY_DESTROY(new_type_map);
        } else {
            zval *type_map = *type_map_p;
            if (Z_TYPE_P(type_map) == IS_ARRAY) {
                add_next_index_string(type_map, sql, 1);
            }
        }
        status = SUCCESS;
    } while(0);
    return SUCCESS;
}

int panda_resource_get_sql_last_id(const char *type, int *sql_id TSRMLS_DC)
{
    int status = FAILURE;
    zval *map = PANDA_G(resources_sqls);
    zval **type_map_p;
    do {
        if (zend_hash_find(Z_ARRVAL_P(map), type, PANDA_STRLEN(type), (void **)&type_map_p) == SUCCESS) {
            *sql_id = (int)PANDA_ARRAY_COUNT(*type_map_p) - 1;
            status = SUCCESS;
        }
    } while(0);
    return status;
}

int panda_resource_set_db_with_instance_id(ulong instance_id, const char *db TSRMLS_DC)
{

    HashTable *ht = &PANDA_G(resource_index_object_dbs_table);
    return zend_hash_index_update(ht, instance_id, (void **)&db, sizeof(db), NULL);
}

int panda_resource_get_db_with_instance_id(ulong instance_id, char **db TSRMLS_DC)
{
    HashTable *ht = &PANDA_G(resource_index_object_dbs_table);
    int status = FAILURE;
    do {
        char **data;
        if (zend_hash_index_find(ht, instance_id, (void **)&data) == SUCCESS) {
              *db = *data;
              status = SUCCESS;
        }
     } while (0);
    return status;
}

int panda_resource_set_prepare_sql_with_stmt_id(ulong stmt_id, char *prepare_sql TSRMLS_DC)
{
    HashTable *ht = &PANDA_G(resource_index_object_prepare_sqls_table);
    return zend_hash_index_update(ht, stmt_id, (void **)&prepare_sql, sizeof(prepare_sql), NULL);
}

int panda_resource_get_prepare_sql_with_stmt_id(ulong stmt_id, char **prepare_sql TSRMLS_DC)
{
    HashTable *ht = &PANDA_G(resource_index_object_prepare_sqls_table);
    int status = FAILURE;
    do {
        char **data;
        if (zend_hash_index_find(ht, stmt_id, (void **)&data) == SUCCESS) {
            *prepare_sql = *data;
            status = SUCCESS;
        }
    } while(0);
    return status;
}

int panda_resource_set_instance_id_with_stmt_id(ulong stmt_id, int instance_id TSRMLS_DC)
{
    HashTable *ht = &PANDA_G(resource_index_object_stmt_table);
    return zend_hash_index_update(ht, stmt_id, (void *)&instance_id, sizeof(instance_id), NULL);
}

int panda_resource_get_instance_id_with_stmt_id(ulong stmt_id, int *instance_id TSRMLS_DC)
{
    HashTable *ht = &PANDA_G(resource_index_object_stmt_table);
    int status = FAILURE;
    do {
       int *data;
       if (zend_hash_index_find(ht, stmt_id, (void **)&data) == SUCCESS) {
           *instance_id = *data;
           status = SUCCESS;
       }
    } while(0);
    return status;
}

int panda_resource_set_url_entity_with_instance_id(int instance_id, panda_url_entity_t *url_entity TSRMLS_DC)
{
    HashTable *ht = &PANDA_G(resource_index_curl_entity_table);
    return zend_hash_index_update(ht, instance_id, (void **)&url_entity, sizeof(panda_url_entity_t), NULL);
}

int panda_resource_get_url_entity_with_instance_id(int instance_id, panda_url_entity_t  **url_entity TSRMLS_DC)
{
    HashTable *ht = &PANDA_G(resource_index_curl_entity_table);
    int status = FAILURE;
    do {
        void **data;
        if (zend_hash_index_find(ht, instance_id, (void **)&data) == SUCCESS) {
            *url_entity = *data;
            status = SUCCESS;
        }
    } while(0);
    return status;
}

int panda_resource_set_child_instances_with_instance_id(int instance_id, zval *child_instances TSRMLS_DC)
{
    HashTable *ht = &PANDA_G(reosurce_index_object_chilrens_table);
    return zend_hash_index_update(ht, instance_id, (void **)&child_instances, sizeof(zval), NULL);
}

int panda_resource_get_child_instances_with_instance_id(int instance_id, zval **child_instances TSRMLS_DC)
{
    HashTable *ht = &PANDA_G(reosurce_index_object_chilrens_table);
    int status = FAILURE;
    do {
        void **data;
        if (zend_hash_index_find(ht, instance_id, (void **)&data) == SUCCESS) {
            *child_instances = *data;
            status = SUCCESS;
        }
    } while(0);
    return status;
}
