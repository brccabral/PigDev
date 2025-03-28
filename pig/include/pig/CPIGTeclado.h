#ifndef _CPIGTeclado_
#define _CPIGTeclado_

#include <pig/PIGTipos.h>

class CPIGTeclado
{
private:

    static const Uint8 *estado;
    static Uint8 teclado[SDL_NUM_SCANCODES];
    static Uint8 teclado_anterior[SDL_NUM_SCANCODES];

public:

    static int ProcessaEvento(const PIGEvento &evento);
    static bool TeclaPressionada(SDL_Scancode tecla);
    static bool TeclaLevantada(SDL_Scancode tecla);
    static bool TeclaBaixa(SDL_Scancode tecla);
    static bool TeclaAlta(SDL_Scancode tecla);
    static void AtualizaEstadoAnterior();
};

#endif
