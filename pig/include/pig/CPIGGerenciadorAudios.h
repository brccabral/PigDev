#ifndef _CPIGGERENCIADORAUDIOS_
#define _CPIGGERENCIADORAUDIOS_

#include <string>

using namespace std;

#include <SDL.h>
#include <SDL_mixer.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGAudio.h>
#include <pig/CPIGRepositorio.h>

class CPIGGerenciadorAudios
{

private:

    static CPIGRepositorio<PIGAudio> *audios;
    static int audioIds[PIG_QTD_CANAIS_PADRAO];
    static Mix_Music *background;
    static int volumeBackground;
    static PIGStatusAudio statusBackground;

    static void TrataParadaAudio(int canal);
    static void TrataParadaBackground();

public:

    static void Inicia();
    static void Encerra();
    static PIGAudio GetAudio(int idAudio);
    static void CarregaBackground(const string &nomeArquivo);
    static void PlayBackground(int nVezes);
    static void StopBackground();
    static void PauseBackground();
    static void ResumeBackground();
    static PIGStatusAudio GetStatusBackground();
    static void SetVolumeBackground(int valor);
    static int GetVolumeBackground();
    static int CriaAudio(const string &nomeArquivo, int nLoops, int tempoExecucao = -1);
    static int InsereAudio(PIGAudio audio);
    static void DestroiAudio(int idAudio);
    static void SetVolumeTudo(int volume);
    static void Play(int idAudio);
    static void StopTudo();
    static void PauseTudo();
    static void ResumeTudo();
};

#endif // _CPIGGERENCIADORAUDIOS_
