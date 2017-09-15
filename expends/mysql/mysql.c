#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "string.h"
#include "stdlib.h"
#include "php.h"
#include "php_panda.h"
#include "panda_expend.h"
#include "panda_stack.h"
#include "panda_resource.h"
#include "expends/mysql/mysql.h"

ZEND_EXTERN_MODULE_GLOBALS(panda);

PANDA_FUNCTION(mysql_connect)
{

    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_MYSQL_FUNC_MYSQL_CONNECT, &_func);
    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int resource_id = -1, instance_id;
    instance_id =  Z_OBJ_HANDLE_P(return_value);

    char *host = NULL;
    int port, free_host = 0;

    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);
    if (params_count == 0) {
        host = PANDA_EXPENDS_EXT_MYSQL_DEFAULT_HOST;
        port = PANDA_EXPENDS_EXT_MYSQL_DEFAULT_PROT;
    } else {
        zval *host_port_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
        char *host_port = Z_STRVAL_P(host_port_val);
        char *tmp = strchr(host_port, ':');
        if (tmp) {
            host = estrndup(host_port, tmp - host_port);
            free_host = 1;
            tmp++;
            if (tmp[0] != '/') {
                port = atoi(tmp);
            }
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
         panda_resource_set_last_instance_id(PANDA_RESOURCE_TYPE_MYSQL, instance_id TSRMLS_CC);
    }

    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MYSQL, PANDA_TRUE);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    if (free_host) {
        efree(host);
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}


PANDA_FUNCTION(mysql_query)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_MYSQL_FUNC_MYSQL_QUERY, &_func);
    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id, resource_id = -1, sql_id = -1;
    zval *sql_val;
    char *sql, *db;
    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);
    sql_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    sql = Z_STRVAL_P(sql_val);

    if (panda_resource_set_sql(PANDA_RESOURCE_TYPE_MYSQL, sql TSRMLS_CC) == SUCCESS) {
        panda_resource_get_sql_last_id(PANDA_RESOURCE_TYPE_MYSQL, &sql_id TSRMLS_CC);
    }

    if (params_count == 1) {
        if (panda_resource_get_last_instance_id(PANDA_RESOURCE_TYPE_MYSQL, &instance_id TSRMLS_CC) == SUCCESS) {
            panda_resource_get_resource_id_with_instance_id(instance_id, &resource_id);
        }
    } else {
        zval *instance_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
        instance_id = Z_OBJ_HANDLE_P(instance_val);
        panda_resource_get_resource_id_with_instance_id((ulong)instance_id, &resource_id TSRMLS_CC);
    }

    if (panda_resource_get_db_with_instance_id(instance_id, &db) == SUCCESS) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME, db, PANDA_TRUE);
    }

    if (resource_id >= 0) {
        add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MYSQL, 1);
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
    }

    if (sql_id >= 0) {
        add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_SQL_ID, sql_id);
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}


PANDA_FUNCTION(mysql_select_db)
{
    zend_execute_data *execute_data = EG(current_execute_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_MYSQL_FUNC_MYSQL_SELECT_DB, &_func);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);


    int instance_id = -1;
    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);
    zval *db_name_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    char *db_name = Z_STRVAL_P(db_name_val);

    if (params_count == 1) {
        panda_resource_get_last_instance_id(PANDA_RESOURCE_TYPE_MYSQL, &instance_id TSRMLS_CC);
    } else {
        zval *instance_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
        instance_id = Z_OBJ_HANDLE_P(instance_val);
    }

    if (instance_id > 0) {
        panda_resource_set_db_with_instance_id(instance_id, db_name TSRMLS_CC);
    }
}

