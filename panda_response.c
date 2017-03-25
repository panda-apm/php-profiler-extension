#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <time.h>
#include "php.h"
#include "main/SAPI.h"
#include "php_panda.h"
#include "panda_response.h"
#include "panda_request.h"

ZEND_EXTERN_MODULE_GLOBALS(panda)
int panda_response_compose_node(TSRMLS_D)
{
    if (!panda_request_is_cli_mode(TSRMLS_C)) {
        zval *zv = PANDA_G(node_response);
        char *mimetype = SG(sapi_headers.mimetype);
        if (mimetype == NULL) {
            mimetype = SAPI_DEFAULT_MIMETYPE;
        }
        add_assoc_long(zv, PANDA_NODE_RESPONSE_HTTP_STATUS, (long)SG(sapi_headers.http_response_code));
        add_assoc_string(zv, PANDA_NODE_RESPONSE_HTTP_MIMETYPE, mimetype, PANDA_TRUE);
        add_assoc_long(zv, PANDA_NODE_RESPONSE_RESPONSE_TIME, time(NULL));
    }
    return PANDA_TRUE;
}


int panda_response_init_globals(TSRMLS_D)
{
    PANDA_ARRAY_INIT(PANDA_G(node_response));
    return SUCCESS;
}

int panda_response_destroy_globals(TSRMLS_D)
{
    PANDA_ARRAY_DESTROY(PANDA_G(node_response));
    return SUCCESS;
}
