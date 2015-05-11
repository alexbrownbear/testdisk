/*

    File: file_mxf.c

    Copyright (C) 2009 Christophe GRENIER <grenier@cgsecurity.org>
  
    This software is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
  
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
  
    You should have received a copy of the GNU General Public License along
    with this program; if not, write the Free Software Foundation, Inc., 51
    Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#include <stdio.h>
#include "types.h"
#include "filegen.h"

static void register_header_check_mxf(file_stat_t *file_stat);

const file_hint_t file_hint_mxf= {
  .extension="mxf",
  .description="Material Exchange Format",
  .min_header_distance=0,
  .max_filesize=PHOTOREC_MAX_FILE_SIZE,
  .recover=1,
  .enable_by_default=1,
  .register_header_check=&register_header_check_mxf
};

/* http://tools.ietf.org/html/rfc4539
 * Media Type Registration for the
 * Society of Motion Picture and Television Engineers (SMPTE)
 * Material Exchange Format (MXF)
 * */

static int header_check_mxf(const unsigned char *buffer, const unsigned int buffer_size, const unsigned int safe_header_only, const file_recovery_t *file_recovery, file_recovery_t *file_recovery_new)
{
  reset_file_recovery(file_recovery_new);
  file_recovery_new->extension=file_hint_mxf.extension;
  return 1;
}

static void register_header_check_mxf(file_stat_t *file_stat)
{
  static const unsigned char mxf_header[11]= {
    0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01, 0x01,
    0x0d, 0x01, 0x02
  };
  register_header_check(0, mxf_header,sizeof(mxf_header), &header_check_mxf, file_stat);
}
