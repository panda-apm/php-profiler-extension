#ifndef PHP_PANDA_BASE_H
#define PHP_PANDA_BASE_H

#define PANDA_NODE_BASE "base"
#define PANDA_NODE_BASE_ID  "id"
#define PANDA_NODE_BASE_KEY "key"
#define PANDA_NODE_BASE_LANG "lang"
#define PANDA_NODE_BASE_LANG_VERSION "version"
#define PANDA_NODE_BASE_PROTOCOL "protocol"
#define PANDA_NODE_BASE_PROTOCOL_VERSION "version"

int panda_base_compose_node(TSRMLS_D);
int panda_base_init_globals(TSRMLS_D);
int panda_base_destroy_globals(TSRMLS_D);

static inline int panda_base_generate_uuid(char *ubuf TSRMLS_DC);
#endif


