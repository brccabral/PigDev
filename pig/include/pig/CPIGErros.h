#ifndef _CPIERROS_
#define _CPIERROS_

#include <exception>
#include <string>

using namespace std;

// classe base de erros na PIG
class CPIGErro : public exception
{
protected:

    string mensagem;
    int codErro;


public:

    CPIGErro();
    explicit CPIGErro(const string &msg);

    string GetMensagem();
    [[nodiscard]] int GetCodigoErro() const;
    void PrintErro() const;
};

// Erro para abertura de arquivo em geral (imagem, audio, video, etc)
class CPIGErroArquivo : public CPIGErro
{

protected:

    string nomeArquivo;

public:

    explicit CPIGErroArquivo(const string &nomeArq);

    string GetNomeArquivo();
};


// Erro para falta de parâmetro ou valor incorreto
class CPIGErroParametro : public CPIGErro
{

protected:

    string nomeParam;
    string nomeArq;

public:

    CPIGErroParametro(const string &parametro, const string &arquivo);
    string GetNomeParam();
    string GetNomeArquivo();
};

// Erro para índices de arrays
class CPIGErroIndice : public CPIGErro
{

protected:

    string tipoDado;
    int indice;

public:

    CPIGErroIndice(int indVetor, const string &tipoDeDado);
    string GetTipoDado();
    [[nodiscard]] int GetIndice() const;
};

// Erro para ponteiros especificos
class CPIGErroPonteiro : public CPIGErro
{

protected:

    string tipoDado;
    int indice;

public:

    explicit CPIGErroPonteiro(const string &tipoDeDado);
    string GetTipoDado();
    [[nodiscard]] int GetIndice() const;
};

#endif //_CPIERROS_
