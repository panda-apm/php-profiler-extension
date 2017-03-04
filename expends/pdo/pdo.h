#ifndef PHP_PANDA_PDO_H
#define PHP_PANDA_PDO_H

#define PANDA_EXPENDS_EXT_PDO_DEFAULT_HOST "127.0.0.1"
#define PANDA_EXPENDS_EXT_PDO_DEFAULT_PORT "3306"


#define PANDA_EXPENDS_EXT_PDO "pdo"
#define PANDA_EXPENDS_EXT_PDO_CLS_PDO "pdo"
#define PANDA_EXPENDS_EXT_PDO_CLS_PDO_STATEMENT "pdostatement"

#define PANDA_EXPENDS_EXT_PDO_CLS_PDO_METHOD_PDO "__construct"
#define PANDA_EXPENDS_EXT_PDO_CLS_PDO_METHOD_QUERY "query"
#define PANDA_EXPENDS_EXT_PDO_CLS_PDO_METHOD_PREPARE "prepare"
#define PANDA_EXPENDS_EXT_PDO_CLS_PDO_METHOD_EXEC "exec"
#define PANDA_EXPENDS_EXT_PDO_CLS_PDO_STATEMENT_METHOD_EXECUTE "execute"

struct pdo_data_src_parser {
    const char *optname;
    char *optval;
    int freeme;
};


PANDA_METHOD(pdo, pdo);
PANDA_METHOD(pdo, query);
PANDA_METHOD(pdo, exec);
PANDA_METHOD(pdo, prepare);
PANDA_METHOD(pdostatement, execute);

static int php_pdo_parse_data_source(const char *data_source, unsigned long data_source_len, struct pdo_data_src_parser *parsed, int nparams);
#endif
