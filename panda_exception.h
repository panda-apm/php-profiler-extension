#ifndef PHP_PANDA_EXCEPTION_H
#define PHP_PANDA_EXCEPTION_H


#define PANDA_EXCEPTION_DEFAULE_CODE_COUNT 1
#define PANDA_EXCEPTION_PROPRETY_CODE "code"

#define PANDA_NODE_EXCEPTION "exception"
#define PANDA_NODE_EXCEPTION_COUNT "count"
#define PANDA_NODE_EXCEPTION_STATISTICS "statistics"

static void (*_panda_exception_execute)(zval *exception TSRMLS_DC);
static void panda_exception_excecute(zval *exception TSRMLS_DC);

int panda_exception_init_globals(TSRMLS_D);
int panda_exception_destroy_globals(TSRMLS_D);
int panda_exception_compose_node(TSRMLS_D);
int panda_exception_init_hooks(TSRMLS_D);
int panda_exception_destroy_hooks(TSRMLS_D);
#endif

