#ifndef _CPIGSTRINGFORMATADA_
#define _CPIGSTRINGFORMATADA_

#include <string>
#include <vector>

using namespace std;

#include <pig/PIGTipos.h>

class CPIGStringFormatada
{

    vector<int> letras{};
    vector<int> largAcumulada{};
    vector<PIGCor> cores{};
    vector<PIGEstilo> estilos{};

public:

    ~CPIGStringFormatada();
    int GetIntLetra(int indice);
    PIGCor GetCor(int indice);
    PIGEstilo GetEstilo(int indice);
    void Clear();
    void Adiciona(int letra, int larguraAcumulada, PIGCor cor, PIGEstilo estilo);

    /*void Print(){
        EXECUTA_SE_DEBUG(printf("__%s__ (%d)\n",letras.c_str(),LargTotalPixels()));
    }*/

    int LargTotalPixels();
    int size();
    vector<CPIGStringFormatada> SeparaPalavras(const string &delim);
    vector<CPIGStringFormatada> ExtraiLinhas(int largMax, const string &delim);
    CPIGStringFormatada operator+=(const CPIGStringFormatada &outra);
};

#endif //_CPIGSTRINGFORMATADA_
