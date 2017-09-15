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
#include "expends/pdo/pdo.h"

ZEND_EXTERN_MODULE_GLOBALS(panda)

PANDA_METHOD(pdo, pdo)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_PDO_CLS_PDO, \
            PANDA_EXPENDS_EXT_PDO_CLS_PDO_METHOD_PDO, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *dsn, *type, *host, *colon, *db_name, *pdo_ext_type;
    int port, type_len;
    zval *dsn_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    dsn = Z_STRVAL_P(dsn_val);
    colon = strchr(dsn, ':');

    if (strncmp(dsn, "uri:", sizeof("uri:") - 1) && colon != NULL) {
        type_len = colon - dsn;
        type = estrndup(dsn, type_len);
        spprintf(&pdo_ext_type, 0, "%s_%s", PANDA_EXPENDS_EXT_PDO, type);

        struct pdo_data_src_parser vars[] = {
            {"dbname", NULL, 0},
            {"host", PANDA_EXPENDS_EXT_PDO_DEFAULT_HOST, 0},
            {"port", PANDA_EXPENDS_EXT_PDO_DEFAULT_PORT, 0},
        };

        php_pdo_parse_data_source(dsn, PANDA_STRLEN(dsn), vars, 3);

        db_name = vars[0].optval;
        host = vars[1].optval;
        if(vars[2].optval) {
            port = atoi(vars[2].optval);
        }

        int instance_id, resource_id = -1;
        instance_id = Z_OBJ_HANDLE_P(this_ptr);

        ulong host_port_hash = panda_stack_get_resource_hash(host, port TSRMLS_CC);

        if (panda_resource_get_resource_id_with_hashkey(host_port_hash, &resource_id TSRMLS_CC) == FAILURE) {
            panda_resource_set_resource(PANDA_RESOURCE_TYPE_MYSQL, host, port, host_port_hash TSRMLS_CC);
            if (panda_resource_get_resource_last_insert_id(PANDA_RESOURCE_TYPE_MYSQL, &resource_id TSRMLS_CC) == SUCCESS) {
                panda_resource_set_resource_id_with_hashkey(host_port_hash, resource_id TSRMLS_CC);
            }
        }

        panda_resource_set_resource_id_with_instance_id((ulong)instance_id, resource_id TSRMLS_CC);
        panda_resource_set_last_instance_id(pdo_ext_type, instance_id TSRMLS_CC);
        if (resource_id >= 0) {
            add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE, PANDA_RESOURCE_TYPE_MYSQL, PANDA_TRUE);
            add_assoc_long(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID, resource_id);
        }

        if (db_name) {
            panda_resource_set_db_with_instance_id(instance_id, db_name TSRMLS_CC);
        }

        efree(pdo_ext_type);
        efree(type);
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_METHOD(pdo, prepare)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_PDO_CLS_PDO, \
        PANDA_EXPENDS_EXT_PDO_CLS_PDO_METHOD_QUERY, &_func);

    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    int stmt_id, instance_id;
    char *prepare_sql;

    zval *sql_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    instance_id = Z_OBJ_HANDLE_P(this_ptr);
    stmt_id = Z_OBJ_HANDLE_P(return_value);
    prepare_sql = Z_STRVAL_P(sql_val);

    panda_resource_set_prepare_sql_with_stmt_id(stmt_id, prepare_sql TSRMLS_CC);
    panda_resource_set_instance_id_with_stmt_id(stmt_id, instance_id TSRMLS_CC);

    PANDA_ARRAY_DESTROY(expend_data);
    efree(execute_name);
}

PANDA_METHOD(pdo, query)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_PDO_CLS_PDO, \
        PANDA_EXPENDS_EXT_PDO_CLS_PDO_METHOD_QUERY, &_func);

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

PANDA_METHOD(pdo, exec)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_PDO_CLS_PDO, \
        PANDA_EXPENDS_EXT_PDO_CLS_PDO_METHOD_QUERY, &_func);

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


PANDA_METHOD(pdostatement, execute)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_CLS_FUNC(&PANDA_G(expend_cls_table), PANDA_EXPENDS_EXT_PDO_CLS_PDO_STATEMENT, \
        PANDA_EXPENDS_EXT_PDO_CLS_PDO_STATEMENT_METHOD_EXECUTE, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    char *db, *prepare_sql;
    int instance_id, resource_id, stmt_id = -1, sql_id = -1;
    instance_id = Z_OBJ_HANDLE_P(this_ptr);

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

static int php_pdo_parse_data_source(const char *data_source,
        unsigned long data_source_len, struct pdo_data_src_parser *parsed,
        int nparams)
{
    int i, j;
    int valstart = -1;
    int semi = -1;
    int optstart = 0;
    int nlen;
    int n_matches = 0;
    int n_semicolumns = 0;

    i = 0;
    while (i < data_source_len) {
        /* looking for NAME= */

        if (data_source[i] == '\0') {
            break;
        }

        if (data_source[i] != '=') {
            ++i;
            continue;
        }

        valstart = ++i;

        /* now we're looking for VALUE; or just VALUE<NUL> */
        semi = -1;
        n_semicolumns = 0;
        while (i < data_source_len) {
            if (data_source[i] == '\0') {
                semi = i++;
                break;
            }
            if (data_source[i] == ';') {
                if ((i + 1 >= data_source_len) || data_source[i+1] != ';') {
                    semi = i++;
                    break;
                } else {
                    n_semicolumns++;
                    i += 2;
                    continue;
                }
            }
            ++i;
        }

        if (semi == -1) {
            semi = i;
        }

        /* find the entity in the array */
        nlen = valstart - optstart - 1;
        for (j = 0; j < nparams; j++) {
            if (0 == strncmp(data_source + optstart, parsed[j].optname, nlen) && parsed[j].optname[nlen] == '\0') {
                /* got a match */
                if (parsed[j].freeme) {
                    efree(parsed[j].optval);
                }

                if (n_semicolumns == 0) {
                    parsed[j].optval = estrndup(data_source + valstart, semi - valstart - n_semicolumns);
                } else {
                    int vlen = semi - valstart;
                    const char *orig_val = data_source + valstart;
                    char *new_val  = (char *) emalloc(vlen - n_semicolumns + 1);

                    parsed[j].optval = new_val;

                    while (vlen && *orig_val) {
                        *new_val = *orig_val;
                        new_val++;

                        if (*orig_val == ';') {
                            orig_val+=2;
                            vlen-=2;
                        } else {
                            orig_val++;
                            vlen--;
                        }
                    }
                    *new_val = '\0';
                }

                parsed[j].freeme = 1;
                ++n_matches;
                break;
            }
        }

        while (i < data_source_len && isspace(data_source[i])) {
            i++;
        }

        optstart = i;
    }

    return n_matches;
}
