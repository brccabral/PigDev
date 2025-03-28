#include <pig/PIGFuncoesBasicas.h>
#include <pig/CPIGBotaoOnOff.h>

void CPIGBotaoOnOff::IniciaCoresBasicas()
{
    coresBasicas[0] = coresBasicas[1] = VERDE;
    coresBasicas[2] = {100, 255, 100, 255};
    coresBasicas[3] = CINZA;
    coresBasicas[4] = VERMELHO;
    coresBasicas[5] = {255, 100, 100, 255};
    coresBasicas[6] = {160, 160, 160, 255};
}

void CPIGBotaoOnOff::ProcessaAtributos(CPIGAtributos atrib)
{
    CPIGBotao::ProcessaAtributos(atrib);

    string valorStr = atrib.GetString("corNormalOff", "");
    if (!valorStr.empty())
    {
        SetCorNormalOff(PIGCriaCorString(valorStr));
    }

    valorStr = atrib.GetString("corMouseSobreOff", "");
    if (!valorStr.empty())
    {
        SetCorMouseSobreOff(PIGCriaCorString(valorStr));
    }

    valorStr = atrib.GetString("corDesabilitadoOff", "");
    if (!valorStr.empty())
    {
        SetCorDesabilitadoOff(PIGCriaCorString(valorStr));
    }

    valorStr = atrib.GetString("corNormalOn", "");
    if (!valorStr.empty())
    {
        SetCorNormalOn(PIGCriaCorString(valorStr));
    }

    valorStr = atrib.GetString("corMouseSobreOn", "");
    if (!valorStr.empty())
    {
        SetCorMouseSobreOn(PIGCriaCorString(valorStr));
    }

    valorStr = atrib.GetString("corDesabilitadoOn", "");
    if (!valorStr.empty())
    {
        SetCorDesabilitadoOn(PIGCriaCorString(valorStr));
    }
}

CPIGBotaoOnOff CPIGBotaoOnOff::LeParametros(int idComponente, CPIGAtributos atrib)
{
    CPIGBotaoOnOff *resp;

    if (!atrib.GetString("nomeArq", "").empty())
    {
        resp = new CPIGBotaoOnOff(
                idComponente, atrib.GetInt("altura", 0), atrib.GetInt("largura", 0),
                atrib.GetString("nomeArq", ""), atrib.GetInt("retiraFundo", 1),
                atrib.GetInt("janela", 0));
    }
    else
    {
        resp = new CPIGBotaoOnOff(
                idComponente, atrib.GetInt("altura", 0), atrib.GetInt("largura", 0),
                atrib.GetInt("janela", 0));
    }

    resp->ProcessaAtributos(atrib);

    return *resp;
}

void CPIGBotaoOnOff::AjustaFrame()
{
    int corAtual;
    if (acionado)
    {
        if (!habilitado)
        {
            corAtual = 6;
        }
        else if (mouseOver)
        {
            corAtual = 5;
        }
        else
        {
            corAtual = 4;
        }
    }
    else
    {
        if (!habilitado)
        {
            corAtual = 3;
        }
        else if (mouseOver)
        {
            corAtual = 2;
        }
        else
        {
            corAtual = 1;
        }
    }

    coresBasicas[0] = coresBasicas[corAtual];
    if (texture)
    {
        MudaFrameAtual(corAtual);
    }
}

PIGEstadoEvento CPIGBotaoOnOff::OnAction()
{
    SetAcionado(!acionado);
    return CPIGComponente::OnAction();
}

CPIGBotaoOnOff::CPIGBotaoOnOff(
        const int idComponente, const int alt, const int larg, const string &nomeArq,
        const int retiraFundo, const int janela)
    : CPIGBotao(idComponente, alt, larg, nomeArq, retiraFundo, janela)
{
    CriaFramesAutomaticosPorLinha(1, 2, 3);
    MudaFrameAtual(1); // frame de estado normal do botao
    tipo = PIG_BOTAOONOFF;
}

CPIGBotaoOnOff::CPIGBotaoOnOff(
        const int idComponente, const int alt, const int larg, const int janela)
    : CPIGBotao(idComponente, alt, larg, janela)
{
    IniciaCoresBasicas();
    tipo = PIG_BOTAOONOFF;
}

CPIGBotaoOnOff::CPIGBotaoOnOff(const int idComponente, const CPIGAtributos &atrib)
    : CPIGBotaoOnOff(LeParametros(idComponente, atrib))
{}

void CPIGBotaoOnOff::SetCorNormalOff(const PIGCor cor)
{
    coresBasicas[1] = cor;
}

void CPIGBotaoOnOff::SetCorMouseSobreOff(const PIGCor cor)
{
    coresBasicas[2] = cor;
}

void CPIGBotaoOnOff::SetCorDesabilitadoOff(const PIGCor cor)
{
    coresBasicas[3] = cor;
}

void CPIGBotaoOnOff::SetCorNormalOn(const PIGCor cor)
{
    coresBasicas[4] = cor;
}

void CPIGBotaoOnOff::SetCorMouseSobreOn(const PIGCor cor)
{
    coresBasicas[5] = cor;
}

void CPIGBotaoOnOff::SetCorDesabilitadoOn(const PIGCor cor)
{
    coresBasicas[6] = cor;
}
