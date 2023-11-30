#include <ListaTarefasCompromissos.hpp>
#include <algorithm>

void ListaTarefasCompromissos::adicionarTarefaCompromisso(const TarefaCompromisso& tarefaCompromisso) {
    // std::vector<TarefaCompromisso>::iterator it;
    // for (it = tarefasCompromissos.begin(); it != tarefasCompromissos.end(); ++it) {
    //     if (tarefaCompromisso.getTimestamp() < it->getTimestamp()) break;
    // }
    // tarefasCompromissos.insert(it, tarefaCompromisso);
    tarefasCompromissos.push_back(tarefaCompromisso);
}

void ListaTarefasCompromissos::reordenarLista(
    std::function<bool(
        TarefaCompromisso const &, TarefaCompromisso const &
    )> comparador
) {
    std::sort(tarefasCompromissos.begin(), tarefasCompromissos.end(), comparador);
}

std::vector<TarefaCompromisso> const &ListaTarefasCompromissos::getLista() const {
    return tarefasCompromissos;
}

std::optional<TarefaCompromisso> ListaTarefasCompromissos::getTarefaCompromisso(
    size_t indice
) {
    if (indice > 0 && indice <= tarefasCompromissos.size())
        return tarefasCompromissos[indice - 1];
    else
        return std::nullopt;
}

bool ListaTarefasCompromissos::removerTarefaCompromisso(size_t indice) {
    if (indice - 1 < tarefasCompromissos.size()) {
        tarefasCompromissos.erase(tarefasCompromissos.begin() + indice - 1);
        return true;
    }
    return false;
}

void ListaTarefasCompromissos::serializar(OutputStream &stream) const {
    std::size_t tamanho = tarefasCompromissos.size();
    stream.write(&tamanho, sizeof(tamanho));
    for (TarefaCompromisso t : tarefasCompromissos) {
        t.serializar(stream);
    }
}

void ListaTarefasCompromissos::deserializar(InputStream &stream) {
    std::size_t tamanho;
    if (stream.read(&tamanho, sizeof(tamanho)) != sizeof(tamanho)) {
        tamanho = 0;
    }
    tarefasCompromissos = std::vector<TarefaCompromisso>(tamanho);
    for (std::size_t i = 0; i < tamanho; ++i) {
        tarefasCompromissos[i].deserializar(stream);
    }
}
