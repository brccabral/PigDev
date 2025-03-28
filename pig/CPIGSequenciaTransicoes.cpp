#include <pig/CPIGSequenciaTransicoes.h>

CPIGSequenciaTransicoes::CPIGSequenciaTransicoes()
{
    tipo = PIG_TRANSICAO_NORMAL;
    transAtual = 0;
}

CPIGSequenciaTransicoes::~CPIGSequenciaTransicoes()
{
    for (auto &tran: trans)
    {
        delete tran;
    }
}

bool CPIGSequenciaTransicoes::TemTransicoes()
{
    return !trans.empty();
}

void CPIGSequenciaTransicoes::Insere(PIGTransicao t)
{
    trans.push_back(t);
}

void CPIGSequenciaTransicoes::SetTipoTransicao(PIG_TipoTransicao valor)
{
    tipo = valor;
}

void CPIGSequenciaTransicoes::IniciaTransicoes()
{
    if (transAtual < trans.size())
    {
        transAtual = 0;
        trans[transAtual]->IniciaTransicao(trans[transAtual]->GetInicio());
    }
}

PIGTransicao CPIGSequenciaTransicoes::GetTransicaoAtual()
{
    if (trans.size() == transAtual)
    {
        return NULL;
    }
    if (trans[transAtual]->CalculaTransicao() == 0)
    {
        if (tipo == PIG_TRANSICAO_INVERTIDA)
        {
            static int somaTrans = 1;
            transAtual += somaTrans;
            if (transAtual == trans.size() || transAtual == -1)
            {
                somaTrans = -somaTrans;
                transAtual += somaTrans;
                for (auto &tran: trans)
                {
                    tran->Inverte();
                }
            }
        }
        else
        {
            transAtual++;
            if (tipo == PIG_TRANSICAO_LOOP)
            {
                transAtual %= trans.size(); // volta à transicao com índice 0
            }
            else
            {
                if (transAtual == trans.size())
                {
                    return NULL; // as transicoes acabaram
                }
            }
        }
        printf("trans atual: %d\n", transAtual);
        trans[transAtual]->IniciaTransicao(trans[transAtual]->GetInicio());
    }
    return trans[transAtual];
}
