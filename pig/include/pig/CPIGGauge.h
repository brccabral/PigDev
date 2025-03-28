#ifndef _CPIGGAUGE_
#define _CPIGGAUGE_

#include <string>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGAtributos.h>
#include <pig/CPIGComponente.h>
#include <pig/CPIGSprite.h>

typedef enum
{
    PIG_GAUGE_CIMA_BAIXO,
    PIG_GAUGE_BAIXO_CIMA,
    PIG_GAUGE_ESQ_DIR,
    PIG_GAUGE_DIR_ESQ,
    PIG_GAUGE_HORARIO,
    PIG_GAUGE_ANTIHORARIO
} PIGGaugeCrescimento;

class CPIGGauge : public CPIGComponente
{

protected:

    PIGSprite marcador{};
    double delta{}, porcentagemConcluida{};
    double valorMax{}, valorMin{}, valorAtual{};
    bool marcadorAtualizado{}, marcadorFrente{};
    PIGGaugeCrescimento orientacaoCrescimento{};

    static PIGGaugeCrescimento ConverteStringCrescimento(string str);
    virtual void AtualizaMarcador();
    void IniciaCoresBasicas();
    void ProcessaAtributos(CPIGAtributos atrib) override;
    virtual void IniciaBase();
    CPIGGauge(
            int idComponente, int altura, int largura, const string &imgTrilha,
            int retiraFundoTrilha = 1, int janela = 0);
    CPIGGauge(int idComponente, int altura, int largura, int janela = 0);
    ~CPIGGauge() override;

public:

    virtual int SetValorMin(double minimo);
    virtual int SetValorMax(double maximo);
    virtual int SetValorAtual(double valor);
    void SetDelta(double valor);
    virtual int SetOrientacao(PIGGaugeCrescimento orientacao) = 0;

    void SetPorcentagemConcluida(double porcentagem);
    double GetValorAtual() const;
    double GetValorMax() const;
    double GetValorMin() const;
    double GetPorcentagemConcluida() const;
    virtual void AvancaMarcador(double valor);
    void AvancaDelta();
    void MinimizaValorAtual();
    void MaximizaValorAtual();
    void SetCorInicial(PIGCor cor);
    void SetCorFinal(PIGCor cor);
    void SetCorTrilha(PIGCor cor);
    void Desloca(double dx, double dy) override;
    void Move(double nx, double ny) override;
    void SetMarcadorFrente(bool valor);
    void SetMargens(int mEsq, int mDir, int mCima, int mBaixo) override;
};

typedef CPIGGauge *PIGGauge;
#endif // _CPIGGAUGE_
