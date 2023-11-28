#ifndef LISTATAREFASCOMPROMISSOS_HPP
#define LISTATAREFASCOMPROMISSOS_HPP

#include <TarefaCompromisso.hpp>
#include <Serializacao.hpp>
#include <optional>
#include <functional>
#include <vector>

class ListaTarefasCompromissos {
public:
    void adicionarTarefaCompromisso(const TarefaCompromisso& tarefaCompromisso);
    void reordenarLista(
        std::function<bool(
            TarefaCompromisso const &, TarefaCompromisso const &
        )> comparador
    );
    std::vector<TarefaCompromisso> const &getLista() const;
    std::optional<TarefaCompromisso> getTarefaCompromisso(size_t indice);
    bool removerTarefaCompromisso(size_t indice);

    void serializar(OutputStream &stream) const;
    void deserializar(InputStream &stream);

private:
    std::vector<TarefaCompromisso> tarefasCompromissos;
};

#endif // LISTATAREFASCOMPROMISSOS_HPP
