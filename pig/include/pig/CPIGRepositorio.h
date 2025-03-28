#ifndef _CPIGREPOSITORIO_
#define _CPIGREPOSITORIO_

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGErros.h>

template<class T>
class CPIGRepositorio
{

protected:

    string tipoElementos{};
    vector<int> posLivres{};
    unordered_map<int, T> elementos{};
    typename std::unordered_map<int, T>::iterator it{};

public:

    CPIGRepositorio(int qtdElementos, const string &tipoDeElementos);
    ~CPIGRepositorio();
    int Insere(T valor);
    void Remove(int id);
    T GetElemento(int id);
    int ProxID();
    T GetPrimeiroElemento();
    T GetProximoElemento();
};

template<class T>
CPIGRepositorio<T>::CPIGRepositorio(int qtdElementos, const string &tipoDeElementos)
{
    for (int i = qtdElementos - 1; i >= 0; i--)
        posLivres.push_back(i);
    tipoElementos = tipoDeElementos;
}

template<class T>
CPIGRepositorio<T>::~CPIGRepositorio()
{
    for (it = elementos.begin(); it != elementos.end(); ++it)
        delete it->second;
}

template<class T>
int CPIGRepositorio<T>::Insere(T valor)
{
    if (posLivres.empty())
    {
        char buffer[100];
        snprintf(
                buffer, sizeof(buffer), "Limite de %s excedido (%d).", tipoElementos.c_str(),
                PIG_MAX_SPRITES);
        throw CPIGErro(buffer);
    }
    int resp = posLivres.back();
    posLivres.pop_back();
    elementos[resp] = valor;
    return resp;
}

template<class T>
void CPIGRepositorio<T>::Remove(int id)
{
    posLivres.push_back(id);
    T elem = GetElemento(id);
    delete elem;
    elementos.erase(id);
}

template<class T>
T CPIGRepositorio<T>::GetElemento(int id)
{
    it = elementos.find(id);
    if (it == elementos.end())
        throw CPIGErroIndice(id, tipoElementos);
    return it->second;
}

template<class T>
int CPIGRepositorio<T>::ProxID()
{
    return posLivres.back();
}

template<class T>
T CPIGRepositorio<T>::GetPrimeiroElemento()
{
    it = elementos.begin();
    if (it == elementos.end())
        return NULL;
    return it->second;
}

template<class T>
T CPIGRepositorio<T>::GetProximoElemento()
{
    ++it;
    if (it == elementos.end())
        return NULL;
    return it->second;
}

#endif // _CPIGREPOSITORIO_
