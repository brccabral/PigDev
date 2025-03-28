#include <pig/CPIGDropDown.h>
#include <pig/CPIGGerenciadorJanelas.h>

void CPIGDropDown::ProcessaAtributos(CPIGAtributos atrib)
{
    CPIGListaItemComponente::ProcessaAtributos(atrib);
}

CPIGDropDown CPIGDropDown::LeParametros(int idComponente, CPIGAtributos atrib)
{
    CPIGDropDown *resp;

    if (!atrib.GetString("nomeArq", "").empty())
    {
        resp = new CPIGDropDown(
                idComponente, atrib.GetInt("largura", 0), atrib.GetInt("alturaLinha", 0),
                atrib.GetInt("alturaIcone", 0), atrib.GetInt("larguraIcone", 0),
                atrib.GetString("nomeArq", ""), atrib.GetInt("retiraFundo", 1),
                atrib.GetInt("janela", 0));
    }
    else
    {
        resp = new CPIGDropDown(
                idComponente, atrib.GetInt("largura", 0), atrib.GetInt("alturaLinha", 0),
                atrib.GetInt("alturaIcone", 0), atrib.GetInt("larguraIcone", 0),
                atrib.GetInt("janela", 0));
    }

    resp->ProcessaAtributos(atrib);

    return *resp;
}

void CPIGDropDown::SetFoco(bool valor)
{
    temFoco = valor;
    if (!temFoco)
    {
        SetRecolhida(true);
    }
}

void CPIGDropDown::SetRecolhida(bool valor)
{
    recolhida = valor;
}

int CPIGDropDown::ChecaMouseOver(SDL_Point pMouse)
{
    SDL_Rect r = {(int) pos.x, (int) pos.y, larg, altBaseLista};
    if (!recolhida)
    {
        r.y -= altBaseLista * itens.size();
        r.h += itens.size() * altBaseLista;
    }
    SetMouseOver(SDL_PointInRect(&pMouse, &r));

    return mouseOver;
}

void CPIGDropDown::DesenhaItemDestaque()
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(
            (int) pos.x, ((int) pos.y), altBaseLista + margemBaixo + margemCima, larg);
    if (imagemPropria)
    { // se tiver imagem de fundo
        dest.h = altBaseLista + margemBaixo + margemCima;
        CPIGComponente::Desenha();
    }
    else
    {
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(
                (int) pos.x, (int) pos.y, altBaseLista, larg, coresBasicas[0]);
    }

    if (itemDestaque >= 0)
    { // desenha o item no cabeçalho do dropdown
        PIGPonto2D pItem = itens[itemDestaque]->GetXY();
        itens[itemDestaque]->Move(
                pItem.x, pos.y + margemBaixo); // move o item para o ponto do cabeçalho
        // printf("%.0f, %0.f\n",pItem.x,pos.y);
        itens[itemDestaque]->Desenha(); // desenha o item no cabeçalho
        itens[itemDestaque]->Move(
                pItem.x,
                pItem.y); // devolve o item para a posiçăo normal (onde também deverá ser desenhado)
    }
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();
}

void CPIGDropDown::DesenhaListaItens()
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(
            (int) pos.x, ((int) pos.y) - ((itens.size()) * altBaseLista),
            ((itens.size() + 1) * altBaseLista) + margemBaixo + margemCima, larg);
    if (imagemPropria)
    {
        frameAtual = 0;
        dest.y = altJanela - pos.y - altBaseLista;
        dest.h = (itens.size() + 1) * altBaseLista + margemBaixo + margemCima;
        CPIGComponente::Desenha();
    }
    else
    {
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(
                (int) pos.x, (int) pos.y - (altBaseLista * itens.size()),
                (itens.size() + 1) * altBaseLista, larg, coresBasicas[0]);
    }

    for (PIGItemComponente i: itens)
    {
        i->Desenha();
    }

    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();
}

CPIGDropDown::CPIGDropDown(
        int idComponente, int larguraTotal, int alturaLinha, int alturaItem, int larguraItem,
        const string &nomeArqFundo, int retiraFundo, int janela)
    : CPIGListaItemComponente(
              idComponente, larguraTotal, alturaLinha, nomeArqFundo, retiraFundo, janela)
{
    SetRecolhida(true);
    itemDestaque = -1;
    tipo = PIG_DROPDOWN;
}

CPIGDropDown::CPIGDropDown(
        int idComponente, int larguraTotal, int alturaLinha, int alturaItem, int larguraItem,
        int janela)
    : CPIGListaItemComponente(idComponente, larguraTotal, alturaLinha, janela)
{
    SetRecolhida(true);
    itemDestaque = -1;
    tipo = PIG_DROPDOWN;
}

CPIGDropDown::CPIGDropDown(int idComponente, const CPIGAtributos &atrib)
    : CPIGDropDown(LeParametros(idComponente, atrib))
{}

int CPIGDropDown::GetItemDestaque() const
{
    return itemDestaque;
}

int CPIGDropDown::SetAcionadoItem(int indice, bool valor)
{
    int resp = CPIGListaItemComponente::SetAcionadoApenasItem(indice, valor);
    if (resp)
    {
        itemDestaque = indice;
    }
    return resp;
}

void CPIGDropDown::CriaItem(
        const string &itemLabel, const string &arqImagemIcone, const string &arqImagemFundoItem,
        bool itemHabilitado, const string &hintMsg, int retiraFundo, int retiraFundoIcone)
{

    int yItem = pos.y - (altBaseLista * (itens.size() + 1)) + margemBaixo;
    CPIGListaItemComponente::CriaItem(
            yItem, itemLabel, arqImagemIcone, arqImagemFundoItem, false, itemHabilitado, hintMsg,
            retiraFundo, retiraFundoIcone);

    if (recolhida)
    {
        SetDimensoes(altBaseLista + margemBaixo + margemCima, larg);
    }
    else
    {
        SetDimensoes((altBaseLista * (itens.size() + 1)) + margemBaixo + margemCima, larg);
    }
}

void CPIGDropDown::CriaItem(CPIGAtributos atrib)
{

    int yItem = pos.y - (altBaseLista * (itens.size() + 1)) + margemBaixo;
    CPIGListaItemComponente::CriaItem(
            yItem, atrib.GetString("label", ""), atrib.GetString("nomeArqIcone", ""),
            atrib.GetString("nomeArq", ""), false, atrib.GetInt("habilitado", 1),
            atrib.GetString("hint", ""), atrib.GetInt("retiraFundo", 1),
            atrib.GetInt("retiraFundoIcone", 1));

    if (recolhida)
    {
        SetDimensoes(altBaseLista + margemBaixo + margemCima, larg);
    }
    else
    {
        SetDimensoes((altBaseLista * (itens.size() + 1)) + margemBaixo + margemCima, larg);
    }
}

int CPIGDropDown::Desenha()
{
    if (!visivel)
    {
        return 0;
    }

    if (recolhida)
    {
        DesenhaItemDestaque();
    }
    else
    {
        DesenhaListaItens();
    }

    return CPIGComponente::Desenha();
}

PIGEstadoEvento CPIGDropDown::TrataEventoMouse(PIGEvento evento)
{
    if (!habilitado)
    {
        return PIG_COMPONENTE_DESABILITADO;
    }
    if (!visivel)
    {
        return PIG_COMPONENTE_INVISIVEL;
    }

    int resp = itemDestaque;
    bool mouseOverAntes = mouseOver;
    SDL_Point p = GetPosicaoMouse();

    if (ChecaMouseOver(p))
    {

        if (!recolhida)
        { // se o dropdown está exibindo os itens, é preciso tratá-los individualmente
            for (unsigned int i = 0; i < itens.size(); i++)
            {
                if (itens[i]->TrataEventoMouse(evento) == PIG_COMPONENTE_TRATADO)
                {
                    if (itens[i]->GetAcionado())
                    {
                        resp = i;
                    }

                    SetAcionadoApenasItem(resp, resp != -1);
                    itemDestaque = resp;
                    OnAction();
                    break;
                }
            }

            if (evento.mouse.acao == PIG_MOUSE_PRESSIONADO &&
                evento.mouse.botao == PIG_MOUSE_ESQUERDO)
            {
                SetRecolhida(!recolhida);
            }

            if (resp >= 0)
            {
                return PIG_COMPONENTE_TRATADO;
            }
            return PIG_COMPONENTE_MOUSEOVER;
        }
        if (evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO)
        {
            SetRecolhida(!recolhida);
            return PIG_COMPONENTE_TRATADO;
        }
    }
    else if (mouseOverAntes)
    { // mouse estava antes, mas saiu
        for (PIGItemComponente i: itens)
        {
            i->SetMouseOver(false);
        }
    }

    return PIG_COMPONENTE_NAOTRATADO;
}


void CPIGDropDown::SetMargens(int mEsq, int mDir, int mCima, int mBaixo)
{
    CPIGListaItemComponente::SetMargens(mEsq, mDir, mCima, mBaixo);
    if (recolhida)
    {
        alt = altBaseLista + margemBaixo + margemCima;
    }
    else
    {
        alt = altBaseLista * (itens.size() + 1) + margemBaixo + margemCima;
    }
}
