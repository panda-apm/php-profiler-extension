#ifndef PHP_PANDA_RESPONSE_H
#define PHP_PANDA_RESPONSE_H

#define PANDA_NODE_RESPONSE "response"
#define PANDA_NODE_RESPONSE_HTTP_STATUS "http_status"
#define PANDA_NODE_RESPONSE_HTTP_MIMETYPE "http_mimetype"
#define PANDA_NODE_RESPONSE_RESPONSE_TIME  "response_time"

int panda_response_compose_node(TSRMLS_D);
int panda_response_init_globals(TSRMLS_D);
int panda_response_destroy_globals(TSRMLS_D);
#endif





