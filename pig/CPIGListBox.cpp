#include <pig/PIGFuncoesBasicas.h>
#include <pig/CPIGListBox.h>
#include <pig/CPIGGerenciadorJanelas.h>

void CPIGListBox::ProcessaAtributos(CPIGAtributos atrib)
{
    CPIGListaItemComponente::ProcessaAtributos(atrib);

    string valorStr = atrib.GetString("corDestaque", "");
    if (!valorStr.empty())
    {
        SetCorDestaque(PIGCriaCorString(valorStr));
    }
}

CPIGListBox CPIGListBox::LeParametros(int idComponente, CPIGAtributos atrib)
{
    CPIGListBox *resp;

    if (!atrib.GetString("nomeArq", "").empty())
    {
        resp = new CPIGListBox(
                idComponente, atrib.GetInt("largura", 0), atrib.GetInt("alturaLinha", 0),
                atrib.GetInt("alturaIcone", 0), atrib.GetInt("larguraIcone", 0),
                atrib.GetString("nomeArq", ""), atrib.GetInt("retiraFundo", 1),
                atrib.GetInt("janela", 0));
    }
    else
    {
        resp = new CPIGListBox(
                idComponente, atrib.GetInt("largura", 0), atrib.GetInt("alturaLinha", 0),
                atrib.GetInt("alturaIcone", 0), atrib.GetInt("larguraIcone", 0),
                atrib.GetInt("janela", 0));
    }

    resp->ProcessaAtributos(atrib);

    return *resp;
}

void CPIGListBox::DesenhaRetanguloMarcacao()
{
    if (itemDestaque != -1)
    {
        PIGPonto2D p = itens[itemDestaque]->GetXY();
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado(
                p.x, p.y, altBaseLista, larg - (margemDir + margemEsq), coresBasicas[1]);
    }
}

CPIGListBox::CPIGListBox(
        int idComponente, int larguraTotal, int alturaLinha, int alturaItem, int larguraItem,
        const string &nomeArqFundo, int retiraFundo, int janela)
    : CPIGListaItemComponente(
              idComponente, larguraTotal, alturaLinha, nomeArqFundo, retiraFundo, janela)
{
    itemDestaque = -1;
    tipo = PIG_LISTBOX;
}

CPIGListBox::CPIGListBox(
        int idComponente, int larguraTotal, int alturaLinha, int alturaItem, int larguraItem,
        int janela)
    : CPIGListaItemComponente(idComponente, larguraTotal, alturaLinha, janela)
{
    itemDestaque = -1;
    tipo = PIG_LISTBOX;
}

CPIGListBox::CPIGListBox(int idComponente, const CPIGAtributos &atrib)
    : CPIGListBox(LeParametros(idComponente, atrib))
{}

int CPIGListBox::GetItemDestaque() const
{
    return itemDestaque;
}

int CPIGListBox::SetAcionadoItem(int indice, bool valor)
{
    int resp = CPIGListaItemComponente::SetAcionadoApenasItem(indice, valor);
    if (resp)
    {
        itemDestaque = indice;
    }
    return resp;
}

PIGEstadoEvento CPIGListBox::TrataEventoTeclado(PIGEvento evento)
{
    if (!temFoco)
    {
        return PIG_COMPONENTE_SEMFOCO;
    }
    if (!habilitado)
    {
        return PIG_COMPONENTE_DESABILITADO;
    }
    if (!visivel)
    {
        return PIG_COMPONENTE_INVISIVEL;
    }

    if (evento.teclado.acao == PIG_TECLA_PRESSIONADA)
    {
        if (evento.teclado.tecla == PIG_TECLA_CIMA && evento.teclado.repeticao == 0)
        {
            itemDestaque--;
            if (itemDestaque < 0)
            {
                itemDestaque = itens.size() - 1;
            }
        }

        if (evento.teclado.tecla == PIG_TECLA_BAIXO && evento.teclado.repeticao == 0)
        {
            itemDestaque = (itemDestaque + 1) % itens.size();
        }
    }
    return PIG_COMPONENTE_TRATADO;
}

PIGEstadoEvento CPIGListBox::TrataEventoMouse(PIGEvento evento)
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

    if (ChecaMouseOver(GetPosicaoMouse()) > 0)
    {
        for (unsigned int i = 0; i < itens.size(); i++)
        {
            int aux = itens[i]->TrataEventoMouse(evento);
            if (aux == PIG_COMPONENTE_TRATADO)
            {
                if (itens[i]->GetAcionado())
                {
                    resp = i;
                }
                // SetHint(itens[i]->GetHint());
                // SetFonteHint(itens[i]->GetFonteHint());
                SetAcionadoApenasItem(resp, resp != -1);
                itemDestaque = resp;
                OnAction();
                break;
            }
        }
        if (resp > 0)
        {
            return PIG_COMPONENTE_TRATADO;
        }
        return PIG_COMPONENTE_MOUSEOVER;
        // SetAcionadoItem(resp,resp!=-1);
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

void CPIGListBox::CriaItem(
        const string &itemLabel, const string &arqImagemIcone, const string &arqImagemFundoItem,
        bool itemMarcado, bool itemHabilitado, const string &hintMsg, int retiraFundo,
        int retiraFundoIcone)
{
    CPIGListaItemComponente::SetDimensoes(
            alt + altBaseLista, larg); // aumenta o tamanho do componente para comportar o novo item
    DeslocaItens(0, altBaseLista); // desloca todos os itens para cima, pois o novo item vai entrar
                                   // abaixo dos outros

    int yItem = pos.y + margemBaixo;
    CPIGListaItemComponente::CriaItem(
            yItem, itemLabel, arqImagemIcone, arqImagemFundoItem, itemMarcado, itemHabilitado,
            hintMsg, retiraFundo, retiraFundoIcone);
}

void CPIGListBox::CriaItem(CPIGAtributos atrib)
{
    CPIGListaItemComponente::SetDimensoes(
            alt + altBaseLista, larg); // aumenta o tamanho do componente para comportar o novo item
    DeslocaItens(0, altBaseLista); // desloca todos os itens para cima, pois o novo item vai entrar
                                   // abaixo dos outros

    int yItem = pos.y + margemBaixo;
    CPIGListaItemComponente::CriaItem(
            yItem, atrib.GetString("label", ""), atrib.GetString("nomeArqIcone", ""),
            atrib.GetString("nomeArq", ""), false, atrib.GetInt("habilitado", 1),
            atrib.GetString("hint", ""), atrib.GetInt("retiraFundo", 1),
            atrib.GetInt("retiraFundoIcone", 1));
}

int CPIGListBox::Desenha()
{
    if (!visivel)
    {
        return 0;
    }

    CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(pos.x, pos.y, alt, larg);

    if (imagemPropria)
    { // se tiver imagem de fundo
        CPIGComponente::Desenha();
    }
    else
    {
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(
                (int) pos.x, (int) pos.y, alt, larg, coresBasicas[0]);
    }

    for (PIGItemComponente i: itens)
    {
        i->Desenha();
    }

    DesenhaRetanguloMarcacao();

    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

    return CPIGComponente::Desenha();
}

void CPIGListBox::SetCorDestaque(PIGCor cor)
{
    coresBasicas[1] = cor;
}

void CPIGListBox::SetDimensoes(int altura, int largura)
{
    CPIGComponente::SetDimensoes(itens.size() * altBaseLista, largura);

    for (PIGItemComponente i: itens)
    {
        i->SetDimensoes(altIcone, largura);
    }

    Move(pos.x, pos.y);
}

void CPIGListBox::SetMargens(int mEsq, int mDir, int mCima, int mBaixo)
{
    CPIGListaItemComponente::SetMargens(mEsq, mDir, mCima, mBaixo);
    alt = altBaseLista * itens.size() + margemBaixo + margemCima;
}
