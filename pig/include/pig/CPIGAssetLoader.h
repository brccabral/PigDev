#ifndef _CPIGASSETLOADER_
#define _CPIGASSETLOADER_

#include <string>
#include <unordered_map>

using namespace std;

#include <SDL.h>
#include <SDL_mixer.h>

class CPIGHashNodeImagem
{

public:

    int cont;
    SDL_Surface *imagem{};

    explicit CPIGHashNodeImagem(const string &nomeArq);
    ~CPIGHashNodeImagem();
};
typedef CPIGHashNodeImagem *PIGHashNodeImagem;

#ifdef PIGCOMAUDIO

class CPIGHashNodeAudio
{

public:

    int cont;
    Mix_Chunk *chunk;

    explicit CPIGHashNodeAudio(const string &nomeArq);
    ~CPIGHashNodeAudio();
};
typedef CPIGHashNodeAudio *PIGHashNodeAudio;

#endif

class CPIGAssetLoader
{

private:

    static int totalBitmaps;
    static unordered_map<string, PIGHashNodeImagem> mapImagens;

#ifdef PIGCOMAUDIO
    static int totalAudios;
    static unordered_map<string, PIGHashNodeAudio> mapAudios;
#endif

public:

    static void Inicia();
    static void Encerra();
    static SDL_Surface *LoadImage(const string &nomeArq);
    static void FreeImage(const string &nomeArq);
#ifdef PIGCOMAUDIO
    static Mix_Chunk *LoadAudio(const string &nomeArq);
    static void FreeAudio(const string &nomeArq);
#endif // PIGCOMAUDIO
};

#endif // _CPIGASSETLOADER_
