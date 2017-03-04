#ifndef PHP_PANDA_EXPEND_H
#define PHP_PANDA_EXPEND_H

#define PANDA_EXPEND_HOOK_FUNC(ht, name, handler)                                                            \
do {                                                                                                         \
    panda_expend_func_pair_t *pair_t = emalloc(sizeof(panda_expend_func_pair_t));                            \
    pair_t->func = handler;                                                                                  \
    ulong hash = zend_inline_hash_func(name, PANDA_STRLEN(name));                                            \
    if (panda_expend_hook_func(name, pair_t->func, &pair_t->_func TSRMLS_CC) == SUCCESS) {                   \
        PANDA_HASHTABLE_INDEX_ADD(ht, hash, (void*)pair_t, sizeof(panda_expend_func_pair_t));                \
    }                                                                                                        \
    efree(pair_t);                                                                                           \
} while(0)                                                                                                   \

#define PANDA_EXPEND_HOOK_CLS_FUNC(ht, cls, name, handler)                                                             \
do {                                                                                                                   \
    panda_expend_func_pair_t *pair_t = emalloc(sizeof(panda_expend_func_pair_t));                                      \
    pair_t->func = handler;                                                                                            \
    ulong hash = zend_inline_hash_func(name, PANDA_STRLEN(name));                                                      \
    if (panda_expend_hook_cls_func(cls, name, pair_t->func, &pair_t->_func TSRMLS_CC) == SUCCESS) {                    \
        void *func_table;                                                                                              \
        if (zend_hash_find(ht, cls, PANDA_STRLEN(cls), (void **)&func_table) == SUCCESS)  {                            \
            PANDA_HASHTABLE_INDEX_ADD((HashTable *)func_table, hash, (void*)pair_t, sizeof(panda_expend_func_pair_t)); \
        } else {                                                                                                       \
            HashTable new_table;                                                                                       \
            PANDA_HASHTABLE_INIT(&new_table);                                                                          \
            PANDA_HASHTABLE_INDEX_ADD(&new_table, hash, (void*)pair_t, sizeof(panda_expend_func_pair_t));              \
            PANDA_HASHTABLE_ASSOC_ADD(ht, cls, (void *)&new_table, sizeof(HashTable));                                 \
        }                                                                                                              \
    }                                                                                                                  \
    efree(pair_t);                                                                                                     \
} while (0)                                                                                                            \

#define PANDA_EXPEND_GET_FUNC(ht, name, handler_ptr)                                  \
do {                                                                                  \
    void *data;                                                                       \
    ulong hash = zend_inline_hash_func(name, PANDA_STRLEN(name));                     \
    if (zend_hash_index_find(ht, hash, (void **)&data) == SUCCESS) {                  \
        panda_expend_func_pair_t *pair_t = (panda_expend_func_pair_t *)data;          \
        *handler_ptr = (panda_expend_func)pair_t->_func;                              \
    }                                                                                 \
} while(0)                                                                            \

#define PANDA_EXPEND_GET_CLS_FUNC(ht, cls, name, handler_ptr)                                          \
do {                                                                                                   \
    void *data, *func_table;                                                                           \
    ulong hash = zend_inline_hash_func(name, PANDA_STRLEN(name));                                      \
    if (zend_hash_find(ht, cls, PANDA_STRLEN(cls), (void **)&func_table) == SUCCESS){                  \
        if (zend_hash_index_find((HashTable *)func_table, hash, (void **)&data) == SUCCESS) {          \
             panda_expend_func_pair_t *pair_t = (panda_expend_func_pair_t *)data;                      \
             *handler_ptr = (panda_expend_func)pair_t->_func;                                          \
        }                                                                                              \
    }                                                                                                  \
} while(0)                                                                                             \

typedef void (*panda_expend_func)(INTERNAL_FUNCTION_PARAMETERS);

typedef struct panda_expend_func_pair {
    panda_expend_func func;
    panda_expend_func _func;
} panda_expend_func_pair_t;

int panda_expend_init_globals(TSRMLS_D);
int panda_expend_destroy_globals(TSRMLS_D);
int panda_expend_init_hooks(TSRMLS_D);
int panda_expend_destroy_hooks(TSRMLS_D);
static inline int panda_expend_hook_func(const char *name, panda_expend_func handler, panda_expend_func *stash TSRMLS_DC);
static inline int panda_expend_hook_cls_func(const char *cls_name, const char *name, panda_expend_func handler, panda_expend_func *stash TSRMLS_DC);
static inline void panda_expend_register_func_hooks(TSRMLS_D);
static inline void panda_expend_register_cls_func_hooks(TSRMLS_D);
#endif
