/*
 * =====================================================================================
 *
 *       Filename:  demo.cpp
 *
 *    Description:  一致性哈希的示例
 *
 *        Version:  1.0
 *        Created:  01/12/2016 10:42:23 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  seth.hg@gmail.com
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <assert.h>
#include "consistent_hash.h"

#include <openssl/md5.h>
uint32_t hash2(const std::string& key)
{
    MD5_CTX ctx;
    unsigned char digest[16] = {0};

    MD5_Init(&ctx);
    MD5_Update(&ctx, key.c_str(), key.length());
    MD5_Final(digest, &ctx);

    uint32_t *ret = (uint32_t *)digest;
    return *ret;
}

static char *random_key()
{
    static char buf[11];
    const char *random_str = "adf9pr134;fjasd f0pr1223rfa;dvasdhrf9erfhpaudsfja;er19043rfnqef;jqef014qpeqp3380p,4tnm;132rj138jfpa98dfn1;43yt9p4rfhl;adfy91n4p1k3j4tr";
    int len = strlen(random_str);
    int pos = random() % (len - 11) + 1;
    assert(pos > 0);
    assert(pos < len - 10);
    int random_len = (random() % 10) + 1;
    assert(random_len > 0);
    assert(random_len < 11);
    strncpy(buf, random_str + pos, random_len);
    buf[random_len] = '\0';
    return buf;
}

int main()
{
    ConsistentHashRouter router;
    std::vector<uint32_t> nodes;
    nodes.push_back(1);
    nodes.push_back(2);
    nodes.push_back(3);
    nodes.push_back(4);
    nodes.push_back(5);
    nodes.push_back(6);
    nodes.push_back(7);
    nodes.push_back(8);
    nodes.push_back(9);
    nodes.push_back(10);
    nodes.push_back(11);
    nodes.push_back(12);
    nodes.push_back(13);
    nodes.push_back(14);
    nodes.push_back(15);
    nodes.push_back(16);
    router.Init(nodes, hash2, 100);

    srandom(time(NULL));
    int ret;
    uint32_t n;
    for (int i = 0; i < 50; i++)
    {
        char *key = random_key();
        ret = router.Route(key, n);
        assert(ret == 0);
        printf("key = %-10s, node = %u\n", key, n);
    }

    return 0;
}
