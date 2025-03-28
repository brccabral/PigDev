#ifndef _CPIGCOMPONENTE_
#define _CPIGCOMPONENTE_

#include <string>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>

#include <pig/CPIGAtributos.h>
#include <pig/CPIGLabel.h>
#include <pig/CPIGSprite.h>

typedef enum
{
    PIG_POSICAO_CIMA_CENTRO,
    PIG_POSICAO_CIMA_ESQ,
    PIG_POSICAO_CIMA_DIR,
    PIG_POSICAO_BAIXO_CENTRO,
    PIG_POSICAO_BAIXO_DIR,
    PIG_POSICAO_BAIXO_ESQ,
    PIG_POSICAO_DIR_CIMA,
    PIG_POSICAO_DIR_BAIXO,
    PIG_POSICAO_DIR_CENTRO,
    PIG_POSICAO_ESQ_BAIXO,
    PIG_POSICAO_ESQ_CENTRO,
    PIG_POSICAO_ESQ_CIMA,
    PIG_POSICAO_CENTRO_CENTRO,
    PIG_POSICAO_PERSONALIZADA
} PIGPosicaoComponente;
typedef enum
{
    PIG_ANCORA_NORTE,
    PIG_ANCORA_SUL,
    PIG_ANCORA_LESTE,
    PIG_ANCORA_OESTE,
    PIG_ANCORA_NORDESTE,
    PIG_ANCORA_NOROESTE,
    PIG_ANCORA_SUDESTE,
    PIG_ANCORA_SUDOESTE,
    PIG_ANCORA_CENTRO
} PIGAncora;
typedef enum
{
    PIG_COMPONENTE_NAOTRATADO,
    PIG_COMPONENTE_SEMFOCO,
    PIG_COMPONENTE_MOUSEOVER,
    PIG_COMPONENTE_INVISIVEL,
    PIG_COMPONENTE_DESABILITADO,
    PIG_COMPONENTE_TRATADO
} PIGEstadoEvento;
typedef enum
{
    PIG_FORM,
    PIG_BOTAOCLICK,
    PIG_BOTAOONOFF,
    PIG_AREADETEXTO,
    PIG_CAMPOTEXTO,
    PIG_RADIOBOX,
    PIG_CHECKBOX,
    PIG_LISTBOX,
    PIG_DROPDOWN,
    PIG_GAUGEBAR,
    PIG_GAUGECIRCULAR,
    PIG_SLIDEBAR,
    PIG_ITEMCOMPONENTE,
    PIG_OUTROCOMPONENTE
} PIGTipoComponente;

class CPIGComponente : public CPIGSprite
{

protected:

    bool temFoco{}, visivel{}, habilitado{}, mouseOver{}, acionado{};
    int audioComponente{};
    PIGPosicaoComponente posLabel{}, posComponente{};
    PIGLabel lab{}, hint{};
    PIGFuncaoSimples acao{};
    PIGCor coresBasicas[10]{};
    PIGTipoComponente tipo{};
    int margemEsq{}, margemDir{}, margemCima{}, margemBaixo{};
    bool imagemPropria{};
    void *param{};

    // inicializa o componente com valores padrão
    void IniciaBase(bool imagem);
    // escreve o label
    void EscreveLabel();
    // escreve o hint do componente na tela
    void EscreveHint();
    // detecta se o mouse está sobre o componente ou não
    virtual int ChecaMouseOver(SDL_Point pMouse);
    static PIGPosicaoComponente ConverteStringPosicao(string str);
    // move o label de acordo com a posição
    void PosicionaLabel();
    virtual PIGEstadoEvento OnAction();
    SDL_Point GetPosicaoMouse();
    virtual void ProcessaAtributos(CPIGAtributos atrib);
    CPIGComponente(int idComponente, int altura, int largura, int janela = 0);
    CPIGComponente(
            int idComponente, int altura, int largura, const string &nomeArq, int retiraFundo = 1,
            int janela = 0);

public:

    ~CPIGComponente() override;
    void DefineAcao(PIGFuncaoSimples funcao, void *parametro);
    PIGTipoComponente GetTipo();
    // desenha o componente, cada subclasse precisa implementar como fazer isso
    int Desenha() override;
    virtual PIGEstadoEvento TrataEventoMouse(PIGEvento evento);
    virtual PIGEstadoEvento TrataEventoTeclado(PIGEvento evento);
    // define a mensagem de hint do componente
    void SetHint(const string &novoHint);
    // recupera o hint
    string GetHint();
    // define a cor do hint
    void SetCorHint(PIGCor cor);
    // recupera a cor do hint
    PIGCor GetCorHint();
    // define a fonte do hint
    virtual void SetFonteHint(int fonte);
    // recupera a fonte do hint
    int GetFonteHint();
    // define o label do componente
    void SetLabel(const string &novoLabel);
    // recupera o label
    string GetLabel();
    // define a cor do label
    void SetCorLabel(PIGCor corLabel);
    // recupera a cor do label
    PIGCor GetCorLabel();
    // define a fonte do label
    void SetFonteLabel(int fonte);
    // recupera a fonte do label
    int GetFonteLabel();
    // define o audio padrão do componente
    virtual void SetAudio(int idAudio);
    // recupera o audio do componente
    virtual int GetAudio();
    // define a posição do label (dentre posições pré-estabelecidas)
    virtual void SetPosicaoPadraoLabel(PIGPosicaoComponente pos);
    // define a posição do label (posição arbiraria, relativa à posição do componente)
    virtual void SetPosicaoPersonalizadaLabel(int rx, int ry);
    virtual void SetVisivel(bool valor);
    virtual void SetFoco(bool valor);
    virtual void SetHabilitado(bool valor);
    virtual void SetMouseOver(bool valor);
    virtual void SetAcionado(bool valor);
    [[nodiscard]] bool GetFoco() const;
    [[nodiscard]] bool GetVisivel() const;
    [[nodiscard]] bool GetHabilitado() const;
    [[nodiscard]] bool GetAcionado() const;
    [[nodiscard]] bool GetMouseOver() const;
    PIGPosicaoComponente GetPosComponente();

    void Move(double nx, double ny) override;
    void Desloca(double dx, double dy) override;
    void SetDimensoes(int altura, int largura) override;
    virtual void SetMargens(int mEsq, int mDir, int mCima, int mBaixo);
};

typedef CPIGComponente *PIGComponente;
#endif // _CPIGCOMPONENTE_
