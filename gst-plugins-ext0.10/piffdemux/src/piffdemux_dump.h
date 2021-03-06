/* GStreamer
 * Copyright (C) <1999> Erik Walthinsen <omega@cse.ogi.edu>
 * Copyright (C) <2009> STEricsson <benjamin.gaignard@stericsson.com>
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
 */

#ifndef __GST_PIFFDEMUX_DUMP_H__
#define __GST_PIFFDEMUX_DUMP_H__

#include <gst/gst.h>
#include <piffdemux.h>

G_BEGIN_DECLS

gboolean piffdemux_dump_vmhd (GstPiffDemux * piffdemux, GstByteReader * data,
    int depth);
gboolean piffdemux_dump_mfro (GstPiffDemux * piffdemux, GstByteReader * data,
    int depth);
gboolean piffdemux_dump_tfra (GstPiffDemux * piffdemux, GstByteReader * data,
    int depth);
gboolean piffdemux_dump_tfhd (GstPiffDemux * piffdemux, GstByteReader * data,
    int depth);
gboolean piffdemux_dump_trun (GstPiffDemux * piffdemux, GstByteReader * data,
    int depth);
gboolean piffdemux_dump_trex (GstPiffDemux * piffdemux, GstByteReader * data,
    int depth);
gboolean piffdemux_dump_sdtp (GstPiffDemux * piffdemux, GstByteReader * data,
    int depth);
gboolean piffdemux_dump_unknown (GstPiffDemux * piffdemux, GstByteReader * data,
    int depth);

gboolean piffdemux_node_dump (GstPiffDemux * piffdemux, GNode * node);

G_END_DECLS
#endif /* __GST_PIFFDEMUX_DUMP_H__ */
