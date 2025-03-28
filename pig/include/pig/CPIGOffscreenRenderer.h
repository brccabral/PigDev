#ifndef _CPIGOFFSCREENRENDERER_
#define _CPIGOFFSCREENRENDERER_

#include <cmath>
#include <vector>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGErros.h>

typedef struct
{
    SDL_Surface *surf;
    SDL_Renderer *render;
} PIGLayer;

class CPIGOffscreenRenderer
{

private:

    PIGLayer layers[PIG_MAX_CAMADAS_OFFSCREEN] = {};
    int qtdLayers, maxLayers;

    int alt, larg, depth;
    double px, py;
    double ang;
    PIGCor corAtual = {};
    PIGFuncaoPintarArea userFunctionPintarArea;

    static void CriaPontosCirculo(
            int centroX, int centroY, int raio, double angInicial, double angFinal,
            vector<double> &angs, vector<SDL_Point> &pontos);

public:

    CPIGOffscreenRenderer(int altura, int largura, int qtdMaxCamadas = 10);
    ~CPIGOffscreenRenderer();

    [[nodiscard]] SDL_Renderer *GetRenderer(int layer = 0) const;
    [[nodiscard]] SDL_Surface *GetSurface(int layer = 0) const;
    [[nodiscard]] int GetAltura() const;
    [[nodiscard]] int GetLargura() const;
    [[nodiscard]] int GetDepth() const;
    void SetCorTransparente(int layer, bool transparencia, PIGCor cor) const;
    void MergeSurface(int layerSuperior, int layerInferior, SDL_BlendMode modo) const;
    PIGLayer CriaLayer();
    void LimpaLayer(int layer, PIGCor cor) const;
    void DesenhaCirculoFinal(
            int raio, PIGCor corFundo, PIGCor corCirculo, double angInicial, double angFinal,
            int layer = 0) const;
    void DesenhaCirculoFatia(
            int centroX, int centroY, int raio, PIGCor cor, double angInicial, double angFinal,
            SDL_Point &iniP, SDL_Point &fimP, int layer = 0) const;
    void PintarFundo(PIGCor cor, int layer = 0) const;
    void PintarArea(int px, int py, PIGCor cor, int layer = 0) const;
    void DesenharLinha(int x1, int y1, int x2, int y2, PIGCor cor, int layer = 0) const;
    void DesenhaLinhasDisjuntas(int x[], int y[], int qtd, PIGCor cor, int layer = 0) const;
    void DesenhaLinhasSequencia(int x[], int y[], int qtd, PIGCor cor, int layer = 0) const;
    void DesenharRetangulo(int x, int y, int altura, int largura, PIGCor cor, int layer = 0) const;
    void
    DesenharRetanguloVazado(int x, int y, int altura, int largura, PIGCor cor, int layer = 0) const;
    void CarregaPixelsSurface(int layer = 0) const;
    void SalvarImagemBMP(const char *nomearq, int layer = 0) const;
    void SalvarImagemPNG(const char *nomearq, int layer = 0) const;
    void DefineFuncaoPintarArea(PIGFuncaoPintarArea funcao);
    void MoveCanetaPara(double nx, double ny);
    void GiraCanetaHorario(double angulo);
    void GiraCanetaAntiHorario(double angulo);
    void GiraAnguloFixo(double angulo);
    [[nodiscard]] double GetAngAtual() const;
    void AvancaCaneta(double distancia, int layer = 0);
    void MudaCorAtualCaneta(PIGCor novaCor);
    [[nodiscard]] double GetXCaneta() const;
    [[nodiscard]] double GetYCaneta() const;
    PIGLayer *GetLayer(int indice);
};

typedef CPIGOffscreenRenderer *PIGOffscreenRenderer;
#endif // _CPIGOFFSCREENRENDERER_
