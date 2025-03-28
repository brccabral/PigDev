#include <algorithm>
#include <climits>
#include <SDL_image.h>

#include <pig/CPIGJanela.h>
#include <pig/CPIGOffscreenRenderer.h>
#include <pig/PIGFuncoesBasicas.h>

CPIGJanela::CPIGJanela(const string &tituloJanela, int idJanela, int altTela, int largTela)
{
    id = idJanela;
    titulo = tituloJanela;
    altura = altTela;
    largura = largTela;
    window = SDL_CreateWindow(
            tituloJanela.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largura, altura,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        printf("Janela %d nao pode ser criada! Erro da SDL: %s\n", id, SDL_GetError());
    }
    else
    {
        // handler = SDL_GetWindowID(window);
        // printf("Meu id %d meu handler %d\n",idJanela,handler);
        SDL_GetWindowPosition(window, &pos.x, &pos.y);
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
        renderer = SDL_CreateRenderer(
                window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
        corFundo = PRETO;
        contFPS = lastFPS = 0;
        timerFPS = new CPIGTimer(false);
        SDL_SetRenderDrawColor(renderer, corFundo.r, corFundo.g, corFundo.b, corFundo.a);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        fechada = false;
        modo = PIG_JANELA_NORMAL;
        cameraMovel = new CPIGCamera(altTela, largTela);
        cameraFixa = new CPIGCamera(altTela, largTela);
        fixo = true;
    }

    opacidade = 1.0F;
    textFundo = NULL;
    block = {.x = 0, .y = 0, .w = -1, .h = -1};
    semRender = SDL_CreateSemaphore(1);
}

CPIGJanela::~CPIGJanela()
{
    delete timerFPS;
    SDL_DestroySemaphore(semRender);
    SDL_DestroyRenderer(renderer);
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    delete cameraMovel;
    delete cameraFixa;
}

[[nodiscard]] SDL_Window *CPIGJanela::GetWindow() const
{
    return window;
}

[[nodiscard]] SDL_Renderer *CPIGJanela::GetRenderer() const
{
    return renderer;
}

[[nodiscard]] PIGCamera CPIGJanela::GetCamera() const
{
    if (fixo)
    {
        return cameraFixa;
    }
    return cameraMovel;
}

void CPIGJanela::PreparaCameraFixa()
{
    fixo = true;
    SDL_RenderSetLogicalSize(renderer, largura, altura);
}

void CPIGJanela::PreparaCameraMovel()
{
    fixo = false;
    double pan = cameraMovel->GetAfastamento();
    SDL_RenderSetLogicalSize(renderer, pan * largura, pan * altura);
}

void CPIGJanela::Fecha()
{
    if (window == NULL)
    {
        return;
    }
    SDL_DestroyWindow(window);
    window = NULL;
    fechada = true;
}

[[nodiscard]] bool CPIGJanela::GetFechada() const
{
    return fechada;
}

void CPIGJanela::Esconde()
{
    SDL_HideWindow(window);
}

void CPIGJanela::Exibe()
{
    SDL_ShowWindow(window);
}

void CPIGJanela::GanhaFoco()
{
    SDL_RaiseWindow(window);
}

[[nodiscard]] bool CPIGJanela::GetUsandoCameraFixa() const
{
    return fixo;
}

void CPIGJanela::MoveCamera(int nx, int ny)
{
    cameraMovel->Move({nx, ny});
}

void CPIGJanela::DeslocaCamera(int dx, int dy) const
{
    cameraMovel->Desloca(dx, dy);
}

double CPIGJanela::SetAfastamento(double valor)
{
    double afastamento = cameraMovel->DefineAfastamento(valor);
    SDL_RenderSetLogicalSize(renderer, afastamento * largura, afastamento * altura);
    return afastamento;
}

void CPIGJanela::ConverteCoordenadaScreenWorld(
        int screenX, int screenY, int &worldX, int &worldY) const
{
    GetCamera()->ConverteCoordenadaScreenWorld(screenX, screenY, worldX, worldY);
}

void CPIGJanela::ConverteCoordenadaWorldScreen(
        int worldX, int worldY, int &screenX, int &screenY) const
{
    GetCamera()->ConverteCoordenadaWorldScreen(worldX, worldY, screenX, screenY);
}

double CPIGJanela::GetAfastamento()
{
    return cameraMovel->GetAfastamento();
}

SDL_Point CPIGJanela::GetPosicaoCamera()
{
    return cameraMovel->GetXY();
}

void CPIGJanela::DefineFundo(const string &nomeArquivo)
{
    SDL_Surface *bitmap = IMG_Load(nomeArquivo.c_str());
    if (textFundo)
    {
        SDL_DestroyTexture(textFundo);
    }
    textFundo = SDL_CreateTextureFromSurface(renderer, bitmap);
    SDL_FreeSurface(bitmap);
}

void CPIGJanela::SaveScreenshot(const string &nomeArquivo, bool BMP)
{
    if (window == NULL)
    {
        return;
    }
    SDL_Surface *infoSurface = NULL;
    infoSurface = SDL_GetWindowSurface(window);
    if (infoSurface != NULL)
    {
        unsigned char *pixels = new unsigned char
                [infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
        if (SDL_RenderReadPixels(
                    renderer, &infoSurface->clip_rect, infoSurface->format->format, pixels,
                    infoSurface->w * infoSurface->format->BytesPerPixel) == 0)
        {
            SDL_Surface *saveSurface = NULL;
            saveSurface = SDL_CreateRGBSurfaceFrom(
                    pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel,
                    infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask,
                    infoSurface->format->Gmask, infoSurface->format->Bmask,
                    infoSurface->format->Amask);
            if (saveSurface != NULL)
            {
                if (BMP)
                {
                    SDL_SaveBMP(saveSurface, nomeArquivo.c_str());
                }
                else
                {
                    IMG_SavePNG(saveSurface, nomeArquivo.c_str());
                }
                SDL_FreeSurface(saveSurface);
            }
        }
        delete[] pixels;
        SDL_FreeSurface(infoSurface);
    }
}

void CPIGJanela::TravaRenderer()
{
    SDL_SemWait(semRender);
}

void CPIGJanela::DestravaRenderer()
{
    SDL_SemPost(semRender);
}

void CPIGJanela::IniciaDesenho()
{
    TravaRenderer();
    if (textFundo == NULL)
    {
        SDL_SetRenderDrawColor(renderer, corFundo.r, corFundo.g, corFundo.b, corFundo.a);
        SDL_RenderClear(renderer);
    }
    else
    {
        SDL_RenderCopy(renderer, textFundo, NULL, NULL);
    }
}

void CPIGJanela::EncerraDesenho()
{
    SDL_RenderPresent(renderer);
    DestravaRenderer();
    contFPS++;
    if (timerFPS->GetTempoDecorrido() > PIG_INTERVALO_FPS)
    {
        lastFPS = contFPS;
        contFPS = 0;

        timerFPS->Reinicia(false);
    }
}

[[nodiscard]] float CPIGJanela::GetFPS(int idJanela) const
{
    return lastFPS / PIG_INTERVALO_FPS;
}

int CPIGJanela::GetAltura() const
{
    return altura;
}

[[nodiscard]] int CPIGJanela::GetLargura() const
{
    return largura;
}

string CPIGJanela::GetTitulo()
{
    return titulo;
}

void CPIGJanela::SetTitulo(const string &novoTitulo)
{
    if (window == NULL)
    {
        return;
    }
    titulo = novoTitulo;
    SDL_SetWindowTitle(window, titulo.c_str());
}

PIGCor CPIGJanela::GetCorFundo()
{
    return corFundo;
}

void CPIGJanela::SetCorFundo(PIGCor cor)
{
    corFundo = cor;
}

[[nodiscard]] float CPIGJanela::GetOpacidade() const
{
    return opacidade;
}

void CPIGJanela::SetOpacidade(float valor)
{
    opacidade = valor;
    SDL_SetWindowOpacity(window, opacidade);
}

void CPIGJanela::SetPosicao(int x, int y)
{
    if (window == NULL)
    {
        return;
    }
    SDL_SetWindowPosition(window, x, y);
}

SDL_Point CPIGJanela::GetXY()
{
    return pos;
}

void CPIGJanela::SetBorda(int valor)
{
    if (window == NULL)
    {
        return;
    }
    SDL_SetWindowBordered(window, SDL_bool(valor));
}

void CPIGJanela::SetModo(int valor)
{
    if (window == NULL)
    {
        return;
    }
    modo = valor;
    SDL_SetWindowFullscreen(window, modo);
    SDL_GetWindowSize(window, &largura, &altura);
}

[[nodiscard]] int CPIGJanela::GetModo() const
{
    return modo;
}

void CPIGJanela::SetTamanho(int alt, int larg)
{
    altura = alt;
    largura = larg;
    SDL_SetWindowSize(window, larg, alt);
    cameraMovel->AjustaTela(altura, largura);
    cameraFixa->AjustaTela(altura, largura);
}

void CPIGJanela::DesenhaRetangulo(int x, int y, int alturaRet, int larguraRet, PIGCor cor) const
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = altura - (y + alturaRet);
    rect.h = alturaRet;
    rect.w = larguraRet;

    GetCamera()->ConverteCoordenadaWorldScreen(rect.x, rect.y, rect.x, rect.y);

    // printf("%d,%d,%d,%d\n",rect.x,rect.y,rect.h,rect.w);

    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, cor.a);
    SDL_RenderFillRect(renderer, &rect);
}

void CPIGJanela::DesenhaRetanguloVazado(
        int x, int y, int alturaRet, int larguraRet, PIGCor cor) const
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = altura - (y + alturaRet);
    rect.h = alturaRet;
    rect.w = larguraRet;

    GetCamera()->ConverteCoordenadaWorldScreen(rect.x, rect.y, rect.x, rect.y);

    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, cor.a);
    SDL_RenderDrawRect(renderer, &rect);
}

void CPIGJanela::DesenhaLinhaSimples(int x1, int y1, int x2, int y2, PIGCor cor)
{
    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, 255);
    int camX1, camY1, camX2, camY2;
    GetCamera()->ConverteCoordenadaWorldScreen(x1, altura - y1 - 1, camX1, camY1);
    GetCamera()->ConverteCoordenadaWorldScreen(x2, altura - y2 - 1, camX2, camY2);
    SDL_RenderDrawLine(renderer, camX1, camY1, camX2, camY2);
    // SDL_RenderDrawLine(renderer,x1-camera->GetX(),altura-y1-1+camera->GetY(),x2-camera->GetX(),altura-y2-1+camera->GetY());
}

void CPIGJanela::DesenhaLinhasDisjuntas(int x[], int y[], int qtd, PIGCor cor)
{
    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, 255);
    int camX1, camY1, camX2, camY2;
    for (int k = 0; k < qtd; k += 2)
    {
        GetCamera()->ConverteCoordenadaWorldScreen(x[k], altura - y[k], camX1, camY1);
        GetCamera()->ConverteCoordenadaWorldScreen(x[k + 1], altura - y[k + 1], camX2, camY2);
        SDL_RenderDrawLine(renderer, camX1, camY1, camX2, camY2);
        // SDL_RenderDrawLine(renderer,x[k]-camera->GetX(),altura-y[k]+camera->GetY(),x[k+1]-camera->GetX(),altura-y[k+1]+camera->GetY());
    }
}

void CPIGJanela::DesenhaLinhasSequencia(int x[], int y[], int qtd, PIGCor cor)
{
    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, 255);
    int camX1, camY1, camX2, camY2;
    for (int k = 0; k < qtd - 1; k++)
    {
        GetCamera()->ConverteCoordenadaWorldScreen(x[k], altura - y[k], camX1, camY1);
        GetCamera()->ConverteCoordenadaWorldScreen(x[k + 1], altura - y[k + 1], camX2, camY2);
        SDL_RenderDrawLine(renderer, camX1, camY1, camX2, camY2);
        // SDL_RenderDrawLine(renderer,x[k]-camera->GetX(),altura-y[k]+camera->GetY(),x[k+1]-camera->GetX(),altura-y[k+1]+camera->GetY());
    }
}

void CPIGJanela::DesenhaPoligono(int px[], int py[], int lados, PIGCor cor) const
{
    int minX = INT_MAX, maxX = -1, minY = INT_MAX, maxY = -1;
    int cx = 0, cy = 0;

    // calcula o bounding-box do poligono
    for (int i = 0; i < lados; i++)
    {
        minX = std::min(px[i], minX);
        minY = std::min(py[i], minY);
        maxX = std::max(px[i], maxX);
        maxY = std::max(py[i], maxY);
        cx += px[i]; // centro do poligono
        cy += py[i]; // centro do poligono
    }
    cx /= lados; // centro do poligono
    cy /= lados; // centro do poligono

    int alt = maxY - minY + 1; // altura absoluta do poligono
    int larg = maxX - minX + 1; // altura absoluta do poligono

    PIGOffscreenRenderer off =
            new CPIGOffscreenRenderer(alt, larg); // ajustado extamente com a altura e largura

    if (PIGCoresIguais(cor, PRETO))
    {
        off->PintarFundo(BRANCO);
    }
    else
    {
        off->PintarFundo(PRETO);
    }

    for (int i = 0; i < lados; i++)
    {
        off->DesenharLinha(
                px[i] - minX, py[i] - minY, px[(i + 1) % lados] - minX, py[(i + 1) % lados] - minY,
                cor);
    }

    off->PintarArea(cx - minX, cy - minY, cor);

    SDL_Surface *surf = off->GetSurface();
    if (PIGCoresIguais(cor, PRETO))
    {
        SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGBA(surf->format, 255, 255, 255, 255));
    }
    else
    {
        SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGBA(surf->format, 0, 0, 0, 255));
    }

    // SDL_Renderer *renderer = CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_Rect r;
    r.h = alt;
    r.w = larg;
    r.x = minX;
    r.y = altura - minY - alt;
    GetCamera()->ConverteCoordenadaWorldScreen(r.x, r.y, r.x, r.y);
    // printf("%d,%d %d,%d\n",r.x,r.y,r.h,r.w);
    SDL_RenderCopy(renderer, text, NULL, &r);
    SDL_DestroyTexture(text);
    delete off;
}

[[nodiscard]] PIGCor CPIGJanela::GetPixel(int x, int y) const
{
    if (x < 0 || x >= largura || y < 0 || y >= altura)
    {
        return PRETO;
    }
    PIGCor resp;
    SDL_Surface *infoSurface = SDL_GetWindowSurface(window);
    if (infoSurface != NULL)
    {
        unsigned char *pixels = new unsigned char
                [infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
        if (SDL_RenderReadPixels(
                    renderer, &infoSurface->clip_rect, infoSurface->format->format, pixels,
                    infoSurface->w * infoSurface->format->BytesPerPixel) == 0)
        {
            Uint32 *p = (Uint32 *) pixels;
            p += (x + (altura - y) * largura);
            SDL_GetRGBA(
                    *p, (const SDL_PixelFormat *) &infoSurface->format->format, &resp.r, &resp.g,
                    &resp.b, &resp.a);
        }
        delete[] pixels;
        SDL_FreeSurface(infoSurface);
    }
    return resp;
}

void CPIGJanela::BloqueiaArea(int x, int y, int alt, int larg)
{
    block.x = x;
    block.y = altura - (y + alt);
    block.h = alt;
    block.w = larg;

    GetCamera()->ConverteCoordenadaWorldScreen(block.x, block.y, block.x, block.y);
    SDL_RenderSetClipRect(renderer, &block);
}

SDL_Rect CPIGJanela::GetAreaBloqueada()
{
    return block;
}

void CPIGJanela::DesbloqueiaArea()
{
    block = {.x = 0, .y = 0, .w = -1, .h = -1};
    SDL_RenderSetClipRect(renderer, NULL);
}
