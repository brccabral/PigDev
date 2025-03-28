#include <pig/CPIGTransicao.h>

#include <algorithm>
#include <pig/PIGFuncoesBasicas.h>

PIGEstadoTransicao operator+(const PIGEstadoTransicao &a, const PIGEstadoTransicao &b)
{
    PIGEstadoTransicao c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.alt = a.alt + b.alt;
    c.larg = a.larg + b.larg;
    c.ang = a.ang + b.ang;
    c.cor = b.cor;
    c.opacidade = a.opacidade + b.opacidade;
    return c;
}

CPIGTransicao::CPIGTransicao() : delta(), tempoTotal(0), sobraAnterior(0), timer(nullptr)
{}

CPIGTransicao::CPIGTransicao(const double tempoTransicao, const PIGEstadoTransicao &modificacao)
{
    tempoTotal = tempoTransicao;
    timer = new CPIGTimer(true);
    delta = modificacao;
    sobraAnterior = 0;
}

CPIGTransicao::CPIGTransicao(const CPIGTransicao *outro)
{
    tempoTotal = outro->tempoTotal;
    timer = new CPIGTimer(true);
    delta = outro->delta;
    sobraAnterior = 0;
}

CPIGTransicao::~CPIGTransicao()
{
    delete timer;
}

void CPIGTransicao::IniciaTransicao(const PIGEstadoTransicao &inicio, const double sobra)
{
    ini = inicio;
    fim = ini + delta;
    timer->Reinicia(false);
    tempoAtual = 0.0;
    sobraAnterior = sobra;
}

double CPIGTransicao::CalculaTransicao()
{
    const double t = timer->GetTempoDecorrido() + sobraAnterior;
    tempoAtual = t / tempoTotal;
    tempoAtual = std::min<double>(tempoAtual, 1);
    return t - tempoTotal;
}

void CPIGTransicao::InsereTransicaoX(const int valorIni, const int valorFim)
{
    ini.x = valorIni;
    fim.x = valorFim;
}

void CPIGTransicao::InsereTransicaoY(const int valorIni, const int valorFim)
{
    ini.y = valorIni;
    fim.y = valorFim;
}

void CPIGTransicao::InsereTransicaoAltura(const int valorIni, const int valorFim)
{
    ini.alt = valorIni;
    fim.alt = valorFim;
}

void CPIGTransicao::InsereTransicaoLargura(const int valorIni, const int valorFim)
{
    ini.larg = valorIni;
    fim.larg = valorFim;
}

void CPIGTransicao::InsereTransicaoCor(const PIGCor valorIni, const PIGCor valorFim)
{
    ini.cor = valorIni;
    fim.cor = valorFim;
}

void CPIGTransicao::InsereTransicaoOpacidade(const int valorIni, const int valorFim)
{
    ini.opacidade = valorIni;
    fim.opacidade = valorFim;
}

void CPIGTransicao::InsereTransicaoAngulo(const double valorIni, const double valorFim)
{
    ini.ang = valorIni;
    fim.ang = valorFim;
}

void CPIGTransicao::InsereTransicaoPersonalizada(
        const int indice, const double valorIni, const double valorFim)
{
    ini.personalizada[indice] = valorIni;
    fim.personalizada[indice] = valorFim;
}

int CPIGTransicao::GetX() const
{
    return (fim.x * (tempoAtual)) + (ini.x * (1 - tempoAtual));
}

int CPIGTransicao::GetY() const
{
    return (fim.y * (tempoAtual)) + (ini.y * (1 - tempoAtual));
}

int CPIGTransicao::GetAltura() const
{
    return (fim.alt * (tempoAtual)) + (ini.alt * (1 - tempoAtual));
}

int CPIGTransicao::GetLargura() const
{
    return (fim.larg * (tempoAtual)) + (ini.larg * (1 - tempoAtual));
}

PIGCor CPIGTransicao::GetCor() const
{
    return PIGMixCor(ini.cor, fim.cor, tempoAtual);
}

int CPIGTransicao::GetOpacidade() const
{
    return (fim.opacidade * (tempoAtual)) + (ini.opacidade * (1 - tempoAtual));
}

double CPIGTransicao::GetAngulo() const
{
    return (fim.ang * (tempoAtual)) + (ini.ang * (1 - tempoAtual));
}

double CPIGTransicao::GetPersonalizada(const int indice) const
{
    return (fim.personalizada[indice] * (tempoAtual)) +
           (ini.personalizada[indice] * (1 - tempoAtual));
}

PIGEstadoTransicao CPIGTransicao::GetEstado() const
{
    PIGEstadoTransicao atual;
    // atual.tempoAtual = tempoAtual;
    atual.x = fim.x * (tempoAtual) + ini.x * (1 - tempoAtual);
    atual.y = fim.y * (tempoAtual) + ini.y * (1 - tempoAtual);
    atual.alt = fim.alt * (tempoAtual) + ini.alt * (1 - tempoAtual);
    atual.larg = fim.larg * (tempoAtual) + ini.larg * (1 - tempoAtual);
    atual.ang = fim.ang * (tempoAtual) + ini.ang * (1 - tempoAtual);
    atual.cor = PIGMixCor(ini.cor, fim.cor, tempoAtual);
    atual.opacidade = fim.opacidade * (tempoAtual) + ini.opacidade * (1 - tempoAtual);
    // fprintf(arqP,"get %f %d %d %d %d
    // %f\n",atual.tempoAtual,atual.x,atual.y,atual.alt,atual.larg,atual.ang);
    return atual;
}

PIGEstadoTransicao CPIGTransicao::GetFim() const
{
    return fim;
}

PIGEstadoTransicao CPIGTransicao::GetInicio() const
{
    return ini;
}

void CPIGTransicao::Inverte()
{
    delta.x *= -1;
    delta.y *= -1;
    delta.alt *= -1;
    delta.larg *= -1;
    delta.ang *= -1;
    delta.opacidade *= -1;
}

CPIGTransicao *CPIGTransicao::PreparaApos(const double tempo, const PIGEstadoTransicao &estado)
{
    return new CPIGTransicao(tempo, estado);
}

void CPIGTransicao::Pausa() const
{
    timer->Pausa();
}

void CPIGTransicao::Despausa() const
{
    timer->Despausa();
}
