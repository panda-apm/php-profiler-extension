#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_panda.h"
#include "panda_error.h"

ZEND_EXTERN_MODULE_GLOBALS(panda);

int panda_error_init_globals(TSRMLS_D)
{
    PANDA_G(error_count) = 0;
    PANDA_ARRAY_INIT(PANDA_G(node_error));
    PANDA_ARRAY_INIT(PANDA_G(error_statistics));
    PANDA_ARRAY_INIT(PANDA_G(error_fatal));
    return SUCCESS;
}
int panda_error_destroy_globals(TSRMLS_D)
{
    PANDA_ARRAY_DESTROY(PANDA_G(node_error));
    PANDA_ARRAY_DESTROY(PANDA_G(error_statistics));
    PANDA_ARRAY_DESTROY(PANDA_G(error_fatal));
    return SUCCESS;
}

int panda_error_compose_node(TSRMLS_D)
{
    zval *node_error = PANDA_G(node_error);
    add_assoc_long(node_error, PANDA_NODE_ERROR_COUNT, PANDA_G(error_count));
    Z_ADDREF_P(PANDA_G(error_statistics));
    add_assoc_zval(node_error, PANDA_NODE_ERROR_STATISTICS, PANDA_G(error_statistics));
    Z_ADDREF_P(PANDA_G(error_fatal));
    add_assoc_zval(node_error, PANDA_NODE_ERROR_FATAL_ERROR, PANDA_G(error_fatal));
    return SUCCESS;
}

int panda_error_init_hooks(TSRMLS_D)
{
    _panda_error_execute = zend_error_cb;
    zend_error_cb = panda_error_execute;
    return SUCCESS;
}

int panda_error_destroy_hooks(TSRMLS_D)
{
    zend_error_cb = _panda_error_execute;
    return SUCCESS;
}

static void panda_error_execute(int type, const char *error_filename, const uint error_lineno,
        const char *format, va_list args) {
    TSRMLS_FETCH();
    error_handling_t  error_handling;
    zval *fatal_error = PANDA_G(error_fatal);


#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 3) || PHP_MAJOR_VERSION >= 6
    error_handling  = EG(error_handling);
#else
    error_handling  = PG(error_handling);
#endif

    char* error_name = panda_error_transfer_error_name(type);
    int error_name_len = PANDA_STRLEN(error_name);

    zval *error_statistics = PANDA_G(error_statistics);
    if (zend_hash_exists(Z_ARRVAL_P(error_statistics), error_name, error_name_len)) {
        PANDA_ASSOC_ARRAY_INC_NUM(error_statistics, error_name, PANDA_ERROR_DEFAULE_CODE_COUNT);
    } else {
        add_assoc_long(error_statistics, error_name,PANDA_ERROR_DEFAULE_CODE_COUNT);
    }

    if (error_handling == EH_NORMAL) {
        if (type == E_ERROR || type == E_CORE_ERROR) {
            va_list args_copy;
            char* error_message;
            va_copy(args_copy, args);
            vspprintf(&error_message, 0, format, args_copy);
            va_end(args_copy);

            add_assoc_long(fatal_error, PANDA_NODE_ERROR_FATAL_ERROR_TYPE, type);
            add_assoc_string(fatal_error, PANDA_NODE_ERROR_FATAL_ERROR_FILE, (char *)error_filename, 1);
            add_assoc_long(fatal_error, PANDA_NODE_ERROR_FATAL_ERROR_LINE, error_lineno);
            add_assoc_string(fatal_error, PANDA_NODE_ERROR_FATAL_ERROR_MESSAGE, error_message, 1);
            efree(error_message);
        }
    }

    PANDA_G(error_count)++;
    _panda_error_execute(type, error_filename, error_lineno, format, args);
}

static char* panda_error_transfer_error_name(int e_type)
{
    switch(e_type) {
    case E_ERROR:
        return "error";
    case E_WARNING:
        return "warning";
    case E_NOTICE:
        return "notice";
    case E_CORE_ERROR:
        return "core_error";
    case E_COMPILE_ERROR:
        return "compile_error";
    case E_COMPILE_WARNING:
        return "compile_warning";
    case E_USER_ERROR:
        return "user_error";
    case E_USER_WARNING:
        return "user_warning";
    case E_USER_NOTICE:
        return "user_notice";
    case E_STRICT:
        return "strict";
    case E_RECOVERABLE_ERROR:
        return "e_recoverable_error";
    case E_DEPRECATED:
        return "deprecated";
    case E_USER_DEPRECATED:
        return "user_deprecated";
    }
    return "unknown";
}
