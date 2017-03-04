#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_panda.h"
#include "panda_stack.h"
#include "panda_compile.h"

ZEND_EXTERN_MODULE_GLOBALS(panda);

int panda_compile_compose_node(TSRMLS_D)
{
    zval *zv = PANDA_G(node_compile);
    add_assoc_long(zv, PANDA_NODE_COMPILE_FILE_COUNT, PANDA_G(compile_file_count));
    add_assoc_long(zv, PANDA_NODE_COMPILE_FILE_WALLTIME, PANDA_G(compile_file_walltime));
    add_assoc_long(zv, PANDA_NODE_COMPILE_STRING_COUNT, PANDA_G(compile_string_count));
    add_assoc_long(zv, PANDA_NODE_COMPILE_STRING_WALLTIME, PANDA_G(compile_string_walltime));
    return SUCCESS;
}

int panda_compile_init_globals(TSRMLS_D)
{
    PANDA_ARRAY_INIT(PANDA_G(node_compile));
    PANDA_G(compile_string_count) = 0;
    PANDA_G(compile_string_walltime) = 0;
    PANDA_G(compile_file_count) = 0;
    PANDA_G(compile_file_walltime) = 0;
    return SUCCESS;
}

int panda_compile_destroy_globals(TSRMLS_D)
{
    PANDA_ARRAY_DESTROY(PANDA_G(node_compile));
    return SUCCESS;
}

int panda_compile_init_hooks(TSRMLS_D)
{
    _panda_compile_file_execute = zend_compile_file;
    zend_compile_file  = panda_compile_file_execute;
    _panda_compile_string_execute = zend_compile_string;
    zend_compile_string = panda_compile_string_execute;
    return SUCCESS;
}

int panda_compile_destroy_hooks(TSRMLS_D)
{
    zend_compile_file = _panda_compile_file_execute;
    zend_compile_string = _panda_compile_string_execute;
    return SUCCESS;
}

static uint64 panda_compile_cycle_timer(TSRMLS_D)
{

    return panda_stack_cycle_timer(TSRMLS_C);
}

static zend_op_array* panda_compile_file_execute(zend_file_handle *file_handle, int type TSRMLS_DC)
{
    uint64 start_us = panda_compile_cycle_timer();
    zend_op_array* ret = _panda_compile_file_execute(file_handle, type TSRMLS_CC);
    uint64 end_us = panda_stack_cycle_timer();
    PANDA_G(compile_file_walltime) += end_us - start_us;
    PANDA_G(compile_file_count)++;
    return ret;
}


static zend_op_array* panda_compile_string_execute(zval *source_string, char *filename TSRMLS_DC)
{
    uint64 start_us = panda_compile_cycle_timer();
    zend_op_array *ret = _panda_compile_string_execute(source_string, filename TSRMLS_CC);
    uint64 end_us = panda_stack_cycle_timer();
    PANDA_G(compile_string_walltime) += end_us - start_us;
    PANDA_G(compile_string_count)++;
    return ret;
}
