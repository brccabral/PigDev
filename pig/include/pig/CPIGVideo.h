#ifndef _CPIGVIDEO_
#define _CPIGVIDEO_

#define __STDC_CONSTANT_MACROS

#ifdef _MSC_VER
#define ALIGN_16(T, F) __declspec(align(16)) T F;
#else
#define ALIGN_16(T, F) T F __attribute__((aligned(16)));
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avstring.h>
#include <libavutil/frame.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>

#define SDL_MAIN_HANDLED

#ifdef __cplusplus
}
#endif

#include <string>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGJanela.h>
#include <pig/CPIGSprite.h>
#include <pig/CPIGTimer.h>
#include <pig/CPIGFilaPacotes.h>

#define MAX_QUEUE_SIZE (15 * 1024 * 1024)

#define VIDEO_PICTURE_QUEUE_SIZE (1)

#define SDL_AUDIO_BUFFER_SIZE 1024

#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000

#define AV_SYNC_THRESHOLD 0.01

#define AV_NOSYNC_THRESHOLD 10.0

typedef struct _VideoPicture
{
    SDL_Texture *texture;
    int width, height;
    int allocated;
    double pts;
} VideoPicture;

typedef struct _VideoState
{
    ALIGN_16(uint8_t, audioBuf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2])
    ALIGN_16(uint8_t, audioConvertedData[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2])
    ALIGN_16(AVPacket, audioPkt)
    ALIGN_16(AVPacket, videoPkt)
    AVFormatContext *pFormatCtx;
    AVCodecContext *audioCtx;
    AVCodecContext *videoCtx;
    struct SwrContext *pSwrCtx;
    struct SwsContext *pSwsCtx;
    int videoStream, audioStream;
    AVStream *audioSt;

    unsigned int audioBufSize, audioBufIndex;
    int hasAudioFrames;
    AVFrame *pAudioFrame;
    AVFrame *pFrameRGB;
    uint8_t *pFrameBuffer;

    int seek_req;
    int seek_flags;
    int64_t seek_pos;

    AVStream *videoSt;

    VideoPicture pictq[VIDEO_PICTURE_QUEUE_SIZE];
    int pictqSize, pictqRindex, pictqWindex;
    SDL_mutex *pictqCs;
    SDL_cond *pictqCv;

    double video_current_pts;
    int64_t video_current_pts_time;

    double videoClock, audioClock, lastFramePts, lastFrameDelay, frameTimer;
} VideoState;

class CPIGVideo : public CPIGSprite
{

    int audioDeviceId;
    double volume;
    VideoState *is;
    SDL_Thread *hParseThread{};
    SDL_Thread *hVideoThread{};
    int quit;
    bool janelaToda;
    PIGStatusVideo estado;
    int64_t pausa{};
    bool decodeEncerrado;
    double tempoFrame;
    PIGJanela janelaAtual;
    PIGTimer timerProx;
    PIGFilaPacotes filaAudio, filaVideo;
    SDL_mutex *mutexBuffer;
    int altPixels, largPixels, pitch{};
    bool mudouFrameVideo;
    void *bufferVideo;


    double get_video_clock();
    static int DecodeThread(void *pUserData);
    double GetAudioClock();
    int QueuePicture(const AVFrame *frame, double pts);
    double SyncVideo(const AVFrame *frame, double pts);
    static int VideoThread(void *pUserData);
    void VideoRefreshTimer();
    void AjustaAspecto2();
    void AllocPicture();
    int DecodeAudioFrame(double *ptsPtr);
    static void AudioCallback(void *userdata, uint8_t *stream, int len);
    static int DecodeInterruptCallback(void *userData);
    int StreamVideoComponentOpen();
    int StreamAudioComponentOpen();
    int CriaVideoState();
    static void DestroiStream(AVStream *stream);
    void DestroiVideoState();

public:

    explicit CPIGVideo(const string &nomeArq, int idJanela = 0);
    ~CPIGVideo() override;
    void SetSeek(double incremento);
    void Play();
    void Stop();
    void Pause();
    void Resume();
    int Desenha() override;
    void SetVolume(double valor);
    double GetVolume() const;
    double GetTempoAtual();
    string GetTempoAtualString();
    double GetTempoTotal();
    string GetTempoTotalString();
    double GetTempoFrame() const;
    double GetFPS() const;
    void OcupaJanelaInteira();
    void UsaResolucaoOriginal();
    void GetResolucao(int &altura, int &largura) const;
};

typedef CPIGVideo *PIGVideo;
#endif // _CPIGVIDEO_
