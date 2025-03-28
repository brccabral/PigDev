#ifndef _CPIGTRANSICAO_
#define _CPIGTRANSICAO_

#include <pig/PIGTipos.h>

#include <pig/CPIGTimer.h>

typedef struct
{
    int x, y, alt, larg;
    double ang;
    PIGCor cor;
    int opacidade;
    double personalizada[10];
} PIGEstadoTransicao;

PIGEstadoTransicao operator+(const PIGEstadoTransicao &a, const PIGEstadoTransicao &b);

class CPIGTransicao
{
private:

    PIGEstadoTransicao ini = {}, fim = {}, delta{};
    double tempoAtual = {}, tempoTotal,
           sobraAnterior; // sobraAnterior é um tempo excedido na transição anterior a ser
                          // descontado nesta transição
    PIGTimer timer;

public:

    CPIGTransicao();
    CPIGTransicao(double tempoTransicao, const PIGEstadoTransicao &modificacao);
    explicit CPIGTransicao(const CPIGTransicao *outro);
    virtual ~CPIGTransicao();
    void IniciaTransicao(const PIGEstadoTransicao &inicio, double sobra = 0);
    double CalculaTransicao();
    void InsereTransicaoX(int valorIni, int valorFim);
    void InsereTransicaoY(int valorIni, int valorFim);
    void InsereTransicaoAltura(int valorIni, int valorFim);
    void InsereTransicaoLargura(int valorIni, int valorFim);
    void InsereTransicaoCor(PIGCor valorIni, PIGCor valorFim);
    void InsereTransicaoOpacidade(int valorIni, int valorFim);
    void InsereTransicaoAngulo(double valorIni, double valorFim);
    void InsereTransicaoPersonalizada(int indice, double valorIni, double valorFim);
    [[nodiscard]] int GetX() const;
    [[nodiscard]] int GetY() const;
    [[nodiscard]] int GetAltura() const;
    [[nodiscard]] int GetLargura() const;
    [[nodiscard]] PIGCor GetCor() const;
    [[nodiscard]] int GetOpacidade() const;
    [[nodiscard]] double GetAngulo() const;
    [[nodiscard]] double GetPersonalizada(int indice) const;

    [[nodiscard]] PIGEstadoTransicao GetEstado() const;
    [[nodiscard]] PIGEstadoTransicao GetFim() const;
    [[nodiscard]] PIGEstadoTransicao GetInicio() const;
    void Inverte();
    static CPIGTransicao *PreparaApos(double tempo, const PIGEstadoTransicao &estado);
    void Pausa() const;
    void Despausa() const;
};

typedef CPIGTransicao *PIGTransicao;

#endif // _CPIGTRANSICAO_
