#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <ListaTarefasCompromissos.hpp>
#include <PreferenciasLista.hpp>
#include <string>

class Usuario {
public:
    Usuario(std::string const &nome, ListaTarefasCompromissos const &lista);

    std::string const &getNome() const;
    ListaTarefasCompromissos &getListaTarefas();
    PreferenciasLista &getPreferencias();
private:
    std::string nome;
    ListaTarefasCompromissos listaTarefas;
    PreferenciasLista preferencias;
};

#endif // USUARIO_HPP
