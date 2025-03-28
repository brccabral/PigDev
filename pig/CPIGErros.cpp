#include <pig/CPIGErros.h>

CPIGErro::CPIGErro()
{
    codErro = 1;
}

CPIGErro::CPIGErro(const string &msg)
{
    codErro = 1;
    mensagem = msg;
    PrintErro();
}

string CPIGErro::GetMensagem()
{
    return mensagem;
}

[[nodiscard]] int CPIGErro::GetCodigoErro() const
{
    return codErro;
}

void CPIGErro::PrintErro() const
{
    printf("Erro: %d %s\n", codErro, mensagem.c_str());
}

CPIGErroArquivo::CPIGErroArquivo(const string &nomeArq)
{
    nomeArquivo = nomeArq;
    mensagem = "Nao foi possivel abrir o arquivo <" + nomeArq + ">";
    codErro = 2;
    PrintErro();
}

string CPIGErroArquivo::GetNomeArquivo()
{
    return nomeArquivo;
}

CPIGErroParametro::CPIGErroParametro(const string &parametro, const string &arquivo)
{
    nomeParam = parametro;
    nomeArq = arquivo;
    mensagem = "O parametro <" + nomeParam +
               "> nao foi definido ou possui valor incorreto no arquivo (" + nomeArq + ")";
    codErro = 3;
    PrintErro();
}

string CPIGErroParametro::GetNomeParam()
{
    return nomeParam;
}

string CPIGErroParametro::GetNomeArquivo()
{
    return nomeArq;
}


CPIGErroIndice::CPIGErroIndice(int indVetor, const string &tipoDeDado)
{
    tipoDado = tipoDeDado;
    indice = indVetor;
    mensagem = "O indice <" + std::to_string(indice) +
               "> nao pode ser utlizado para referenciar um (" + tipoDado + ")";
    codErro = 4;
    PrintErro();
}

string CPIGErroIndice::GetTipoDado()
{
    return tipoDado;
}

[[nodiscard]] int CPIGErroIndice::GetIndice() const
{
    return indice;
}

CPIGErroPonteiro::CPIGErroPonteiro(const string &tipoDeDado)
{
    tipoDado = tipoDeDado;
    indice = -1;
    mensagem = "Ponteiro <" + tipoDado + "> com valor NULO ou inconsistente";
    codErro = 5;
    PrintErro();
}

string CPIGErroPonteiro::GetTipoDado()
{
    return tipoDado;
}

[[nodiscard]] int CPIGErroPonteiro::GetIndice() const
{
    return indice;
}
