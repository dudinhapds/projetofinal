#include <PreferenciasLista.hpp>

PreferenciasLista::Filtro::Filtro(
    PreferenciasLista const &pref
) : pref(pref), now(std::time(nullptr)) {}

bool PreferenciasLista::Filtro::operator()(
    TarefaCompromisso const &tarefa
) const {
    return
        (pref.concluidas || !tarefa.getConcluida()) &&
        (pref.passadas || tarefa.getTimestamp() >= now) &&
        (pref.prioridades[(int) tarefa.getPrioridade() - 1]);
}

PreferenciasLista::Comparador::Comparador(
    PreferenciasLista const &pref
) : pref(pref) {}

bool PreferenciasLista::Comparador::operator()(
    TarefaCompromisso const &a,
    TarefaCompromisso const &b
) const {
    switch (pref.ordem) {
        case Ordem::DATA:
            return a.getTimestamp() < b.getTimestamp();
        case Ordem::DATA_DECR:
            return a.getTimestamp() > b.getTimestamp();
        case Ordem::PRIORIDADE:
            return a.getPrioridade() < b.getPrioridade();
        case Ordem::PRIORIDADE_DECR:
            return a.getPrioridade() > b.getPrioridade();
    }
    return false;
}

PreferenciasLista::PreferenciasLista()
: concluidas(true), passadas(true), prioridades{true, true, true} {}

bool &PreferenciasLista::getConcluidas() {
    return concluidas;
}

bool &PreferenciasLista::getPassadas() {
    return passadas;
}

bool &PreferenciasLista::getPrioridade(TarefaCompromisso::Prioridade prioridade) {
    return prioridades[(int) prioridade - 1];
}

PreferenciasLista::Ordem &PreferenciasLista::getOrdem() {
    return ordem;
}

PreferenciasLista::Filtro PreferenciasLista::getFiltro() const {
    return Filtro(*this);
}

PreferenciasLista::Comparador PreferenciasLista::getComparador() const {
    return Comparador(*this);
}

void PreferenciasLista::serializar(OutputStream &stream) const {
    stream.write(&concluidas, sizeof(bool));
    stream.write(&passadas, sizeof(bool));
}

void PreferenciasLista::deserializar(InputStream &stream) {
    stream.read(&concluidas, sizeof(bool));
    stream.read(&passadas, sizeof(bool));
}
