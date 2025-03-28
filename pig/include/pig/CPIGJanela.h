#ifndef _CPIGJanela_
#define _CPIGJanela_

#include <string>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGTimer.h>
#include <pig/CPIGCamera.h>

class CPIGJanela
{

private:

    SDL_Window *window{};
    SDL_Renderer *renderer{};
    SDL_Texture *textFundo{};
    int contFPS, lastFPS;
    PIGTimer timerFPS{};
    PIGCor corFundo = {};
    int altura, largura;
    SDL_Point pos = {};
    int id;
    int modo{};
    bool fechada;
    float opacidade;
    string titulo{};
    SDL_Rect block = {};
    PIGCamera cameraMovel{}, cameraFixa{};
    SDL_sem *semRender{};
    bool fixo;

public:

    CPIGJanela(const string &tituloJanela, int idJanela, int altTela, int largTela);
    ~CPIGJanela();
    [[nodiscard]] SDL_Window *GetWindow() const;
    [[nodiscard]] SDL_Renderer *GetRenderer() const;
    [[nodiscard]] PIGCamera GetCamera() const;
    void PreparaCameraFixa();
    void PreparaCameraMovel();
    void Fecha();
    [[nodiscard]] bool GetFechada() const;
    void Esconde();
    void Exibe();
    void GanhaFoco();
    [[nodiscard]] bool GetUsandoCameraFixa() const;
    void MoveCamera(int nx, int ny);
    void DeslocaCamera(int dx, int dy) const;
    double SetAfastamento(double valor);
    void ConverteCoordenadaScreenWorld(int screenX, int screenY, int &worldX, int &worldY) const;
    void ConverteCoordenadaWorldScreen(int worldX, int worldY, int &screenX, int &screenY) const;
    double GetAfastamento();
    SDL_Point GetPosicaoCamera();
    void DefineFundo(const string &nomeArquivo);
    void SaveScreenshot(const string &nomeArquivo, bool BMP);
    void TravaRenderer();
    void DestravaRenderer();
    void IniciaDesenho();
    void EncerraDesenho();
    [[nodiscard]] float GetFPS(int idJanela = 0) const;
    [[nodiscard]] int GetAltura() const;
    [[nodiscard]] int GetLargura() const;
    string GetTitulo();
    void SetTitulo(const string &novoTitulo);
    PIGCor GetCorFundo();
    void SetCorFundo(PIGCor cor);
    [[nodiscard]] float GetOpacidade() const;
    void SetOpacidade(float valor);
    void SetPosicao(int x, int y);
    SDL_Point GetXY();
    void SetBorda(int valor);
    void SetModo(int valor);
    [[nodiscard]] int GetModo() const;
    void SetTamanho(int alt, int larg);
    void DesenhaRetangulo(int x, int y, int alturaRet, int larguraRet, PIGCor cor) const;
    void DesenhaRetanguloVazado(int x, int y, int alturaRet, int larguraRet, PIGCor cor) const;
    void DesenhaLinhaSimples(int x1, int y1, int x2, int y2, PIGCor cor);
    void DesenhaLinhasDisjuntas(int x[], int y[], int qtd, PIGCor cor);
    void DesenhaLinhasSequencia(int x[], int y[], int qtd, PIGCor cor);
    void DesenhaPoligono(int px[], int py[], int lados, PIGCor cor) const;
    [[nodiscard]] PIGCor GetPixel(int x, int y) const;
    void BloqueiaArea(int x, int y, int alt, int larg);
    SDL_Rect GetAreaBloqueada();
    void DesbloqueiaArea();
};

typedef CPIGJanela *PIGJanela;
#endif // _CPIGJanela_
