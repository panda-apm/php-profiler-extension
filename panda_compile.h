#ifndef PHP_PANDA_COMPILE_H
#define PHP_PANDA_COMPILE_H

#define PANDA_NODE_COMPILE "compile"
#define PANDA_NODE_COMPILE_FILE_NUM    "file_num"
#define PANDA_NODE_COMPILE_FILE_WALLTIME "file_walltime"
#define PANDA_NODE_COMPILE_STRING_NUM   "string_num"
#define PANDA_NODE_COMPILE_STRING_WALLTIME "string_walltime"

static zend_op_array * (*_panda_compile_file_execute) (zend_file_handle *file_handle, int type TSRMLS_DC);
static zend_op_array * (*_panda_compile_string_execute) (zval *source_string, char *filename TSRMLS_DC);

static zend_op_array* panda_compile_file_execute(zend_file_handle *file_handle, int type TSRMLS_DC);
static zend_op_array* panda_compile_string_execute(zval *source_string, char *filename TSRMLS_DC);

int panda_compile_init_globals(TSRMLS_D);
int panda_compile_destroy_globals(TSRMLS_D);
int panda_compile_compose_node(TSRMLS_D);
int panda_compile_init_hooks(TSRMLS_D);
int panda_compile_destroy_hooks(TSRMLS_D);
static uint64 panda_compile_cycle_timer(TSRMLS_D);
#endif
