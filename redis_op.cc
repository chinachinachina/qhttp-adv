#include <stdlib.h>
#include <string.h>
#include "redis_op.h"

/* 建立Redis连接 */
bool Database::redis_conn(redisContext *&rc)
{
    /* 建立连接 */
    rc = redisConnect("127.0.0.1", 6379);
    /* 连接出错 */
    if (rc == NULL || rc->err)
    {
        if (rc)
        {
            printf("[ERROR] %s \n", rc->errstr);
        }
        else
        {
            printf("[ERROR] Can't cllocate redis context \n");
        }

        return false;
    }
    return true;
}

/* 从Redis读取键值对 */
char *Database::redis_get(redisContext *rc, const char *command)
{
    redisReply *rr = (redisReply *)redisCommand(rc, command);
    /* 未查询到结果或查询出错 */
    if (rr == NULL || rr->type != REDIS_REPLY_STRING)
    {
        printf("[INFO] Fail to execute command [%s] \n", command);
        /* 释放redisReply的内存 */
        freeReplyObject(rr);
        return NULL;
    }
    /* 为结果分配内存 */
    char *res = (char *)malloc(2048);
    strcpy(res, rr->str);
    /* 释放redisReply的内存 */
    freeReplyObject(rr);
    return res;
}

/* 向Redis写入键值对 */
bool Database::redis_set(redisContext *rc, const char *command)
{
    redisReply *rr = (redisReply *)redisCommand(rc, command);
    /* 未查询到结果或查询出错 */
    if (rr == NULL || rr->type != REDIS_REPLY_STATUS || strcasecmp(rr->str, "OK") != 0)
    {
        printf("[INFO] Fail to execute command [%s] \n", command);
        /* 释放redisReply的内存 */
        freeReplyObject(rr);
        return false;
    }
    /* 释放redisReply的内存 */
    freeReplyObject(rr);
    return true;
}