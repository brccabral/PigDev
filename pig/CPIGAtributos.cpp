#include <algorithm>
#include <sstream>
#include <ranges>

using namespace std;

#include <pig/CPIGAtributos.h>

CPIGAtributos::CPIGAtributos() = default;

CPIGAtributos::CPIGAtributos(const CPIGAtributos *outro)
{
    if (outro)
    {
        valoresInt = outro->valoresInt;
        valoresString = outro->valoresString;
    }
}

CPIGAtributos::~CPIGAtributos() = default;

void CPIGAtributos::LimpaAtributos()
{
    valoresInt.clear();
    valoresString.clear();
}

void CPIGAtributos::SetValorInt(const int chave, const int valor)
{
    valoresInt[chave] = std::to_string(valor);
}

void CPIGAtributos::SetValorInt(string chave, const int valor)
{
    ranges::transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
    valoresString[chave] = std::to_string(valor);
}

void CPIGAtributos::SetValorFloat(const int chave, const float valor)
{
    valoresInt[chave] = std::to_string(valor);
}

void CPIGAtributos::SetValorFloat(string chave, const float valor)
{
    ranges::transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
    valoresString[chave] = std::to_string(valor);
}

void CPIGAtributos::SetValorString(const int chave, const string &valor)
{
    valoresInt[chave] = valor;
}

void CPIGAtributos::SetValorString(string chave, const string &valor)
{
    ranges::transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
    valoresString[chave] = valor;
}

bool CPIGAtributos::GetValorInt(const int chave, int &valor)
{
    const map<int, string>::iterator it = valoresInt.find(chave);
    if (it == valoresInt.end())
    {
        return false;
    }
    valor = stoi(it->second);
    return true;
}

bool CPIGAtributos::GetValorInt(string chave, int &valor)
{
    ranges::transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
    const map<string, string>::iterator it = valoresString.find(chave);
    if (it == valoresString.end())
    {
        return false;
    }
    valor = stoi(it->second);
    return true;
}

bool CPIGAtributos::GetValorFloat(const int chave, float &valor)
{
    const map<int, string>::iterator it = valoresInt.find(chave);
    if (it == valoresInt.end())
    {
        return false;
    }
    valor = stof(it->second);
    return true;
}

bool CPIGAtributos::GetValorFloat(string chave, float &valor)
{
    ranges::transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
    const map<string, string>::iterator it = valoresString.find(chave);
    if (it == valoresString.end())
    {
        return false;
    }
    valor = stof(it->second);
    return true;
}

bool CPIGAtributos::GetValorString(const int chave, string &valor)
{
    const map<int, string>::iterator it = valoresInt.find(chave);
    if (it == valoresInt.end())
    {
        return false;
    }
    valor = it->second;
    return true;
}

bool CPIGAtributos::GetValorString(string chave, string &valor)
{
    ranges::transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
    const map<string, string>::iterator it = valoresString.find(chave);
    if (it == valoresString.end())
    {
        return false;
    }
    valor = it->second;
    return true;
}

float CPIGAtributos::GetFloat(string chave, const float retNegativo)
{
    ranges::transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
    const map<string, string>::iterator it = valoresString.find(chave);
    if (it == valoresString.end())
    {
        return retNegativo;
    }
    return stof(it->second);
}

string CPIGAtributos::GetString(string chave, string retNegativo)
{
    ranges::transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
    const map<string, string>::iterator it = valoresString.find(chave);
    if (it == valoresString.end())
    {
        return retNegativo;
    }
    return it->second;
}

int CPIGAtributos::GetInt(string chave, const int retNegativo)
{
    ranges::transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
    const map<string, string>::iterator it = valoresString.find(chave);
    if (it == valoresString.end())
    {
        return retNegativo;
    }
    return stoi(it->second);
}

void CPIGAtributos::dump()
{
    printf("starting dump...\n");

    for (auto &it: valoresString)
    {
        printf("%s: %s\n", it.first.c_str(), it.second.c_str());
    }

    for (auto &it: valoresInt)
    {
        printf("%d: %s\n", it.first, it.second.c_str());
    }
}

// le um conjunto de palavras da stream até encontrar uma que termine com " como último caractere,
// retorna a string toda
string CPIGAtributos::LeString(const string &inicial, istream &ss)
{
    string resp = inicial;

    if (resp[0] == '\"')
    { // se começa com aspas, retira as aspas
        resp.erase(0, 1);
        if (resp[resp.size() - 1] == '\"')
        { // se termina com aspas também retira
            resp.erase(resp.end() - 1);
        }
        else
        {
            string aux;
            // entra no loop procurando a palavras que vai terminar com aspas
            while (ss >> aux && aux[aux.size() - 1] != '\"')
            {
                resp += " " + aux;
            }
            if (aux[aux.size() - 1] == '\"')
            { // acrescenta a última palavra que termina com aspas (depois de tirar as aspas)
                aux.erase(aux.end() - 1);
                resp += " " + aux;
            }
        }
    }

    return resp;
}

CPIGAtributos CPIGAtributos::GetAtributos(const string &parametros)
{
    CPIGAtributos resp;
    stringstream ss(parametros);
    string variavel, valorString; // NOLINT(*-isolate-declaration)

    while (ss >> variavel)
    {
        ss >> valorString;
        valorString = LeString(valorString, ss);
        resp.SetValorString(variavel, valorString);
    }

    return resp;
}
