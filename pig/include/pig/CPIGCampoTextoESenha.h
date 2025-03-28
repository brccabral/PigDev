#ifndef _CPIGCAMPOTEXTOESENHA_
#define _CPIGCAMPOTEXTOESENHA_

#include <string>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGAtributos.h>
#include <pig/CPIGCaixaTexto.h>
#include <pig/CPIGComponente.h>

class CPIGCampoTextoESenha : public CPIGCaixaTexto
{

private:

    char mascara{}; // símbolo usado quando o campo for de senha
    bool somenteNumeros{}; // se o campo só aceita números ou aceita também letras
    string (CPIGCampoTextoESenha::*GetTextoVisivelPtr)(){}; // ponteiro para a funçăo que vai
                                                            // retornar o texto visivel

    void ProcessaAtributos(CPIGAtributos atrib) override;
    static CPIGCampoTextoESenha LeParametros(int idComponente, CPIGAtributos atrib);
    // retorna o texto com a quantidade de símbolos (máscara) igual ao tamanho da string com
    // textobase
    string GetTextoMask();
    // recupera a string com o texto visível (com máscara de senha ou năo)
    string GetTextoVisivel() override;
    void IniciaPosicaoTexto();
    // ajusta o alinhamento do cursor
    void AjustaPosicaoTextoCursor() override;
    int SobeCursor() override;

    int DesceCursor() override;

    int PulaLinha() override;

    void IniciaBase(bool campoSenha, bool apenasNumero);

public:

    CPIGCampoTextoESenha(
            int idComponente, int altura, int largura, const string &nomeArq,
            int maxCars = PIG_MAX_CARS_CAIXATEXTO, bool apenasNumeros = false,
            bool campoSenha = false, int retiraFundo = 1, int janela = 0);
    CPIGCampoTextoESenha(
            int idComponente, int altura, int largura, int maxCars = PIG_MAX_CARS_CAIXATEXTO,
            bool apenasNumeros = false, bool campoSenha = false, int janela = 0);
    CPIGCampoTextoESenha(int idComponente, const CPIGAtributos &atrib);

    ~CPIGCampoTextoESenha() override = default;

    // desenha o componente completo
    int Desenha() override;
    PIGEstadoEvento TrataEventoMouse(PIGEvento evento) override;
    void SetMascara(char c);
    int AdicionaTexto(const string &frase) override;
};

typedef CPIGCampoTextoESenha *PIGCampoTextoESenha;
#endif // _CPIGCAMPOTEXTOESENHA_
