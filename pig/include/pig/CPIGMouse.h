#ifndef _CPIGMouse_
#define _CPIGMouse_

#include <string>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGSprite.h>

class CPIGMouse
{

private:

    static PIGSprite cursores;
    static SDL_Point pTela, pWorld;
    static Uint8 botoes[SDL_BUTTON_X2 + 1];
    static Uint8 botoes_anterior[SDL_BUTTON_X2 + 1];

public:

    static void Inicia(bool cursorCustomizado);
    static void Encerra();
    static bool GetBotaoPressionado(int botao);
    static bool GetBotaoLevantado(int botao);
    static bool GetBotaoBaixo(int botao);
    static bool GetBotaoAlto(int botao);
    static void AtualizaEstadoAnterior();
    static int GetEstadoBotaoDireito();
    static int GetEstadoBotaoCentral();
    static int GetEstadoBotaoEsquerdo();
    static void PegaXYTela(int &x, int &y);
    static SDL_Point PegaXYWorld();
    static SDL_Point PegaXYTela();
    static int ProcessaEvento(PIGEvento &evento);
    static int GetEstadoBotao(int botao);
    static int MudaCursor(int indice);
    static void Desenha(int idJanela = 0);
    static void Move(int x, int y);
    static void CarregaCursor(const string &nomeArquivo, int idJanela = 0);
    static void CarregaFramesPorColuna(int frameInicial, int qtdLinhas, int qtdColunas);
    static void CarregaFramesPorLinha(int frameInicial, int qtdLinhas, int qtdColunas);
    static void CriaFrameCursor(int idFrame, int x, int y, int alt, int larg);
};

#endif // _CPIGMouse_
