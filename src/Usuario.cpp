#include <Usuario.hpp>

Usuario::Usuario(std::string const &nome)
: nome(nome), listaTarefas(), preferencias() {}

Usuario::Usuario(
    std::string const &nome,
    ListaTarefasCompromissos const &lista
) : nome(nome), listaTarefas(lista), preferencias() {}

std::string const &Usuario::getNome() const {
    return nome;
}

ListaTarefasCompromissos& Usuario::getListaTarefas() {
    return listaTarefas;
}

PreferenciasLista& Usuario::getPreferencias() {
    return preferencias;
}
