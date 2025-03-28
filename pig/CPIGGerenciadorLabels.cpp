#include <pig/CPIGGerenciadorLabels.h>

CPIGRepositorio<PIGLabel> *CPIGGerenciadorLabels::labels{};

PIGLabel CPIGGerenciadorLabels::GetLabel(int idLabel)
{
    return labels->GetElemento(idLabel);
}

void CPIGGerenciadorLabels::Inicia()
{
    labels = new CPIGRepositorio<PIGLabel>(PIG_MAX_LABELS, "labels");
}

void CPIGGerenciadorLabels::Encerra()
{
    delete labels;
}

int CPIGGerenciadorLabels::CriaLabel(const string &texto, PIGCor cor, int numFonte, int idJanela)
{
    return labels->Insere(new CPIGLabel(texto, cor, numFonte, idJanela));
}

int CPIGGerenciadorLabels::InsereLabel(PIGLabel label)
{
    return labels->Insere(label);
}

void CPIGGerenciadorLabels::DestroiLabel(int idLabel)
{
    labels->Remove(idLabel);
}
