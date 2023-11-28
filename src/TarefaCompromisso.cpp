#include <TarefaCompromisso.hpp>

TarefaCompromisso::TarefaCompromisso(
    const std::string& descricao,
    const std::time_t timestamp,
    Prioridade prioridade,
    bool concluida
) : descricao(descricao), timestamp(timestamp),
    prioridade(prioridade), concluida(concluida) {}

const std::string& TarefaCompromisso::getDescricao() const {
    return descricao;
}

void TarefaCompromisso::setDescricao(const std::string &descricao) {
    this->descricao = descricao;
}

std::time_t TarefaCompromisso::getTimestamp() const {
    return timestamp;
}

void TarefaCompromisso::setTimestamp(std::time_t timestamp) {
    this->timestamp = timestamp;
}

std::tm TarefaCompromisso::getDataHora() const {
    return *std::localtime(&timestamp);
}

TarefaCompromisso::Prioridade TarefaCompromisso::getPrioridade() const {
    return prioridade;
}

void TarefaCompromisso::setPrioridade(Prioridade prioridade) {
    this->prioridade = prioridade;
}

bool TarefaCompromisso::getConcluida() const {
    return concluida;
}

void TarefaCompromisso::setConcluida(bool b) {
    concluida = b;
}

void TarefaCompromisso::serializar(OutputStream &stream) const {
    std::size_t tamanho = descricao.size();
    stream.write(&tamanho, sizeof(tamanho));
    stream.write(descricao.c_str(), tamanho);

    stream.write(&timestamp, sizeof(timestamp));

    stream.write(&prioridade, sizeof(prioridade));
    
    stream.write(&concluida, sizeof(concluida));
}

void TarefaCompromisso::deserializar(InputStream &stream) {
    std::size_t tamanho;
    stream.read(&tamanho, sizeof(tamanho));
    descricao = std::string(tamanho, '\0');
    stream.read(descricao.data(), tamanho);
    
    stream.read(&timestamp, sizeof(timestamp));
    
    stream.read(&prioridade, sizeof(prioridade));

    stream.read(&concluida, sizeof(concluida));
}
