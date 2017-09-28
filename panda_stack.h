#ifndef PHP_PANDA_STACK_H
#define PHP_PANDA_STACK_H
#define PANDA_NODE_STACK "stack"

//#define PANDA_STACK_CLS_NAME_SPEA_POINTER   "->"
#define PANDA_STACK_MAIN_FUNCTION "__main__"
#define PANDA_STACK_ENTITY_DEFAULT_LEVEL  1
#define PANDA_STACK_ENTITY_DEFAULT_PARENT_ID 0
#define PANDA_STACK_ENTITY_DEFAULT_CALL_TIME 1
#define PANDA_STACK_CLS_NAME_SPRA_QUOTATION "::"

#define PANDA_NODE_STACK "stack"
#define PANDA_NODE_STACK_MAPS "maps"
#define PANDA_NODE_STACK_COUNT "count"
#define PADNA_NODE_STACK_MAX_LEVEL "maxLevel"
#define PANDA_NODE_STACK_MAPS_NAME "mn"
#define PANDA_NODE_STACK_MAPS_ID "id"
#define PANDA_NODE_STACK_MAPS_PARENT_ID "pid"
#define PANDA_NODE_STACK_MAPS_START_TIME_MS "st"
#define PANDA_NODE_STACK_MAPS_END_TIME_MS "et"
#define PANDA_NODE_STACK_MAPS_WALL_TIME_US "wt"
#define PANDA_NODE_STACK_MAPS_MEMORY_USAGE "mu"
#define PANDA_NODE_STACK_MAPS_MEMORY_PEAK_USAGE "pmu"
#define PANDA_NODE_STACK_MAPS_CALL_TIME "ct"
#define PANDA_NODE_STACK_MAPS_CPU_TIME_US "c"
#define PANDA_NODE_STACK_MAPS_FLAG_SLOWLY "s"
#define PANDA_NODE_STACL_MAPS_FLAG_FATAL_ERROR "fe"
#define PANDA_NODE_STACK_MAPS_FLAG_SLOWLY_REFRENCE_VALUE "srv"
#define PANDA_NODE_STACK_MAPS_LEVEL "l"
#define PANDA_NODE_STACK_MAPS_REFRENCES "refs"

/* common */
#define PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE "rt"
#define PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID  "rid"
#define PANDA_NODE_STACK_MAPs_REFRENCES_RESOURCE_IDS "rids"
#define PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME "db"
/* mysql */
#define PANDA_NODE_STACK_MAPS_REFRENCES_SQL_ID "sqlid"
/* memecache, memcached redis */
#define PANDA_NODE_STACK_MAPS_REFRENCES_KEY "key"
#define PANDA_NODE_STACK_MAPS_REFRENCES_KEYS "keys"
#define PANDA_NODE_STACK_MAPS_REFRENCES_SERVER_KEY "skey"
#define PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE "vsize"
#define PANDA_NODE_STACK_MAPS_REFRENCES_ITEMS "items"
#define PANDA_NODE_STACK_MAPS_REFRENCES_FIELD "field"
#define PANDA_NODE_STACK_MAPS_REFRENCES_FIELDS "fields"
#define PANDA_NODE_STACK_MAPS_REFRENCES_POS "pos"
/* curl */
#define PANDA_NODE_STACK_MAPS_REFRENCES_URL "url"
#define PANDA_NODE_STACK_MAPS_REFRENCES_URLS "urls"
/* filename */
#define PANDA_NODE_STACK_MAPS_REFRENCES_FILENAME "filename"


#define PANDA_STACK_GET_ENTITY_CPU_TIME(entity) panda_stack_get_us_interval(&(entity->start_ru.ru_utime), &(entity->end_ru.ru_utime) TSRMLS_CC) + \
        panda_stack_get_us_interval(&(entity->start_ru.ru_stime), &(entity->end_ru.ru_stime) TSRMLS_CC)
#define PANDA_STACK_GET_ENTITY_WALL_TIME(entity) entity->end_us - entity->start_us
#define PANDA_STACK_GET_ENTITY_MEMORY_USAGE(entity) entity->end_mu - entity->start_mu
#define PANDA_STACK_GET_ENTITY_MEMORY_PEAK_USAGE(entity) entity->end_pmu - entity->start_pmu
#define PANDA_STACK_INC_ENTITY_ITEM_NUM(zval, name, num) panda_stcak_inc_entity_item_num(zval, name, num TSRMLS_CC)

#define PANDA_STACK_ALLOC_ENTITY() malloc(sizeof(panda_stack_entity_t))
#define PANDA_STACK_DESTROY_ENTITY(entity) free(entity);

#define PANDA_STACK_BEGIN_PROFILING(entities, symbol, execute_data)               \
    do {                                                                         \
        int must_new = PANDA_FALSE;                                              \
        panda_stack_entity_t *entity = PANDA_STACK_ALLOC_ENTITY();                  \
        entity->name = symbol;                                                    \
        entity->name_len = PANDA_STRLEN(symbol);                                  \
        entity->start_us = panda_stack_cycle_timer(TSRMLS_C);                     \
        entity->hash_code = zend_inline_hash_func(entity->name, entity->name_len);  \
        entity->start_mu = zend_memory_usage(0 TSRMLS_CC);                        \
        entity->start_pmu = zend_memory_peak_usage(0 TSRMLS_CC);                  \
        getrusage(RUSAGE_SELF, &entity->start_ru);                                \
        entity->prev_entity = (*(entities));                                        \
        if (*entities == NULL) {                                                  \
            entity->level = PANDA_STACK_ENTITY_DEFAULT_LEVEL;                      \
            entity->parent_id = PANDA_STACK_ENTITY_DEFAULT_PARENT_ID;              \
        } else {                                                                 \
            entity->level = (*(entities))->level + 1;                              \
            entity->parent_id = (*(entities))->id;                                 \
        }                                                                        \
        if (execute_data == NULL) {                                              \
            must_new = PANDA_TRUE;                                               \
        }                                                                        \
        entity->id = panda_stack_get_entity_id(entity, must_new TSRMLS_CC);         \
        (*(entities)) = (entity);                                                  \
    } while (0)                                                                  \

#define PANDA_STACK_END_PROFILING(entities, execute_data, expend_data)               \
    do {                                                                            \
        panda_stack_entity_t *entity = (*entities);                                    \
        entity->end_mu = zend_memory_usage(0 TSRMLS_CC);                             \
        entity->end_pmu = zend_memory_peak_usage(0 TSRMLS_CC);                            \
        entity->end_us = panda_stack_cycle_timer(TSRMLS_C);                          \
        getrusage(RUSAGE_SELF, &entity->end_ru);                                     \
        panda_stack_extract_entity_data(entity, execute_data, expend_data TSRMLS_CC); \
        (*(entities)) = (*(entities))->prev_entity;                                    \
        panda_stack_free_entity(entity TSRMLS_CC);                                    \
    } while (0)                                                                     \

#if PHP_VERSION_ID < 50500
static void (*_panda_stack_execute) (zend_op_array *ops TSRMLS_DC);
static void panda_stack_execute (zend_op_array *ops TSRMLS_DC);
#else
static void (*_panda_stack_execute_ex) (zend_execute_data *execute_data TSRMLS_DC);
static void panda_stack_execute_ex (zend_execute_data *execute_data TSRMLS_DC);
#endif

int panda_stack_init_globals(TSRMLS_D);
int panda_stack_destroy_globals(TSRMLS_D);
int panda_stack_compose_node(TSRMLS_D);
int panda_stack_init_hooks(TSRMLS_D);
int panda_stack_destroy_hooks(TSRMLS_D);
int panda_stack_begin_profiling(TSRMLS_D);
int panda_stack_end_profiling(int has_fatal_error TSRMLS_DC);
zval* panda_stack_get_main(TSRMLS_D);
uint64 panda_stack_cycle_timer(TSRMLS_D);
int panda_stack_free_entity(panda_stack_entity_t *entity TSRMLS_DC);
void **panda_stack_get_execute_parameters(zend_execute_data *execute_data TSRMLS_DC);
zval *panda_stack_get_execute_param(zend_execute_data *execute_data, int n TSRMLS_DC);
int panda_stack_get_execute_paramters_count(zend_execute_data *execute_data TSRMLS_DC);
int panda_stack_extract_entity_data(panda_stack_entity_t *entity, zend_execute_data *execute_data, zval *expend_data TSRMLS_DC);
int panda_stack_get_entity_id(panda_stack_entity_t *entity, int must_new TSRMLS_DC);
ulong panda_stack_get_resource_hash(const char *host, int port TSRMLS_DC);
char *panda_stack_get_function_name(zend_execute_data *execute_data TSRMLS_DC);
static inline int panda_stcak_inc_entity_item_num(zval *zv, char* name, int64 num TSRMLS_DC);
static inline long panda_stack_get_us_interval(struct timeval *start, struct timeval *end TSRMLS_DC);
static int panda_stack_array_compare(const void *a, const void *b TSRMLS_DC);
static inline void panda_stack_set_slowly_flag(zval *entity, int flag, int refrence_value TSRMLS_DC);
static inline void panda_stack_set_fatal_error_flag(zval *entity, int flag TSRMLS_DC);
#endif
