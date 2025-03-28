#ifndef _CPIGFILAPACOTES_
#define _CPIGFILAPACOTES_

#include <SDL_thread.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include <libavformat/avformat.h>

#ifdef __cplusplus
}
#endif

typedef struct ListAVPacket
{
    AVPacket pkt;
    struct ListAVPacket *next;
} ListAVPacket;
class CPIGFilaPacotes
{

private:

    ListAVPacket *first, *last;
    int nb_packets, size;

    AVPacket flushPkt{};
    SDL_mutex *cs;
    SDL_cond *cv;

public:

    [[nodiscard]] int GetQtdPacotes() const;
    [[nodiscard]] int GetSize() const;
    void SetQtdPacotes(int valor);
    void SetSize(int valor);
    int Put(const AVPacket *srcPkt);
    int Get(AVPacket *pkt, int block, const int &encerrar);
    int PutFlush();
    void Flush();
    CPIGFilaPacotes();
    ~CPIGFilaPacotes();
    bool IgualFlushData(const uint8_t *data) const;
    void LiberaBlock();
};

typedef CPIGFilaPacotes *PIGFilaPacotes;
#endif //_CPIGFILAPACOTES_
