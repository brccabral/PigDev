#include <algorithm>
#include <cstdint>

using namespace std;

#include <pig/PIGFuncoesBasicas.h>
#include <pig/CPIGGauge.h>

PIGGaugeCrescimento CPIGGauge::ConverteStringCrescimento(string str)
{
    ranges::transform(str.begin(), str.end(), str.begin(), ::toupper);
    if (str == "ESQ_DIR")
    {
        return PIG_GAUGE_ESQ_DIR;
    }
    if (str == "DIR_ESQ")
    {
        return PIG_GAUGE_DIR_ESQ;
    }
    if (str == "CIMA_BAIXO")
    {
        return PIG_GAUGE_CIMA_BAIXO;
    }
    if (str == "BAIXO_CIMA")
    {
        return PIG_GAUGE_BAIXO_CIMA;
    }
    if (str == "HORARIO")
    {
        return PIG_GAUGE_HORARIO;
    }
    if (str == "ANTIHORARIO")
    {
        return PIG_GAUGE_ANTIHORARIO;
    }
    return PIG_GAUGE_ESQ_DIR;
}

void CPIGGauge::AtualizaMarcador()
{
    coresBasicas[3] = PIGMixCor(coresBasicas[1], coresBasicas[2], porcentagemConcluida);
    marcadorAtualizado = true;
}

void CPIGGauge::IniciaCoresBasicas()
{
    coresBasicas[0] = BRANCO;
    coresBasicas[1] = CINZA;
    coresBasicas[2] = CINZA;
}

void CPIGGauge::ProcessaAtributos(CPIGAtributos atrib)
{
    CPIGComponente::ProcessaAtributos(atrib);

    int valorInt = atrib.GetInt("valorMin", INT_MAX);
    if (valorInt != INT_MAX)
    {
        SetValorMin(valorInt);
    }

    valorInt = atrib.GetInt("valorMax", INT_MIN);
    if (valorInt != INT_MIN)
    {
        SetValorMax(valorInt);
    }

    valorInt = atrib.GetInt("valorAtual", INT_MIN);
    if (valorInt != INT_MIN)
    {
        SetValorAtual(valorInt);
    }

    valorInt = atrib.GetInt("delta", 0);
    if (valorInt != 0)
    {
        SetDelta(valorInt);
    }

    float valorFloat = atrib.GetFloat("porcentagem", 0);
    if (valorFloat != 0)
    {
        SetPorcentagemConcluida(valorFloat);
    }

    string valorStr = atrib.GetString("corTrilha", "");
    if (!valorStr.empty())
    {
        SetCorTrilha(PIGCriaCorString(valorStr));
    }

    valorStr = atrib.GetString("corInicial", "");
    if (!valorStr.empty())
    {
        SetCorInicial(PIGCriaCorString(valorStr));
    }

    valorStr = atrib.GetString("corFinal", "");
    if (!valorStr.empty())
    {
        SetCorFinal(PIGCriaCorString(valorStr));
    }

    valorStr = atrib.GetString("orientacao", "");
    if (!valorStr.empty())
    {
        SetOrientacao(ConverteStringCrescimento(valorStr));
    }
}

void CPIGGauge::IniciaBase()
{
    valorMin = valorAtual = 0;
    valorMax = 100;
    porcentagemConcluida = 0;
    orientacaoCrescimento = PIG_GAUGE_ESQ_DIR;
    delta = 1;
    marcador = NULL;
    marcadorAtualizado = false;
    marcadorFrente = true;
    IniciaCoresBasicas();
}

CPIGGauge::CPIGGauge(
        int idComponente, int altura, int largura, const string &imgTrilha, int retiraFundoTrilha,
        int janela)
    : CPIGComponente(idComponente, altura, largura, imgTrilha, retiraFundoTrilha, janela)
{
    CPIGGauge::IniciaBase();
}

CPIGGauge::CPIGGauge(int idComponente, int altura, int largura, int janela)
    : CPIGComponente(idComponente, altura, largura, janela)
{
    CPIGGauge::IniciaBase();
}

CPIGGauge::~CPIGGauge()
{
    delete marcador;
}

int CPIGGauge::SetValorMin(double minimo)
{
    if (minimo <= valorMax)
    {
        valorMin = minimo;
        marcadorAtualizado = false;
        return 1;
    }
    return 0;
}

int CPIGGauge::SetValorMax(double maximo)
{
    if (valorMin <= maximo)
    {
        valorMax = maximo;
        marcadorAtualizado = false;
        return 1;
    }
    return 0;
}

int CPIGGauge::SetValorAtual(double valor)
{
    if (valor >= valorMin && valor <= valorMax)
    {
        valorAtual = valor;
        marcadorAtualizado = false;
        return 1;
    }
    return 0;
}

void CPIGGauge::SetDelta(double valor)
{
    delta = valor;
}

void CPIGGauge::SetPorcentagemConcluida(double porcentagem)
{
    porcentagemConcluida = PIGLimitaValor(porcentagem, 0.0, 1.0);
    valorAtual = valorMin + (valorMax - valorMin) * porcentagemConcluida;
    porcentagemConcluida = (valorAtual - valorMin) /
                           (valorMax - valorMin); // correção para que o percentual represent um
                                                  // valor inteiro dentro da faixa min-max
    marcadorAtualizado = false;
    OnAction();
}

double CPIGGauge::GetValorAtual() const
{
    return valorAtual;
}

double CPIGGauge::GetValorMax() const
{
    return valorMax;
}

double CPIGGauge::GetValorMin() const
{
    return valorMin;
}

double CPIGGauge::GetPorcentagemConcluida() const
{
    return porcentagemConcluida;
}

void CPIGGauge::AvancaMarcador(double valor)
{
    valorAtual += valor;

    valorAtual = PIGLimitaValor(valorAtual, valorMin, valorMax);
    porcentagemConcluida = (valorAtual - valorMin) / (valorMax - valorMin);

    marcadorAtualizado = false;

    if (valor != 0)
    {
        OnAction();
    }
}

void CPIGGauge::AvancaDelta()
{
    AvancaMarcador(delta);
}

void CPIGGauge::MinimizaValorAtual()
{
    valorAtual = valorMin;
    porcentagemConcluida = (valorAtual - valorMin) / (valorMax - valorMin);
    marcadorAtualizado = false;
}

void CPIGGauge::MaximizaValorAtual()
{
    valorAtual = valorMax;
    porcentagemConcluida = (valorAtual - valorMin) / (valorMax - valorMin);
    marcadorAtualizado = false;
}

void CPIGGauge::SetCorInicial(PIGCor cor)
{
    coresBasicas[1] = cor;
    marcadorAtualizado = false;
}

void CPIGGauge::SetCorFinal(PIGCor cor)
{
    coresBasicas[2] = cor;
    marcadorAtualizado = false;
}

void CPIGGauge::SetCorTrilha(PIGCor cor)
{
    coresBasicas[0] = cor;
    marcadorAtualizado = false;
}

void CPIGGauge::Desloca(double dx, double dy)
{
    CPIGComponente::Desloca(dx, dy);
    if (marcador)
    {
        marcador->Desloca(dx, dy);
    }
}

void CPIGGauge::Move(double nx, double ny)
{
    if (marcador)
    {
        marcador->Desloca(nx - pos.x, ny - pos.y);
    }
    CPIGComponente::Move(nx, ny);
}

void CPIGGauge::SetMarcadorFrente(bool valor)
{
    marcadorFrente = valor;
    marcadorAtualizado = false;
}

void CPIGGauge::SetMargens(int mEsq, int mDir, int mCima, int mBaixo)
{
    CPIGComponente::SetMargens(mEsq, mDir, mCima, mBaixo);
    marcadorAtualizado = false;
}
