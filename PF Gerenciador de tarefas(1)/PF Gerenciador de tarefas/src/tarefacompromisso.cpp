#include "TarefaCompromisso.hpp"

TarefaCompromisso::TarefaCompromisso(const std::string& descricao, const std::tm& dataHora, bool concluida)
    : descricao(descricao), dataHora(dataHora), concluida(concluida) {}

const std::string& TarefaCompromisso::getDescricao() const {
    return descricao;
}

const std::tm& TarefaCompromisso::getDataHora() const {
    return dataHora;
}

bool TarefaCompromisso::estaConcluida() const {
    return concluida;
}

void TarefaCompromisso::marcarConcluida() {
    concluida = true;
}
