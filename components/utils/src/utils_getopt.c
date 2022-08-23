#include <stdio.h>
#include <utils_getopt.h>

/*
 * This file is derived from musl v1.2.0.
 * Modifications are applied.
 * Copyright (C) Bouffalo Lab 2016-2020
 */

/*
 * Copyright © 2005-2020 Rich Felker, et al.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

int utils_getopt_init(getopt_env_t *env, int opterr)
{
    if (!env) {
        return -1;
    }
    env->optarg = NULL;
    env->optind = 1;
    env->opterr = opterr;
    env->optopt = 0;
    env->__optpos = 0;
    return 0;
}

#define NEWLINE "\r\n"

int utils_getopt(getopt_env_t *env, int argc, char * const argv[], const char *optstring)
{
    int i;
    char c, d;
    char *optchar;

    if (!env) {
        return -1;
    }

    if (env->optind >= argc || !argv[env->optind])
        return -1;

    if (argv[env->optind][0] != '-') {
        if (optstring[0] == '-') {
            env->optarg = argv[env->optind++];
            return 1;
        }
        return -1;
    }

    if (!argv[env->optind][1])
        return -1;

    if (argv[env->optind][1] == '-' && !argv[env->optind][2])
        return env->optind++, -1;

    if (!env->__optpos) env->__optpos++;
    c = argv[env->optind][env->__optpos];
    optchar = argv[env->optind] + env->__optpos;
    env->__optpos += !!c;

    if (!argv[env->optind][env->__optpos]) {
        env->optind++;
        env->__optpos = 0;
    }

    if (optstring[0] == '-' || optstring[0] == '+')
        optstring++;

    i = 0;
    do d = optstring[i++]; while (d && d != c);

    if (d != c || c == ':') {
        env->optopt = c;
        if (optstring[0] != ':' && env->opterr)
            printf("%s: unrecognized option: %c"NEWLINE, argv[0], *optchar);
        return '?';
    }
    if (optstring[i] == ':') {
        env->optarg = 0;
        if (optstring[i+1] != ':' || env->__optpos) {
            env->optarg = argv[env->optind++] + env->__optpos;
            env->__optpos = 0;
        }
        if (env->optind > argc) {
            env->optopt = c;
            if (optstring[0] == ':') return ':';
            if (env->opterr) {
                printf("%s: option requires an argument: %c"NEWLINE, argv[0], *optchar);
            }
            return '?';
        }
    }
    return c;
}
