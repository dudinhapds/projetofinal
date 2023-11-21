#ifndef NOTIFICACOES_HPP
#define NOTIFICACOES_HPP

#include "TarefaCompromisso.hpp"

class Notificacoes {
public:
    void enviarLembrete(const TarefaCompromisso& tarefaCompromisso, int minutosAntes);
};

#endif // NOTIFICACOES_HPP
