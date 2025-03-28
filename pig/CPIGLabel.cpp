#include <thread>

using namespace std;

#include <pig/PIGFuncoesBasicas.h>
#include <pig/CPIGLabel.h>
#include <pig/CPIGGerenciadorFontes.h>

void CPIGLabel::AtualizaTextura()
{
    PIGFonte fonte = CPIGGerenciadorFontes::GetFonte(idFonte);
    larg = fonte->GetLarguraPixelsString(frase);
    alt = fonte->GetFonteAscent() + fonte->GetFonteDescent() + 5;

    if (this_thread::get_id() != PIG_MAIN_THREAD_ID)
    {
        // printf("atualizando textura <%s> com thread %d
        // (%d)\n",frase.c_str(),this_thread::get_id(),PIG_MAIN_THREAD_ID);
        return;
    }

    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
    texture = SDL_CreateTexture(
            renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, larg, alt);

    if (SDL_SetRenderTarget(renderer, texture) == 0)
    { // mudou o target sem erro (==0)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, NULL);
    }
    else
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }

    if (texture)
    {
        fonte->Escreve(frase, texture, corFonte);
        precisaAtualizar = false;
    }

    SetDimensoes(alt, larg);
    DefineFrame(0, {0, 0, larg, alt});
    MudaFrameAtual(0);
}

CPIGLabel::CPIGLabel(const string &texto, PIGCor cor, int numFonte, int idJanela)
    : CPIGSprite(idJanela)
{
    idFonte = numFonte;
    texture = NULL;
    corFonte = cor;
    frase = texto;
    precisaAtualizar = true;
    CPIGLabel::AtualizaTextura();
}

void CPIGLabel::SetTexto(const string &texto)
{
    frase = texto;
    AtualizaTextura();
}

void CPIGLabel::SetFonte(int numFonte)
{
    idFonte = numFonte;
    AtualizaTextura();
}

void CPIGLabel::SetCorFonte(PIGCor novaCor)
{
    corFonte = novaCor;
    AtualizaTextura();
}

int CPIGLabel::GetAltura()
{
    return alt;
}

int CPIGLabel::GetLargura()
{
    return larg;
}

string CPIGLabel::GetTexto()
{
    return frase;
}

int CPIGLabel::GetFonte() const
{
    return idFonte;
}

PIGCor CPIGLabel::GetCorFonte()
{
    return corFonte;
}
