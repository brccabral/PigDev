#ifndef _CPIGLABEL_
#define _CPIGLABEL_

#include <string>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGSprite.h>

class CPIGLabel : public CPIGSprite
{

private:

    string frase;
    int idFonte;
    PIGCor corFonte{};

    void AtualizaTextura() override;

public:

    CPIGLabel(const string &texto, PIGCor cor, int numFonte, int idJanela = 0);
    void SetTexto(const string &texto);
    void SetFonte(int numFonte);
    void SetCorFonte(PIGCor novaCor);
    int GetAltura();
    int GetLargura();
    string GetTexto();
    int GetFonte() const;
    PIGCor GetCorFonte();
};

typedef CPIGLabel *PIGLabel;
#endif // _CPIGLABEL_
