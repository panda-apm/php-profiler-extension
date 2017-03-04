#ifndef PHP_PANDA_STACK_H
#define PHP_PANDA_STACK_H
#define PANDA_NODE_STACK "stack"

//#define PANDA_STACK_CLS_NAME_SPEA_POINTER   "->"
#define PANDA_STACK_MAIN_FUNCTION "__main__"
#define PANDA_STACK_ENTRY_DEFAULT_LEVEL  1
#define PANDA_STACK_ENTRY_DEFAULT_PARENT_ID 0
#define PANDA_STACK_ENTRY_DEFAULT_CALL_TIME 1
#define PANDA_STACK_CLS_NAME_SPRA_QUOTATION "::"

#define PANDA_NODE_STACK "stack"
#define PANDA_NODE_STACK_MAPS "maps"
#define PANDA_NODE_STACK_COUNT "count"
#define PADNA_NODE_STACK_MAX_LEVEL "max_level"
#define PANDA_NODE_STACK_MAPS_NAME "mn"
#define PANDA_NODE_STACK_MAPS_ID "id"
#define PANDA_NODE_STACK_MAPS_PARENT_ID "pid"
#define PANDA_NODE_STACK_MAPS_START_TIME_MS "st_ms"
#define PANDA_NODE_STACK_MAPS_END_TIME_MS "et_ms"
#define PANDA_NODE_STACK_MAPS_WALL_TIME_US "wt_us"
#define PANDA_NODE_STACK_MAPS_MEMORY_USAGE "mu"
#define PANDA_NODE_STACK_MAPS_MEMORY_PEAK_USAGE "pmu"
#define PANDA_NODE_STACK_MAPS_CALL_TIME "ct"
#define PANDA_NODE_STACK_MAPS_CPU_TIME_US "ct_us"
#define PANDA_NODE_STACK_MAPS_LEVEL "l"
#define PANDA_NODE_STACK_MAPS_REFRENCES "_refs"

/* common */
#define PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_TYPE "r_t"
#define PANDA_NODE_STACK_MAPS_REFRENCES_RESOURCE_ID  "r_id"
#define PANDA_NODE_STACK_MAPs_REFRENCES_RESOURCE_IDS "r_ids"
#define PANDA_NODE_STACK_MAPS_REFRENCES_DB_NAME "db"
/* mysql */
#define PANDA_NODE_STACK_MAPS_REFRENCES_SQL_ID "sql_id"
/* memecache, memcached redis */
#define PANDA_NODE_STACK_MAPS_REFRENCES_KEY "key"
#define PANDA_NODE_STACK_MAPS_REFRENCES_KEYS "keys"
#define PANDA_NODE_STACK_MAPS_REFRENCES_SERVER_KEY "s_key"
#define PANDA_NODE_STACK_MAPS_REFRENCES_VAL_SIZE "v_size"
#define PANDA_NODE_STACK_MAPS_REFRENCES_ITEMS "items"
#define PANDA_NODE_STACK_MAPS_REFRENCES_FIELD "field"
#define PANDA_NODE_STACK_MAPS_REFRENCES_FIELDS "fields"
#define PANDA_NODE_STACK_MAPS_REFRENCES_POS "pos"
/* curl */
#define PANDA_NODE_STACK_MAPS_REFRENCES_URL "url"
#define PANDA_NODE_STACK_MAPS_REFRENCES_URLS "urls"
/* filename */
#define PANDA_NODE_STACK_MAPS_REFRENCES_FILENAME "filename"


#define PANDA_STACK_GET_ENTRY_CPU_TIME(entry) panda_stack_get_us_interval(&(entry->start_ru.ru_utime), &(entry->end_ru.ru_utime) TSRMLS_CC) + \
        panda_stack_get_us_interval(&(entry->start_ru.ru_stime), &(entry->end_ru.ru_stime) TSRMLS_CC)
#define PANDA_STACK_GET_ENTRY_WALL_TIME(entry) entry->end_us - entry->start_us
#define PANDA_STACK_GET_ENTRY_MEMORY_USAGE(entry) entry->end_mu - entry->start_mu
#define PANDA_STACK_GET_ENTRY_MEMORY_PEAK_USAGE(entry) entry->end_pmu - entry->start_pmu
#define PANDA_STACK_INC_ENTRY_ITEM_NUM(zval, name, num) panda_stcak_inc_entry_item_num(zval, name, num TSRMLS_CC)

#define PANDA_STACK_ALLOC_ENTRY() malloc(sizeof(panda_stack_entry_t))
#define PANDA_STACK_DESTROY_ENTRY(entry) free(entry);

#define PANDA_STACK_BEGIN_PROFILING(entries, symbol, execute_data)               \
    do {                                                                         \
        int must_new = PANDA_FALSE;                                              \
        panda_stack_entry_t *entry = PANDA_STACK_ALLOC_ENTRY();                  \
        entry->name = symbol;                                                    \
        entry->name_len = PANDA_STRLEN(symbol);                                  \
        entry->start_us = panda_stack_cycle_timer(TSRMLS_C);                     \
        entry->hash_code = zend_inline_hash_func(entry->name, entry->name_len);  \
        entry->start_mu = zend_memory_usage(0 TSRMLS_CC);                        \
        entry->start_pmu = zend_memory_peak_usage(0 TSRMLS_CC);                  \
        getrusage(RUSAGE_SELF, &entry->start_ru);                                \
        entry->prev_entry = (*(entries));                                        \
        if (*entries == NULL) {                                                  \
            entry->level = PANDA_STACK_ENTRY_DEFAULT_LEVEL;                      \
            entry->parent_id = PANDA_STACK_ENTRY_DEFAULT_PARENT_ID;              \
        } else {                                                                 \
            entry->level = (*(entries))->level + 1;                              \
            entry->parent_id = (*(entries))->id;                                 \
        }                                                                        \
        if (execute_data == NULL) {                                              \
            must_new = PANDA_TRUE;                                               \
        }                                                                        \
        entry->id = panda_stack_get_entry_id(entry, must_new TSRMLS_CC);         \
        (*(entries)) = (entry);                                                  \
    } while (0)                                                                  \

#define PANDA_STACK_END_PROFILING(entries, execute_data, expend_data)               \
    do {                                                                            \
        panda_stack_entry_t *entry = (*entries);                                    \
        entry->end_mu = zend_memory_usage(0 TSRMLS_CC);                             \
        entry->end_pmu = zend_memory_usage(0 TSRMLS_CC);                            \
        entry->end_us = panda_stack_cycle_timer(TSRMLS_C);                          \
        getrusage(RUSAGE_SELF, &entry->end_ru);                                     \
        panda_stack_extract_entry_data(entry, execute_data, expend_data TSRMLS_CC); \
        (*(entries)) = (*(entries))->prev_entry;                                    \
        panda_stack_free_entry(entry TSRMLS_CC);                                    \
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
int panda_stack_end_profiling(TSRMLS_D);
uint64 panda_stack_cycle_timer(TSRMLS_D);
int panda_stack_free_entry(panda_stack_entry_t *entry TSRMLS_DC);
void **panda_stack_get_execute_parameters(zend_execute_data *execute_data TSRMLS_DC);
zval *panda_stack_get_execute_param(zend_execute_data *execute_data, int n TSRMLS_DC);
int panda_stack_get_execute_paramters_count(zend_execute_data *execute_data TSRMLS_DC);
int panda_stack_extract_entry_data(panda_stack_entry_t *entry, zend_execute_data *execute_data, zval *expend_data TSRMLS_DC);
int panda_stack_get_entry_id(panda_stack_entry_t *entry, int must_new TSRMLS_DC);
ulong panda_stack_get_resource_hash(const char *host, int port TSRMLS_DC);
char *panda_stack_get_function_name(zend_execute_data *execute_data TSRMLS_DC);
static inline int panda_stcak_inc_entry_item_num(zval *zv, char* name, int64 num TSRMLS_DC);
static inline long panda_stack_get_us_interval(struct timeval *start, struct timeval *end TSRMLS_DC);
static int panda_array_stack_compare(const void *a, const void *b TSRMLS_DC);
#endif
