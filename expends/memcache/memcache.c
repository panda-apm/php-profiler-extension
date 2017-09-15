#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_panda.h"
#include "panda_expend.h"
#include "panda_stack.h"
#include "panda_resource.h"
#include "expends/memcache/memcache.h"

ZEND_EXTERN_MODULE_GLOBALS(panda);

PANDA_METHOD(memcache, connect)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHE_CLS_MEMCACHE, \
            PANDA_EXPENDS_EXT_MEMCACHE_CLS_MEMCACHE_METHOD_CONNECT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int resource_id = -1, instance_id;
    instance_id =  Z_OBJ_HANDLE_P(this_ptr);

    char *host = NULL;
    int port;

    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);
    zval *host_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    host = Z_STRVAL_P(host_val);
    if (params_count == 1) {
        port = PANDA_EXPENDS_EXT_MEMCACHE_DEFAULT_PROT;
    }

    if (host && port) {
         ulong host_port_hash = panda_stack_get_resource_hash(host, port TSRMLS_CC);

         if (panda_resource_get_resource_id_with_hashkey(host_port_hash, &resource_id TSRMLS_CC) == FAILURE) {
             panda_resource_set_resource(PANDA_RESOURCE_TYPE_MEMCACHE, host, port, host_port_hash TSRMLS_CC);
             if (panda_resource_get_resource_last_insert_id(PANDA_RESOURCE_TYPE_MEMCACHE, &resource_id TSRMLS_CC) == SUCCESS) {
                 panda_resource_set_resource_id_with_hashkey(host_port_hash, resource_id TSRMLS_CC);
             }
         }
         panda_resource_set_last_instance_id(PANDA_EXPENDS_EXT_MEMCACHE, instance_id TSRMLS_CC);
    }

    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MEMCACHE, PANDA_TRUE);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}


PANDA_METHOD(memcache, pconnect)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHE_CLS_MEMCACHE, \
            PANDA_EXPENDS_EXT_MEMCACHE_CLS_MEMCACHE_METHOD_PCONNECT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int resource_id = -1, instance_id;
    instance_id =  Z_OBJ_HANDLE_P(this_ptr);

    char *host = NULL;
    int port;

    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);
    zval *host_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    host = Z_STRVAL_P(host_val);
    if (params_count == 1) {
        port = PANDA_EXPENDS_EXT_MEMCACHE_DEFAULT_PROT;
    }

    if (host && port) {
         ulong host_port_hash = panda_stack_get_resource_hash(host, port TSRMLS_CC);
         if (panda_resource_get_resource_id_with_hashkey(host_port_hash, &resource_id TSRMLS_CC) == FAILURE) {
             panda_resource_set_resource(PANDA_RESOURCE_TYPE_MEMCACHE, host, port, host_port_hash TSRMLS_CC);
             if (panda_resource_get_resource_last_insert_id(PANDA_RESOURCE_TYPE_MEMCACHE, &resource_id TSRMLS_CC) == SUCCESS) {
                 panda_resource_set_resource_id_with_hashkey(host_port_hash, resource_id TSRMLS_CC);
             }
         }
         panda_resource_set_last_instance_id(PANDA_EXPENDS_EXT_MEMCACHE, instance_id TSRMLS_CC);
    }

    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MEMCACHE, PANDA_TRUE);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_METHOD(memcache, close)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHE_CLS_MEMCACHE, \
            PANDA_EXPENDS_EXT_MEMCACHE_CLS_MEMCACHE_METHOD_CLOSE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_METHOD(memcache, addserver)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHE_CLS_MEMCACHE, \
            PANDA_EXPENDS_EXT_MEMCACHE_CLS_MEMCACHE_METHOD_ADD_SERVER, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int resource_id = -1, instance_id;
    instance_id =  Z_OBJ_HANDLE_P(this_ptr);

    char *host = NULL;
    int port;

    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);
    zval *host_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    host = Z_STRVAL_P(host_val);
    if (params_count == 1) {
        port = PANDA_EXPENDS_EXT_MEMCACHE_DEFAULT_PROT;
    }

    if (host && port) {
         ulong host_port_hash = panda_stack_get_resource_hash(host, port TSRMLS_CC);

         if (panda_resource_get_resource_id_with_hashkey(host_port_hash, &resource_id TSRMLS_CC) == FAILURE) {
             panda_resource_set_resource(PANDA_RESOURCE_TYPE_MEMCACHE, host, port, host_port_hash TSRMLS_CC);
             if (panda_resource_get_resource_last_insert_id(PANDA_RESOURCE_TYPE_MEMCACHE, &resource_id TSRMLS_CC) == SUCCESS) {
                 panda_resource_set_resource_id_with_hashkey(host_port_hash, resource_id TSRMLS_CC);
             }
         }
         panda_resource_set_last_instance_id(PANDA_EXPENDS_EXT_MEMCACHE, instance_id TSRMLS_CC);
    }

    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MEMCACHE, PANDA_TRUE);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_METHOD(memcache, set)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHE_CLS_MEMCACHE, \
            PANDA_EXPENDS_EXT_MEMCACHE_CLS_MEMCACHE_METHOD_SET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key;
    ulong val_len;

    zval *key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    if (Z_TYPE_P(key_val) == IS_STRING) {
        key = Z_STRVAL_P(key_val);
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    } else if (Z_TYPE_P(key_val) == IS_LONG) {
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, Z_LVAL_P(key_val));
    }

    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));
    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_METHOD(memcache, get)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHE_CLS_MEMCACHE, \
            PANDA_EXPENDS_EXT_MEMCACHE_CLS_MEMCACHE_METHOD_GET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key;
    zval *key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    if (Z_TYPE_P(key_val) == IS_STRING) {
        key = Z_STRVAL_P(key_val);
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    } else if (Z_TYPE_P(key_val) == IS_LONG) {
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, Z_LVAL_P(key_val));
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_METHOD(memcache, delete)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MEMCACHE_CLS_MEMCACHE, \
            PANDA_EXPENDS_EXT_MEMCACHE_CLS_MEMCACHE_METHOD_DELETE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);


    char *key;
    zval *key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    if (Z_TYPE_P(key_val) == IS_STRING) {
        key = Z_STRVAL_P(key_val);
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    } else {
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, Z_LVAL_P(key_val));
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_FUNCTION(memcache_connect)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_MEMCACHE_FUNC_MEMCACHE_CONNECT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int resource_id = -1, instance_id;
    instance_id =  Z_OBJ_HANDLE_P(return_value);

    char *host = NULL;
    int port;

    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);
    zval *host_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    host = Z_STRVAL_P(host_val);
    if (params_count == 1) {
        port = PANDA_EXPENDS_EXT_MEMCACHE_DEFAULT_PROT;
    }

    if (host && port) {
        ulong host_port_hash = panda_stack_get_resource_hash(host, port TSRMLS_CC);

        if (panda_resource_get_resource_id_with_hashkey(host_port_hash, &resource_id TSRMLS_CC) == FAILURE) {
            panda_resource_set_resource(PANDA_RESOURCE_TYPE_MEMCACHE, host, port, host_port_hash TSRMLS_CC);
            if (panda_resource_get_resource_last_insert_id(PANDA_RESOURCE_TYPE_MEMCACHE, &resource_id TSRMLS_CC) == SUCCESS) {
                panda_resource_set_resource_id_with_hashkey(host_port_hash, resource_id TSRMLS_CC);
            }
        }
         panda_resource_set_last_instance_id(PANDA_EXPENDS_EXT_MEMCACHE, instance_id TSRMLS_CC);
    }

    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MEMCACHE, PANDA_TRUE);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_FUNCTION(memcache_pconnect)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_MEMCACHE_FUNC_MEMCACHE_PCONNECT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);


    int resource_id = -1, instance_id;
    instance_id =  Z_OBJ_HANDLE_P(return_value);

    char *host = NULL;
    int port;

    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);
    zval *host_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    host = Z_STRVAL_P(host_val);
    if (params_count == 1) {
        port = PANDA_EXPENDS_EXT_MEMCACHE_DEFAULT_PROT;
    }

    if (host && port) {
        ulong host_port_hash = panda_stack_get_resource_hash(host, port TSRMLS_CC);

        if (panda_resource_get_resource_id_with_hashkey(host_port_hash, &resource_id TSRMLS_CC) == FAILURE) {
            panda_resource_set_resource(PANDA_RESOURCE_TYPE_MEMCACHE, host, port, host_port_hash TSRMLS_CC);
            if (panda_resource_get_resource_last_insert_id(PANDA_RESOURCE_TYPE_MEMCACHE, &resource_id TSRMLS_CC) == SUCCESS) {
                panda_resource_set_resource_id_with_hashkey(host_port_hash, resource_id TSRMLS_CC);
            }
        }
        panda_resource_set_last_instance_id(PANDA_EXPENDS_EXT_MEMCACHE, instance_id TSRMLS_CC);
    }

    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MEMCACHE, PANDA_TRUE);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_FUNCTION(memcache_add_server)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_MEMCACHE_FUNC_MEMCACHE_ADD_SERVER, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int resource_id = -1, instance_id;
    instance_id =  Z_OBJ_HANDLE_P(return_value);

    char *host = NULL;
    int port;

    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);
    zval *host_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    host = Z_STRVAL_P(host_val);
    if (params_count == 1) {
        port = PANDA_EXPENDS_EXT_MEMCACHE_DEFAULT_PROT;
    }

    if (host && port) {
        ulong host_port_hash = panda_stack_get_resource_hash(host, port TSRMLS_CC);

        if (panda_resource_get_resource_id_with_hashkey(host_port_hash, &resource_id TSRMLS_CC) == FAILURE) {
            panda_resource_set_resource(PANDA_RESOURCE_TYPE_MEMCACHE, host, port, host_port_hash TSRMLS_CC);
            if (panda_resource_get_resource_last_insert_id(PANDA_RESOURCE_TYPE_MEMCACHE, &resource_id TSRMLS_CC) == SUCCESS) {
                panda_resource_set_resource_id_with_hashkey(host_port_hash, resource_id TSRMLS_CC);
            }
        }

        panda_resource_set_last_instance_id(PANDA_EXPENDS_EXT_MEMCACHE, instance_id TSRMLS_CC);
    }

    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MEMCACHE, PANDA_TRUE);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_FUNCTION(memcache_set)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_MEMCACHE_FUNC_MEMCACHE_SET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key;

    ulong val_len;

    zval *key_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    zval *val_val = panda_stack_get_execute_param(execute_data, 2 TSRMLS_CC);

    if (Z_TYPE_P(key_val) == IS_STRING) {
        key = Z_STRVAL_P(key_val);
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    } else if (Z_TYPE_P(key_val) == IS_LONG) {
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, Z_LVAL_P(key_val));
    }

    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_FUNCTION(memcache_get)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_MEMCACHE_FUNC_MEMCACHE_GET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key;
    zval *key_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    if (Z_TYPE_P(key_val) == IS_STRING) {
        key = Z_STRVAL_P(key_val);
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    } else if (Z_TYPE_P(key_val) == IS_LONG) {
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, Z_LVAL_P(key_val));
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);

}

PANDA_FUNCTION(memcache_delete)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);
    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_MEMCACHE_FUNC_MEMCACHE_DELETE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *key;
    zval *key_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    if (Z_TYPE_P(key_val) == IS_STRING) {
        key = Z_STRVAL_P(key_val);
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    } else if (Z_TYPE_P(key_val) == IS_LONG) {
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, Z_LVAL_P(key_val));
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_FUNCTION(memcache_close)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_MEMCACHE_FUNC_MEMCACHE_CLOSE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);


    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}
