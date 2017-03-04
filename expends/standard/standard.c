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
#include "expends/standard/standard.h"

ZEND_EXTERN_MODULE_GLOBALS(panda)


PANDA_FUNCTION(file_get_contents)
{
    zend_execute_data *execute_data = EG(current_execute_data);
    char* execute_name = panda_stack_get_function_name(execute_data TSRMLS_CC);

    zval *expend_data;
    PANDA_ARRAY_INIT(expend_data);

    panda_expend_func _func;
    PANDA_EXPEND_GET_FUNC(&PANDA_G(expend_func_table), PANDA_EXPENDS_EXT_STANDARD_FUNC_FILE_GET_CONTENTS, &_func);

    PANDA_STACK_BEGIN_PROFILING(&PANDA_G(stack_entries), execute_name, NULL);
    (_func)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    PANDA_STACK_END_PROFILING(&PANDA_G(stack_entries), execute_data, expend_data);

    zval *filename_zval;
    filename_zval = panda_stack_get_execute_param(execute_data, 0 TSRMLS_CC);
    add_assoc_string(expend_data, PANDA_NODE_STACK_MAPS_REFRENCES_FILENAME, Z_STRVAL_P(filename_zval),  PANDA_TRUE);

    efree(execute_name);
    PANDA_ARRAY_DESTROY(expend_data);
}
