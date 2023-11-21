#ifndef APLICATIVOGERENCIADOR_HPP
#define APLICATIVOGERENCIADOR_HPP

#include <ListaTarefasCompromissos.hpp>
#include <Usuario.hpp>

class AplicativoGerenciador {
public:
    AplicativoGerenciador();

    void iniciar();

private:
    ListaTarefasCompromissos listaTarefas;
    Notificacoes notificacoes;
    Usuario usuario;
};

#endif // APLICATIVOGERENCIADOR_HPP
