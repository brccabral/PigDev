#include <thread>

using namespace std;

#include <pig/PIGFuncoesBasicas.h>
#include <pig/CPIGSprite.h>
#include <pig/CPIGGerenciadorJanelas.h>
#include <pig/CPIGAssetLoader.h>

void CPIGSprite::CarregaImagem(const string &nomeArq)
{
    nomeArquivo = nomeArq;

#ifdef PIG_SHARE_BITMAP
    surface = CPIGAssetLoader::LoadImage(nomeArquivo);
#else
    bitmap = IMG_Load(nomeArquivo.c_str());
#endif
    if (!surface)
    {
        throw CPIGErroArquivo(nomeArquivo);
    }
}

void CPIGSprite::IniciaBase(int altura, int largura, int janela)
{
    frameAtual = 0;
    automacao = NULL;
    tipoFixo = 0;
    IniciaCor();
    IniciaJanela(janela);
    IniciaDimensoes(altura, largura);
    IniciaOrientacao();
}

void CPIGSprite::ExtraiPixels()
{
    if (!surface)
    {
        return;
    }
    pixels = new PIGCor[surface->h * surface->w];

    Uint32 *pix32 = (Uint32 *) surface->pixels;
    for (int h = 0; h < surface->h; h++)
    {
        for (int w = 0; w < surface->w; w++)
        {
            SDL_GetRGBA(
                    (*pix32), surface->format, &(pixels[(h * surface->w) + w].r),
                    &(pixels[(h * surface->w) + w].g), &(pixels[(h * surface->w) + w].b),
                    &(pixels[(h * surface->w) + w].a));
            pix32++;
        }
    }
}

// Atributos relativos à coloração e textura do Sprite
void CPIGSprite::IniciaCor()
{
    coloracao = BRANCO;
    opacidade = 255; // totalmente opaco
    texture = NULL;
}

// Atributos relativos à janela do Sprite
void CPIGSprite::IniciaJanela(int janela)
{
    idJanela = janela;
    // altJanela = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAltura();
    renderer = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
}

// Atributos relativos ao tamanho do Sprite
void CPIGSprite::IniciaDimensoes(int altura, int largura)
{
    altOriginal = alt = altura;
    largOriginal = larg = largura;
}

// Atributos relativos à rotação do Sprite
void CPIGSprite::IniciaOrientacao()
{
    pos = {.x = 0, .y = 0};
    angulo = 0;
    pivoAbs = {.x = 0, .y = 1.0 * alt};
    pivoInteiro = {.x = 0, .y = alt};
    proporcaoPivo = {.x = 0, .y = 0};
    usaPivoRelativo = false;

    dest.x = pos.x;
    dest.y = altJanela - pos.y - alt;
    dest.h = alt;
    dest.w = larg;

    frames[0].x = frames[0].y = 0;
    frames[0].h = alt;
    frames[0].w = larg;

    flip = SDL_FLIP_NONE;
}


void CPIGSprite::AplicaTransicao(const PIGEstadoTransicao &estado)
{
    Move(estado.x, estado.y);
    if (estado.alt != alt || estado.larg != larg)
    {
        SetDimensoes(estado.alt, estado.larg);
    }
    if (estado.cor != BRANCO)
    {
        SetColoracao(estado.cor);
    }
    if (estado.opacidade != opacidade)
    {
        SetOpacidade(estado.opacidade);
    }
    if (estado.ang != angulo)
    {
        SetAngulo(estado.ang);
    }
}

void CPIGSprite::AtualizaTextura()
{
    if (this_thread::get_id() == PIG_MAIN_THREAD_ID)
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
        }
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        precisaAtualizar = false;
    }
}


int CPIGSprite::GetId() const
{
    return id;
}

// Construtor para arquivos de vídeo ou Componentes
CPIGSprite::CPIGSprite(int idSprite, int altura, int largura, const string &nomeArq, int janela)
    : altJanela(CPIGGerenciadorJanelas::GetJanela(janela)->GetAltura())
{
    id = idSprite;

    precisaAtualizar = true;
    nomeArquivo = nomeArq;
    surface = NULL;

    IniciaBase(altura, largura, janela);
    pixels = NULL;
}

// Construtor básico para leitura de imagens digitais
CPIGSprite::CPIGSprite(
        int idSprite, const string &nomeArq, int retiraFundo, const PIGCor *corFundo, int janela)
    : altJanela(CPIGGerenciadorJanelas::GetJanela(janela)->GetAltura())
{
    id = idSprite;

    precisaAtualizar = true;
    nomeArquivo = nomeArq;

    CarregaImagem(nomeArq);

    IniciaBase(surface->h, surface->w, janela);
    PreparaTextura(retiraFundo, corFundo);
    ExtraiPixels();
}

// Construtor para imagens provenientes do renderizador offscreen
CPIGSprite::CPIGSprite(
        int idSprite, PIGOffscreenRenderer offRender, int retiraFundo, const PIGCor *corFundo,
        int janela)
    : altJanela(CPIGGerenciadorJanelas::GetJanela(janela)->GetAltura())
{
    id = idSprite;

    precisaAtualizar = true;
    nomeArquivo = "";

    SDL_Surface *surface = offRender->GetSurface();

    surface = SDL_CreateRGBSurfaceWithFormatFrom(
            surface->pixels, surface->w, surface->h, offRender->GetDepth(), surface->pitch,
            surface->format->format);

    IniciaBase(surface->h, surface->w, janela);
    PreparaTextura(retiraFundo, corFundo);
    ExtraiPixels();
}

// Construtor para Sprite "copiado" de outro Sprite
CPIGSprite::CPIGSprite(
        int idSprite, const CPIGSprite *spriteBase, int retiraFundo, const PIGCor *corFundo,
        int janela)
    : altJanela(CPIGGerenciadorJanelas::GetJanela(janela)->GetAltura())
{
    id = idSprite;

    precisaAtualizar = true;

    CarregaImagem(spriteBase->nomeArquivo);

    IniciaBase(surface->h, surface->w, janela);
    PreparaTextura(retiraFundo, corFundo);
    ExtraiPixels();

    frameAtual = spriteBase->frameAtual;
    frames = spriteBase->frames;

    SetColoracao(spriteBase->coloracao);
    SetOpacidade(spriteBase->opacidade);
    CPIGSprite::SetAngulo(spriteBase->angulo);
    SetFlip(spriteBase->flip);
    CPIGSprite::SetDimensoes(spriteBase->alt, spriteBase->larg);

    usaPivoRelativo = spriteBase->usaPivoRelativo;
    if (usaPivoRelativo)
    {
        SetPivoProporcional(spriteBase->proporcaoPivo);
    }
    else
    {
        proporcaoPivo = spriteBase->proporcaoPivo;
        SetPivoAbsoluto(spriteBase->pivoAbs);
    }

    CPIGSprite::Move(spriteBase->pos.x, spriteBase->pos.y);

    if (spriteBase->automacao)
    {
        automacao = new CPIGAutomacao(id, spriteBase->automacao);
    }
    else
    {
        automacao = NULL;
    }
}

// Construtor para sprite "vazio", cuja imagem será gerada posteriormente
CPIGSprite::CPIGSprite(int janela)
    : altJanela(CPIGGerenciadorJanelas::GetJanela(janela)->GetAltura())
{
    id = -1;
    idJanela = janela;
    nomeArquivo = "";
    pivoAbs = {0, 1.0 * alt};
    pivoInteiro = {0, alt};
    proporcaoPivo = {0, 0};
    usaPivoRelativo = false;
    angulo = 0;
    flip = PIG_FLIP_NENHUM;
    texture = NULL;
    surface = NULL;
    frameAtual = 0;
    frames[0] = {0, 0, 0, 0};
    pos = {0, 0};
    pixels = NULL;
    automacao = NULL;
    // altJanela = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAltura();
    renderer = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
}

void CPIGSprite::PreparaTextura(int retiraFundo, const PIGCor *corFundo)
{
    if (!surface)
    {
        return;
    }
    if (retiraFundo)
    {
        Uint8 red, green, blue, alpha;
        if (corFundo != NULL)
        {
            red = corFundo->r;
            green = corFundo->g;
            blue = corFundo->b;
            alpha = corFundo->a;
        }
        else
        {
            Uint32 *pixel = (Uint32 *) surface->pixels;
            SDL_GetRGBA(*pixel, surface->format, &red, &green, &blue, &alpha);
        }

        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGBA(surface->format, red, green, blue, alpha));
    }
    else
    {
        SDL_SetColorKey(surface, SDL_FALSE, 0);
    }

    AtualizaTextura();
}

int CPIGSprite::RecebeFilho(CPIGSprite *filho, int fixo)
{
    filho->tipoFixo = fixo;
    filhos.push_back(filho);
    return 1;
}

int CPIGSprite::Retirafilho(const CPIGSprite *filho)
{
    for (unsigned int i = 0; i < filhos.size(); i++)
    {
        if (filhos[i] == filho)
        {
            filhos.erase(filhos.begin() + i);
            return 1;
        }
    }
    return 0;
}

void CPIGSprite::InsereTransicao(PIGTransicao t, PIGAutomacao automaExt)
{
    if (automaExt == NULL)
    {
        automaExt = automacao;
    }
    if (automaExt == NULL)
    {
        automaExt = new CPIGAutomacao(id);
    }
    automaExt->InsereTransicao(t);
}

void CPIGSprite::InsereTransicao(
        double tempo, const PIGEstadoTransicao &estado, PIGAutomacao automaExt)
{
    if (automaExt == NULL)
    {
        automaExt = automacao;
    }
    if (automaExt == NULL)
    {
        automaExt = new CPIGAutomacao(id);
    }
    automaExt->InsereTransicao(new CPIGTransicao(tempo, estado));
}

void CPIGSprite::LeTransicoes(const string &nomeArq, PIGAutomacao automaExt)
{
    int dx = 0, dy = 0, dAlt = 0, dLarg = 0, dOpa = 0;
    double dAng = 0, tempo = 0;
    PIGCor dCor = BRANCO;

    if (automaExt == NULL)
    {
        automaExt = automacao;
    }
    if (automaExt == NULL)
    {
        automaExt = new CPIGAutomacao(id);
    }
    // printf("arquivo %s\n",nomeArq.c_str());
    FILE *arq = fopen(nomeArq.c_str(), "r");
    // NOLINTNEXTLINE
    while (fscanf(arq, "%lf %d %d %d %d %lf %hhu %hhu %hhu %hhu %d\n", &tempo, &dx, &dy, &dAlt,
                  &dLarg, &dAng, &dCor.r, &dCor.g, &dCor.b, &dCor.a, &dOpa) > 0)
    {
        // printf("%f %d %d %d %d %f %d %d %d %d
        // %d\n",tempo,dx,dy,dAlt,dLarg,dAng,dCor.r,dCor.g,dCor.b,dCor.a,dOpa);
        automaExt->InsereTransicao(
                new CPIGTransicao(tempo, {dx, dy, dAlt, dLarg, dAng, dCor, dOpa}));
    }
    // NOLINTNEXTLINE
    fclose(arq);
}

void CPIGSprite::IniciaAutomacao(PIGAutomacao automaExt)
{
    if (automaExt == NULL)
    {
        automaExt = automacao;
    }
    if (automaExt)
    {
        automaExt->IniciaAutomacao(
                {(int) pos.x, (int) pos.y, alt, larg, angulo, coloracao, opacidade});
    }
}

void CPIGSprite::LimpaTransicoes(PIGAutomacao automaExt)
{
    if (automaExt == NULL)
    {
        automaExt = automacao;
    }
    if (automaExt)
    {
        automaExt->LimpaTransicoes();
    }
}

bool CPIGSprite::ExecutandoTransicao(PIGAutomacao automaExt)
{
    if (automaExt == NULL)
    {
        automaExt = automacao;
    }
    if (automaExt == NULL)
    {
        return NULL;
    }
    return automaExt->ExecutandoTransicao();
}

void CPIGSprite::TrataAutomacao(PIGAutomacao automaExt)
{
    if (automaExt == NULL)
    {
        automaExt = automacao;
    }
    if (automaExt)
    {
        PIGTransicao t = automaExt->GetTransicaoAtual();
        if (t)
        {
            AplicaTransicao(t->GetEstado());
        }
        automaExt->TrataAcao();
    }
}

void CPIGSprite::PausaAutomacao(PIGAutomacao automaExt)
{
    if (automaExt == NULL)
    {
        automaExt = automacao;
    }
    if (automaExt)
    {
        automaExt->PausaAutomacao();
    }
}

void CPIGSprite::DespausaAutomacao(PIGAutomacao automaExt)
{
    if (automaExt == NULL)
    {
        automaExt = automacao;
    }
    if (automaExt)
    {
        automaExt->DespausaAutomacao();
    }
}

void CPIGSprite::InsereAcao(
        double tempo, double repeticao, PIGFuncaoSimples acao, void *param, PIGAutomacao automaExt)
{
    if (automaExt == NULL)
    {
        automaExt = automacao;
    }
    if (automaExt == NULL)
    {
        automaExt = new CPIGAutomacao(id);
    }

    automaExt->InsereAcao(acao, tempo, repeticao, param);
}

void CPIGSprite::LimpaAcoes(PIGAutomacao automaExt)
{
    if (automaExt == NULL)
    {
        automaExt = automacao;
    }
    if (automaExt)
    {
        automaExt->LimpaAcoes();
    }
}

void CPIGSprite::DefineTipoTransicao(PIGTipoTransicao tipo, PIGAutomacao automaExt)
{
    if (automaExt == NULL)
    {
        automaExt = automacao;
    }
    if (automaExt)
    {
        automaExt->SetTipoTransicao(tipo);
    }
}

// Destrutor para todos os tipos de Sprites
CPIGSprite::~CPIGSprite()
{

    delete[] pixels;


    delete automacao;

    if (texture)
    {
        SDL_DestroyTexture(texture);
    }

    if (nomeArquivo.empty())
    {
        if (surface)
        {
            SDL_FreeSurface(surface);
        }
    }
    else
    {
#ifdef PIG_SHARE_BITMAP
        CPIGAssetLoader::FreeImage(nomeArquivo);
#else
        if (bitmap)
            SDL_FreeSurface(bitmap);
#endif
    }
}

int CPIGSprite::GetIdJanela() const
{
    return idJanela;
}

void CPIGSprite::DefineFrame(int idFrame, SDL_Rect r)
{
    frames[idFrame] = r;
}

void CPIGSprite::DefineFrames(const SDL_Rect *r, size_t count)
{
    for (size_t i = 0; i < count; ++i)
    {
        DefineFrame(i, r[i]);
    }
}

PIGPonto2D CPIGSprite::GetXY()
{
    return pos;
}

void CPIGSprite::SetColoracao(PIGCor cor)
{
    coloracao = cor;
    SDL_SetTextureColorMod(texture, cor.r, cor.g, cor.b);
}

PIGCor CPIGSprite::GetColoracao()
{
    return coloracao;
}

// NOLINTNEXTLINE
void CPIGSprite::Rotaciona(double px, double py, double graus)
{
    double cosseno = cos(graus * M_PI / 180.0);
    double seno = sin(graus * M_PI / 180.0);

    double dx = pos.x - px;
    double dy = pos.y - py;
    double nx = (cosseno * dx) - (seno * dy);
    double ny = (seno * dx) + (cosseno * dy);

    Move(nx + px, ny + py);

    SetAngulo(angulo + graus);
}

// NOLINTNEXTLINE
void CPIGSprite::SetAngulo(double a)
{
    double delta = a - angulo;
    angulo = a;
    double pivoRealX = pos.x + pivoAbs.x;
    double pivoRealY = pos.y + (alt - pivoAbs.y);

    for (auto &filho: filhos)
    {
        if (filho->tipoFixo == 0)
        {
            continue;
        }
        if (filho->tipoFixo == 1)
        {
            filho->Rotaciona(pivoRealX, pivoRealY, delta);
        }
        else
        { // tipoFixo==2
            double pivoFilhoX = filho->pivoAbs.x + filho->pos.x;
            double pivoFilhoY = filho->pos.y + filho->alt - filho->pivoAbs.y;
            filho->Rotaciona(pivoFilhoX, pivoFilhoY, delta);
            filho->Desloca(
                    -pivoFilhoX + pivoRealX,
                    -pivoFilhoY + pivoRealY); //-pivoFilhoY-(alt-filhos[i]->pivoRelativo.y));
            // printf("%f,%f\n",filhos[i]->pos.x,filhos[i]->pos.y);
        }
    }
}

double CPIGSprite::GetAngulo() const
{
    return angulo;
}

void CPIGSprite::SetFlip(PIGFlip valor)
{
    flip = valor;
}

PIGFlip CPIGSprite::GetFlip()
{
    return flip;
}

// Pivô relativo ao ponto (0,0) por meio de soma
void CPIGSprite::SetPivoAbsoluto(PIGPonto2D pivo)
{
    pivoAbs.x = pivo.x;
    pivoAbs.y = alt - pivo.y;
    pivoInteiro = {(int) pivoAbs.x, (int) pivoAbs.y};
    usaPivoRelativo = false;
}

// Pivo relativo ao ponto (0,0) por meio de multiplicação
void CPIGSprite::SetPivoProporcional(PIGPonto2D pivo)
{
    proporcaoPivo = pivo;
    pivoAbs.x = pivo.x * larg;
    pivoAbs.y = alt * pivo.y;
    pivoInteiro = {(int) pivoAbs.x, (int) (alt - pivoAbs.y)};
    usaPivoRelativo = true;
}

// recupera o ponto pivô
PIGPonto2D CPIGSprite::GetPivo()
{
    return pivoAbs;
}

void CPIGSprite::Move(double nx, double ny)
{
    Desloca(nx - pos.x, ny - pos.y);
}

// NOLINTNEXTLINE
void CPIGSprite::Desloca(double dx, double dy)
{
    pos.x += dx;
    pos.y += dy;
    dest.x = pos.x;
    dest.y = altJanela - alt - pos.y;
    for (auto &filho: filhos)
    {
        if (filho->tipoFixo != 0)
        {
            filho->Desloca(dx, dy);
        }
    }
}

void CPIGSprite::SetDimensoes(int altura, int largura)
{
    dest.h = alt = altura;
    dest.w = larg = largura;
    dest.x = pos.x;
    dest.y = altJanela - alt - pos.y;

    if (usaPivoRelativo)
    {
        SetPivoProporcional(proporcaoPivo);
    }
    else
    {
        SetPivoAbsoluto(pivoAbs);
    }
}

void CPIGSprite::GetDimensoes(int &altura, int &largura)
{
    altura = alt;
    largura = larg;
}

void CPIGSprite::GetDimensoesOriginais(int &altura, int &largura) const
{
    altura = altOriginal;
    largura = largOriginal;
}

void CPIGSprite::SetOpacidade(int valor)
{
    opacidade = valor;
    SDL_SetTextureAlphaMod(texture, valor);
}

void CPIGSprite::RestauraDimensoesOriginais()
{
    SetDimensoes(altOriginal, largOriginal);
}

int CPIGSprite::GetOpacidade() const
{
    return opacidade;
}

int CPIGSprite::MudaFrameAtual(int novoFrame)
{
    if (!frames.contains(novoFrame))
    {
        return 0;
    }
    frameAtual = novoFrame;
    dest.w = frames[frameAtual].w;
    dest.h = frames[frameAtual].h;
    alt = frames[frameAtual].h;
    larg = frames[frameAtual].w;
    return 1;
}

int CPIGSprite::GetFrameAtual() const
{
    return frameAtual;
}

void CPIGSprite::CarregaArquivoFrames(const string &nomeArq)
{
    int idFrame, xBitmap, yBitmap, altFrame, largFrame;
    FILE *arq = fopen(nomeArq.c_str(), "r");
    // NOLINTNEXTLINE
    while (fscanf(arq, "%d %d %d %d %d\n", &idFrame, &xBitmap, &yBitmap, &altFrame, &largFrame) ==
           5)
    {
        DefineFrame(idFrame, {xBitmap, yBitmap, largFrame, altFrame});
    }
    // NOLINTNEXTLINE
    fclose(arq);
}

void CPIGSprite::CriaFramesAutomaticosPorLinha(int idFrameInicial, int qtdLinhas, int qtdColunas)
{
    if (qtdLinhas <= 0 || qtdColunas <= 0)
    {
        return;
    }
    int largFrame = largOriginal / qtdColunas;
    int altFrame = altOriginal / qtdLinhas;
    for (int i = 0; i < qtdLinhas; i++)
    {
        for (int j = 0; j < qtdColunas; j++)
        {
            DefineFrame(idFrameInicial++, {j * largFrame, i * altFrame, largFrame, altFrame});
        }
    }
}

void CPIGSprite::CriaFramesAutomaticosPorColuna(int idFrameInicial, int qtdLinhas, int qtdColunas)
{
    if (qtdLinhas <= 0 || qtdColunas <= 0)
    {
        return;
    }
    int largFrame = largOriginal / qtdColunas;
    int altFrame = altOriginal / qtdLinhas;
    for (int j = 0; j < qtdColunas; j++)
    {
        for (int i = 0; i < qtdLinhas; i++)
        {
            DefineFrame(idFrameInicial++, {j * largFrame, i * altFrame, largFrame, altFrame});
        }
    }
}

// NOLINTNEXTLINE
int CPIGSprite::Desenha()
{
    dest.y = altJanela - alt - pos.y;
    SDL_Rect enquadrado = dest;
    // printf("%d,%d,%d,%d\n",dest.x,*altJanela-dest.y,dest.h,dest.w);
    // SDL_Point p = {pivoRelativo.x,pivoRelativo.y};
    CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaWorldScreen(
            enquadrado.x, enquadrado.y, enquadrado.x, enquadrado.y);
//
#if PIG_MULTITHREAD_TELAS == 1
    if (precisaAtualizar)
    { // criada!=PIG_MAIN_THREAD_ID){
        // printf("mandei atualizar...");
        AtualizaTextura();
        // printf("resultado: %d\n",precisaAtualizar);
    }
#endif

    SDL_RenderCopyEx(
            renderer, texture, &frames[frameAtual], &enquadrado, -angulo, &pivoInteiro, flip);
    // printf("%d %d\n",pivoInteiro.x,pivoInteiro.y);
    for (auto &filho: filhos)
    {
        filho->Desenha();
    }
    return 0;
}

// NOLINTNEXTLINE
void CPIGSprite::DesenhaOffScreen(PIGOffscreenRenderer offRender)
{
    SDL_Texture *textAux = SDL_CreateTextureFromSurface(offRender->GetRenderer(), surface);
    SDL_Rect rectAux = dest;
    rectAux.y = offRender->GetAltura() - alt - pos.y;
    SDL_RenderCopyEx(
            offRender->GetRenderer(), textAux, &frames[frameAtual], &rectAux, -angulo, &pivoInteiro,
            flip);
    SDL_DestroyTexture(textAux);
    for (auto &filho: filhos)
    {
        filho->DesenhaOffScreen(offRender);
    }
}

void CPIGSprite::AtualizaPixels(int retiraFundo, int opacidadeObj)
{
    if (!pixels)
    {
        return;
    }

    Uint32 *pix32 = (Uint32 *) surface->pixels;
    for (int h = 0; h < surface->h; h++)
    {
        for (int w = 0; w < surface->w; w++)
        {
            SDL_GetRGBA(
                    (*pix32), surface->format, &(pixels[(h * surface->w) + w].r),
                    &(pixels[(h * surface->w) + w].g), &(pixels[(h * surface->w) + w].b),
                    &(pixels[(h * surface->w) + w].a));
            pix32++;
        }
    }

    SetOpacidade(opacidadeObj);
    PreparaTextura(retiraFundo);
}

PIGCor *CPIGSprite::GetPixels()
{
    return pixels;
}

string CPIGSprite::GetNomeArquivo()
{
    return nomeArquivo;
}
