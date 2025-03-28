#include <pig/CPIGTimer.h>

CPIGTimer::CPIGTimer(const bool congelado)
{
    pausadoGeral = false;
    Reinicia(congelado);
}

double CPIGTimer::GetTempoDecorrido() const
{
    std::chrono::duration<double> tempo{};
    if (pausado || pausadoGeral)
    {
        tempo = std::chrono::duration_cast<std::chrono::duration<double>>(pausa - inicio);
    }
    else
    {
        tempo = std::chrono::duration_cast<std::chrono::duration<double>>(
                std::chrono::system_clock::now() - inicio);
    }
    return tempo.count() - totalPausa;
}

void CPIGTimer::Pausa()
{
    if (!pausado)
    {
        pausado = true;
        if (!pausadoGeral)
        {
            pausa = std::chrono::system_clock::now();
        }
    }
}

void CPIGTimer::PausaGeral()
{
    if (!pausadoGeral)
    {
        pausadoGeral = true;
        if (!pausado)
        {
            pausa = std::chrono::system_clock::now();
        }
    }
}

void CPIGTimer::DespausaGeral()
{
    if (pausadoGeral)
    {
        pausadoGeral = false;
        if (!pausado)
        {
            const std::chrono::duration<double> tempo =
                    std::chrono::duration_cast<std::chrono::duration<double>>(
                            std::chrono::system_clock::now() - pausa);
            totalPausa += tempo.count();
        }
    }
}

double CPIGTimer::GetPausa() const
{
    return totalPausa;
}

void CPIGTimer::Despausa()
{
    if (pausado)
    {
        if (!pausadoGeral)
        {
            const std::chrono::duration<double> tempo =
                    std::chrono::duration_cast<std::chrono::duration<double>>(
                            std::chrono::system_clock::now() - pausa);
            totalPausa += tempo.count();
        }
        pausado = false;
    }
}

void CPIGTimer::Reinicia(const bool congelado)
{
    pausa = inicio = std::chrono::system_clock::now();
    totalPausa = 0;
    pausado = congelado;
}

CPIGTimer *CPIGTimer::Copia() const
{
    CPIGTimer *outro = new CPIGTimer(pausado);
    outro->inicio = inicio;
    outro->pausa = pausa;
    outro->totalPausa = totalPausa;
    return outro;
}
