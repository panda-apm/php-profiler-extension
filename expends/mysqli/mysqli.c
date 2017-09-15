#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "stdlib.h"
#include "php.h"
#include "php_panda.h"
#include "panda_expend.h"
#include "panda_stack.h"
#include "panda_resource.h"
#include "expends/mysqli/mysqli.h"

ZEND_EXTERN_MODULE_GLOBALS(panda);

PANDA_METHOD(mysqli, mysqli)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI, \
            PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI_METHOD_MYSQLI, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int resource_id = -1, instance_id;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    char *host = NULL; int port;
    if (params_count > 0) {
        zval *host_val, *port_val, *db_val;
        char *db_name = NULL;
        host_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
        host = Z_STRVAL_P(host_val);

        if (params_count > 3) {
            db_val = panda_stack_get_execute_param(execute_data, 3 TSRMLS_CC);
            db_name = Z_STRVAL_P(db_val);
            panda_resource_set_db_with_instance_id(instance_id, db_name TSRMLS_CC);
        }

        if (params_count > 4) {
            port_val = panda_stack_get_execute_param(execute_data, 4 TSRMLS_CC);
            if (Z_TYPE_P(port_val) == IS_LONG) {
                port = Z_LVAL_P(port_val);
            } else {
                port = atoi(Z_STRVAL_P(port_val));
            }
        } else {
            port = PANDA_EXPENDS_EXT_MYSQLI_DEFAULT_PROT;
        }
    }

    if (host && port) {
         ulong host_port_hash = panda_stack_get_resource_hash(host, port TSRMLS_CC);

         if (panda_resource_get_resource_id_with_hashkey(host_port_hash, &resource_id TSRMLS_CC) == FAILURE) {
             panda_resource_set_resource(PANDA_RESOURCE_TYPE_MYSQL, host, port, host_port_hash TSRMLS_CC);
             if (panda_resource_get_resource_last_insert_id(PANDA_RESOURCE_TYPE_MYSQL, &resource_id TSRMLS_CC) == SUCCESS) {
                 panda_resource_set_resource_id_with_hashkey(host_port_hash, resource_id TSRMLS_CC);
             }
         }
         panda_resource_set_resource_id_with_instance_id((ulong)instance_id, resource_id TSRMLS_CC);
         panda_resource_set_last_instance_id(PANDA_EXPENDS_EXT_MYSQLI, instance_id TSRMLS_CC);
    }

    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MYSQL, PANDA_TRUE);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}


PANDA_FUNCTION(mysqli_connect)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_MYSQLI_FUNC_MYSQLI_CONNECT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int resource_id = -1, instance_id;
    instance_id = Z_OBJ_HANDLE_P(return_value);

    char *host = NULL, *db_name = NULL;int port;
    if (params_count > 0) {
        zval *host_val, *port_val, *db_val;
        host_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
        host = Z_STRVAL_P(host_val);

        if (params_count > 3) {
            db_val = panda_stack_get_execute_param(execute_data, 3 TSRMLS_CC);
            db_name = Z_STRVAL_P(db_val);
            panda_resource_set_db_with_instance_id(instance_id, db_name TSRMLS_CC);
        }

        if (params_count > 4) {
            port_val = panda_stack_get_execute_param(execute_data, 4 TSRMLS_CC);
            if (Z_TYPE_P(port_val) == IS_LONG) {
                port = Z_LVAL_P(port_val);
            } else {
                port = atoi(Z_STRVAL_P(port_val));
            }
        } else {
            port = PANDA_EXPENDS_EXT_MYSQLI_DEFAULT_PROT;
        }
    }

    if (host && port) {
         ulong host_port_hash = panda_stack_get_resource_hash(host, port TSRMLS_CC);

         if (panda_resource_get_resource_id_with_hashkey(host_port_hash, &resource_id TSRMLS_CC) == FAILURE) {
             panda_resource_set_resource(PANDA_RESOURCE_TYPE_MYSQL, host, port, host_port_hash TSRMLS_CC);
             if (panda_resource_get_resource_last_insert_id(PANDA_RESOURCE_TYPE_MYSQL, &resource_id TSRMLS_CC) == SUCCESS) {
                 panda_resource_set_resource_id_with_hashkey(host_port_hash, resource_id TSRMLS_CC);
             }
         }

         panda_resource_set_resource_id_with_instance_id((ulong)instance_id, resource_id TSRMLS_CC);
         panda_resource_set_last_instance_id(PANDA_EXPENDS_EXT_MYSQLI, instance_id TSRMLS_CC);
    }

    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MYSQL, PANDA_TRUE);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_METHOD(mysqli, query)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI, \
            PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI_METHOD_QUERY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id, resource_id = -1, sql_id = -1;
    zval *sql_val;
    char *sql, *db;
    sql_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    sql = Z_STRVAL_P(sql_val);

    if (panda_resource_set_sql(PANDA_RESOURCE_TYPE_MYSQL, sql TSRMLS_CC) == SUCCESS) {
        panda_resource_get_sql_last_id(PANDA_RESOURCE_TYPE_MYSQL, &sql_id TSRMLS_CC);
    }

    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    panda_resource_get_resource_id_with_instance_id((ulong)instance_id, &resource_id TSRMLS_CC);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    }
    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MYSQL, PANDA_TRUE);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    if (sql_id >= 0) {
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SQL_ID, sql_id);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_FUNCTION(mysqli_query)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI, \
            PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI_METHOD_QUERY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id, resource_id = -1, sql_id = -1;
    zval *sql_val, *instance_val;
    char *sql, *db;
    sql_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    sql = Z_STRVAL_P(sql_val);

    if (panda_resource_set_sql(PANDA_RESOURCE_TYPE_MYSQL, sql TSRMLS_CC) == SUCCESS) {
        panda_resource_get_sql_last_id(PANDA_RESOURCE_TYPE_MYSQL, &sql_id TSRMLS_CC);
    }

    instance_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    instance_id = Z_OBJ_HANDLE_P(instance_val);

    panda_resource_get_resource_id_with_instance_id((ulong)instance_id, &resource_id TSRMLS_CC);

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    }

    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MYSQL, PANDA_TRUE);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    if (sql_id >= 0) {
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SQL_ID, sql_id);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(mysqli, select_db)
{
    zend_execute_data *execute_data = EG(current_execute_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI, \
            PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI_METHOD_SELECT_DB, &_func);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);

    char *db_name;
    zval *db_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    int instance_id = Z_OBJ_HANDLE_P(this_ptr);
    db_name = Z_STRVAL_P(db_val);

    panda_resource_set_db_with_instance_id(instance_id, db_name TSRMLS_CC);
}

PANDA_FUNCTION(mysqli_select_db)
{
    zend_execute_data *execute_data = EG(current_execute_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_MYSQLI_FUNC_MYSQLI_SELECT_DB, &_func);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);

    char *db_name;
    int instance_id;
    zval *instance_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *db_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    instance_id = Z_OBJ_HANDLE_P(instance_val);
    db_name = Z_STRVAL_P(db_val);

    panda_resource_set_db_with_instance_id(instance_id, db_name TSRMLS_CC);
}


PANDA_METHOD(mysqli, prepare)
{
    zend_execute_data *execute_data = EG(current_execute_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI, \
            PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI_METHOD_PREPARE, &_func);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);

    char *prepare_sql;
    int stmt_id, instance_id;
    zval *sql_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    stmt_id = Z_OBJ_HANDLE_P(return_value);
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    prepare_sql = Z_STRVAL_P(sql_val);

    panda_resource_set_prepare_sql_with_stmt_id(stmt_id, prepare_sql TSRMLS_CC);
    panda_resource_set_instance_id_with_stmt_id(stmt_id, instance_id TSRMLS_CC);
}

PANDA_FUNCTION(mysqli_prepare)
{
    zend_execute_data *execute_data = EG(current_execute_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_MYSQLI_FUNC_MYSQLI_PREPARE, &_func);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);

    char *prepare_sql;
    int  stmt_id, instance_id;
    zval *instance_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *sql_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);

    stmt_id = Z_OBJ_HANDLE_P(return_value);
    prepare_sql = Z_STRVAL_P(sql_val);
    instance_id = Z_OBJ_HANDLE_P(instance_val);

    panda_resource_set_prepare_sql_with_stmt_id(stmt_id, prepare_sql TSRMLS_CC);
    panda_resource_set_instance_id_with_stmt_id(stmt_id, instance_id TSRMLS_CC);
}



PANDA_METHOD(mysqli, stmt_init)
{
    zend_execute_data *execute_data = EG(current_execute_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI, \
            PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI_METHOD_STMT_INIT, &_func);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);

    int stmt_id, instance_id;
    stmt_id = Z_OBJ_HANDLE_P(return_value);
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

    panda_resource_set_instance_id_with_stmt_id(stmt_id, instance_id TSRMLS_CC);
}


PANDA_METHOD(mysqli_stmt, prepare)
{
    zend_execute_data *execute_data = EG(current_execute_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI_STMT, \
            PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI_STMT_METHOD_PREPARE, &_func);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);

    int stmt_id;
    char *prepare_sql;
    zval *sql_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    prepare_sql = Z_STRVAL_P(sql_val);
    stmt_id = Z_OBJ_HANDLE_P(this_ptr);
    panda_resource_set_prepare_sql_with_stmt_id(stmt_id, prepare_sql TSRMLS_CC);
}

PANDA_METHOD(mysqli_stmt, execute)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI_STMT, \
            PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI_STMT_METHOD_EXECUTE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *prepare_sql, *db = NULL;
    int stmt_id, instance_id, resource_id, sql_id = -1;
    stmt_id = Z_OBJ_HANDLE_P(this_ptr);


    if (panda_resource_get_prepare_sql_with_stmt_id(stmt_id, &prepare_sql TSRMLS_CC) == SUCCESS) {
        if (panda_resource_set_sql(PANDA_RESOURCE_TYPE_MYSQL, prepare_sql TSRMLS_CC) == SUCCESS) {
            panda_resource_get_sql_last_id(PANDA_RESOURCE_TYPE_MYSQL, &sql_id TSRMLS_CC);
        }
    }

    if (panda_resource_get_instance_id_with_stmt_id(stmt_id, &instance_id) == SUCCESS) {

        if (panda_resource_get_resource_id_with_instance_id(instance_id, &resource_id) == SUCCESS) {
            add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MYSQL, PANDA_TRUE);
            add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
        }

        if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
            add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
        }
    }

    if (sql_id >= 0) {
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SQL_ID, sql_id);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_FUNCTION(mysqli_stmt_init)
{
    zend_execute_data *execute_data = EG(current_execute_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI, \
            PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI_METHOD_STMT_INIT, &_func);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);

    int stmt_id, instance_id;
    zval *instance_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);

    stmt_id = Z_OBJ_HANDLE_P(return_value);
    instance_id = Z_OBJ_HANDLE_P(instance_val);

    panda_resource_set_instance_id_with_stmt_id(stmt_id, instance_id TSRMLS_CC);
}

PANDA_FUNCTION(mysqli_stmt_prepare)
{
    zend_execute_data *execute_data = EG(current_execute_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI_STMT, \
            PANDA_EXPENDS_EXT_MYSQLI_CLS_MYSQLI_STMT_METHOD_PREPARE, &_func);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);

    int stmt_id;
    char *prepare_sql;
    zval *stmt_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    zval *sql_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    prepare_sql = Z_STRVAL_P(sql_val);
    stmt_id = Z_OBJ_HANDLE_P(stmt_val);

    panda_resource_set_prepare_sql_with_stmt_id(stmt_id, prepare_sql TSRMLS_CC);
}

PANDA_FUNCTION(mysqli_stmt_execute)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_MYSQLI_FUNC_MYSQLI_STMT_EXECUTE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *prepare_sql, *db = NULL;
    int stmt_id, instance_id, resource_id, sql_id = FAILURE;
    zval *stmt_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    stmt_id = Z_OBJ_HANDLE_P(stmt_val);

    if (panda_resource_get_prepare_sql_with_stmt_id(stmt_id, &prepare_sql TSRMLS_CC) == SUCCESS) {
        if (panda_resource_set_sql(PANDA_RESOURCE_TYPE_MYSQL, prepare_sql TSRMLS_CC) == SUCCESS) {
            panda_resource_get_sql_last_id(PANDA_RESOURCE_TYPE_MYSQL, &sql_id TSRMLS_CC);
        }
    }

    if (panda_resource_get_instance_id_with_stmt_id(stmt_id, &instance_id) == SUCCESS) {
        if (panda_resource_get_resource_id_with_instance_id(instance_id, &resource_id) == SUCCESS) {
            add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MYSQL, PANDA_TRUE);
            add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
        }

        if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
            add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
        }
    }

    if (sql_id >= 0) {
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SQL_ID, sql_id);
    }

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

