#ifndef LISTATAREFASCOMPROMISSOS_HPP
#define LISTATAREFASCOMPROMISSOS_HPP

#include "TarefaCompromisso.hpp"
#include <vector>

class ListaTarefasCompromissos {
public:
    void adicionarTarefaCompromisso(const TarefaCompromisso& tarefaCompromisso);
    void listarTarefasCompromissos() const;
    void removerTarefaCompromisso(size_t indice);

private:
    std::vector<TarefaCompromisso> tarefasCompromissos;
};

#endif // LISTATAREFASCOMPROMISSOS_HPP
