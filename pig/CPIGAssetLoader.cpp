#include <SDL_image.h>
#include <ranges>
#include <pig/CPIGAssetLoader.h>

int CPIGAssetLoader::totalBitmaps{};
unordered_map<string, PIGHashNodeImagem> CPIGAssetLoader::mapImagens{};

#ifdef PIGCOMAUDIO
int CPIGAssetLoader::totalAudios{};
unordered_map<string, PIGHashNodeAudio> CPIGAssetLoader::mapAudios{};
#endif

CPIGHashNodeImagem::CPIGHashNodeImagem(const string &nomeArq)
{
    cont = 1;
    SDL_Surface *aux = IMG_Load(nomeArq.c_str());
    imagem = SDL_ConvertSurfaceFormat(aux, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(aux);
}

CPIGHashNodeImagem::~CPIGHashNodeImagem()
{
    SDL_FreeSurface(imagem);
}

#ifdef PIGCOMAUDIO

CPIGHashNodeAudio::CPIGHashNodeAudio(const string &nomeArq)
{
    cont = 1;
    chunk = Mix_LoadWAV(nomeArq.c_str());
}

CPIGHashNodeAudio::~CPIGHashNodeAudio()
{
    Mix_FreeChunk(chunk);
}

#endif

void CPIGAssetLoader::Inicia()
{
    totalBitmaps = 0;
#ifdef PIGCOMAUDIO
    totalAudios = 0;
#endif
}

void CPIGAssetLoader::Encerra()
{
    for (auto &value: views::values(mapImagens))
    {
        delete value;
    }
#ifdef PIGCOMAUDIO
    for (auto &value: views::values(mapAudios))
    {
        delete value;
    }
#endif
}

SDL_Surface *CPIGAssetLoader::LoadImage(const string &nomeArq)
{
    unordered_map<string, PIGHashNodeImagem>::iterator it = mapImagens.find(nomeArq);
    if (it == mapImagens.end())
    { // não achou
        PIGHashNodeImagem imagem = new CPIGHashNodeImagem(nomeArq);
        mapImagens[nomeArq] = imagem;
        totalBitmaps++;
        return imagem->imagem;
    }

    it->second->cont++;
    return it->second->imagem;
}

void CPIGAssetLoader::FreeImage(const string &nomeArq)
{
    unordered_map<string, PIGHashNodeImagem>::iterator it = mapImagens.find(nomeArq);
    if (it == mapImagens.end())
    { // não achou
        printf("Nao existe asset carregado: %s\n", nomeArq.c_str());
    }
    else
    {
        it->second->cont--;
        if (it->second->cont == 0)
        {
            delete it->second;
            mapImagens.erase(it);
        }
    }
}

#ifdef PIGCOMAUDIO

Mix_Chunk *CPIGAssetLoader::LoadAudio(const string &nomeArq)
{
    unordered_map<string, PIGHashNodeAudio>::iterator it = mapAudios.find(nomeArq);
    if (it == mapAudios.end())
    { // não achou
        PIGHashNodeAudio audio = new CPIGHashNodeAudio(nomeArq);
        mapAudios[nomeArq] = audio;
        totalAudios++;
        return audio->chunk;
    }

    it->second->cont++;
    return it->second->chunk;
}

void CPIGAssetLoader::FreeAudio(const string &nomeArq)
{
    unordered_map<string, PIGHashNodeAudio>::iterator it = mapAudios.find(nomeArq);
    if (it == mapAudios.end())
    { // não achou
        printf("Nao existe asset carregado: %s\n", nomeArq.c_str());
    }
    else
    {
        it->second->cont--;
        if (it->second->cont == 0)
        {
            delete it->second;
            mapAudios.erase(it);
        }
    }
}

#endif // PIGCOMAUDIO
