#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "main/SAPI.h"
#include "ext/date/php_date.h"
#include "php_panda.h"
#include "panda_request.h"


ZEND_EXTERN_MODULE_GLOBALS(panda)

int panda_request_compose_node(TSRMLS_D)
{
    zval *zv = PANDA_G(node_request);
    int status = FAILURE;
    do {
        zval *server, *server_ip, *request_time, *script_name, *user;

        int cli_mode  = panda_request_is_cli_mode(TSRMLS_C);

        PANDA_ARRAY_INIT(server);
        char *sapi_name = panda_request_get_sapi_name(TSRMLS_C);
        request_time = PANDA_REQUEST_GET_PARAM(PANDA_REQUEST_VARS_SERVER, PANDA_REQUEST_VARS_SERVER_REQUEST_TIME);
        script_name = PANDA_REQUEST_GET_PARAM(PANDA_REQUEST_VARS_SERVER, PANDA_REQUEST_VARS_SERVER_SCRIPT_NAME);
        user = PANDA_REQUEST_GET_PARAM(PANDA_REQUEST_VARS_SERVER, PANDA_REQUEST_VARS_SERVER_USER);
        timelib_tzinfo *default_tz = get_timezone_info(TSRMLS_C);
        char *timezone = default_tz->name;

        if (request_time != NULL) {
            add_assoc_long(server, PANDA_NODE_REQUEST_SERVER_REQUEST_TIME, Z_LVAL_P(request_time));
        }

        if (script_name != NULL) {
            add_assoc_string(server, PANDA_NODE_REQUEST_SERVER_SCRIPT_NAME, Z_STRVAL_P(script_name), PANDA_TRUE);
        }

        if (user != NULL) {
            add_assoc_string(server, PANDA_NODE_REQUEST_SERVER_USER, Z_STRVAL_P(user), PANDA_TRUE);
        }

        add_assoc_string(server, PANDA_NODE_REQUEST_SERVER_SAPI, sapi_name, PANDA_TRUE);
        add_assoc_string(server, PANDA_NODE_REQUEST_SERVER_TIMEZONE, timezone, PANDA_TRUE);
        add_assoc_long(server, PANDA_NODE_REQUEST_SERVER_IS_CLI_MODE, (long)cli_mode);
        add_assoc_zval(zv, PANDA_NODE_REQUEST_SERVERS, server);
        Z_ADDREF_P(server);

        if (cli_mode == PANDA_FALSE) {
            zval *server_addr, *server_port, *redirect_status, *request_method, *user_agent, *request_uri;
            zval *client_addr, *server_name;
            int xml_request = panda_request_is_xml_http_request(TSRMLS_C);
            server_addr = PANDA_REQUEST_GET_PARAM(PANDA_REQUEST_VARS_SERVER, PANDA_REQUEST_VARS_SERVER_SERVER_ADDR);
            server_port = PANDA_REQUEST_GET_PARAM(PANDA_REQUEST_VARS_SERVER, PANDA_REQUEST_VARS_SERVER_SERVER_PORT);
            redirect_status = PANDA_REQUEST_GET_PARAM(PANDA_REQUEST_VARS_SERVER, PANDA_REQUEST_VARS_SERVER_REDIRECT_STATUS);
            request_method = PANDA_REQUEST_GET_PARAM(PANDA_REQUEST_VARS_SERVER, PANDA_REQUEST_VARS_SERVER_REQUEST_METHOD);
            user_agent = PANDA_REQUEST_GET_PARAM(PANDA_REQUEST_VARS_SERVER, PANDA_REQUEST_VARS_SERVER_HTTP_USER_AGENT);
            request_uri = PANDA_REQUEST_GET_PARAM(PANDA_REQUEST_VARS_SERVER, PANDA_REQUEST_VARS_SERVER_REQUEST_URI);
            server_name = PANDA_REQUEST_GET_PARAM(PANDA_REQUEST_VARS_SERVER, PANDA_REQUEST_VARS_SERVER_SERVER_NAME);
            client_addr = panda_request_get_real_client_addr(TSRMLS_C);


            convert_to_long(server_port);
            convert_to_long(redirect_status);
            add_assoc_string(server, PANDA_NODE_REQUEST_SERVER_SERVER_ADDR, Z_STRVAL_P(server_addr), PANDA_TRUE);
            add_assoc_string(server, PANDA_NODE_REQUEST_SERVER_CLIENT_ADDR, Z_STRVAL_P(client_addr), PANDA_TRUE);
            add_assoc_string(server, PANDA_NODE_REQUEST_SERVER_REQUEST_METHOD, Z_STRVAL_P(request_method), PANDA_TRUE);
            add_assoc_string(server, PANDA_NODE_REQUEST_SERVER_HTTP_USER_AGENT, Z_STRVAL_P(user_agent), PANDA_TRUE);
            add_assoc_string(server, PANDA_NODE_REQUEST_SERVER_REQUEST_URI, Z_STRVAL_P(request_uri), PANDA_TRUE);
            add_assoc_string(server, PANDA_NODE_REQUEST_SERVER_SERVER_NAME, Z_STRVAL_P(server_name), PANDA_TRUE);
            add_assoc_long(server, PANDA_NODE_REQUEST_SERVER_SERVER_PORT, Z_LVAL_P(server_port));
            add_assoc_long(server, PANDA_NODE_REQUEST_SERVER_REDIRECT_STATUS, Z_LVAL_P(redirect_status));
            add_assoc_long(server, PANDA_NODE_REQUEST_SERVER_IS_XML_REQUEST, (long)xml_request);

            if (PANDA_G(config_collect_request_cookie)) {
                zval *cookie = PANDA_REQUEST_GET_PARAMS(PANDA_REQUEST_VARS_COOKIE);
                add_assoc_zval(zv, PANDA_NODE_REQUEST_COOKIES, cookie);
            }

            if (PANDA_G(config_collect_request_post)) {
                zval *posts = PANDA_REQUEST_GET_PARAMS(PANDA_REQUEST_VARS_POST);
                add_assoc_zval(zv, PANDA_NODE_REQUEST_POSTS, posts);
            }
        }


        PANDA_ARRAY_DESTROY(server);
        status = SUCCESS;
    } while(0);

    return status;
}

int panda_request_init_globals(TSRMLS_D)
{
    PANDA_ARRAY_INIT(PANDA_G(node_request));
    return SUCCESS;
}

int panda_request_destroy_globals(TSRMLS_D)
{
    PANDA_ARRAY_DESTROY(PANDA_G(node_request));
    return SUCCESS;
}

int panda_request_is_cli_mode(TSRMLS_D)
{
    int res = PANDA_FALSE;
    if (!SG(request_info).request_method) {
        if (!strncasecmp(sapi_module.name, "cli", 3)) {
           res = PANDA_TRUE;
        }
    }
    return res;
}


static inline char *panda_request_get_sapi_name(TSRMLS_D)
{
    return sapi_module.name;
}

static inline zval *panda_request_get_params(uint type TSRMLS_DC)
{
    zval *data;
    zend_bool jit_initialization = PG(auto_globals_jit);

    switch (type) {
    case PANDA_REQUEST_VARS_POST:
        if (jit_initialization) {
            zend_is_auto_global(ZEND_STRL("_POST") TSRMLS_CC);
        }
        data = PG(http_globals)[PANDA_REQUEST_VARS_POST];
        break;
    case PANDA_REQUEST_VARS_GET:
        if (jit_initialization) {
            zend_is_auto_global(ZEND_STRL("_GET") TSRMLS_CC);
        }
        data = PG(http_globals)[PANDA_REQUEST_VARS_GET];
        break;
    case PANDA_REQUEST_VARS_FILES:
    case PANDA_REQUEST_VARS_COOKIE:
        if (jit_initialization) {
            zend_is_auto_global(ZEND_STRL("_COOKIE") TSRMLS_CC);
        }
        data = PG(http_globals)[PANDA_REQUEST_VARS_COOKIE];
        break;
    case PANDA_REQUEST_VARS_ENV:
    case PANDA_REQUEST_VARS_SERVER:
        if (jit_initialization) {
            zend_is_auto_global(ZEND_STRL("_SERVER") TSRMLS_CC);
        }
        data = PG(http_globals)[PANDA_REQUEST_VARS_SERVER];
        break;
    case PANDA_REQUEST_VARS_REQUEST:
    default:
        data = NULL;
        break;
    }
    return data;
}

static inline zval *panda_request_get_param_with_name(uint type, char *key, int key_len TSRMLS_DC)
{
    zval *params = PANDA_REQUEST_GET_PARAMS(type);
    zval **ret;

    if (params != NULL) {
        if (zend_hash_find(Z_ARRVAL_P(params), key, key_len, (void **)&ret) == FAILURE) {
            return NULL;
        }
    }
    return *ret;
}


static inline zval *panda_request_get_real_client_addr(TSRMLS_D)
{
    zval *client_addr;
    do {
        client_addr = PANDA_REQUEST_GET_PARAM(PANDA_REQUEST_VARS_SERVER, PANDA_REQUEST_VARS_SERVER_HTTP_X_REAL_IP);
        if (NULL != client_addr) {
            break;
        }
        client_addr = PANDA_REQUEST_GET_PARAM(PANDA_REQUEST_VARS_SERVER, PANDA_REQUEST_VARS_SERVER_HTTP_X_FORWARDED_FOR);
        if (NULL != client_addr) {
            break;
        }
        client_addr = PANDA_REQUEST_GET_PARAM(PANDA_REQUEST_VARS_SERVER, PANDA_REQUEST_VARS_SERVER_REMOTE_ADDR);
    } while(0);

    return client_addr;
}

static inline int panda_request_is_xml_http_request(TSRMLS_D)
{
    zval *http_x_requested_with;
    int result = PANDA_FALSE;
    http_x_requested_with = PANDA_REQUEST_GET_PARAM(PANDA_REQUEST_VARS_SERVER, PANDA_REQUEST_VARS_SERVER_HTTP_X_REQUESTED_WITH);
    if (http_x_requested_with != NULL) {
        if (strncasecmp("XMLHttpRequest", Z_STRVAL_P(http_x_requested_with), Z_STRLEN_P(http_x_requested_with)) == 0) {
            result = PANDA_TRUE;
        }
    }
    return result;
}
