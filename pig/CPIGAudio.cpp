#include <pig/CPIGAudio.h>
#include <pig/CPIGAssetLoader.h>
#include <pig/CPIGErros.h>

CPIGAudio::CPIGAudio(const string &nomeArquivo, const int nLoops, const int tempoPlay)
{
    nomeArq = nomeArquivo;
#ifdef PIG_SHARE_AUDIO
    chunk = CPIGAssetLoader::LoadAudio(nomeArq);
#else
    chunk = Mix_LoadWAV(nomeArq.c_str());
#endif

    if (!chunk)
    {
        throw CPIGErroArquivo(nomeArquivo);
    }

    volume = PIG_VOLUME_PADRAO;
    tempoExecucao = tempoPlay;
    status = PIG_AUDIO_PARADO;
    loops = nLoops;
    canal = -1;
}

CPIGAudio::~CPIGAudio()
{
#ifdef PIG_SHARE_AUDIO
    CPIGAssetLoader::FreeAudio(nomeArq);
#else
    Mix_FreeChunk(chunk);
#endif
}

Mix_Chunk *CPIGAudio::GetChunk()
{
    return chunk;
}

void CPIGAudio::SetVolume(const int valor)
{
    volume = valor;
    if (canal != -1)
    {
        Mix_Volume(canal, volume);
    }
}

[[nodiscard]] int CPIGAudio::GetCanal() const
{
    return canal;
}

[[nodiscard]] int CPIGAudio::GetVolume() const
{
    return volume;
}

[[nodiscard]] int CPIGAudio::GetTempoPlay() const
{
    return tempoExecucao;
}

PIGStatusAudio CPIGAudio::GetStatus()
{
    return status;
}

[[nodiscard]] int CPIGAudio::GetLoops() const
{
    return loops;
}

int CPIGAudio::Play()
{
    status = PIG_AUDIO_TOCANDO;
    canal = Mix_PlayChannelTimed(-1, chunk, loops, tempoExecucao);
    Mix_Volume(canal, volume);
    return canal;
}

void CPIGAudio::Pause()
{
    status = PIG_AUDIO_PAUSADO;
    if (canal != -1)
    {
        Mix_Pause(canal);
    }
}

void CPIGAudio::Resume()
{
    status = PIG_AUDIO_TOCANDO;
    if (canal != -1)
    {
        Mix_Resume(canal);
    }
}

void CPIGAudio::Stop()
{
    status = PIG_AUDIO_PARADO;
    if (canal != -1)
    {
        Mix_HaltChannel(canal);
        canal = -1;
    }
}
