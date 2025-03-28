#include <pig/CPIGItemComponente.h>
#include <pig/CPIGGerenciadorAudios.h>
#include <pig/CPIGGerenciadorJanelas.h>

PIGEstadoEvento CPIGItemComponente::OnMouseClick()
{
    SetAcionado(!GetAcionado());
#ifdef PIGCOMAUDIO
    if (audioComponente >= 0)
    {
        CPIGGerenciadorAudios::Play(audioComponente);
    }
#endif
    return PIG_COMPONENTE_TRATADO;
}

void CPIGItemComponente::IniciaBase(
        const string &labelItem, const string &arqImagemIcone, int alturaIcone, int larguraIcone,
        int retiraFundoIcone)
{
    altIcone = alturaIcone;
    largIcone = larguraIcone;
    if (!arqImagemIcone.empty())
    {
        icone = new CPIGSprite(-1, arqImagemIcone, retiraFundoIcone, NULL, idJanela);
        icone->SetDimensoes(altIcone, largIcone);
        AlinhaIcone(PIG_POSICAO_ESQ_CENTRO);
    }
    else
    {
        icone = NULL;
    }
    SetLabel(labelItem);
    posRelativaLabel = PIG_POSICAO_ESQ_CENTRO;
    SetPosicaoPadraoLabel(PIG_POSICAO_ESQ_CENTRO);
    AjustaFrame = NULL;
    coresBasicas[0] = {0, 0, 0, 0};
    habilitadoPorSi = true;
    tipo = PIG_ITEMCOMPONENTE;
}

// item com icone e com fundo
CPIGItemComponente::CPIGItemComponente(
        int idComponente, int alturaIcone, int larguraIcone, const string &arqImagemIcone,
        const string &arqImagemFundo, const string &labelItem, int larguraLista,
        int alturaItemLista, int retiraFundo, int retiraFundoIcone, int janela)
    : CPIGComponente(
              idComponente, alturaItemLista, larguraLista, arqImagemFundo, retiraFundo, janela)
{
    IniciaBase(labelItem, arqImagemIcone, alturaIcone, larguraIcone, retiraFundoIcone);
}

// item com icone e sem fundo
CPIGItemComponente::CPIGItemComponente(
        int idComponente, int alturaIcone, int larguraIcone, const string &arqImagemIcone,
        const string &labelItem, int larguraLista, int alturaItemLista, int retiraFundoIcone,
        int janela)
    : CPIGComponente(idComponente, alturaItemLista, larguraLista, janela)
{
    IniciaBase(labelItem, arqImagemIcone, alturaIcone, larguraIcone, retiraFundoIcone);
}

// item sem icone e com fundo
CPIGItemComponente::CPIGItemComponente(
        int idComponente, const string &arqImagemFundo, const string &labelItem, int larguraLista,
        int alturaItemLista, int retiraFundo, int janela)
    : CPIGComponente(
              idComponente, alturaItemLista, larguraLista, arqImagemFundo, retiraFundo, janela)
{
    IniciaBase(labelItem, "", 0, 0);
}

// item sem icone e sem fundo
CPIGItemComponente::CPIGItemComponente(
        int idComponente, const string &labelItem, int larguraLista, int alturaItemLista,
        int retiraFundo, int janela)
    : CPIGComponente(idComponente, alturaItemLista, larguraLista, janela)
{
    IniciaBase(labelItem, "", 0, 0);
}

CPIGItemComponente::~CPIGItemComponente()
{
    delete icone;
}

void CPIGItemComponente::SetAcionado(bool valor)
{
    CPIGComponente::SetAcionado(valor);
    if (AjustaFrame)
    {
        AjustaFrame(this);
    }
}

void CPIGItemComponente::SetHabilitado(bool valor)
{
    habilitadoPorSi = valor;
    CPIGComponente::SetHabilitado(valor);
    if (AjustaFrame)
    {
        AjustaFrame(this);
    }
}

void CPIGItemComponente::SetHabilitadoLista(bool valor)
{
    if (valor)
    {
        CPIGComponente::SetHabilitado(habilitadoPorSi);
    }
    else
    {
        habilitadoPorSi = habilitado;
        CPIGComponente::SetHabilitado(valor);
    }
    if (AjustaFrame)
    {
        AjustaFrame(this);
    }
}

void CPIGItemComponente::SetMouseOver(bool valor)
{
    CPIGComponente::SetMouseOver(valor);
    if (AjustaFrame)
    {
        AjustaFrame(this);
    }
}

void CPIGItemComponente::DefineFuncaoAjusteFrame(void (*funcao)(CPIGItemComponente *))
{
    AjustaFrame = funcao;
    if (AjustaFrame)
    {
        AjustaFrame(this);
    }
}

int CPIGItemComponente::Desenha()
{
    if (!visivel)
    {
        return 0;
    }

    // fundo
    if (imagemPropria)
    {
        CPIGComponente::Desenha();
    }
    else
    {
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(
                (int) pos.x, (int) pos.y, alt, larg, coresBasicas[0]);
    }

    if (icone)
    {
        icone->Desenha();
    }
    // CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado((int)pos.x,(int)pos.y,alt,larg,AMARELO);

    return CPIGComponente::Desenha();
}

void CPIGItemComponente::SetDimensoesIcone(int alturaIcone, int larguraIcone)
{
    altIcone = alturaIcone;
    largIcone = larguraIcone;
    icone->SetDimensoes(altIcone, largIcone);
}

void CPIGItemComponente::AlinhaLabel(PIGPosicaoComponente valor)
{
    posRelativaLabel = valor;
    int largLabel = lab->GetLargura();
    if (icone && (valor == PIG_POSICAO_DIR_CENTRO || valor == PIG_POSICAO_CENTRO_CENTRO ||
                  valor == PIG_POSICAO_ESQ_CENTRO))
    {
        switch (posRelativaLabel)
        {
            case PIG_POSICAO_ESQ_CENTRO:
                if (posIcone == PIG_POSICAO_ESQ_CENTRO)
                {
                    SetPosicaoPersonalizadaLabel(largIcone + margemEsq, 0);
                }
                else
                {
                    SetPosicaoPersonalizadaLabel(margemEsq, 0);
                }
                break;
            case PIG_POSICAO_CENTRO_CENTRO:
                if (posIcone == PIG_POSICAO_ESQ_CENTRO)
                {
                    SetPosicaoPersonalizadaLabel(
                            margemEsq + largIcone +
                                    ((larg - largIcone - margemEsq - margemDir) / 2) -
                                    (largLabel / 2),
                            0);
                }
                else
                {
                    SetPosicaoPersonalizadaLabel(
                            margemDir + ((larg - largIcone - margemEsq - margemDir) / 2) -
                                    (largLabel / 2),
                            0);
                }
                break;
            case PIG_POSICAO_DIR_CENTRO:
                if (posIcone == PIG_POSICAO_ESQ_CENTRO)
                {
                    SetPosicaoPersonalizadaLabel(larg - largLabel - margemDir, 0);
                }
                else
                {
                    SetPosicaoPersonalizadaLabel(larg - largLabel - largIcone - margemDir, 0);
                }
                break;
            default:
                break;
        }
    }
    else
    {
        switch (posRelativaLabel)
        {
            case PIG_POSICAO_ESQ_CENTRO:
                SetPosicaoPersonalizadaLabel(margemEsq, 0);
                break;
            case PIG_POSICAO_CENTRO_CENTRO:
                SetPosicaoPersonalizadaLabel(
                        margemEsq + ((larg - margemEsq - margemDir) / 2) - (largLabel / 2), 0);
                break;
            case PIG_POSICAO_DIR_CENTRO:
                SetPosicaoPersonalizadaLabel(larg - largLabel - margemDir, 0);
                break;
            default:
                break;
        }
    }
}

void CPIGItemComponente::AlinhaIcone(PIGPosicaoComponente valor)
{
    if (icone && (valor == PIG_POSICAO_DIR_CENTRO || valor == PIG_POSICAO_ESQ_CENTRO))
    {
        posIcone = valor;
        if (valor == PIG_POSICAO_DIR_CENTRO)
        {
            icone->Move(pos.x + larg - largIcone - margemDir, pos.y);
        }
        else
        {
            icone->Move(pos.x + margemEsq, pos.y);
        }
        AlinhaLabel(posRelativaLabel);
    }
}

// define a posiçăo do label (dentre posiçőes pré-estabelecidas)
void CPIGItemComponente::SetPosicaoPadraoLabel(PIGPosicaoComponente pos)
{
    AlinhaLabel(pos);
}

PIGEstadoEvento CPIGItemComponente::TrataEventoMouse(PIGEvento evento)
{
    if (!habilitado)
    {
        return PIG_COMPONENTE_DESABILITADO;
    }
    if (!visivel)
    {
        return PIG_COMPONENTE_INVISIVEL;
    }

    ChecaMouseOver(GetPosicaoMouse());

    if (mouseOver)
    {
        if (evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO)
        {
            return OnMouseClick();
        }
        return PIG_COMPONENTE_MOUSEOVER;
    }

    return PIG_COMPONENTE_NAOTRATADO;
}

void CPIGItemComponente::Move(double nx, double ny)
{
    int dx = nx - pos.x;
    int dy = ny - pos.y;
    Desloca(dx, dy);
    SetPosicaoPadraoLabel(posLabel);
}

void CPIGItemComponente::Desloca(double dx, double dy)
{
    CPIGComponente::Desloca(dx, dy);
    if (icone)
    {
        icone->Desloca(dx, dy);
    }
    lab->Desloca(dx, dy);
}

PIGSprite CPIGItemComponente::GetIcone()
{
    return icone;
}

void CPIGItemComponente::SetCorFundo(PIGCor cor)
{
    coresBasicas[0] = cor;
}
