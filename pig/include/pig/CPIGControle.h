#ifndef _CPIGCONTROLE_
#define _CPIGCONTROLE_

#include <string>

using namespace std;

#include <SDL.h>

class CPIGControle
{

private:

    int id;
    SDL_GameController *ctrl;
    SDL_Joystick *joy;
    int qtdEixos, qtdBotoes;
    string nome;

public:

    explicit CPIGControle(int idControle);
    ~CPIGControle();
    int BotaoPressionado(int botao);
    int EixoAcionado(int eixo);
    float EixoAcionadoPercentual(int eixo);
    [[nodiscard]] int GetQtdEixos() const;
    [[nodiscard]] int GetQtdBotoes() const;
    string GetNome();
};

typedef CPIGControle *PIGControle;
#endif // _CPIGCONTROLE_
