#ifndef _CPIGGERENCIADORCONTROLES_
#define _CPIGGERENCIADORCONTROLES_

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGControle.h>

class CPIGGerenciadorControles
{

private:

    static int qtdControles;
    static PIGControle controles[PIG_MAX_CONTROLES];

public:

    static void Inicia();
    static void Encerra();
    static PIGControle GetControle(int idControle);
};

#endif // _CPIGGERENCIADORCONTROLES_
