#ifndef PHP_PANDA_RESPONSE_H
#define PHP_PANDA_RESPONSE_H

#define PANDA_NODE_RESPONSE "response"
#define PANDA_NODE_RESPONSE_HTTP_STATUS "httpStatus"
#define PANDA_NODE_RESPONSE_HTTP_MIMETYPE "httpMimetype"
#define PANDA_NODE_RESPONSE_RESPONSE_TIME  "responseTime"

int panda_response_compose_node(TSRMLS_D);
int panda_response_init_globals(TSRMLS_D);
int panda_response_destroy_globals(TSRMLS_D);
#endif





