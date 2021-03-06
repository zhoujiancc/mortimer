 /*
 * This library is licensed under 2 different licenses and you
 * can choose to use it under the terms of either one of them. The
 * two licenses are the MPL 1.1 and the LGPL.
 *
 * MPL:
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/.
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * LGPL:
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * The Original Code is Fluendo MPEG Demuxer plugin.
 *
 * The Initial Developer of the Original Code is Fluendo, S.L.
 * Portions created by Fluendo, S.L. are Copyright (C) 2005
 * Fluendo, S.L. All Rights Reserved.
 *
 * Contributor(s): Jan Schmidt <jan@fluendo.com>
 */

#ifndef __FLUTS_PMT_INFO_H__
#define __FLUTS_PMT_INFO_H__

#include <glib.h>
#include "wfdtspmtstreaminfo.h"

G_BEGIN_DECLS

typedef struct FluTsPmtInfoClass {
  GObjectClass parent_class;
} WFDTsPmtInfoClass;

typedef struct FluTsPmtInfo {
  GObject parent;

  guint16 program_no;
  guint16 pcr_pid;

  guint8 version_no;

  GValueArray *descriptors;
  GValueArray *streams;
} WFDTsPmtInfo;

WFDTsPmtInfo *mpegts_pmt_info_new (guint16 program_no, guint16 pcr_pid, guint8 version);
void mpegts_pmt_info_add_stream (WFDTsPmtInfo *pmt_info, WFDTsPmtStreamInfo *stream);
void mpegts_pmt_info_add_descriptor (WFDTsPmtInfo *pmt_info,	
  const gchar *descriptor, guint length);

GType wfd_ts_pmt_info_get_type (void);

#define WFD_TS_TYPE_PMT_INFO (wfd_ts_pmt_info_get_type ())
#define WFD_TS_IS_PMT_INFO(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), WFD_TS_TYPE_PMT_INFO))
#define WFD_TS_PMT_INFO(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),WFD_TS_TYPE_PMT_INFO, WFDTsPmtInfo))

G_END_DECLS

#endif
