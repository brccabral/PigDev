#include <pig/CPIGGerenciadorForms.h>

CPIGRepositorio<PIGForm> *CPIGGerenciadorForms::forms;

void CPIGGerenciadorForms::Inicia()
{
    forms = new CPIGRepositorio<PIGForm>(PIG_MAX_FORMS, "forms");
}

void CPIGGerenciadorForms::Encerra()
{
    delete forms;
}

PIGForm CPIGGerenciadorForms::GetForm(int idForm)
{
    return forms->GetElemento(idForm);
}

PIGForm CPIGGerenciadorForms::GetFormComponente(int idComponente)
{
    return GetForm(idComponente / PIG_MAX_COMPONENTES);
}

int CPIGGerenciadorForms::CriaForm(int altura, int largura, int janela)
{
    int resp = forms->ProxID();
    return forms->Insere(new CPIGForm(resp, altura, largura, janela));
}

int CPIGGerenciadorForms::InsereForm(PIGForm form)
{
    return forms->Insere(form);
}

int CPIGGerenciadorForms::CriaForm(
        int altura, int largura, const string &nomeArq, int retiraFundo, int janela)
{
    int resp = forms->ProxID();
    return forms->Insere(new CPIGForm(resp, altura, largura, nomeArq, retiraFundo, janela));
}

int CPIGGerenciadorForms::CriaForm(const string &nomeArqTexto)
{
    int resp = forms->ProxID();
    return forms->Insere(new CPIGForm(resp, nomeArqTexto));
}

void CPIGGerenciadorForms::DestroiForm(int idForm)
{
    forms->Remove(idForm);
}
