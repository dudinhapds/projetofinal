#include "ListaTarefasCompromissos.hpp"
#include <iostream>

void ListaTarefasCompromissos::adicionarTarefaCompromisso(const TarefaCompromisso& tarefaCompromisso) {
    tarefasCompromissos.push_back(tarefaCompromisso);
}

void ListaTarefasCompromissos::listarTarefasCompromissos() const {
    for (size_t i = 0; i < tarefasCompromissos.size(); ++i) {
        const TarefaCompromisso& tarefaCompromisso = tarefasCompromissos[i];
        std::cout << "Descrição: " << tarefaCompromisso.getDescricao() << std::endl;
        std::cout << "Data e Hora: " << asctime(&tarefaCompromisso.getDataHora()) << std::endl;
        std::cout << "Concluída: " << (tarefaCompromisso.estaConcluida() ? "Sim" : "Não") << std::endl;
        std::cout << "------------------------------" << std::endl;
    }
}

void ListaTarefasCompromissos::removerTarefaCompromisso(size_t indice) {
    if (indice < tarefasCompromissos.size()) {
        tarefasCompromissos.erase(tarefasCompromissos.begin() + indice);
    }
}