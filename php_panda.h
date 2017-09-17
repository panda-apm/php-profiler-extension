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

#ifndef PHP_PANDA_H
#define PHP_PANDA_H

extern zend_module_entry panda_module_entry;
#define phpext_panda_ptr &panda_module_entry

#define PHP_PANDA_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_PANDA_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_PANDA_API __attribute__ ((visibility("default")))
#else
#	define PHP_PANDA_API
#endif

#include <sys/resource.h>
#ifdef ZTS
#include "TSRM.h"
#endif

#ifdef ZTS
#define PANDA_G(v) TSRMG(panda_globals_id, zend_panda_globals *, v)
#else
#define PANDA_G(v) (panda_globals.v)
#endif

#define PANDA_AGENT_NAME          "PandaAgent"
#define PANDA_AGENT_VERSION       "1.0.0"
#define PANDA_AGENT_DATA_VERSION  10000
#define PANDA_AGENT_COPYRIGHT     "Panda Team 2017"
#define PANDA_AGENT_AUTHOR        "himanhimao"
#define PANDA_TRANSFER_PROTOCOL_VERSION  "v1"

#define PANDA_TRUE 1
#define PANDA_FALSE 0
#define PANDA_STRLEN(s)  strlen(s) + 1
#define PANDA_HASHTABLE_INIT(ht) zend_hash_init(ht, 0, NULL, NULL, 1)
#define PANDA_HASHTABLE_ASSOC_ADD(ht, name, func_type, func_size) zend_hash_add(ht, name, PANDA_STRLEN(name), func_type, func_size, NULL)
#define PANDA_HASHTABLE_INDEX_ADD(ht, lval, func_type, func_size) zend_hash_index_update(ht, lval, func_type, func_size, NULL)
#define PANDA_HASHTABLE_DESTROY(ht) zend_hash_destroy(ht)
#define PANDA_ARRAY_INIT(val) MAKE_STD_ZVAL(val);array_init(val)
#define PANDA_ARRAY_DESTROY(val) zval_ptr_dtor(&val)
#define PANDA_ARRAY_PRINT(val)  zend_print_zval_r(val, 0 TSRMLS_CC)
#define PANDA_ARRAY_COUNT(val) zend_hash_num_elements(Z_ARRVAL_P(val))
#define PANDA_OBJECT_GET_PROPERTY(ex, property) zend_read_property(Z_OBJCE_P(ex), ex, property, sizeof(property) - 1, 0 TSRMLS_CC)
#define PANDA_FUNCTION(name) PHP_FUNCTION(panda_expend_##name)
#define PANDA_METHOD(cls, name) PHP_METHOD(panda_expend_##cls, name)
#define PANDA_FN(name) PHP_FN(panda_expend_##name)
#define PANDA_MN(cls, name) PHP_MN(panda_expend_##cls##_##name)
#define PANDA_MACRO_STR(macro) #macro

#define PANDA_TRAN_COMMAND_EOF "\n"
#define PANDA_TRAN_COMMAND_NEW_CONFIG "new_config"
#define PANDA_TRAN_COMMAND_REGISTER "register"
#define PANDA_TRAN_COMMAND_RESP_STATUS "status"
#define PANDA_TRAN_COMMAND_RESP_MESSAGE "message"
#define PANDA_TRAN_COMMAND_RESP_MESSAGE_HASH   "_hash"
#define PANDA_TRAN_COMMAND_RESP_MESSAGE_COLLECT_REQUEST_POST "collectRequestPost"
#define PANDA_TRAN_COMMAND_RESP_MESSAGE_COLLECT_REQUEST_COOKIE "collectRequestCookie"
#define PANDA_TRAN_COMMAND_RESP_MESSAGE_TRACE_STACK "traceStack"
#define PANDA_TRAN_COMMAND_RESP_MESSAGE_TRACE_ERROR "traceError"
#define PANDA_TRAN_COMMAND_RESP_MESSAGE_TRACE_EXCEPTION "traceException"
#define PANDA_TRAN_COMMAND_RESP_MESSAGE_TRACE_COMPILE "traceCompile"
#define PANDA_TRAN_COMMAND_RESP_MESSAGE_STACK_MERGE "stackMerge"
#define PANDA_TRAN_COMMAND_RESP_MESSAGE_STACK_MAX_NODES "stackMaxNodes"
#define PANDA_TRAN_COMMAND_RESP_MESSAGE_STACK_MAX_LEVELS "stackMaxLevels"
#define PANDA_TRAN_COMMAND_RESP_MESSAGE_LIMIT_FUNCTION_TIME_US "limitFunctionTimeUs"
#define PANDA_TRAN_COMMAND_RESP_MESSAGE_LIMIT_TIME_MS "limitTimeMs"
#define PANDA_TRAN_COMMAND_REGISTER_MAX_BUF_LEN 46
#define PANDA_TRAN_COMMAND_REGISTER_MAX_RES_BUF_LEN 512


#define PANDA_LOG(message)                                                                         \
    do {                                                                                           \
        if (PANDA_G(config_enable_log)) {                                                          \
            char *date_format = "Y-m-d\\TH:i:sP";                                                  \
            char *date = php_format_date(date_format, strlen(date_format), time(NULL), 1);         \
            _php_error_log(3, date, PANDA_G(config_log_file), NULL TSRMLS_CC);                     \
            _php_error_log(3, ": ", PANDA_G(config_log_file), NULL TSRMLS_CC);                    \
            _php_error_log(3, message, PANDA_G(config_log_file), NULL TSRMLS_CC);                  \
            _php_error_log(3, "\n", PANDA_G(config_log_file), NULL TSRMLS_CC);                     \
            efree(date);                                                                           \
        }                                                                                          \
    } while (0)                                                                                    \

#define PANDA_ASSOC_ARRAY_INC_NUM(zv, name, num)                                                   \
    do {                                                                                           \
        zval **item;                                                                               \
        HashTable *ht = Z_ARRVAL_P(zv);                                                            \
        int name_len = PANDA_STRLEN(name);                                                         \
        ulong name_hash  = zend_get_hash_value(name, name_len);                                    \
        if (zend_hash_quick_find(ht, name, name_len, name_hash, (void **)&item) == SUCCESS) {      \
            ZVAL_LONG(*item, Z_LVAL_PP(item) + num);                                               \
        }                                                                                          \
    } while(0)                                                                                     \

#define PANDA_INDEX_ARRAY_INC_NUM(zv, index, num)                                                  \
    do {                                                                                           \
        zval **item;                                                                               \
        HashTable *ht = Z_ARRVAL_P(zv);                                                            \
        if (zend_hash_index_find(ht, (ulong)index, (void **)&item) == SUCCESS) {                   \
            ZVAL_LONG(*item, Z_LVAL_PP(item) + num);                                               \
        }                                                                                          \
    } while(0)                                                                                     \

#if !defined(uint64)
typedef unsigned long long uint64;
#endif
#if !defined(int64)
typedef long int int64;
#endif
#if !defined(uint8)
typedef unsigned char uint8;
#endif

typedef struct panda_stack_entity {
    int    level;
    char   *name;
    int    name_len;
    struct rusage start_ru;
    struct rusage end_ru;
    int    id;
    int    parent_id;
    int64  start_mu;
    int64  end_mu;
    int64  start_pmu;
    int64  end_pmu;
    uint64 start_us;
    uint64 end_us;
    ulong  hash_code;
    struct panda_stack_entity *prev_entity;
} panda_stack_entity_t;


typedef struct _panda_url_entity {
    char *url;
    int url_len;
} panda_url_entity_t;


ZEND_BEGIN_MODULE_GLOBALS(panda)
/* config variables */
zend_bool config_collect_request_post;
zend_bool config_collect_request_cookie;
zend_bool config_stack_merge;
zend_bool config_enable_log;
char* config_key;
char* config_log_file;
char* config_unix_socket;
char* config_hash;
int config_limit_function_time_us;
int config_limit_time_ms;
int config_stack_max_nodes;
int config_stack_max_levels;
/*command variables*/
int is_registered;


/* node variables*/
zval *node_base;
zval *node_request;
zval *node_response;
zval *node_error;
zval *node_exception;
zval *node_compile;
zval *node_stack;
zval *node_extend;
zval *node_resource;

/* stack variables */
panda_stack_entity_t *stack_entries;
panda_stack_entity_t *stack_prev_entity;
zval *stack_maps;
long stack_count;
long stack_max_level;
int stack_entity_id;

/* exception variables*/
int exception_count;
zval *exception_statistics;

/* error variables*/
int error_count;
zval *error_fatal;
zval *error_statistics;

/* compile variables */
int compile_file_count;
long compile_file_walltime;
int compile_string_count;
long compile_string_walltime;

/* hook variables */
HashTable expend_func_table;
HashTable expend_cls_table;

/* resource variable */
zval *resources_sqls;
zval *resources_maps;
HashTable resource_index_object_dbs_table;
HashTable resource_index_object_resources_table;
HashTable resource_index_object_prepare_sqls_table;
HashTable resource_index_object_stmt_table;
HashTable resource_index_hashkey_resources_table;
HashTable resource_index_last_instances_table;
HashTable resource_index_curl_entity_table;
HashTable reosurce_index_object_chilrens_table;

ZEND_END_MODULE_GLOBALS(panda)

int remote_is_registered(char *register_key, zval *client_config TSRMLS_DC);
int get_new_config(char *new_config, zval *client_config TSRMLS_DC);
void  sync_config(zval *config TSRMLS_DC);
#endif	/* PHP_PANDA_H */
