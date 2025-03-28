#include <pig/CPIGControle.h>

CPIGControle::CPIGControle(int idControle)
{
    if (SDL_IsGameController(idControle))
    {
        printf("Controle da posicao \'%d\' compativel\n", idControle);
        ctrl = SDL_GameControllerOpen(idControle);
        joy = SDL_GameControllerGetJoystick(ctrl);
        id = idControle;
        qtdEixos = SDL_JoystickNumAxes(joy);
        qtdBotoes = SDL_JoystickNumButtons(joy);
        nome.assign(SDL_JoystickName(joy));
        printf("Eixos: %d\n", qtdEixos);
        printf("Botoes: %d\n", qtdBotoes);
        printf("Nome: %s\n", nome.c_str());
    }
    else
    {
        printf("Controle da posicao \'%d\' incompativel\n", idControle);
    }
}

CPIGControle::~CPIGControle()
{
    SDL_GameControllerClose(ctrl);
}

int CPIGControle::BotaoPressionado(int botao)
{
    return SDL_GameControllerGetButton(ctrl, (SDL_GameControllerButton) botao);
}

int CPIGControle::EixoAcionado(int eixo)
{
    return SDL_GameControllerGetAxis(ctrl, (SDL_GameControllerAxis) eixo);
}

float CPIGControle::EixoAcionadoPercentual(int eixo)
{
    return SDL_GameControllerGetAxis(ctrl, (SDL_GameControllerAxis) eixo) / 32768.0F;
}

[[nodiscard]] int CPIGControle::GetQtdEixos() const
{
    return qtdEixos;
}

[[nodiscard]] int CPIGControle::GetQtdBotoes() const
{
    return qtdBotoes;
}

string CPIGControle::GetNome()
{
    return nome;
}
