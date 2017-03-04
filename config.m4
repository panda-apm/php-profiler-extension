dnl $Id$
dnl config.m4 for extension panda

AC_DEFUN([PANDA_CHECK_PHP_VERSION],[
  tmp_version=$PHP_VERSION
  if test -z "$tmp_version"; then
    if test -z "$PHP_CONFIG"; then
      AC_MSG_ERROR([php-config not found])
    fi
    php_version=`$PHP_CONFIG --version 2>/dev/null|head -n 1|sed -e 's#\([0-9]\.[0-9]*\.[0-9]*\)\(.*\)#\1#'`
  else
    php_version=`echo "$tmp_version"|sed -e 's#\([0-9]\.[0-9]*\.[0-9]*\)\(.*\)#\1#'`
  fi

  if test -z "$php_version"; then
    AC_MSG_ERROR([failed to detect PHP version, please report])
  fi

  ac_IFS=$IFS
  IFS="."
  set $php_version
  IFS=$ac_IFS
  panda_php_version=`expr [$]1 \* 1000000 + [$]2 \* 1000 + [$]3`

  if test "$panda_php_version" -le "5003000"; then
    AC_MSG_ERROR([You need at least PHP 5.3.0 to be able to use this version of Yaf. PHP $php_version found])
  else
    AC_MSG_RESULT([php version :$php_version, ok])
  fi
])  

PHP_ARG_WITH(panda, for panda support,
Make sure that the comment is aligned:
[  --with-panda             Include panda support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(panda, whether to enable panda support,
Make sure that the comment is aligned:
[  --enable-panda           Enable panda support])
if test "$PHP_PANDA" != "no"; then
  dnl Write more examples of tests here...
 
# --with-panda -> check with-path
  SEARCH_PATH="/usr/local /usr"     # you might want to change this
  SEARCH_FOR_UUID="/include/uuid/uuid.h"  # you most likely want to change this
  if test -r $UUID_DIR/$SEARCH_FOR_UUID; then # path given as parameter
    PANDA_UUID_DIR=$UUID_DIR
  else # search default path list
    AC_MSG_CHECKING([uuid library path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR_UUID; then
        PANDA_UUID_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi
  
  if test -z "$PANDA_UUID_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the UUID distribution])
  fi

  SEARCH_FOR_CURL="include/curl/curl.h"
  if test -r $CURL_DIR/$SEARCH_FOR_CURL; then # path given as parameter
    PANDA_CURL_DIR=$CURL_DIR
  else # search default path list
    AC_MSG_CHECKING([curl header])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR_CURL; then
        PANDA_CURL_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi
  
  if test -z "$PANDA_CURL_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the CURL distribution])
  fi
 
  PANDA_CHECK_PHP_VERSION
    
  if test `uname` != "Darwin"; then
    PHP_CHECK_LIBRARY(uuid, uuid_unparse,
    [
      PHP_ADD_LIBRARY_WITH_PATH(uuid, $PANDA_UUID_DIR/$PHP_LIBDIR, PANDA_SHARED_LIBADD)
      AC_DEFINE(HAVE_UUIDLIB, 1,[ ])
    ],[
      if test "$BUILD_OS_IS_DARWIN" != "no"; then  
        AC_MSG_ERROR([wrong uuid lib version or lib not found])
      fi
    ],[
      -L$PANDA_DIR/$PHP_LIBDIR -luuid
     ])
  fi
  
  PHP_ADD_INCLUDE($PANDA_DIR/include)
  PHP_SUBST(PANDA_SHARED_LIBADD)
  PHP_NEW_EXTENSION(panda, 
  panda.c panda_base.c panda_stack.c panda_error.c \
  panda_exception.c panda_request.c panda_response.c \
  panda_expend.c panda_compile.c panda_resource.c expends/mysql/mysql.c \
  expends/mysqli/mysqli.c expends/pdo/pdo.c expends/memcached/memcached.c \
  expends/memcache/memcache.c expends/redis/redis.c expends/curl/curl.c \
  expends/standard/standard.c common/socket.c, $ext_shared)
   
  PHP_ADD_BUILD_DIR([$ext_builddir/expends])
fi
