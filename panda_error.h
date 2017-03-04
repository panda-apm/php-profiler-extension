#ifndef PHP_PANDA_ERROR_H
#define PHP_PANDA_ERROR_H

#define PANDA_ERROR_DEFAULE_CODE_COUNT 1

#define PANDA_NODE_ERROR "error"
#define PANDA_NODE_ERROR_COUNT "count"
#define PANDA_NODE_ERROR_STATISTICS "statistics"
#define PANDA_NODE_ERROR_FATAL_ERROR "fatal_error"
#define PANDA_NODE_ERROR_FATAL_ERROR_TYPE "type"
#define PANDA_NODE_ERROR_FATAL_ERROR_FILE "file"
#define PANDA_NODE_ERROR_FATAL_ERROR_LINE "line"
#define PANDA_NODE_ERROR_FATAL_ERROR_MESSAGE "message"

static void (*_panda_error_execute)(int type, const char *error_filename,
        const uint error_lineno, const char *format, va_list args);
static void panda_error_execute(int type, const char *error_filename, const uint error_lineno,
        const char *format, va_list args);

int panda_error_init_globals(TSRMLS_D);
int panda_error_destroy_globals(TSRMLS_D);
int panda_error_compose_node(TSRMLS_D);
int panda_error_init_hooks(TSRMLS_D);
int panda_error_destroy_hooks(TSRMLS_D);
static char* panda_error_transfer_error_name(int e_type TSRMLS_DC);
#endif
