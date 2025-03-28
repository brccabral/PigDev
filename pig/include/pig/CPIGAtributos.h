#ifndef _CPIGATRIBUTOS_
#define _CPIGATRIBUTOS_

#include <map>
#include <string>

using namespace std;

class CPIGAtributos
{

private:

    map<int, string> valoresInt;
    map<string, string> valoresString;

public:

    CPIGAtributos();

    explicit CPIGAtributos(const CPIGAtributos *outro);

    virtual ~CPIGAtributos();

    void LimpaAtributos();

    void SetValorInt(int chave, int valor);

    void SetValorInt(string chave, int valor);

    void SetValorFloat(int chave, float valor);

    void SetValorFloat(string chave, float valor);

    void SetValorString(int chave, const string &valor);

    void SetValorString(string chave, const string &valor);

    bool GetValorInt(int chave, int &valor);

    bool GetValorInt(string chave, int &valor);

    bool GetValorFloat(int chave, float &valor);

    bool GetValorFloat(string chave, float &valor);

    bool GetValorString(int chave, string &valor);

    bool GetValorString(string chave, string &valor);

    float GetFloat(string chave, float retNegativo);

    string GetString(string chave, string retNegativo);

    int GetInt(string chave, int retNegativo);

    void dump();

    // le um conjunto de palavras da stream até encontrar uma que termine com " como último
    // caractere, retorna a string toda
    static string LeString(const string &inicial, istream &ss);

    static CPIGAtributos GetAtributos(const string &parametros);
};
typedef CPIGAtributos *PIGAtributos;
#endif //_CPIGATRIBUTOS_
