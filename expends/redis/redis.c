#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "stdlib.h"
#include "php.h"
#include "php_panda.h"
#include "panda_expend.h"
#include "panda_stack.h"
#include "panda_resource.h"
#include "expends/redis/redis.h"

ZEND_EXTERN_MODULE_GLOBALS(panda);
PANDA_METHOD(redis, connect)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_CONNECT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int resource_id = -1, instance_id;
    instance_id =  Z_OBJ_HANDLE_P(this_ptr);
    zval *host_val, *port_val;
    char *host = NULL;
    long port = 0;
    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);

    host_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    host = Z_STRVAL_P(host_val);

    if (params_count == 1) {
        if (host[0] != '/') {
            port = PANDA_EXPENDS_EXT_REDIS_DEFAULT_PROT;
        }
    } else {
        port_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
        port = Z_LVAL_P(port_val);
    }

    if (host && port) {
        ulong host_port_hash = panda_stack_get_resource_hash(host, port TSRMLS_CC);

        if (panda_resource_get_resource_id_with_hashkey(host_port_hash, &resource_id TSRMLS_CC) == FAILURE) {
            panda_resource_set_resource(PANDA_RESOURCE_TYPE_REDIS, host, port, host_port_hash TSRMLS_CC);

            if (panda_resource_get_resource_last_insert_id(PANDA_RESOURCE_TYPE_REDIS, &resource_id TSRMLS_CC) == SUCCESS) {
                panda_resource_set_resource_id_with_hashkey(host_port_hash, resource_id TSRMLS_CC);
            }
            panda_resource_set_resource_id_with_instance_id((ulong)instance_id, resource_id TSRMLS_CC);
            panda_resource_set_last_instance_id(PANDA_RESOURCE_TYPE_REDIS, instance_id TSRMLS_CC);
        }
    }

    if (resource_id >= 0) {
          add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_REDIS, PANDA_TRUE);
          add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, open)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_OPEN, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int resource_id = -1, instance_id;
    instance_id =  Z_OBJ_HANDLE_P(this_ptr);
    zval *host_val, *port_val;
    char *host = NULL;
    long port = 0;
    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);

    host_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    host = Z_STRVAL_P(host_val);

    if (params_count == 1) {
        if (host[0] != '/') {
            port = PANDA_EXPENDS_EXT_REDIS_DEFAULT_PROT;
        }
    } else {
        port_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
        port = Z_LVAL_P(port_val);
    }

    if (host && port) {
        ulong host_port_hash = panda_stack_get_resource_hash(host, port TSRMLS_CC);

        if (panda_resource_get_resource_id_with_hashkey(host_port_hash, &resource_id TSRMLS_CC) == FAILURE) {
            panda_resource_set_resource(PANDA_RESOURCE_TYPE_REDIS, host, port, host_port_hash TSRMLS_CC);

            if (panda_resource_get_resource_last_insert_id(PANDA_RESOURCE_TYPE_REDIS, &resource_id TSRMLS_CC) == SUCCESS) {
                panda_resource_set_resource_id_with_hashkey(host_port_hash, resource_id TSRMLS_CC);
            }
            panda_resource_set_resource_id_with_instance_id((ulong)instance_id, resource_id TSRMLS_CC);
            panda_resource_set_last_instance_id(PANDA_RESOURCE_TYPE_REDIS, instance_id TSRMLS_CC);
        }
    }

    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_REDIS, PANDA_TRUE);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, popen)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_POPEN, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int resource_id = -1, instance_id;
    instance_id =  Z_OBJ_HANDLE_P(this_ptr);
    zval *host_val, *port_val;
    char *host = NULL;
    long port = 0;
    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);

    host_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    host = Z_STRVAL_P(host_val);

    if (params_count == 1) {
        if (host[0] != '/') {
            port = PANDA_EXPENDS_EXT_REDIS_DEFAULT_PROT;
        }
    } else {
        port_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
        port = Z_LVAL_P(port_val);
    }

    if (host && port) {
        ulong host_port_hash = panda_stack_get_resource_hash(host, port TSRMLS_CC);
        if (panda_resource_get_resource_id_with_hashkey(host_port_hash, &resource_id TSRMLS_CC) == FAILURE) {
            panda_resource_set_resource(PANDA_RESOURCE_TYPE_REDIS, host, port, host_port_hash TSRMLS_CC);

            if (panda_resource_get_resource_last_insert_id(PANDA_RESOURCE_TYPE_REDIS, &resource_id TSRMLS_CC) == SUCCESS) {
                panda_resource_set_resource_id_with_hashkey(host_port_hash, resource_id TSRMLS_CC);
            }
            panda_resource_set_resource_id_with_instance_id((ulong)instance_id, resource_id TSRMLS_CC);
            panda_resource_set_last_instance_id(PANDA_RESOURCE_TYPE_REDIS, instance_id TSRMLS_CC);
        }
    }

    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_REDIS, PANDA_TRUE);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, pconnect)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_PCONNECT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int resource_id = -1, instance_id;
    instance_id =  Z_OBJ_HANDLE_P(this_ptr);
    zval *host_val, *port_val;
    char *host = NULL;
    long port = 0;
    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);

    host_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    host = Z_STRVAL_P(host_val);

    if (params_count == 1) {
        if (host[0] != '/') {
            port = PANDA_EXPENDS_EXT_REDIS_DEFAULT_PROT;
        }
    } else {
        port_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
        port = Z_LVAL_P(port_val);
    }

    if (host && port) {
        ulong host_port_hash = panda_stack_get_resource_hash(host, port TSRMLS_CC);

        if (panda_resource_get_resource_id_with_hashkey(host_port_hash, &resource_id TSRMLS_CC) == FAILURE) {
            panda_resource_set_resource(PANDA_RESOURCE_TYPE_REDIS, host, port, host_port_hash TSRMLS_CC);

            if (panda_resource_get_resource_last_insert_id(PANDA_RESOURCE_TYPE_REDIS, &resource_id TSRMLS_CC) == SUCCESS) {
                panda_resource_set_resource_id_with_hashkey(host_port_hash, resource_id TSRMLS_CC);
            }
            panda_resource_set_resource_id_with_instance_id((ulong)instance_id, resource_id TSRMLS_CC);
            panda_resource_set_last_instance_id(PANDA_RESOURCE_TYPE_REDIS, instance_id TSRMLS_CC);
        }
    }

    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_REDIS, PANDA_TRUE);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, select)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);
    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SELECT, &_func);

    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);

    int instance_id;
    zval *db_val;

    db_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    convert_to_string(db_val);
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    Z_ADDREF_P(db_val);
    panda_resource_set_db_with_instance_id(instance_id, Z_STRVAL_P(db_val) TSRMLS_CC);

    efree(execute_name);
}

PANDA_METHOD(redis, close)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_CLOSE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, get)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_GET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, set)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, setex)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SETEX, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 2 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, psetex)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_PSETEX, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);


    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 2 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, setnx)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SETNX, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, exists)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_EXISTS, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, delete)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_DELETE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, del)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_DEL, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, incr)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_INCR, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, incrby)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_INCRBY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, incrbyfloat)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_INCRBYFLOAT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, decr)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_DECR, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, decrby)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_DECRBY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, mget)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_MGET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *keys_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    keys_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    add_assoc_zval(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEYS, keys_val);
    Z_ADDREF_P(keys_val);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, getmultiple)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_GETMULTIPLE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *keys_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    keys_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    add_assoc_zval(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEYS, keys_val);
    Z_ADDREF_P(keys_val);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, getset)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_GETSET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, move)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_MOVE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);

    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, expireat)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_EXPIREAT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, pexpireat)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_PEXPIREAT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, keys)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_KEYS, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, getkeys)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_GETKEYS, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, append)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_APPEND, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, getrange)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_GETRANGE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, setrange)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SETRANGE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 2 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }
    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, strlen)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_STRLEN, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, ttl)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_TTL, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, pttl)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_PTTL, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, rename)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_RENAME, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    char *db;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }


    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, renamekey)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_RENAMEKEY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    char *db;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, renamenx)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_RENAMENX, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    char *db;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, sort)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SORT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    char *db;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, persist)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_GETKEYS, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, mset)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_MSET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    int count, i;
    char *db;
    zval **z_item;
    zval *items;
    zval *items_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

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

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, msetnx)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_MSETNX, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    int count, i;
    char *db;
    zval **z_item;
    zval *items;
    zval *items_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

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

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, hdel)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_HDEL, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *field_val;
    char *key, *field, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    field_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    field = Z_STRVAL_P(field_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_FIELD, field, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, hexists)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_HEXISTS, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *field_val;
    char *key, *field, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    field_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    field = Z_STRVAL_P(field_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_FIELD, field, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, hget)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_HGET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *field_val;
    char *key, *field, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    field_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    field = Z_STRVAL_P(field_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_FIELD, field, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, hgetall)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_HGETALL, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, hincrby)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_HINCRBY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *field_val;
    char *key, *field, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    field_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    field = Z_STRVAL_P(field_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_FIELD, field, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, hincrbyfloat)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_HINCRBY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *field_val;
    char *key, *field, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    field_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    field = Z_STRVAL_P(field_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_FIELD, field, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, hkeys)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_HKEYS, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, hlen)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_HLEN, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, hmset)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_HMSET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    int count, i;
    char *key, *db;
    zval **z_item;
    zval *items;
    zval *key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *items_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    key = Z_STRVAL_P(key_val);
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
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_zval(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_ITEMS, items);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, hmget)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_HMGET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *fields_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    fields_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    add_assoc_zval(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_FIELDS, fields_val);
    Z_ADDREF_P(fields_val);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);

}

PANDA_METHOD(redis, hset)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_HSET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *field_val, *val_val;
    char *key, *field, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    field_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 2 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    field = Z_STRVAL_P(field_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_FIELD, field, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }


    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);

}


PANDA_METHOD(redis, hsetnx)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_HSETNX, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *field_val, *val_val;
    char *key, *field, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    field_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 2 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    field = Z_STRVAL_P(field_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_FIELD, field, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, hvals)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_HVALS, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *field_val;
    char *key, *field, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    field = Z_STRVAL_P(field_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, blpop)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_BLPOP, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, brpop)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_BRPOP, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    char *db;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, brpoplpush)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_BRPOPLPUSH, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    char *db;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, lindex)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_LINDEX, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *pos_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    pos_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_POS, Z_LVAL_P(pos_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, lget)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_LGET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *pos_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    pos_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_POS, Z_LVAL_P(pos_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, lpop)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_LPOP, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, lpush)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_LPUSH, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, lpushx)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_LPUSHX, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, lrange)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_LRANGE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, lgetrange)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_LGETRANGE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, lset)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PADNA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_LSET, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *pos_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    pos_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_POS, Z_LVAL_P(pos_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);

}

PANDA_METHOD(redis, ltrim)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_LTRIM, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);

}

PANDA_METHOD(redis, listtrim)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_LISTTRIM, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);

}

PANDA_METHOD(redis, rpop)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_RPOP, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }


    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, rpoplpush)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_RPOPLPUSH, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    char *db;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);

}

PANDA_METHOD(redis, rpush)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_RPUSH, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, rpushx)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_RPUSHX, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, llen)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_LLEN, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }


    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, lsize)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_LSIZE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }


    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, sadd)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SADD, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }


    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);

}


PANDA_METHOD(redis, scard)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SCARD, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);

}

PANDA_METHOD(redis, ssize)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SSIZE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, sdiff)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SDIFF, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    char *db;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, sdiffstore)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SDIFFSTORE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    char *db;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, sinter)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SINTER, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    char *db;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, sinterstore)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SINTERSTORE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    char *db;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, sismember)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SISMEMBER, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, scontains)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SCONTAINS, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);

}

PANDA_METHOD(redis, smembers)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SMEMBERS, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }


    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, sgetmembers)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SGETMEMBERS, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }


    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, smove)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SMOVE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    char *db;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, spop)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SPOP, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, srandmember)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SRANDMEMBER, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }


    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, srem)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SREM, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, sremove)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SREMOVE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }


    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, sunion)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SUNION, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    char *db;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, sunionstore)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SUNIONSTORE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    char *db;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, zadd)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZADD, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 2 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }


    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);

}

PANDA_METHOD(redis, zcard)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZCARD, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, zsize)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZSIZE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);

}

PANDA_METHOD(redis, zcount)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZCOUNT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);

}

PANDA_METHOD(redis, zincrby)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZINCRBY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 2 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }


    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, zrange)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZRANGE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, zrangebyscore)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZRANGEBYSCORE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, zrevrangebyscore)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZREVRANGEBYSCORE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, zrangebylex)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZRANGEBYLEX, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, zrank)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZRANK, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, zrevrank)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZREVRANK, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, zrem)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZREM, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }


    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);

}

PANDA_METHOD(redis, zdelete)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZDELETE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, zremrangebyrank)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZREMRANGEBYRANK, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);

}

PANDA_METHOD(redis, zdeleterangebyrank)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZDELETERANGEBYRANK, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, zremrangebyscore)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZREMRANGEBYSCORE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);


    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, zdeleterangebyscore)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZDELETERANGEBYSCORE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, zrevrange)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZREVRANGE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}


PANDA_METHOD(redis, zscore)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZSCORE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val, *val_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);
    add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE, Z_STRLEN_P(val_val));

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, zunion)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_ZUNION, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *key_val;
    char *key, *db = NULL;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    key_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    key = Z_STRVAL_P(key_val);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_KEY, key, PANDA_TRUE);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    } else {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, PANDA_EXPENDS_EXT_REDIS_DEFAULT_DB, PANDA_TRUE);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, psubscribe)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_PSUBSCRIBE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, publish)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_PUBLISH, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, subscribe)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SUBSCRIBE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, pubsub)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_PUBSUB, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, eval)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_EVAL, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(redis, script)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_REDIS_CLS_REDIS, \
            PANDA_EXPENDS_EXT_REDIS_CLS_REDIS_METHOD_SCRIPT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}
