#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "string.h"
#include "stdlib.h"
#include "curl/curl.h"
#include "php.h"
#include "php_panda.h"
#include "panda_expend.h"
#include "panda_stack.h"
#include "panda_resource.h"
#include "expends/curl/curl.h"

ZEND_EXTERN_MODULE_GLOBALS(panda)

PANDA_FUNCTION(curl_init)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_CURL_FUNC_CURL_INIT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    zval *url_val;
    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);
    int instance_id = Z_OBJ_HANDLE_P(return_value);
    panda_url_entity_t *url_entity = emalloc(sizeof(panda_url_entity_t));
    url_entity->url = NULL;
    url_entity->url_len = 0;

    if (params_count > 0) {
        url_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
        url_entity->url = Z_STRVAL_P(url_val);
        url_entity->url_len = Z_STRLEN_P(url_val);
    }

    panda_resource_set_url_entity_with_instance_id(instance_id, url_entity TSRMLS_CC);

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}


PANDA_FUNCTION(curl_setopt)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_CURL_FUNC_CURL_SETOPT, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *instance_val, *key_val, *val_val;
    panda_url_entity_t *url_entity;

    instance_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    key_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    val_val = panda_stack_get_execute_param(execute_data, 2 TSRMLS_CC);

    instance_id = Z_OBJ_HANDLE_P(instance_val);
    if (Z_LVAL_P(key_val) == CURLOPT_URL) {
        if (panda_resource_get_url_entity_with_instance_id(instance_id, &url_entity TSRMLS_CC) == SUCCESS) {
            url_entity->url = Z_STRVAL_P(val_val);
            url_entity->url_len = Z_STRLEN_P(val_val);
        }
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_FUNCTION(curl_setopt_array)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_CURL_FUNC_CURL_SETOPT_ARRAY, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *instance_val, *items_val;
    zval **url_item;
    panda_url_entity_t *curl_entity;
    instance_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    items_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    instance_id = Z_OBJ_HANDLE_P(instance_val);

    if (zend_hash_index_find(Z_ARRVAL_P(items_val), CURLOPT_URL, (void **)&url_item) == SUCCESS) {
        if (panda_resource_get_url_entity_with_instance_id(instance_id, &curl_entity TSRMLS_CC) == SUCCESS) {
            curl_entity->url = Z_STRVAL_PP(url_item);
            curl_entity->url_len = Z_STRLEN_PP(url_item);
        }
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_FUNCTION(curl_exec)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_CURL_FUNC_CURL_EXEC, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *instance_val;
    panda_url_entity_t *url_entity;

    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);
    if (params_count > 0) {
        instance_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
        instance_id = Z_OBJ_HANDLE_P(instance_val);
        if (panda_resource_get_url_entity_with_instance_id(instance_id, &url_entity TSRMLS_CC) == SUCCESS) {
            add_assoc_stringl(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_URL, url_entity->url, url_entity->url_len, PANDA_TRUE);
        }
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_FUNCTION(curl_close)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_CURL_FUNC_CURL_CLOSE, &_func);

    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);

    int instance_id;
    zval *instance_val;
    panda_url_entity_t *url_entity;

    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);
    if (params_count > 0) {
        instance_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
        instance_id = Z_OBJ_HANDLE_P(instance_val);
        if (panda_resource_get_url_entity_with_instance_id(instance_id, &url_entity TSRMLS_CC) == SUCCESS) {
            efree(url_entity);
        }
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_FUNCTION(curl_multi_init)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);

    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_CURL_FUNC_CURL_MULTI_INIT, &_func);

    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);

    zval *child_instances;
    int instance_id = Z_OBJ_HANDLE_P(return_value);
    PANDA_ARRAY_INIT(child_instances);
    panda_resource_set_child_instances_with_instance_id(instance_id, child_instances);

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_FUNCTION(curl_multi_close)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_CURL_FUNC_CURL_CLOSE, &_func);

    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);

    int instance_id;
    zval *instance_val, *child_instances;

    int params_count = panda_stack_get_execute_paramters_count(execute_data TSRMLS_CC);
    if (params_count > 0) {
        instance_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
        instance_id = Z_OBJ_HANDLE_P(instance_val);
        if (panda_resource_get_child_instances_with_instance_id(instance_id, &child_instances TSRMLS_CC) == SUCCESS) {
            PANDA_ARRAY_DESTROY(child_instances);
        }
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_FUNCTION(curl_multi_add_handle)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_CURL_FUNC_CURL_MULTI_ADD_HANDLE, &_func);

    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);

    zval *instance_val, *child_val, *child_instances;
    int instance_id, child_id;

    instance_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    child_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    instance_id = Z_OBJ_HANDLE_P(instance_val);
    child_id = Z_OBJ_HANDLE_P(child_val);

    if (panda_resource_get_child_instances_with_instance_id(instance_id, &child_instances TSRMLS_CC) == SUCCESS) {
        int count, i, is_exist_val = 0;
        zval **z_item;
        count = zend_hash_num_elements(Z_ARRVAL_P(child_instances));
        zend_hash_internal_pointer_reset(Z_ARRVAL_P(child_instances));
        for (i = 0; i < count; i ++) {
            zend_hash_get_current_data(Z_ARRVAL_P(child_instances), (void**) &z_item);
            zend_hash_move_forward(Z_ARRVAL_P(child_instances));
            if (Z_TYPE_PP(z_item) == IS_LONG && Z_LVAL_PP(z_item) == child_id ) {
                is_exist_val = 1;
            }
        }

        if (!is_exist_val) {
            add_next_index_long(child_instances, child_id);
        }
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_FUNCTION(curl_multi_remove_handle)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_CURL_FUNC_CURL_MULTI_REMOVE_HANDLE, &_func);

    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);

    zval *instance_val, *child_val, *child_instances;
    int instance_id, child_id;

    instance_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    child_val = panda_stack_get_execute_param(execute_data, 1 TSRMLS_CC);
    instance_id = Z_OBJ_HANDLE_P(instance_val);
    child_id = Z_OBJ_HANDLE_P(child_val);

    if (panda_resource_get_child_instances_with_instance_id(instance_id, &child_instances TSRMLS_CC) == SUCCESS) {
        int count, i;
        zval **z_item;
        count = zend_hash_num_elements(Z_ARRVAL_P(child_instances));
        zend_hash_internal_pointer_reset(Z_ARRVAL_P(child_instances));
        for (i = 0; i < count; i ++) {
            char* key;
            ulong idx;
            zend_hash_get_current_data(Z_ARRVAL_P(child_instances), (void**) &z_item);
            zend_hash_get_current_key(Z_ARRVAL_P(child_instances), &key, &idx, 0);
            zend_hash_move_forward(Z_ARRVAL_P(child_instances));
            if (Z_TYPE_PP(z_item) == IS_LONG && Z_LVAL_PP(z_item) == child_id) {
                zend_hash_index_del(Z_ARRVAL_P(child_instances), idx);
            }
        }
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}

PANDA_FUNCTION(curl_multi_exec)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_CURL_FUNC_CURL_MULTI_EXEC, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    int instance_id;
    zval *instance_val, *child_instances, *urls;
    instance_val = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    instance_id = Z_OBJ_HANDLE_P(instance_val);

    PANDA_ARRAY_INIT(urls);
    add_assoc_zval(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_URLS, urls);
    Z_ADDREF_P(urls);
    PANDA_ARRAY_DESTROY(urls);

    if (panda_resource_get_child_instances_with_instance_id(instance_id, &child_instances TSRMLS_CC) == SUCCESS) {
        int count, i;
        zval **z_item;
        count = zend_hash_num_elements(Z_ARRVAL_P(child_instances));
        zend_hash_internal_pointer_reset(Z_ARRVAL_P(child_instances));

        for (i = 0; i < count; i ++) {
            int child_id;
            panda_url_entity_t *url_entity;
            zend_hash_get_current_data(Z_ARRVAL_P(child_instances), (void**) &z_item);
            zend_hash_move_forward(Z_ARRVAL_P(child_instances));
            if (Z_TYPE_PP(z_item) == IS_LONG) {
                child_id = Z_LVAL_PP(z_item);
                if (panda_resource_get_url_entity_with_instance_id(child_id, &url_entity TSRMLS_CC) == SUCCESS) {
                    add_next_index_stringl(urls, url_entity->url, url_entity->url_len, PANDA_TRUE);
                }
            }
        }
    }

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}
