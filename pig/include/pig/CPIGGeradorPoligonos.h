#ifndef _CPIGGeradorPoligonos_
#define _CPIGGeradorPoligonos_

#include <cmath>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGOffscreenRenderer.h>

class CPIGGeradorPoligonos
{

private:

    CPIGOffscreenRenderer *off{};

public:

    CPIGGeradorPoligonos() = default;

    void GeraPoligonoRegular(int raio, int lados, PIGCor cor);
    void GeraRetanguloChanfrado(int altura, int largura, int chanfro, PIGCor cor);
    void GeraEstrela(int raio, int pontas, PIGCor cor);
    void GeraCirculoAberto(int raio, int angulo, PIGCor cor);
    ~CPIGGeradorPoligonos() = default;
};

#endif //_CPIGGeradorPoligonos_
