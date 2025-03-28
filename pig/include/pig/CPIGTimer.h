#ifndef _CPIGTIMER_
#define _CPIGTIMER_

#include <chrono>

class CPIGTimer
{

private:

    std::chrono::system_clock::time_point inicio{};
    std::chrono::system_clock::time_point pausa{};
    double totalPausa{};
    bool pausado{}, pausadoGeral;

public:

    explicit CPIGTimer(bool congelado);
    ~CPIGTimer() = default;
    [[nodiscard]] double GetTempoDecorrido() const;
    void Pausa();
    void PausaGeral();
    void DespausaGeral();
    [[nodiscard]] double GetPausa() const;
    void Despausa();
    void Reinicia(bool congelado);
    [[nodiscard]] CPIGTimer *Copia() const;
};

typedef CPIGTimer *PIGTimer;
#endif // _CPIGTIMER_
