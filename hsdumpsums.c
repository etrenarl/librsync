/*				       	-*- c-file-style: "bsd" -*-
 * rproxy -- dynamic caching and delta update in HTTP
 * $Id$
 * 
 * Copyright (C) 2000 by Martin Pool <mbp@samba.org>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "includes.h"
#include "sum_p.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>


int
main(int argc, char **argv)
{
    int c;
    hs_filebuf_t       *sig_fb;
    hs_sumset_t        *sums;

    hs_trace_set_level(LOG_INFO);
    while ((c = getopt(argc, argv, "D")) != -1) {
        switch (c) {
        case '?':
        case ':':
            return 1;
        case 'D':
            hs_trace_set_level(LOG_DEBUG);
            break;
        }
    }

    sig_fb = hs_filebuf_from_fd(STDIN_FILENO);
    sums = hs_read_sumset(hs_filebuf_read, sig_fb);

    hs_sumset_dump(sums);

    hs_free_sumset(sums);

    return 0;
}