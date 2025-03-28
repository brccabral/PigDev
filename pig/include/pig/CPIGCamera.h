#ifndef _CPIGCAMERA_
#define _CPIGCAMERA_

#include <SDL.h>

class CPIGCamera
{

private:

    int altTela, largTela, altAtual, largAtual;
    SDL_Point pos = {};
    double pan, minPan, maxPan;

public:

    CPIGCamera(int alturaTela, int larguraTela);
    SDL_Point GetXY();
    // não utilizada
    void AjustaTela(int novaAltura, int novaLargura);
    void Move(SDL_Point nova);
    void Desloca(int dx, int dy);
    double DefineAfastamento(double valor);
    [[nodiscard]] double GetAfastamento() const;
    void ConverteCoordenadaWorldScreen(int xObj, int yObj, int &cx, int &cy) const;
    void ConverteCoordenadaScreenWorld(int xTela, int yTela, int &cx, int &cy) const;
};
typedef CPIGCamera *PIGCamera;
#endif // _CPIGCAMERA_
