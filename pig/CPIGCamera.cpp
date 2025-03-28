#include <pig/CPIGCamera.h>
#include <pig/PIGTipos.h>
#include <pig/PIGFuncoesBasicas.h>

CPIGCamera::CPIGCamera(const int alturaTela, const int larguraTela)
{
    altTela = altAtual = alturaTela;
    largTela = largAtual = larguraTela;
    pos = {.x = 0, .y = 0};
    pan = 1.0;
    minPan = PIG_AFASTAMENTO_MINIMO;
    maxPan = PIG_AFASTAMENTO_MAXIMO;
}

SDL_Point CPIGCamera::GetXY()
{
    return pos;
}

// não utilizada
void CPIGCamera::AjustaTela(const int novaAltura, const int novaLargura)
{
    altTela = novaAltura;
    largTela = novaLargura;
    DefineAfastamento(pan);
}

void CPIGCamera::Move(const SDL_Point nova)
{
    pos = nova;
}

void CPIGCamera::Desloca(const int dx, const int dy)
{
    pos.x += dx;
    pos.y += dy;
}

double CPIGCamera::DefineAfastamento(const double valor)
{
    pan = PIGLimitaValor(valor, minPan, maxPan);
    largAtual = pan * largTela;
    altAtual = pan * altTela;
    return pan;
}

double CPIGCamera::GetAfastamento() const
{
    return pan;
}

void CPIGCamera::ConverteCoordenadaWorldScreen(
        const int xObj, const int yObj, int &cx, int &cy) const
{
    cx = xObj - pos.x + (largAtual - largTela) / 2;
    cy = yObj + pos.y + (altAtual - altTela) / 2;
}

void CPIGCamera::ConverteCoordenadaScreenWorld(
        const int xTela, const int yTela, int &cx, int &cy) const
{
    double propX = (xTela - largTela / 2.0) / largTela;
    double propY = (yTela - altTela / 2.0) / altTela;
    cx = xTela + pos.x + propX * (largAtual - largTela);
    cy = yTela + pos.y + propY * (altAtual - altTela);
}
