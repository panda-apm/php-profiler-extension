#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_panda.h"
#include "panda_base.h"
#include "uuid/uuid.h"

ZEND_EXTERN_MODULE_GLOBALS(panda)

int panda_base_compose_node(TSRMLS_D)
{
    zval *zv = PANDA_G(node_base);
    int status = FAILURE;
    do {
        zval *lang;
        PANDA_ARRAY_INIT(lang);
        add_assoc_string(lang, PANDA_NODE_BASE_LANG_VERSION, PHP_VERSION, PANDA_TRUE);
        add_assoc_zval(zv, PANDA_NODE_BASE_LANG, lang);

        zval *protocol;
        PANDA_ARRAY_INIT(protocol);
        add_assoc_string(protocol, PANDA_NODE_BASE_PROTOCOL_VERSION, PANDA_TRANSFER_PROTOCOL_VERSION, PANDA_TRUE);
        add_assoc_zval(zv, PANDA_NODE_BASE_PROTOCOL, protocol);
        Z_ADDREF_P(protocol);
        PANDA_ARRAY_DESTROY(protocol);

        char uuid_str[37];
        if (panda_base_generate_uuid(uuid_str TSRMLS_CC) == SUCCESS) {
            add_assoc_string(zv, PANDA_NODE_BASE_ID, uuid_str, PANDA_TRUE);
        }
        add_assoc_string(zv, PANDA_NODE_BASE_KEY, PANDA_G(config_key), PANDA_TRUE);
        status = SUCCESS;
    } while(0);
    return status;
}

int panda_base_init_globals(TSRMLS_D)
{
    PANDA_ARRAY_INIT(PANDA_G(node_base));
    return SUCCESS;
}

int panda_base_destroy_globals(TSRMLS_D)
{
    PANDA_ARRAY_DESTROY(PANDA_G(node_base));
    return SUCCESS;
}

static inline int panda_base_generate_uuid(char *ubuf TSRMLS_DC)
{
    uuid_t uuid;
    uuid_generate(uuid);
    uuid_unparse(uuid, ubuf);
    return SUCCESS;
}
