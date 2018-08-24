#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include "tool.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace std;
using namespace cv;

#ifdef __cplusplus
extern "C" {
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/frame.h>
#include <unistd.h>
#include <pthread.h>

#ifdef __cplusplus
}
#endif
#if 1

class PdVideoCapture{
public:
    PdVideoCapture(string url):url(url)
    {
        opened=false;
        width=0;
        height=0;
        if(!init_input()){
            prt(info,"@@@@@err");
            exit(0);
        }
        if(!init_decoder()){
            prt(info,"@@@@@err");
            exit(0);
        }
        opened=true;
        //  int t= cvNamedWindow("123");
    }
    ~PdVideoCapture()
    {

    }
    bool read(Mat &BGRImage)
    {
        // int t= cvNamedWindow("123");
        Mat YUVImage;
        int size;
        size=width*height;
        av_init_packet(&av_pkt);
        if ((av_read_frame(fmt, &av_pkt) < 0)) {
            prt(info,"read frm fail");
            return false;
        }
        //    fmt->iformat->read_header()
        //rtsp_read_header
        //  read_header()
        //    RTSPState *state = _formatCtx->priv_data;
        //        RTSPStream *stream = state->rtsp_streams[0];
        //        RTPDemuxContext *demux = stream->transport_priv;
        //        demux->timestamp


       //RTSPState *state=(RTSPState) fmt->priv_data;




        int64_t dt,wt;
        av_get_output_timestamp(fmt,0,&dt,&wt);
        prt(info,"read frm stamp %d ",fmt->start_time_realtime);
        prt(info,"read frm stamp1 %d ",fmt->start_time);
        prt(info,"read frm stamp2 %d ",av_pkt.pts);
        prt(info,"read frm stamp3 %d ",av_pkt.dts);
        prt(info,"read frm stamp4 %d ",av_pkt.pos);
        if(decode()){
            // prt(info,"decode a frame");
            YUVImage.create(width*3/2, height, CV_8UC1);
            memcpy(YUVImage.data, buf_y, size);
            memcpy(YUVImage.data + size, buf_u, size /4);
            memcpy(YUVImage.data + size + size /4, buf_v, size / 4);
            cvtColor(YUVImage, BGRImage, CV_YUV2BGR_I420);
           // imshow("123",BGRImage);

         //   waitKey(10);
            return true;
        }else{
            prt(info,"decode a fail");
            return false;
        }
    }
    bool isOpened()
    {
        return opened;
    }
    void release()
    {
        release_input();
        release_decoder();
        opened=false;
    }
    int get(int cmd)
    {
        int ret;
        switch(cmd){
        case CV_CAP_PROP_FRAME_WIDTH:ret=width;break;
        case CV_CAP_PROP_FRAME_HEIGHT:ret=height;break;
        default:break;

        }
        return ret;
    }
private:
    bool init_input()
    {
        bool ret=true;
        av_register_all();
        avformat_network_init();
        fmt = avformat_alloc_context();
        if(avformat_open_input(&fmt, url.data(), NULL, 0) != 0) {
            ret=false;
        } else if (avformat_find_stream_info(fmt, NULL) < 0) {
            ret=false;
        }
        return ret;
    }
    bool init_decoder()
    {
        bool ret=false;
        codec = avcodec_find_decoder(CODEC_ID_H264);
        codec_ctx = avcodec_alloc_context3(codec);
        if (avcodec_open2(codec_ctx, codec, NULL) >= 0){
            avframe=NULL;
            avframe= avcodec_alloc_frame();
            if(avframe)
                ret=true;
        }
        else {
            prt(info,"fail to open decoder");
        }
        return ret;
    }
    void release_decoder()
    {
        av_free(avframe);
        avcodec_close(codec_ctx);
    }
    void release_input()
    {
        avformat_close_input(&fmt);
    }

    bool decode()
    {
        int got_picture = 0;
        int len = 0;

        while (av_pkt.size > 0) {
           // prt(info,"decoing size: %d",av_pkt.size);
            len = avcodec_decode_video2(codec_ctx, avframe, &got_picture, &av_pkt);
            if (len < 0) {
                return false;
            }
            if (got_picture)
            {
                buf_y = (unsigned char *) avframe->data[0];
                buf_u = (unsigned char *) avframe->data[1];
                buf_v = (unsigned char *) avframe->data[2];
         //      prt(info,"decode size %d  (%d  %d)",av_pkt.size,avframe->width,avframe->height);
                //                prt(info,"%d",av_pkt.pts);
                width=avframe->height;
                height=avframe->width;


                return true;

            }
            av_pkt.size -= len;
            av_pkt.data += len;
        }
        return false;
    }


public:
    AVCodec *codec;
    AVCodecContext *codec_ctx;
    AVFrame *avframe;
    AVFormatContext *fmt;
    AVPacket av_pkt;
    bool opened;
    string url;
    unsigned char *buf_y;
    unsigned char *buf_u;
    unsigned char *buf_v;
    int width;
    int height;
};
#define USE_CVCAP 1

class VideoSource
{
public:

    VideoSource(string path);
    ~VideoSource();
    inline string get_url()
    {
        return url;
    }
    bool get_size(int &w,int &h)
    {
        bool ret=false;
        if(vcap.isOpened()){
            ret=true;
            w=vcap.get(CV_CAP_PROP_FRAME_WIDTH);
            h=vcap.get(CV_CAP_PROP_FRAME_HEIGHT);
        }
        return ret;
    }
    bool get_frame(Mat &frame)
    {
        int ret=false;
        lock.lock();
        if(frame_list.size()>0){
            frame_list.front().copyTo(frame);
            frame_list.pop_front();
            ret=true;
        }else{
            ret=false;
        }
        lock.unlock();
        return ret;
    }
private:
    void run();
    void check_point()
    {
        if(vcap.isOpened()){
            double w= vcap.get(CV_CAP_PROP_POS_FRAMES);
        }
    }
private:
#ifdef USE_CVCAP
    VideoCapture  vcap;
#else
    PdVideoCapture vcap;
#endif
    //  PdVideoCapture vcap;
    //  VideoCapture vcap;
    list <Mat> frame_list;
    int frame_wait_time;
    mutex lock;
    int frame_rate;
    string url;
    volatile bool quit_flg;
    Timer1 t1;

    thread *src_trd;
};
#endif
#endif // VIDEOSOURCE_H