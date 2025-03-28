#include <pig/CPIGFilaPacotes.h>

[[nodiscard]] int CPIGFilaPacotes::GetQtdPacotes() const
{
    return nb_packets;
}

[[nodiscard]] int CPIGFilaPacotes::GetSize() const
{
    return size;
}

void CPIGFilaPacotes::SetQtdPacotes(int valor)
{
    nb_packets = valor;
}

void CPIGFilaPacotes::SetSize(int valor)
{
    size = valor;
}

int CPIGFilaPacotes::Put(const AVPacket *srcPkt)
{
    AVPacket pkt = {};

    if (srcPkt != &flushPkt && av_packet_ref(&pkt, srcPkt) < 0)
    {
        return -1;
    }

    ListAVPacket *elt = new ListAVPacket;
    elt->pkt = pkt;
    elt->next = NULL;

    SDL_LockMutex(cs);

    if (!last)
    {
        first = elt;
    }
    else
    {
        last->next = elt;
    }
    last = elt;
    nb_packets++;
    size += elt->pkt.size;
    SDL_CondSignal(cv);

    SDL_UnlockMutex(cs);
    return 0;
}

int CPIGFilaPacotes::Get(AVPacket *pkt, int block, const int &encerrar)
{
    int rv{};

    if (!pkt)
    { // NOLINT(*-implicit-bool-conversion)
        return -1;
    }

    SDL_LockMutex(cs);
    while (!encerrar)
    {

        ListAVPacket *elt = first;
        if (elt)
        {
            first = elt->next;
            if (!first)
            {
                last = NULL;
            }
            nb_packets--;
            size -= elt->pkt.size;
            *pkt = elt->pkt;
            av_free(elt);
            rv = 1;
            break;
        }
        if (!block)
        {
            rv = 0;
            break;
        }
        SDL_CondWait(cv, cs);
    }
    SDL_UnlockMutex(cs);
    return rv;
}

int CPIGFilaPacotes::PutFlush()
{
    return Put(&flushPkt);
}

void CPIGFilaPacotes::Flush()
{
    ListAVPacket *pkt, *pkt1;
    SDL_LockMutex(cs);
    for (pkt = first; pkt != NULL; pkt = pkt1)
    {
        pkt1 = pkt->next;
        av_packet_unref(&pkt->pkt);
        av_freep(&pkt);
    }
    last = NULL;
    first = NULL;
    nb_packets = 0;
    size = 0;
    SDL_UnlockMutex(cs);
}

CPIGFilaPacotes::CPIGFilaPacotes()
{
    cs = SDL_CreateMutex();
    cv = SDL_CreateCond();
    size = 0;
    nb_packets = 0;
    first = last = NULL;
    flushPkt = {};
    flushPkt.data = (uint8_t *) "FLUSH";
}

CPIGFilaPacotes::~CPIGFilaPacotes()
{
    Flush();
    SDL_DestroyMutex(cs);
    SDL_DestroyCond(cv);
}

bool CPIGFilaPacotes::IgualFlushData(const uint8_t *data) const
{
    return flushPkt.data == data;
}

void CPIGFilaPacotes::LiberaBlock()
{
    SDL_UnlockMutex(cs);
    SDL_CondSignal(cv);
}
