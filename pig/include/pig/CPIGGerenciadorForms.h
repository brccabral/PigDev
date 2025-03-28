#ifndef _CPIGGERENCIADORFORMS_
#define _CPIGGERENCIADORFORMS_

#include <string>

using namespace std;

#include <pig/CPIGRepositorio.h>
#include <pig/CPIGForm.h>

class CPIGGerenciadorForms
{

private:

    static CPIGRepositorio<PIGForm> *forms;

public:

    static void Inicia();
    static void Encerra();
    static PIGForm GetForm(int idForm);
    static PIGForm GetFormComponente(int idComponente);
    template<class T>
    static T GetComponente(int idComponente);
    static int CriaForm(int altura, int largura, int janela = 0);
    static int InsereForm(PIGForm form);
    static int
    CriaForm(int altura, int largura, const string &nomeArq, int retiraFundo = 1, int janela = 0);
    static int CriaForm(const string &nomeArqTexto);
    static void DestroiForm(int idForm);
};

template<class T>
T CPIGGerenciadorForms::GetComponente(int idComponente)
{
    PIGForm f = GetFormComponente(idComponente);
    return f->GetComponente<T>(idComponente);
}

#endif // _CPIGGERENCIADORFORMS_
