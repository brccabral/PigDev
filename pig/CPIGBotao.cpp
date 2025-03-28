#include <pig/CPIGBotao.h>
#include <pig/CPIGGerenciadorJanelas.h>

void CPIGBotao::ProcessaAtributos(const CPIGAtributos atrib)
{
    CPIGComponente::ProcessaAtributos(atrib);
}

void CPIGBotao::SetAcionado(const bool valor)
{
    if (acionado && !valor)
    {
        Desloca(-margemEsq, margemCima);
        // SetDimensoes(alt-(margemCima+margemBaixo),larg-(margemEsq+margemDir));
    }
    else if (!acionado && valor)
    {
        Desloca(margemEsq, -margemCima);
        // SetDimensoes(alt+(margemCima+margemBaixo),larg+(margemEsq+margemDir));
    }
    CPIGComponente::SetAcionado(valor);
    AjustaFrame();
}

void CPIGBotao::SetMouseOver(const bool valor)
{
    CPIGComponente::SetMouseOver(valor);
    AjustaFrame();
}

void CPIGBotao::SetHabilitado(const bool valor)
{
    CPIGComponente::SetHabilitado(valor);
    AjustaFrame();
}

CPIGBotao::CPIGBotao(
        const int idComponente, const int alt, const int larg, const string &nomeArq,
        const int retiraFundo, const int janela)
    : CPIGComponente(idComponente, alt, larg, nomeArq, retiraFundo, janela)
{
    tecla = PIG_TECLA_ENTER; // sem tecla de atalho
    CPIGComponente::SetPosicaoPadraoLabel(PIG_POSICAO_CENTRO_CENTRO);
}

CPIGBotao::CPIGBotao(const int idComponente, const int alt, const int larg, const int janela)
    : CPIGComponente(idComponente, alt, larg, janela)
{
    tecla = PIG_TECLA_ENTER; // sem tecla de atalho
    CPIGComponente::SetPosicaoPadraoLabel(PIG_POSICAO_CENTRO_CENTRO);
}

PIGEstadoEvento CPIGBotao::TrataEventoMouse(const PIGEvento evento)
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
            return OnAction();
        }
        return PIG_COMPONENTE_MOUSEOVER;
    }

    return PIG_COMPONENTE_NAOTRATADO;
}

PIGEstadoEvento CPIGBotao::TrataEventoTeclado(const PIGEvento evento)
{
    if (!habilitado)
    {
        return PIG_COMPONENTE_DESABILITADO;
    }
    if (!visivel)
    {
        return PIG_COMPONENTE_INVISIVEL;
    }

    if (evento.teclado.acao == PIG_TECLA_PRESSIONADA && evento.teclado.tecla == tecla)
    {
        return OnAction();
    }
    return PIG_COMPONENTE_NAOTRATADO;
}

void CPIGBotao::DefineAtalho(const int teclaAtalho)
{
    tecla = teclaAtalho;
}

int CPIGBotao::Desenha()
{
    if (!visivel)
    {
        return 0;
    }

    CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(pos.x, pos.y, alt, larg);

    if (imagemPropria)
    {
        CPIGComponente::Desenha();
    }
    else
    {
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(
                (int) pos.x, (int) pos.y, alt, larg, coresBasicas[0]);
    }

    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

    return CPIGComponente::Desenha();
}
