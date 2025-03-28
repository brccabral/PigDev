#include <SDL_image.h>

#include <pig/CPIGOffscreenRenderer.h>

void CPIGOffscreenRenderer::CriaPontosCirculo(
        int centroX, int centroY, int raio, double angInicial, double angFinal,
        vector<double> &angs, vector<SDL_Point> &pontos)
{
    int x = -raio, y = 0, err = 2 - (2 * raio); /* II. Quadrant */
    vector<SDL_Point> q1, q2, q3, q4;
    vector<double> ang1, ang2, ang3, ang4;

    do
    {
        SDL_Point p = {centroX - x, centroY - y};
        q1.push_back(p);
        double a = atan(1. * y / -x) * 180 / M_PI;
        ang1.push_back(a);

        p = {.x = centroX - y, .y = centroY + x};
        q2.push_back(p);
        a = 180 + atan(1. * x / y) * 180 / M_PI;
        ang2.push_back(a);

        p = {.x = centroX + x, .y = centroY + y};
        q3.push_back(p);
        a = atan(1. * -y / x) * 180 / M_PI + 180;
        ang3.push_back(a);

        p = {.x = centroX + y, .y = centroY - x};
        q4.push_back(p);
        if (x == -raio)
        {
            a = 270;
        }
        else
        {
            a = 360 + atan(1. * -x / -y) * 180 / M_PI;
        }
        ang4.push_back(a);

        raio = err;
        if (raio <= y)
        {
            err += ++y * 2 + 1; /* e_xy+e_y < 0 */
        }
        if (raio > x || err > y)
        {
            err += ++x * 2 + 1; /* e_xy+e_x > 0 or no 2nd y-step */
        }
    }
    while (x < 0);

    angs.clear();
    pontos.clear();

    // colocar os pontos em ordem pelo ângulo
    for (size_t i = 0; i < q1.size(); i++)
    { // primeiro quadrante
        if (ang1[i] <= angFinal - angInicial && (i == 0 || ang1[i] > ang1[i - 1]))
        {
            angs.push_back(ang1[i]);
            pontos.push_back(q1[i]);
        }
    }
    for (size_t i = 0; i < q2.size(); i++)
    { // segundo quadrante
        if (ang2[i] <= angFinal - angInicial && (i == 0 || ang2[i] > ang2[i - 1]))
        {
            angs.push_back(ang2[i]);
            pontos.push_back(q2[i]);
        }
    }
    for (size_t i = 0; i < q3.size(); i++)
    { // terceiro quadrante
        if (ang3[i] <= angFinal - angInicial && (i == 0 || ang3[i] > ang3[i - 1]))
        {
            angs.push_back(ang3[i]);
            pontos.push_back(q3[i]);
        }
    }
    for (size_t i = 0; i < q4.size(); i++)
    { // quarto quadrante
        if (ang4[i] <= angFinal - angInicial && (i == 0 || ang4[i] > ang4[i - 1]))
        {
            angs.push_back(ang4[i]);
            pontos.push_back(q4[i]);
        }
    }
}

[[nodiscard]] SDL_Renderer *CPIGOffscreenRenderer::GetRenderer(int layer) const
{
    return layers[layer].render;
}

[[nodiscard]] SDL_Surface *CPIGOffscreenRenderer::GetSurface(int layer) const
{
    return layers[layer].surf;
}

[[nodiscard]] int CPIGOffscreenRenderer::GetAltura() const
{
    return alt;
}

[[nodiscard]] int CPIGOffscreenRenderer::GetLargura() const
{
    return larg;
}

[[nodiscard]] int CPIGOffscreenRenderer::GetDepth() const
{
    return depth;
}

void CPIGOffscreenRenderer::SetCorTransparente(int layer, bool transparencia, PIGCor cor) const
{
    SDL_SetColorKey(
            layers[layer].surf, transparencia,
            SDL_MapRGBA(layers[layer].surf->format, cor.r, cor.g, cor.b, cor.a));
}

void CPIGOffscreenRenderer::MergeSurface(
        int layerSuperior, int layerInferior, SDL_BlendMode modo) const
{
    SDL_SetSurfaceBlendMode(layers[layerInferior].surf, modo);
    SDL_BlitSurface(layers[layerSuperior].surf, NULL, layers[layerInferior].surf, NULL);
}

PIGLayer CPIGOffscreenRenderer::CriaLayer()
{
    PIGLayer l;
    l.surf = SDL_CreateRGBSurfaceWithFormat(0, larg, alt, depth, SDL_PIXELFORMAT_RGBA32);
    l.render = SDL_CreateSoftwareRenderer(l.surf);
    SDL_RenderClear(l.render);
    qtdLayers++;
    return l;
}

void CPIGOffscreenRenderer::LimpaLayer(int layer, PIGCor cor) const
{
    SDL_SetRenderDrawColor(layers[layer].render, cor.r, cor.g, cor.b, cor.a);
    SDL_RenderClear(layers[layer].render);
}

CPIGOffscreenRenderer::CPIGOffscreenRenderer(int altura, int largura, int qtdMaxCamadas)
{
    alt = altura;
    larg = largura;
    depth = 32; // 32 bits por pixel
    maxLayers = qtdMaxCamadas;
    qtdLayers = 0;
    for (int i = 0; i < maxLayers; i++)
    {
        layers[i] = CriaLayer();
    }

    userFunctionPintarArea = NULL;

    px = py = 1;
    ang = 0;
    corAtual = BRANCO;
}

void CPIGOffscreenRenderer::DesenhaCirculoFinal(
        int raio, PIGCor corFundo, PIGCor corCirculo, double angInicial, double angFinal,
        int layer) const
{
    int xm = larg / 2;
    int ym = alt / 2;
    SDL_Point p1, p2;
    LimpaLayer(layer, corCirculo);

    DesenhaCirculoFatia(xm, ym, raio, corFundo, angInicial, angFinal, p1, p2, layer);
    if (angFinal - angInicial < 360 && angFinal - angInicial > 0)
    {
        SDL_RenderDrawLine(layers[layer].render, p1.x, p1.y, xm, ym);
        SDL_RenderDrawLine(layers[layer].render, p2.x, p2.y, xm, ym);
    }

    PintarArea(0, 0, corFundo, layer);
}

void CPIGOffscreenRenderer::DesenhaCirculoFatia(
        int centroX, int centroY, int raio, PIGCor cor, double angInicial, double angFinal,
        SDL_Point &iniP, SDL_Point &fimP, int layer) const
{
    vector<double> angs;
    vector<SDL_Point> pontos;
    CriaPontosCirculo(centroX, centroY, raio, angInicial, angFinal, angs, pontos);

    iniP = pontos[0];
    fimP = pontos.back();

    SDL_SetRenderDrawColor(layers[layer].render, cor.r, cor.g, cor.b, cor.a);

    for (size_t i = 1; i < pontos.size(); i++)
    {
        SDL_RenderDrawLine(
                layers[layer].render, pontos[i - 1].x, pontos[i - 1].y, pontos[i].x, pontos[i].y);
    }
}

void CPIGOffscreenRenderer::PintarFundo(PIGCor cor, int layer) const
{
    SDL_SetRenderDrawColor(layers[layer].render, cor.r, cor.g, cor.b, cor.a);
    SDL_RenderClear(layers[layer].render);
}

void CPIGOffscreenRenderer::PintarArea(int px, int py, PIGCor cor, int layer) const
{
    if (px < 0 || py < 0 || px >= larg || py >= alt)
    {
        return;
    }
    SDL_Surface *surface = layers[layer].surf;
    SDL_LockSurface(surface);
    Uint32 *pBase = (Uint32 *) surface->pixels;
    pBase += (px + (alt - py - 1) * larg);
    Uint32 corBase = *pBase;

    Uint32 color = SDL_MapRGBA(
            (const SDL_PixelFormat *) &surface->format->format, cor.r, cor.g, cor.b, cor.a);
    if (color == corBase)
    {
        return;
    }

    vector<SDL_Point> pilha;
    pilha.push_back({px, py});

    while (!pilha.empty())
    {
        const SDL_Point elemento = pilha.back();
        pilha.pop_back();
        if (elemento.x >= 0 && elemento.y >= 0 && elemento.x < larg && elemento.y < alt)
        {
            Uint32 *p = (Uint32 *) surface->pixels;
            p += (elemento.x + (alt - elemento.y - 1) * larg);

            if ((*p) == corBase)
            {

                if (userFunctionPintarArea)
                {
                    PIGCor corAtual;
                    SDL_GetRGBA(
                            corBase, (const SDL_PixelFormat *) &surface->format->format,
                            &(corAtual.r), &(corAtual.g), &(corAtual.b), &(corAtual.a));
                    cor = userFunctionPintarArea(elemento.x, elemento.y, alt, larg, corAtual, cor);
                    color = SDL_MapRGBA(
                            (const SDL_PixelFormat *) &surface->format->format, cor.r, cor.g, cor.b,
                            cor.a);
                }

                *p = color; // muda efetivamente a cor
                pilha.push_back({elemento.x + 1, elemento.y + 0});
                pilha.push_back({elemento.x + 0, elemento.y + 1});
                pilha.push_back({elemento.x - 1, elemento.y + 0});
                pilha.push_back({elemento.x + 0, elemento.y - 1});
            }
        }
    }

    SDL_UnlockSurface(surface);
}

void CPIGOffscreenRenderer::DesenharLinha(
        int x1, int y1, int x2, int y2, PIGCor cor, int layer) const
{
    SDL_SetRenderDrawColor(layers[layer].render, cor.r, cor.g, cor.b, cor.a);
    SDL_RenderDrawLine(layers[layer].render, x1, alt - y1 - 1, x2, alt - y2 - 1);
}

void CPIGOffscreenRenderer::DesenhaLinhasDisjuntas(
        int x[], int y[], int qtd, PIGCor cor, int layer) const
{
    SDL_SetRenderDrawColor(layers[layer].render, cor.r, cor.g, cor.b, 255);
    for (int k = 0; k < qtd; k += 2)
    {
        SDL_RenderDrawLine(layers[layer].render, x[k], alt - y[k], x[k + 1], alt - y[k + 1]);
        // SDL_RenderDrawLine(renderer,x[k]-camera->GetX(),altura-y[k]+camera->GetY(),x[k+1]-camera->GetX(),altura-y[k+1]+camera->GetY());
    }
}

void CPIGOffscreenRenderer::DesenhaLinhasSequencia(
        int x[], int y[], int qtd, PIGCor cor, int layer) const
{
    SDL_SetRenderDrawColor(layers[layer].render, cor.r, cor.g, cor.b, 255);
    for (int k = 0; k < qtd - 1; k++)
    {
        SDL_RenderDrawLine(layers[layer].render, x[k], alt - y[k], x[k + 1], alt - y[k + 1]);
        // SDL_RenderDrawLine(renderer,x[k]-camera->GetX(),altura-y[k]+camera->GetY(),x[k+1]-camera->GetX(),altura-y[k+1]+camera->GetY());
    }
}

void CPIGOffscreenRenderer::DesenharRetangulo(
        int x, int y, int altura, int largura, PIGCor cor, int layer) const
{
    SDL_Rect r = {x, alt - y - altura - 1, largura, altura};

    SDL_SetRenderDrawColor(layers[layer].render, cor.r, cor.g, cor.b, cor.a);
    SDL_RenderFillRect(layers[layer].render, &r);
}

void CPIGOffscreenRenderer::DesenharRetanguloVazado(
        int x, int y, int altura, int largura, PIGCor cor, int layer) const
{
    SDL_Rect r = {x, alt - y - altura - 1, largura, altura};

    SDL_SetRenderDrawColor(layers[layer].render, cor.r, cor.g, cor.b, cor.a);
    SDL_RenderDrawRect(layers[layer].render, &r);
}

void CPIGOffscreenRenderer::CarregaPixelsSurface(int layer) const
{
    SDL_RenderReadPixels(
            layers[layer].render, NULL, SDL_PIXELFORMAT_ARGB8888, layers[layer].surf->pixels,
            layers[layer].surf->pitch);
}

void CPIGOffscreenRenderer::SalvarImagemBMP(const char *nomearq, int layer) const
{
    SDL_SaveBMP(layers[layer].surf, nomearq);
}

void CPIGOffscreenRenderer::SalvarImagemPNG(const char *nomearq, int layer) const
{
    IMG_SavePNG(layers[layer].surf, nomearq);
}

void CPIGOffscreenRenderer::DefineFuncaoPintarArea(PIGFuncaoPintarArea funcao)
{
    userFunctionPintarArea = funcao;
}

void CPIGOffscreenRenderer::MoveCanetaPara(double nx, double ny)
{
    px = nx;
    py = ny;
}

void CPIGOffscreenRenderer::GiraCanetaHorario(double angulo)
{
    ang -= angulo;
}

void CPIGOffscreenRenderer::GiraCanetaAntiHorario(double angulo)
{
    ang += angulo;
}

void CPIGOffscreenRenderer::GiraAnguloFixo(double angulo)
{
    ang = angulo;
}

[[nodiscard]] double CPIGOffscreenRenderer::GetAngAtual() const
{
    return ang;
}

void CPIGOffscreenRenderer::AvancaCaneta(double distancia, int layer)
{
    double nx = px + (cos(ang * M_PI / 180.0) * distancia);
    double ny = py + (sin(ang * M_PI / 180.0) * distancia);
    DesenharLinha(px, py, nx, ny, corAtual, layer);
    px = nx;
    py = ny;
}

void CPIGOffscreenRenderer::MudaCorAtualCaneta(PIGCor novaCor)
{
    corAtual = novaCor;
}

[[nodiscard]] double CPIGOffscreenRenderer::GetXCaneta() const
{
    return px;
}

[[nodiscard]] double CPIGOffscreenRenderer::GetYCaneta() const
{
    return py;
}

PIGLayer *CPIGOffscreenRenderer::GetLayer(int indice)
{
    if (indice < qtdLayers)
    {
        return &layers[indice];
    }
    throw CPIGErroIndice(indice, "layer do renderizador offscreen");
}

CPIGOffscreenRenderer::~CPIGOffscreenRenderer()
{
    for (int i = 0; i < maxLayers; i++)
    {
        SDL_DestroyRenderer(layers[i].render);
        SDL_FreeSurface(layers[i].surf);
    }
}
