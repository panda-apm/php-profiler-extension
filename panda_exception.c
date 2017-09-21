#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend_exceptions.h"
#include "php_panda.h"
#include "panda_exception.h"

ZEND_EXTERN_MODULE_GLOBALS(panda);

int panda_exception_compose_node(TSRMLS_D)
{
    zval *node_exceptions = PANDA_G(node_exception);
    add_assoc_long(node_exceptions, PANDA_NODE_EXCEPTION_COUNT, PANDA_G(exception_count));
    Z_ADDREF_P(PANDA_G(exception_statistics));

    int count = zend_hash_num_elements(Z_ARRVAL_P(PANDA_G(exception_statistics)));
    if (count == 0) {
        convert_to_object(PANDA_G(exception_statistics));
    }


    add_assoc_zval(node_exceptions, PANDA_NODE_EXCEPTION_STATISTICS, PANDA_G(exception_statistics));
    return SUCCESS;
}

int panda_exception_init_hooks(TSRMLS_D)
{
     _panda_exception_execute = zend_throw_exception_hook;
    zend_throw_exception_hook = panda_exception_excecute;
    return SUCCESS;
}


int panda_exception_destroy_hooks(TSRMLS_D)
{
    zend_throw_exception_hook = _panda_exception_execute;
    return SUCCESS;
}

int panda_exception_init_globals(TSRMLS_D)
{
    PANDA_G(exception_count) = 0;
    PANDA_ARRAY_INIT(PANDA_G(node_exception));
    PANDA_ARRAY_INIT(PANDA_G(exception_statistics));
    return SUCCESS;
}

int panda_exception_destroy_globals(TSRMLS_D)
{
    PANDA_ARRAY_DESTROY(PANDA_G(node_exception));
    PANDA_ARRAY_DESTROY(PANDA_G(exception_statistics));
    return SUCCESS;
}

static void panda_exception_excecute(zval *exception TSRMLS_DC)
{
    zend_class_entry *exception_ce;
    zval *exception_statistics = PANDA_G(exception_statistics);
    zval *code_val;
    zval **name_maps_data;
    long code;
    const char *exception_name;
    zend_uint exception_name_len = 0;

    do {
        if (!exception) {
            break;
        }
        exception_ce = Z_OBJCE_P(exception);
        code_val = PANDA_OBJECT_GET_PROPERTY(exception, PANDA_EXCEPTION_PROPRETY_CODE);

        code = Z_LVAL_P(code_val);
        zend_get_object_classname(exception, &exception_name, &exception_name_len TSRMLS_CC);

        if (exception_statistics != NULL) {
            if (zend_hash_find(Z_ARRVAL_P(exception_statistics), exception_name, exception_name_len + 1, (void **)&name_maps_data) == SUCCESS) {
                PANDA_INDEX_ARRAY_INC_NUM(*name_maps_data, code, PANDA_EXCEPTION_DEFAULE_CODE_COUNT);
            } else {
                zval *name_maps;
                PANDA_ARRAY_INIT(name_maps);
                add_index_long(name_maps, code, PANDA_EXCEPTION_DEFAULE_CODE_COUNT);
                add_assoc_zval_ex(exception_statistics, exception_name, exception_name_len + 1, name_maps);
                convert_to_object(name_maps);
                Z_ADDREF_P(name_maps);
                PANDA_ARRAY_DESTROY(name_maps);
            }
            PANDA_G(exception_count)++;
        }

    } while(0);

    if (_panda_exception_execute) {
        _panda_exception_execute(exception TSRMLS_CC);
    }
}
