#ifndef _CPIGGERENCIADORTIMERS_
#define _CPIGGERENCIADORTIMERS_

#include <cstddef>
#include <ranges>
#include <vector>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGTimer.h>
#include <pig/CPIGRepositorio.h>

class CPIGGerenciadorTimers
{

private:

    static CPIGRepositorio<PIGTimer> *timers;
    static vector<int> grupos[PIG_MAX_GRUPOS_TIMERS];

public:

    static void Inicia();
    static void Encerra();
    static PIGTimer GetTimer(int idTimer);
    static int CriaTimer(bool congelado = false);
    static int InsereTimer(PIGTimer timer);
    static void DestroiTimer(int idTimer);
    static void PausaTodos();
    static void DespausaTodos();
    static int AssociaTimerGrupo(int idTimer, int idGrupo);
    static int DesassociaTimerGrupo(int idTimer, int idGrupo);
    static int PausaGrupo(int idGrupo);
    static int DespausaGrupo(int idGrupo);
    static int ReiniciaGrupo(int idGrupo, bool valor);
};

#endif // _CPIGGERENCIADORTIMERS_
