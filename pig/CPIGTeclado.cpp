#include <cstddef>
#include <pig/CPIGTeclado.h>

const Uint8 *CPIGTeclado::estado = SDL_GetKeyboardState(NULL);
Uint8 CPIGTeclado::teclado[SDL_NUM_SCANCODES]{};
Uint8 CPIGTeclado::teclado_anterior[SDL_NUM_SCANCODES]{};

bool CPIGTeclado::TeclaPressionada(SDL_Scancode tecla)
{
    if (tecla >= SDL_NUM_SCANCODES)
    {
        return false;
    }
    return teclado[tecla] && teclado_anterior[tecla] != teclado[tecla];
}
bool CPIGTeclado::TeclaLevantada(SDL_Scancode tecla)
{
    if (tecla >= SDL_NUM_SCANCODES)
    {
        return false;
    }
    return !teclado[tecla] && teclado_anterior[tecla] != teclado[tecla];
}
bool CPIGTeclado::TeclaBaixa(SDL_Scancode tecla)
{
    if (tecla >= SDL_NUM_SCANCODES)
    {
        return false;
    }
    return teclado[tecla];
}
bool CPIGTeclado::TeclaAlta(SDL_Scancode tecla)
{
    if (tecla >= SDL_NUM_SCANCODES)
    {
        return false;
    }
    return !teclado[tecla];
}

int CPIGTeclado::ProcessaEvento(const PIGEvento &evento)
{
    if (evento.tipoEvento != PIG_EVENTO_TECLADO)
    {
        return 0;
    }
    if (evento.teclado.acao == PIG_TECLA_PRESSIONADA || evento.teclado.acao == PIG_TECLA_LIBERADA)
    {
        teclado_anterior[evento.teclado.tecla] = teclado[evento.teclado.tecla];
        teclado[evento.teclado.tecla] = estado[evento.teclado.tecla];
    }
    return 1;
}

void CPIGTeclado::AtualizaEstadoAnterior()
{
    memcpy(teclado_anterior, teclado, SDL_NUM_SCANCODES * sizeof(Uint8));
}
