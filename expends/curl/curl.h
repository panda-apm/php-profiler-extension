#ifndef PHP_PANDA_CURL_H
#define PHP_PANDA_CURL_H

#define PANDA_EXPENDS_EXT_CURL "curl"

#define PANDA_EXPENDS_EXT_CURL_FUNC_CURL_INIT "curl_init"
#define PANDA_EXPENDS_EXT_CURL_FUNC_CURL_SETOPT "curl_setopt"
#define PANDA_EXPENDS_EXT_CURL_FUNC_CURL_SETOPT_ARRAY "curl_setopt_array"
#define PANDA_EXPENDS_EXT_CURL_FUNC_CURL_EXEC "curl_exec"
#define PANDA_EXPENDS_EXT_CURL_FUNC_CURL_CLOSE "curl_close"
#define PANDA_EXPENDS_EXT_CURL_FUNC_CURL_MULTI_INIT "curl_multi_init"
#define PANDA_EXPENDS_EXT_CURL_FUNC_CURL_MULTI_CLOSE "curl_multi_close"
#define PANDA_EXPENDS_EXT_CURL_FUNC_CURL_MULTI_ADD_HANDLE "curl_multi_add_handle"
#define PANDA_EXPENDS_EXT_CURL_FUNC_CURL_MULTI_REMOVE_HANDLE "curl_multi_remove_handle"
#define PANDA_EXPENDS_EXT_CURL_FUNC_CURL_MULTI_EXEC "curl_multi_exec"


PANDA_FUNCTION(curl_init);
PANDA_FUNCTION(curl_setopt);
PANDA_FUNCTION(curl_setopt_array);
PANDA_FUNCTION(curl_exec);
PANDA_FUNCTION(curl_close);
PANDA_FUNCTION(curl_multi_init);
PANDA_FUNCTION(curl_multi_close);
PANDA_FUNCTION(curl_multi_add_handle);
PANDA_FUNCTION(curl_multi_remove_handle);
PANDA_FUNCTION(curl_multi_exec);

#endif
