#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_panda.h"
#include "panda_expend.h"
#include "panda_stack.h"
#include "panda_resource.h"
#include "expends/memcached/memcached.h"

ZEND_EXTERN_MODULE_GLOBALS(panda);

PANDA_METHOD(memcached, add)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_ADD, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key;
    ulong val_len;

    zval *key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);

}

PANDA_METHOD(memcached, addbykey)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_ADD_BY_KEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key, *server_key;
    ulong val_len;

    zval *server_key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *key_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    zval *val_val = panda_stack_get_execute_param(execute_data, 2 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    server_key = Z_STRVAL_P(server_key_val);

    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SERVER_KEY, server_key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(memcached, addserver)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_ADD_SERVER, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    zval *host_val, *port_val;
    char *host;
    int port;
    int resource_id, instance_id;

    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    host_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    port_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    host = Z_STRVAL_P(host_val);
    port = (int)Z_LVAL_P(port_val);

    ulong host_port_hash = panda_stack_get_resource_hash(host, port TSRMLS_CC);

    if (panda_resource_get_resource_id_with_hashkey(host_port_hash, &resource_id TSRMLS_CC) == FAILURE) {
        panda_resource_set_resource(PANDA_RESOURCE_TYPE_MEMCACHE, host, port TSRMLS_CC);
        if (panda_resource_get_resource_last_insert_id(PANDA_RESOURCE_TYPE_MEMCACHE, &resource_id TSRMLS_CC) == SUCCESS) {
            panda_resource_set_resource_id_with_hashkey(host_port_hash, resource_id TSRMLS_CC);
        }
    }

    panda_resource_set_last_instance_id(PANDA_EXPENDS_EXT_MEMCACHED, instance_id TSRMLS_CC);

    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MEMCACHE, PANDA_TRUE);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, addservers)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_ADD_SERVERS, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int count, i;
    int resource_id, instance_id;

    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    zval *servers_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);;
    count = zend_hash_num_elements(Z_ARRVAL_P(servers_val));
    zend_hash_internal_pointer_reset(Z_ARRVAL_P(servers_val));

    zval* resource_ids;
    PANDA_ARRAY_INIT(resource_ids);

    Z_ADDREF_P(resource_ids);
    add_assoc_zval(expend_data, PANDA_NODE_STACK_MAPs_REFRENCES_RESOURCE_IDS, resource_ids);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MEMCACHE, PANDA_TRUE);

    for (i = 0; i < count; i ++) {
        char* host = NULL;
        int port = -1;
        zval **z_item, **host_item, **port_item;

        zend_hash_get_current_data(Z_ARRVAL_P(servers_val), (void**) &z_item);
        if (zend_hash_index_find(Z_ARRVAL_PP(z_item), 0, (void **)&host_item) == SUCCESS) {
            host = Z_STRVAL_PP(host_item);
        }

        if (zend_hash_index_find(Z_ARRVAL_PP(z_item), 1, (void **)&port_item) == SUCCESS) {
            port = (int)Z_LVAL_PP(port_item);
        }

        ulong host_port_hash = panda_stack_get_resource_hash(host, port TSRMLS_CC);

        if (panda_resource_get_resource_id_with_hashkey(host_port_hash, &resource_id TSRMLS_CC) == FAILURE) {
            panda_resource_set_resource(PANDA_RESOURCE_TYPE_MEMCACHE, host, port TSRMLS_CC);
            if (panda_resource_get_resource_last_insert_id(PANDA_RESOURCE_TYPE_MEMCACHE, &resource_id TSRMLS_CC) == SUCCESS) {
                panda_resource_set_resource_id_with_hashkey(host_port_hash, resource_id TSRMLS_CC);
            }
        }

        panda_resource_set_last_instance_id(PANDA_EXPENDS_EXT_MEMCACHED, instance_id TSRMLS_CC);
        add_next_index_long(resource_ids, resource_id);

        zend_hash_move_forward(Z_ARRVAL_P(servers_val));
    }

    PANDA_ARRAY_DESTROY(resource_ids);
    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, append)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_APPEND, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key;
    ulong val_len;

    zval *key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, appendbykey)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_APPEND_BY_KEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key, *server_key;
    ulong val_len;

    zval *server_key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *key_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    zval *val_val = panda_stack_get_execute_param(execute_data, 2 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    server_key = Z_STRVAL_P(server_key_val);

    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SERVER_KEY, server_key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, decrement)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_DECREMENT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key;
    zval *key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, decrementbykey)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_DECREMENT_BY_KEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key, *server_key;
    ulong val_len;

    zval *server_key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *key_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    server_key = Z_STRVAL_P(server_key_val);

    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SERVER_KEY, server_key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(memcached, delete)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_DELETE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key;
    ulong val_len;

    zval *key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(memcached, deletebykey)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_DELETE_BY_KEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key, *server_key;
    ulong val_len;

    zval *server_key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *key_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    server_key = Z_STRVAL_P(server_key_val);

    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SERVER_KEY, server_key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, deletemulti)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_DELETE_MULTI, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, deletemultibykey)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_APPEND_BY_KEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);



    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, get)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_GET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key;
    ulong val_len;

    zval *key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, getbykey)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_GET_BY_KEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key, *server_key;
    ulong val_len;

    zval *server_key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *key_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    zval *val_val = panda_stack_get_execute_param(execute_data, 2 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    server_key = Z_STRVAL_P(server_key_val);

    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SERVER_KEY, server_key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, getdelayed)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_GET_DELAYED, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    zval *keys_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    add_assoc_zval(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEYS, keys_val);
    Z_ADDREF_P(keys_val);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, getmulti)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_GET_MULTI, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    zval *keys_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    add_assoc_zval(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEYS, keys_val);
    Z_ADDREF_P(keys_val);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, getmultibykey)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_GET_MULTI_BY_KEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    zval *server_key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *keys_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SERVER_KEY, Z_STRVAL_P(server_key_val), PANDA_TRUE);
    add_assoc_zval(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEYS, keys_val);
    Z_ADDREF_P(keys_val);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, increment)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_INCREMENT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key;
    ulong val_len;

    zval *key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, incrementbykey)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_INCREMENT_BY_KEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key, *server_key;
    ulong val_len;

    zval *server_key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *key_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    server_key = Z_STRVAL_P(server_key_val);

    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SERVER_KEY, server_key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, prepend)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_PREPEND, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key;
    ulong val_len;

    zval *key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, prependbykey)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_PREPEND_BY_KEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key, *server_key;
    ulong val_len;

    zval *server_key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *key_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    zval *val_val = panda_stack_get_execute_param(execute_data, 2 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    server_key = Z_STRVAL_P(server_key_val);

    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SERVER_KEY, server_key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, replace)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_REPLACE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key;
    ulong val_len;

    zval *key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, replacebykey)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_REPLACE_BY_KEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key, *server_key;
    ulong val_len;

    zval *server_key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *key_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    zval *val_val = panda_stack_get_execute_param(execute_data, 2 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    server_key = Z_STRVAL_P(server_key_val);

    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SERVER_KEY, server_key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, set)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_SET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key;
    ulong val_len;

    zval *key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, setbykey)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_REPLACE_BY_KEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key, *server_key;
    ulong val_len;

    zval *server_key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *key_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    zval *val_val = panda_stack_get_execute_param(execute_data, 2 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    server_key = Z_STRVAL_P(server_key_val);

    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SERVER_KEY, server_key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, setmulti)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_SET_MULTI, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    zval *items_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    int count, i;
    zval **z_item;
    zval *items;

    PANDA_ARRAY_INIT(items);
    count = zend_hash_num_elements(Z_ARRVAL_P(items_val));
    zend_hash_internal_pointer_reset(Z_ARRVAL_P(items_val));

    for (i = 0; i < count; i ++) {
        char* key;
        ulong idx;
        zval *item;
        PANDA_ARRAY_INIT(item);

        zend_hash_get_current_data(Z_ARRVAL_P(items_val), (void**) &z_item);
        zend_hash_get_current_key(Z_ARRVAL_P(items_val), &key, &idx, 0);
        zend_hash_move_forward(Z_ARRVAL_P(items_val));

        add_assoc_string(item, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
        add_assoc_long(item, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_PP(z_item));

        Z_ADDREF_P(item);
        add_next_index_zval(items, item);

        PANDA_ARRAY_DESTROY(item);
    }

    Z_ADDREF_P(items);
    add_assoc_zval(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_ITEMS, items);

    PANDA_ARRAY_DESTROY(items);
    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, setmultibykey)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_SET_MULTI_BY_KEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    zval *server_key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *items_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    int count, i;
    zval **z_item;
    zval *items;

    PANDA_ARRAY_INIT(items);
    count = zend_hash_num_elements(Z_ARRVAL_P(items_val));
    zend_hash_internal_pointer_reset(Z_ARRVAL_P(items_val));

    for (i = 0; i < count; i ++) {
        char* key;
        ulong idx;
        zval *item;
        PANDA_ARRAY_INIT(item);

        zend_hash_get_current_data(Z_ARRVAL_P(items_val), (void**) &z_item);
        zend_hash_get_current_key(Z_ARRVAL_P(items_val), &key, &idx, 0);
        zend_hash_move_forward(Z_ARRVAL_P(items_val));

        add_assoc_string(item, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
        add_assoc_long(item, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_PP(z_item));

        Z_ADDREF_P(item);
        add_next_index_zval(items, item);

        PANDA_ARRAY_DESTROY(item);
    }

    Z_ADDREF_P(items);
    add_assoc_zval(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_ITEMS, items);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SERVER_KEY, Z_STRVAL_P(server_key_val), PANDA_TRUE);

    PANDA_ARRAY_DESTROY(items);
    PANDA_ARRAY_DESTROY(expend_data);

    efree(execute_name);
}

PANDA_METHOD(memcached, fetch)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_SET_MULTI_BY_KEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    zval *server_key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *items_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(memcached, fetchall)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_SET_MULTI_BY_KEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    zval *server_key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *items_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(memcached, quit)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED, \
            PANDA_EXPENDS_EXT_MEMCACHED_CLS_MEMCACHED_METHOD_SET_MULTI_BY_KEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    zval *server_key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *items_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}
