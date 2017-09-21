/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <time.h>
#include <unistd.h>
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/standard/php_smart_str.h"
#include "ext/standard/basic_functions.h"
#include "ext/standard/php_array.h"
#include "ext/date/php_date.h"
#include "ext/json/php_json.h"
#include "Zend/zend_virtual_cwd.h"

#include "php_panda.h"
#include "panda_base.h"
#include "panda_request.h"
#include "panda_response.h"
#include "panda_stack.h"
#include "panda_error.h"
#include "panda_exception.h"
#include "panda_compile.h"
#include "panda_expend.h"
#include "panda_resource.h"
#include "common/socket.h"

ZEND_DECLARE_MODULE_GLOBALS(panda)
/* True global resources - no need for thread safety here */
//static int le_panda;

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    STD_PHP_INI_BOOLEAN("panda.stack_merge", "0", PHP_INI_SYSTEM, OnUpdateBool, config_stack_merge, zend_panda_globals, panda_globals)
    STD_PHP_INI_BOOLEAN("panda.collect_request_post", "0", PHP_INI_SYSTEM, OnUpdateBool, config_collect_request_post, zend_panda_globals, panda_globals)
    STD_PHP_INI_BOOLEAN("panda.collect_request_cookie", "0", PHP_INI_SYSTEM, OnUpdateBool, config_collect_request_cookie, zend_panda_globals, panda_globals)
    STD_PHP_INI_BOOLEAN("panda.enable_log", "0", PHP_INI_SYSTEM, OnUpdateBool, config_enable_log, zend_panda_globals, panda_globals)
    STD_PHP_INI_ENTRY("panda.key", "", PHP_INI_SYSTEM, OnUpdateString, config_key, zend_panda_globals, panda_globals)
    STD_PHP_INI_ENTRY("panda.limit_function_time_us", "1000", PHP_INI_SYSTEM, OnUpdateLong, config_limit_function_time_us, zend_panda_globals, panda_globals)
    STD_PHP_INI_ENTRY("panda.limit_time_ms", "5000", PHP_INI_SYSTEM, OnUpdateLong, config_limit_time_ms, zend_panda_globals, panda_globals)
    STD_PHP_INI_ENTRY("panda.stack_max_nodes", "500", PHP_INI_SYSTEM, OnUpdateLong, config_stack_max_nodes, zend_panda_globals, panda_globals)
    STD_PHP_INI_ENTRY("panda.stack_max_levels", "200", PHP_INI_SYSTEM, OnUpdateLong, config_stack_max_levels, zend_panda_globals, panda_globals)
    STD_PHP_INI_ENTRY("panda.log_file", "/tmp/panda_agent.log", PHP_INI_SYSTEM, OnUpdateStringUnempty, config_log_file, zend_panda_globals, panda_globals)
    STD_PHP_INI_ENTRY("panda.unix_socket", "/tmp/panda_agent.sock", PHP_INI_SYSTEM, OnUpdateStringUnempty, config_unix_socket, zend_panda_globals, panda_globals)
PHP_INI_END()
/* }}} */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_panda_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_panda_compiled)
{
    char *arg = NULL;
    int arg_len, len;
    char *strg;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
        return;
    }

    len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "panda", arg);
    RETURN_STRINGL(strg, len, 0);
}
/* }}} */



/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(panda)
{
    REGISTER_INI_ENTRIES();
    if (panda_request_is_cli_mode(TSRMLS_C) == PANDA_FALSE) {
        zval *client_config;
        PANDA_ARRAY_INIT(client_config);
        if (PANDA_G(config_key) && remote_is_registered(PANDA_G(config_key), client_config TSRMLS_CC) == SUCCESS) {
            zval **status = NULL;
            zval **message = NULL;

            if (zend_hash_find(Z_ARRVAL_P(client_config), PANDA_TRAN_COMMAND_RESP_STATUS,
                    PANDA_STRLEN(PANDA_TRAN_COMMAND_RESP_STATUS), (void **)&status) == SUCCESS) {
                if (Z_TYPE_PP(status) == IS_BOOL && Z_BVAL_PP(status)) {
                    if (zend_hash_find(Z_ARRVAL_P(client_config), PANDA_TRAN_COMMAND_RESP_MESSAGE,
                            PANDA_STRLEN(PANDA_TRAN_COMMAND_RESP_MESSAGE), (void **)&message) == SUCCESS) {
                        zval *config = *message;
                       sync_config(config TSRMLS_CC);
                    }
                    PANDA_G(is_registered) = 1;
                    panda_stack_init_hooks(TSRMLS_C);
                    panda_compile_init_hooks(TSRMLS_C);
                    panda_error_init_hooks(TSRMLS_C);
                    panda_exception_init_hooks(TSRMLS_C);
                    panda_expend_init_globals(TSRMLS_C);
                    panda_expend_init_hooks(TSRMLS_C);
                }
            }
        }


        PANDA_ARRAY_DESTROY(client_config);
    }
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(panda)
{
    if (panda_request_is_cli_mode(TSRMLS_C) == PANDA_FALSE) {
        if (PANDA_G(is_registered)) {
            panda_stack_destroy_hooks(TSRMLS_C);
            panda_compile_destroy_hooks(TSRMLS_C);
            panda_error_destroy_hooks(TSRMLS_C);
            panda_exception_destroy_hooks(TSRMLS_C);
            panda_expend_destroy_hooks(TSRMLS_C);
            panda_expend_destroy_globals(TSRMLS_C);
        }

        if (PANDA_G(config_hash)) {
            efree(PANDA_G(config_hash));
            PANDA_G(config_hash) = NULL;
        }
    }
    UNREGISTER_INI_ENTRIES();
    return SUCCESS;
}
/* }}} */


/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(panda)
{
    if (PANDA_G(is_registered)) {
        if (PANDA_G(config_hash)) {
            zval *new_client_config;
            PANDA_ARRAY_INIT(new_client_config);
            if (get_new_config(PANDA_G(config_hash), new_client_config TSRMLS_CC) == SUCCESS) {
                zval **status = NULL;
                zval **message = NULL;
                if (zend_hash_find(Z_ARRVAL_P(new_client_config), PANDA_TRAN_COMMAND_RESP_STATUS,
                        PANDA_STRLEN(PANDA_TRAN_COMMAND_RESP_STATUS), (void **)&status) == SUCCESS) {
                    if (Z_TYPE_PP(status) == IS_BOOL && Z_BVAL_PP(status)) {
                        if (zend_hash_find(Z_ARRVAL_P(new_client_config), PANDA_TRAN_COMMAND_RESP_MESSAGE,
                                PANDA_STRLEN(PANDA_TRAN_COMMAND_RESP_MESSAGE), (void **)&message) == SUCCESS) {
                            zval *config = *message;
                            sync_config(config TSRMLS_CC);
                        }
                    }
                }
            }
            PANDA_ARRAY_DESTROY(new_client_config);
        }

        panda_request_init_globals();
        panda_response_init_globals();
        panda_base_init_globals();
        panda_stack_init_globals(TSRMLS_C);
        panda_resource_init_globals(TSRMLS_C);
        panda_exception_init_globals(TSRMLS_C);
        panda_error_init_globals(TSRMLS_C);
        panda_compile_init_globals(TSRMLS_C);
        panda_stack_begin_profiling(TSRMLS_C);
    }
    return SUCCESS;
}
/* }}} */



/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(panda)
{
    if (PANDA_G(is_registered)) {
        panda_stack_end_profiling(TSRMLS_C);

        zval *data;
        PANDA_ARRAY_INIT(data);

        panda_base_compose_node(TSRMLS_C);
        Z_ADDREF_P(PANDA_G(node_base));
        add_assoc_zval(data, PANDA_NODE_BASE, PANDA_G(node_base));
        panda_base_destroy_globals();

        panda_request_compose_node(TSRMLS_C);
        Z_ADDREF_P(PANDA_G(node_request));
        add_assoc_zval(data, PANDA_NODE_REQUEST, PANDA_G(node_request));
        panda_request_destroy_globals();

        panda_response_compose_node(TSRMLS_C);
        Z_ADDREF_P(PANDA_G(node_response));
        add_assoc_zval(data, PANDA_NODE_RESPONSE, PANDA_G(node_response));
        panda_response_destroy_globals();

        panda_stack_compose_node(TSRMLS_C);
        Z_ADDREF_P(PANDA_G(node_stack));
        add_assoc_zval(data, PANDA_NODE_STACK, PANDA_G(node_stack));
        panda_stack_destroy_globals(TSRMLS_C);

        panda_resource_compose_node(TSRMLS_C);
        Z_ADDREF_P(PANDA_G(node_resource));
        add_assoc_zval(data, PANDA_NODE_RESOURCE, PANDA_G(node_resource));
        panda_resource_destroy_globals(TSRMLS_C);

        panda_exception_compose_node(TSRMLS_C);
        add_assoc_zval(data, PANDA_NODE_EXCEPTION, PANDA_G(node_exception));
        Z_ADDREF_P(PANDA_G(node_exception));
        panda_exception_destroy_globals();

        panda_error_compose_node(TSRMLS_C);
        Z_ADDREF_P(PANDA_G(node_error));
        add_assoc_zval(data, PANDA_NODE_ERROR, PANDA_G(node_error));
        panda_error_destroy_globals();


        panda_compile_compose_node(TSRMLS_C);
        Z_ADDREF_P(PANDA_G(node_compile));
        add_assoc_zval(data, PANDA_NODE_COMPILE, PANDA_G(node_compile));
        panda_compile_destroy_globals();

        long options = 0;
        smart_str buf_json = {0};
        php_json_encode(&buf_json, data, options TSRMLS_CC);
        smart_str_0(&buf_json);
        PANDA_LOG(buf_json.c);
        php_log_err(buf_json.c);

        if (VCWD_ACCESS(PANDA_G(config_unix_socket), F_OK) == 0) {
            if (send_result(PANDA_G(config_unix_socket), buf_json.c, buf_json.len, NULL, 0)) {
                PANDA_LOG("send ok!");
            } else {
                PANDA_LOG("send error!");
            }
        }
        smart_str_free(&buf_json);
        PANDA_ARRAY_DESTROY(data);
    }
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(panda)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "panda support", "enabled");
    php_info_print_table_header(2, "PandaAgent Version", PANDA_AGENT_VERSION);
    php_info_print_table_row(2, "PandaAgent Copyright", PANDA_AGENT_COPYRIGHT);
    php_info_print_table_row(2, "PandaAgent Author", PANDA_AGENT_AUTHOR);
    php_info_print_table_end();

    DISPLAY_INI_ENTRIES();
}
/* }}} */


int get_new_config(char *config_hash, zval* client_config TSRMLS_DC)
{
    int status = FAILURE;
    if (VCWD_ACCESS(PANDA_G(config_unix_socket), F_OK) == 0) {
        char *command;
        char *buf = emalloc(PANDA_TRAN_COMMAND_REGISTER_MAX_RES_BUF_LEN);
        int command_len = spprintf(&command, PANDA_TRAN_COMMAND_REGISTER_MAX_BUF_LEN,
             "%s:%s%s", PANDA_TRAN_COMMAND_NEW_CONFIG, config_hash, PANDA_TRAN_COMMAND_EOF);
        if  (send_result(PANDA_G(config_unix_socket), command, command_len,
                buf, PANDA_TRAN_COMMAND_REGISTER_MAX_RES_BUF_LEN)) {
            int buf_len = strlen(buf);
            char c[255];
            php_log_err(buf);
            php_json_decode(client_config, buf, buf_len , 1, 512 TSRMLS_CC);
            if (zend_hash_num_elements(Z_ARRVAL_P(client_config)) > 0) {
                status = SUCCESS;
            }
        }
        efree(command);
        efree(buf);
    }
    return SUCCESS;
}

int remote_is_registered(char *register_key, zval *client_config TSRMLS_DC)
{
    int status =  FAILURE;
    if (VCWD_ACCESS(PANDA_G(config_unix_socket), F_OK) == 0) {
        char *command;
        char *buf = emalloc(PANDA_TRAN_COMMAND_REGISTER_MAX_RES_BUF_LEN);
        int command_len = spprintf(&command, PANDA_TRAN_COMMAND_REGISTER_MAX_BUF_LEN,
                "%s:%s%s", PANDA_TRAN_COMMAND_REGISTER, register_key, PANDA_TRAN_COMMAND_EOF);
        if  (send_result(PANDA_G(config_unix_socket), command, command_len,
                buf, PANDA_TRAN_COMMAND_REGISTER_MAX_RES_BUF_LEN)) {
            int buf_len = strlen(buf);
            char c[255];
            php_log_err(buf);
            php_json_decode(client_config, buf, buf_len , 1, 512 TSRMLS_CC);
            if (zend_hash_num_elements(Z_ARRVAL_P(client_config)) > 0) {
                status = SUCCESS;
            }
        }
        efree(command);
        efree(buf);
    }
    return status;
}

void sync_config(zval *config TSRMLS_DC)
{
    zval **hash;
    zval **collect_request_post = NULL;
    zval **collect_request_cookie = NULL;
    zval **stack_merge = NULL;
    zval **stack_max_nodes = NULL;
    zval **stack_max_levels = NULL;
    zval **limit_function_time_us = NULL;
    zval **limit_time_ms = NULL;

    if (zend_hash_find(Z_ARRVAL_P(config), PANDA_TRAN_COMMAND_RESP_MESSAGE_HASH,
        PANDA_STRLEN(PANDA_TRAN_COMMAND_RESP_MESSAGE_HASH), (void **)&hash) == SUCCESS) {
        if (Z_TYPE_PP(hash) == IS_STRING && Z_STRLEN_PP(hash) > 0) {
            PANDA_G(config_hash) = estrndup(Z_STRVAL_PP(hash), 9);
        }
    }

    if (zend_hash_find(Z_ARRVAL_P(config), PANDA_TRAN_COMMAND_RESP_MESSAGE_COLLECT_REQUEST_POST,
        PANDA_STRLEN(PANDA_TRAN_COMMAND_RESP_MESSAGE_COLLECT_REQUEST_POST), (void **)&collect_request_post) == SUCCESS) {
        if (Z_TYPE_PP(collect_request_post) == IS_BOOL) {
            PANDA_G(config_collect_request_post) = Z_BVAL_PP(collect_request_post);
        }
    }

    if (zend_hash_find(Z_ARRVAL_P(config), PANDA_TRAN_COMMAND_RESP_MESSAGE_COLLECT_REQUEST_COOKIE,
        PANDA_STRLEN(PANDA_TRAN_COMMAND_RESP_MESSAGE_COLLECT_REQUEST_COOKIE), (void **)&collect_request_cookie) == SUCCESS) {
        if (Z_TYPE_PP(collect_request_cookie) == IS_BOOL) {
            PANDA_G(config_collect_request_cookie) = Z_BVAL_PP(collect_request_cookie);
        }
    }

    if (zend_hash_find(Z_ARRVAL_P(config), PANDA_TRAN_COMMAND_RESP_MESSAGE_STACK_MERGE,
        PANDA_STRLEN(PANDA_TRAN_COMMAND_RESP_MESSAGE_STACK_MERGE), (void **)&stack_merge) == SUCCESS) {
        if (Z_TYPE_PP(stack_merge) == IS_BOOL) {
            PANDA_G(config_stack_merge) = Z_BVAL_PP(stack_merge);
        }
    }

    if (zend_hash_find(Z_ARRVAL_P(config), PANDA_TRAN_COMMAND_RESP_MESSAGE_STACK_MAX_NODES,
        PANDA_STRLEN(PANDA_TRAN_COMMAND_RESP_MESSAGE_STACK_MAX_NODES), (void **)&stack_max_nodes) == SUCCESS) {
        if (Z_TYPE_PP(stack_max_nodes) == IS_LONG) {
            PANDA_G(config_stack_max_nodes) = Z_LVAL_PP(stack_max_nodes);
        }
    }

    if (zend_hash_find(Z_ARRVAL_P(config), PANDA_TRAN_COMMAND_RESP_MESSAGE_STACK_MAX_LEVELS,
        PANDA_STRLEN(PANDA_TRAN_COMMAND_RESP_MESSAGE_STACK_MAX_LEVELS), (void **)&stack_max_levels) == SUCCESS) {
        if (Z_TYPE_PP(stack_max_levels) == IS_LONG) {
            PANDA_G(config_stack_max_levels) = Z_LVAL_PP(stack_max_levels);
        }
    }

    if (zend_hash_find(Z_ARRVAL_P(config), PANDA_TRAN_COMMAND_RESP_MESSAGE_LIMIT_FUNCTION_TIME_US,
        PANDA_STRLEN(PANDA_TRAN_COMMAND_RESP_MESSAGE_LIMIT_FUNCTION_TIME_US), (void **)&limit_function_time_us) == SUCCESS) {
        if (Z_TYPE_PP(limit_function_time_us) == IS_LONG) {
            PANDA_G(config_limit_function_time_us) = Z_LVAL_PP(limit_function_time_us);
        }
    }

    if (zend_hash_find(Z_ARRVAL_P(config), PANDA_TRAN_COMMAND_RESP_MESSAGE_LIMIT_TIME_MS,
        PANDA_STRLEN(PANDA_TRAN_COMMAND_RESP_MESSAGE_LIMIT_TIME_MS), (void **)&limit_time_ms) == SUCCESS) {
        if (Z_TYPE_PP(limit_time_ms) == IS_LONG) {
            PANDA_G(config_limit_time_ms) = Z_LVAL_PP(limit_time_ms);
        }
    }
}

/* {{{ panda_functions[]
 *
 * Every user visible function must have an entity in panda_functions[].
 */
const zend_function_entry panda_functions[] = {
    PHP_FE(confirm_panda_compiled,    NULL)        /* For testing, remove later. */
    PHP_FE_END    /* Must be the last line in panda_functions[] */
};
/* }}} */

/* {{{ panda_module_entity
 */
zend_module_entry panda_module_entry = {
    STANDARD_MODULE_HEADER,
    "panda",
    panda_functions,
    PHP_MINIT(panda),
    PHP_MSHUTDOWN(panda),
    PHP_RINIT(panda),        /* Replace with NULL if there's nothing to do at request start */
    PHP_RSHUTDOWN(panda),    /* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(panda),
    PHP_PANDA_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PANDA
ZEND_GET_MODULE(panda)
#endif
