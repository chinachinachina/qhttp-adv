/***********************************************************************************
 * File name: redis_op.h
 * Description: A head file containing operations related to redis
 * Author: Zeyuan Qiu
 * Version: 3.0
 * Date: 2020/06/09
***********************************************************************************/

#ifndef REDIS_OP_H
#define REDIS_OP_H

#include <hiredis/hiredis.h>

class Database
{
public:
    /* Redis连接对象 */
    static redisContext *rc;

    /* 建立Redis连接 */
    static bool redis_conn(redisContext *&rc);
    /* 从Redis读取键值对 */
    static char *redis_get(redisContext *rc, const char *format);
    /* 向Redis写入键值对 */
    static bool redis_set(redisContext *rc, const char *format);
};

#endif