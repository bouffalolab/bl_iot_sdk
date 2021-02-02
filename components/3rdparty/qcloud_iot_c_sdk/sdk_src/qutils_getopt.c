/*
 * Copyright (c) 2017-2019 Tencent Group. All rights reserved.
 * License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "qutils_getopt.h"

#include <stdio.h>
#include <string.h>

#include "qcloud_iot_import.h"

static int utils_opterr = 1;   /* if error message should be printed */
static int utils_optind = 1;   /* index into parent argv vector */
static int utils_optopt;       /* character checked for validity */
static int utils_optreset = 1; /* reset getopt */

char *utils_optarg; /* argument associated with option */

int qutils_getopt(int nargc, char *const *nargv, const char *options)
{
#define BADCH  (int)'?'
#define BADARG (int)':'
#define EMSG   ""

    static char *place = EMSG; /* option letter processing */
    const char * oli;          /* option letter list index */

    if (utils_optreset || !*place) { /* update scanning pointer */
        utils_optreset = 0;

        if (utils_optind >= nargc || *(place = nargv[utils_optind]) != '-') {
            utils_optind   = 1;
            utils_optreset = 1;
            place          = EMSG;
            return (-1);
        }

        place++;
    }

    /* option letter okay? */
    if ((utils_optopt = (int)*place++) == (int)':' || !(oli = strchr(options, utils_optopt))) {
        /*
         * if the user didn't specify '-' as an option,
         * assume it means -1.
         */
        if (utils_optopt == (int)'-')
            return (-1);

        if (!*place)
            ++utils_optind;

        if (utils_opterr && *options != ':')
            HAL_Printf("illegal option - %c\n", utils_optopt);

        return (BADCH);
    }

    if (*++oli != ':') { /* don't need argument */
        utils_optarg = NULL;
        if (!*place)
            ++utils_optind;
    } else {
        /* need an argument */
        if (*place) /* no white space */
            utils_optarg = place;
        else if (nargc <= ++utils_optind) { /* no arg */
            place = EMSG;
            if (*options == ':')
                return (BADARG);
            if (utils_opterr)
                HAL_Printf("option requires an argument - %c\n", utils_optopt);
            return (BADCH);
        } else /* white space */
            utils_optarg = nargv[utils_optind];

        place = EMSG;
        ++utils_optind;
    }

    /* dump back option letter */
    return (utils_optopt);
}
