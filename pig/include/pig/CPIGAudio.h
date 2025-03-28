#ifndef _CPIGAUDIO_
#define _CPIGAUDIO_

#include <string>

using namespace std;

#include <SDL_mixer.h>

#include <pig/PIGTipos.h>

class CPIGAudio
{

private:

    Mix_Chunk *chunk{};
    int volume;
    int tempoExecucao;
    PIGStatusAudio status;
    int loops;
    string nomeArq;
    int canal;

public:

    CPIGAudio(const string &nomeArquivo, int nLoops, int tempoPlay = -1);
    ~CPIGAudio();
    Mix_Chunk *GetChunk();
    void SetVolume(int valor);
    [[nodiscard]] int GetCanal() const;
    [[nodiscard]] int GetVolume() const;
    [[nodiscard]] int GetTempoPlay() const;
    PIGStatusAudio GetStatus();
    [[nodiscard]] int GetLoops() const;
    int Play();
    void Pause();
    void Resume();
    void Stop();
};

typedef CPIGAudio *PIGAudio;
#endif // _CPIGAUDIO_
