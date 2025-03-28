#ifndef _CPIGJOGO_
#define _CPIGJOGO_

#include <cstdlib>
#include <string>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGAtributos.h>
#include <pig/CPIGOffscreenRenderer.h>

class CPIGJogo : public CPIGAtributos
{

private:

    PIGEvento ultimoEvento = {};
    PIGTeclado teclado;
    int estado;
    bool rodando;
    string diretorioAtual;
    PIGOffscreenRenderer offRenderer;

public:

    explicit CPIGJogo(
            const string &nome, int cursor = 0, int altura = PIG_ALT_TELA,
            int largura = PIG_LARG_TELA);
    ~CPIGJogo() override;
    PIGEvento PegaEvento();
    PIGTeclado PegaTeclado();
    void PoolEventos();
    static void IniciaInputTextoTela();
    static void EncerraInputTextoTela();
    static void IniciaDesenho(int idJanela = -1);
    static void EncerraDesenho(int idJanela = -1);
    [[nodiscard]] bool GetRodando() const;
    void SetEstado(int valor);
    static float GetFPS(int idJanela = 0);
    void PreparaOffScreenRenderer(int altura, int largura);
    PIGOffscreenRenderer GetOffScreenRender();
};

typedef CPIGJogo *PIGJogo;
#endif // _CPIGJOGO_
