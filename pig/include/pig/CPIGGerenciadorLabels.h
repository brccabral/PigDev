#ifndef _CPIGGERENCIADORLABELS_
#define _CPIGGERENCIADORLABELS_

#include <string>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGLabel.h>
#include <pig/CPIGRepositorio.h>

class CPIGGerenciadorLabels
{

private:

    static CPIGRepositorio<PIGLabel> *labels;

public:

    static PIGLabel GetLabel(int idLabel);
    static void Inicia();
    static void Encerra();
    static int CriaLabel(const string &texto, PIGCor cor, int numFonte, int idJanela = 0);
    static int InsereLabel(PIGLabel label);
    static void DestroiLabel(int idLabel);
};

#endif //_CPIGGERENCIADORLABELS_
