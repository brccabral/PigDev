#include <pig/CPIGMouse.h>
#include <pig/CPIGGerenciadorJanelas.h>

PIGSprite CPIGMouse::cursores{};
SDL_Point CPIGMouse::pTela{}, CPIGMouse::pWorld{};
Uint8 CPIGMouse::botoes[PIG_MOUSE_X2 + 1]{};
Uint8 CPIGMouse::botoes_anterior[PIG_MOUSE_X2 + 1]{};

void CPIGMouse::Inicia(bool cursorCustomizado)
{
    SDL_ShowCursor(!cursorCustomizado);
    cursores = NULL;
}

void CPIGMouse::Encerra()
{
    delete cursores;
}

int CPIGMouse::GetEstadoBotaoDireito()
{
    return GetBotaoBaixo(PIG_MOUSE_DIREITO) ? SDL_MOUSEBUTTONDOWN : SDL_MOUSEBUTTONUP;
}

int CPIGMouse::GetEstadoBotaoCentral()
{
    return GetBotaoBaixo(PIG_MOUSE_CENTRAL) ? SDL_MOUSEBUTTONDOWN : SDL_MOUSEBUTTONUP;
}

int CPIGMouse::GetEstadoBotaoEsquerdo()
{
    return GetBotaoBaixo(PIG_MOUSE_ESQUERDO) ? SDL_MOUSEBUTTONDOWN : SDL_MOUSEBUTTONUP;
}

bool CPIGMouse::GetBotaoPressionado(int botao)
{
    switch (botao)
    {
        case PIG_MOUSE_DIREITO:
        case PIG_MOUSE_CENTRAL:
        case PIG_MOUSE_ESQUERDO:
        case PIG_MOUSE_X1:
        case PIG_MOUSE_X2:
            return botoes[botao] && botoes_anterior[botao] != botoes[botao];
        default:
            break;
    }
    return false;
}
bool CPIGMouse::GetBotaoLevantado(int botao)
{
    switch (botao)
    {
        case PIG_MOUSE_DIREITO:
        case PIG_MOUSE_CENTRAL:
        case PIG_MOUSE_ESQUERDO:
        case PIG_MOUSE_X1:
        case PIG_MOUSE_X2:
            return !botoes[botao] && botoes_anterior[botao] != botoes[botao];
        default:
            break;
    }
    return false;
}
bool CPIGMouse::GetBotaoBaixo(int botao)
{
    switch (botao)
    {
        case PIG_MOUSE_DIREITO:
        case PIG_MOUSE_CENTRAL:
        case PIG_MOUSE_ESQUERDO:
        case PIG_MOUSE_X1:
        case PIG_MOUSE_X2:
            return botoes[botao];
        default:
            break;
    }
    return false;
}
bool CPIGMouse::GetBotaoAlto(int botao)
{
    switch (botao)
    {
        case PIG_MOUSE_DIREITO:
        case PIG_MOUSE_CENTRAL:
        case PIG_MOUSE_ESQUERDO:
        case PIG_MOUSE_X1:
        case PIG_MOUSE_X2:
            return !botoes[botao];
        default:
            break;
    }
    return false;
}

void CPIGMouse::PegaXYTela(int &x, int &y)
{
    x = pTela.x;
    y = pTela.y;
}

SDL_Point CPIGMouse::PegaXYWorld()
{
    return pWorld;
}

SDL_Point CPIGMouse::PegaXYTela()
{
    return pTela;
}

int CPIGMouse::ProcessaEvento(PIGEvento &evento)
{
    if (evento.tipoEvento != PIG_EVENTO_MOUSE)
    {
        return 0;
    }
    if (evento.mouse.acao == PIG_MOUSE_PRESSIONADO || evento.mouse.acao == PIG_MOUSE_LIBERADO)
    {
        switch (evento.mouse.botao)
        {
            case PIG_MOUSE_DIREITO:
            case PIG_MOUSE_CENTRAL:
            case PIG_MOUSE_ESQUERDO:
            case PIG_MOUSE_X1:
            case PIG_MOUSE_X2:
                botoes_anterior[evento.mouse.botao] = botoes[evento.mouse.botao];
                botoes[evento.mouse.botao] = evento.mouse.acao == PIG_MOUSE_PRESSIONADO ? 1 : 0;
                break;
            default:
                break;
        }
    }
    else if (evento.mouse.acao == PIG_MOUSE_MOVIDO)
    {
        Move(evento.mouse.posX, evento.mouse.posY);
    }
    CPIGGerenciadorJanelas::GetJanela(evento.mouse.numeroJanela)
            ->ConverteCoordenadaScreenWorld(pTela.x, pTela.y, pWorld.x, pWorld.y);
    evento.mouse.worldX = pWorld.x;
    evento.mouse.worldY = pWorld.y;
    return 1;
}

int CPIGMouse::GetEstadoBotao(int botao)
{
    switch (botao)
    {
        case PIG_MOUSE_DIREITO:
        case PIG_MOUSE_CENTRAL:
        case PIG_MOUSE_ESQUERDO:
        case PIG_MOUSE_X1:
        case PIG_MOUSE_X2:
            return botoes[botao];
        default:
            break;
    }
    return 0;
}

int CPIGMouse::MudaCursor(int indice)
{
    if (cursores)
    {
        return cursores->MudaFrameAtual(indice);
    }
    return 0;
}

void CPIGMouse::Desenha(int idJanela)
{
    if (cursores)
    {
        cursores->Desenha();
    }
}

void CPIGMouse::Move(int x, int y)
{
    pTela.x = x;
    pTela.y = y;
    if (cursores)
    {
        cursores->Move(x, y - 32);
    }
}

void CPIGMouse::CarregaCursor(const string &nomeArquivo, int idJanela)
{
    delete cursores;
    cursores = new CPIGSprite(-1, nomeArquivo, idJanela);
    cursores->SetDimensoes(32, 32);
}

void CPIGMouse::CarregaFramesPorColuna(int frameInicial, int qtdLinhas, int qtdColunas)
{
    if (cursores)
    {
        cursores->CriaFramesAutomaticosPorColuna(frameInicial, qtdLinhas, qtdColunas);
    }
}

void CPIGMouse::CarregaFramesPorLinha(int frameInicial, int qtdLinhas, int qtdColunas)
{
    if (cursores)
    {
        cursores->CriaFramesAutomaticosPorLinha(frameInicial, qtdLinhas, qtdColunas);
    }
}

void CPIGMouse::CriaFrameCursor(int idFrame, int x, int y, int alt, int larg)
{
    if (cursores)
    {
        cursores->DefineFrame(idFrame, {x, y, larg, alt});
    }
}

void CPIGMouse::AtualizaEstadoAnterior()
{
    memcpy(botoes_anterior, botoes, (PIG_MOUSE_X2 + 1) * sizeof(Uint8));
}
