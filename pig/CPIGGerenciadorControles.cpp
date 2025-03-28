#include <pig/CPIGGerenciadorControles.h>

int CPIGGerenciadorControles::qtdControles{};
PIGControle CPIGGerenciadorControles::controles[PIG_MAX_CONTROLES]{};

void CPIGGerenciadorControles::Inicia()
{
    // Initialize the joystick subsystem
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);

    qtdControles = SDL_NumJoysticks();
    for (int i = 0; i < qtdControles; ++i)
    {
        controles[i] = new CPIGControle(i);
    }
}

void CPIGGerenciadorControles::Encerra()
{
    for (int i = 0; i < qtdControles; ++i)
    {
        delete controles[i];
    }
}

PIGControle CPIGGerenciadorControles::GetControle(int idControle)
{
    return controles[idControle];
}
