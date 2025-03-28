#include <pig/CPIGBotaoClick.h>
#include <pig/CPIGMouse.h>
#include <pig/PIGFuncoesBasicas.h>


void CPIGBotaoClick::IniciaCoresBasicas()
{
    coresBasicas[0] = coresBasicas[1] = AZUL;
    coresBasicas[2] = PIGCor{100, 100, 255, 255};
    coresBasicas[3] = AMARELO;
    coresBasicas[4] = CINZA;
}

void CPIGBotaoClick::ProcessaAtributos(CPIGAtributos atrib)
{
    CPIGBotao::ProcessaAtributos(atrib);

    float valorFloat = atrib.GetFloat("tempoRepeticao", -1);
    if (valorFloat > 0)
    {
        DefineTempoRepeticao(valorFloat);
    }

    valorFloat = atrib.GetFloat("tempoAcionamento", -1);
    if (valorFloat > 0)
    {
        DefineTempoAcionamento(valorFloat);
    }

    string valorStr = atrib.GetString("corNormal", "");
    if (!valorStr.empty())
    {
        SetCorNormal(PIGCriaCorString(valorStr));
    }

    valorStr = atrib.GetString("corMouseSobre", "");
    if (!valorStr.empty())
    {
        SetCorMouseSobre(PIGCriaCorString(valorStr));
    }

    valorStr = atrib.GetString("corAcionado", "");
    if (!valorStr.empty())
    {
        SetCorAcionado(PIGCriaCorString(valorStr));
    }

    valorStr = atrib.GetString("corDesabilitado", "");
    if (!valorStr.empty())
    {
        SetCorDesabilitado(PIGCriaCorString(valorStr));
    }
}

CPIGBotaoClick CPIGBotaoClick::LeParametros(const int idComponente, CPIGAtributos atrib)
{
    CPIGBotaoClick *resp;

    if (!atrib.GetString("nomeArq", "").empty())
    {
        resp = new CPIGBotaoClick(
                idComponente, atrib.GetInt("altura", 0), atrib.GetInt("largura", 0),
                atrib.GetString("nomeArq", ""), atrib.GetInt("retiraFundo", 1),
                atrib.GetInt("janela", 0));
    }
    else
    {
        resp = new CPIGBotaoClick(
                idComponente, atrib.GetInt("altura", 0), atrib.GetInt("largura", 0),
                atrib.GetInt("janela", 0));
    }

    resp->ProcessaAtributos(atrib);

    return *resp;
}

void CPIGBotaoClick::AjustaFrame()
{
    if (!visivel)
    {
        return;
    }
    int corAtual = 1;
    if (!habilitado)
    {
        corAtual = 4;
    }
    else
    {
        if (acionado)
        {
            corAtual = 3;
        }
        else if (mouseOver)
        {
            corAtual = 2;
        }
    }

    coresBasicas[0] = coresBasicas[corAtual];
    if (texture)
    {
        MudaFrameAtual(corAtual);
    }
}

void CPIGBotaoClick::TrataTimer()
{
    double tempo = timer->GetTempoDecorrido();
    if (tempo >= tempoRepeticao)
    {
        if (tempoRepeticao > 0 && mouseOver &&
            CPIGMouse::GetEstadoBotaoEsquerdo() == PIG_MOUSE_PRESSIONADO)
        {
            OnAction();
        }
    }
    else if (tempo > tempoAcionamento)
    {
        SetAcionado(false);
    }
}

PIGEstadoEvento CPIGBotaoClick::OnAction()
{
    if (timer->GetTempoDecorrido() > tempoRepeticao)
    {
        SetAcionado(true);
        timer->Reinicia(false);
    }
    return CPIGComponente::OnAction();
}

void CPIGBotaoClick::IniciaBase()
{
    tempoRepeticao = 0.5;
    tempoAcionamento = 0.2;
    timer = new CPIGTimer(false);
    tipo = PIG_BOTAOCLICK;
}

CPIGBotaoClick::CPIGBotaoClick(
        const int idComponente, const int alt, const int larg, const string &nomeArq,
        const int retiraFundo, const int janela)
    : CPIGBotao(idComponente, alt, larg, nomeArq, retiraFundo, janela)
{
    CriaFramesAutomaticosPorLinha(1, 1, 4);
    MudaFrameAtual(1); // frame de estado normal do botao
    IniciaBase();
}

CPIGBotaoClick::CPIGBotaoClick(
        const int idComponente, const int alt, const int larg, const int janela)
    : CPIGBotao(idComponente, alt, larg, janela)
{
    IniciaCoresBasicas();
    IniciaBase();
}

CPIGBotaoClick::CPIGBotaoClick(const int idComponente, const CPIGAtributos &atrib)
    : CPIGBotaoClick(LeParametros(idComponente, atrib))
{}

CPIGBotaoClick::~CPIGBotaoClick()
{
    delete timer;
}

void CPIGBotaoClick::DefineTempoRepeticao(const double segundos)
{
    tempoRepeticao = segundos;
}

void CPIGBotaoClick::DefineTempoAcionamento(const double segundos)
{
    tempoAcionamento = segundos;
}

int CPIGBotaoClick::Desenha()
{
    TrataTimer();
    return CPIGBotao::Desenha();
}

void CPIGBotaoClick::SetCorNormal(const PIGCor cor)
{
    coresBasicas[1] = cor;
}

void CPIGBotaoClick::SetCorMouseSobre(const PIGCor cor)
{
    coresBasicas[2] = cor;
}

void CPIGBotaoClick::SetCorAcionado(const PIGCor cor)
{
    coresBasicas[3] = cor;
}

void CPIGBotaoClick::SetCorDesabilitado(const PIGCor cor)
{
    coresBasicas[4] = cor;
}
