#ifndef PHP_PANDA_SERVER_H
#define PHP_PANDA_SERVER_H

#define PANDA_REQUEST_VARS_TYPE    unsigned int
#define PANDA_REQUEST_VARS_POST    TRACK_VARS_POST
#define PANDA_REQUEST_VARS_GET     TRACK_VARS_GET
#define PANDA_REQUEST_VARS_ENV     TRACK_VARS_ENV
#define PANDA_REQUEST_VARS_FILES   TRACK_VARS_FILES
#define PANDA_REQUEST_VARS_SERVER  TRACK_VARS_SERVER
#define PANDA_REQUEST_VARS_REQUEST TRACK_VARS_REQUEST
#define PANDA_REQUEST_VARS_COOKIE  TRACK_VARS_COOKIE

#define PANDA_REQUEST_VARS_SERVER_REQUEST_TIME          "REQUEST_TIME"
#define PANDA_REQUEST_VARS_SERVER_SCRIPT_NAME           "SCRIPT_NAME"
#define PANDA_REQUEST_VARS_SERVER_USER                  "USER"
#define PANDA_REQUEST_VARS_SERVER_SERVER_ADDR           "SERVER_ADDR"
#define PANDA_REQUEST_VARS_SERVER_SERVER_PORT           "SERVER_PORT"
#define PANDA_REQUEST_VARS_SERVER_SERVER_NAME           "SERVER_NAME"
#define PANDA_REQUEST_VARS_SERVER_REDIRECT_STATUS       "REDIRECT_STATUS"
#define PANDA_REQUEST_VARS_SERVER_REQUEST_METHOD        "REQUEST_METHOD"
#define PANDA_REQUEST_VARS_SERVER_REQUEST_URI           "REQUEST_URI"
#define PANDA_REQUEST_VARS_SERVER_DOCUMENT_URI          "DOCUMENT_URI"
#define PANDA_REQUEST_VARS_SERVER_HTTP_USER_AGENT       "HTTP_USER_AGENT"
#define PANDA_REQUEST_VARS_SERVER_REMOTE_ADDR           "REMOTE_ADDR"
#define PANDA_REQUEST_VARS_SERVER_HTTP_X_REAL_IP        "HTTP_X_REAL_IP"
#define PANDA_REQUEST_VARS_SERVER_HTTP_X_FORWARDED_FOR  "HTTP_X_FORWARDED_FOR"
#define PANDA_REQUEST_VARS_SERVER_HTTP_X_REQUESTED_WITH "HTTP_X_REQUESTED_WITH"

#define PANDA_NODE_REQUEST "request"
#define PANDA_NODE_REQUEST_SERVERS "servers"
#define PANDA_NODE_REQUEST_COOKIES "cookies"
#define PANDA_NODE_REQUEST_POSTS   "posts"
#define PANDA_NODE_REQUEST_SERVER_SAPI "sapi"
#define PANDA_NODE_REQUEST_SERVER_REQUEST_TIME "request_time"
#define PANDA_NODE_REQUEST_SERVER_SCRIPT_NAME "script_name"
#define PANDA_NODE_REQUEST_SERVER_USER "user"
#define PANDA_NODE_REQUEST_SERVER_SERVER_NAME "server_name"
#define PANDA_NODE_REQUEST_SERVER_SERVER_ADDR "server_addr"
#define PANDA_NODE_REQUEST_SERVER_CLIENT_ADDR "client_addr"
#define PANDA_NODE_REQUEST_SERVER_SERVER_PORT "server_port"
#define PANDA_NODE_REQUEST_SERVER_REDIRECT_STATUS "redirect_status"
#define PANDA_NODE_REQUEST_SERVER_REQUEST_METHOD "request_method"
#define PANDA_NODE_REQUEST_SERVER_REQUEST_URI  "request_uri"
#define PANDA_NODE_REQUEST_SERVER_DOCUMENT_URI "document_uri"
#define PANDA_NODE_REQUEST_SERVER_HTTP_USER_AGENT "http_user_agent"
#define PANDA_NODE_REQUEST_SERVER_IS_CLI_MODE "is_cli_mode"
#define PANDA_NODE_REQUEST_SERVER_IS_XML_REQUEST "is_xml_request"
#define PANDA_NODE_REQUEST_SERVER_TIMEZONE "timezone"

#define PANDA_REQUEST_GET_PARAMS(type) panda_request_get_params(type TSRMLS_CC);
#define PANDA_REQUEST_GET_PARAM(type, name) panda_request_get_param_with_name(type, name, PANDA_STRLEN(name) TSRMLS_CC)

int panda_request_compose_node(TSRMLS_D);
int panda_request_init_globals(TSRMLS_D);
int panda_request_destroy_globals(TSRMLS_D);
int panda_request_is_cli_mode(TSRMLS_D);
static inline char *panda_request_get_sapi_name(TSRMLS_D);
static inline zval *panda_request_get_real_client_addr(TSRMLS_D);
static inline zval *panda_request_get_params(uint type TSRMLS_DC);
static inline zval *panda_request_get_param_with_name(uint type, char *key, int key_len TSRMLS_DC);
static inline int panda_request_is_xml_http_request(TSRMLS_D);

#endif
