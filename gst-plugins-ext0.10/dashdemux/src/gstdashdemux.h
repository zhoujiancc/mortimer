/*
 * DASH demux plugin for GStreamer
 *
 * gstdashdemux.h
 *
 * Copyright (C) 2012 Orange
 *
 * Authors:
 *   David Corvoysier <david.corvoysier@orange.com>
 *   Hamid Zakari <hamid.zakari@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library (COPYING); if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GST_DASH_DEMUX_H__
#define __GST_DASH_DEMUX_H__
#define DASHDEMUX_MODIFICATION
#include <gst/gst.h>
#include <gst/base/gstdataqueue.h>
#include "gstmpdparser.h"
#include "gstfragmented.h"
#include "gsturidownloader.h"
#include "gstdownloadrate.h"

G_BEGIN_DECLS
#define GST_TYPE_DASH_DEMUX \
        (gst_dash_demux_get_type())
#define GST_DASH_DEMUX(obj) \
        (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_DASH_DEMUX,GstDashDemux))
#define GST_DASH_DEMUX_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_DASH_DEMUX,GstDashDemuxClass))
#define GST_IS_DASH_DEMUX(obj) \
        (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_DASH_DEMUX))
#define GST_IS_DASH_DEMUX_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_DASH_DEMUX))
//
typedef struct _GstDashDemux GstDashDemux;
typedef struct _GstDashDemuxClass GstDashDemuxClass;
typedef struct _GstDashDemuxStream GstDashDemuxStream;

struct _GstDashDemuxStream {
  guint idx;
  GstPad *srcpad;
  GstCaps *output_caps;
  GstCaps *input_caps;
  GstDataQueue *queue;
  GstClockTime start_time;
  gboolean download_end_of_period;
  gboolean stream_end_of_period;
  gboolean stream_eos;
  gboolean need_header;
  gboolean need_segment;
  GstDownloadRate dnl_rate;
};

#define MAX_LANGUAGES 20
/**
 * GstDashDemux:
 *
 * Opaque #GstDashDemux data structure.
 */
struct _GstDashDemux
{
  GstElement parent;
  GstPad *sinkpad;
  GSList *streams;
  gint max_video_width;
  gint max_video_height;

  GstBuffer *manifest;
  GstUriDownloader *downloader;
  GstMpdClient *client;         /* MPD client */
  gboolean end_of_period;
  gboolean end_of_manifest;

  /* Properties */
  GstClockTime max_buffering_time;      /* Maximum buffering time accumulated during playback */
  gfloat bandwidth_usage;       /* Percentage of the available bandwidth to use       */
  guint64 max_bitrate;          /* max of bitrate supported by target decoder         */

  /* Streaming task */
  GstTask *stream_task;
  GStaticRecMutex stream_lock;
  GMutex *stream_timed_lock;

  /* Download task */
  GstTask *download_task;
  GStaticRecMutex download_lock;
  volatile gboolean cancelled;
  GMutex download_mutex;
  GCond download_cond;

  /* Manifest update */
  GstClockTime last_manifest_update;
};

struct _GstDashDemuxClass
{
  GstElementClass parent_class;
};

GType gst_dash_demux_get_type (void);

G_END_DECLS
#endif /* __GST_DASH_DEMUX_H__ */
