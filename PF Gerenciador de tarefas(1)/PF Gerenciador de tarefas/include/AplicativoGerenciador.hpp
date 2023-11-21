#ifndef APLICATIVOGERENCIADOR_HPP
#define APLICATIVOGERENCIADOR_HPP

#include <ListaTarefasCompromissos.hpp>
#include <Usuario.hpp>

class AplicativoGerenciador {
public:
    void telaInicial();
    void fazerLogin();
    void criarConta();
    
    void menuPrincipal(Usuario &usuario);
    void adicionarTarefaCompromisso(Usuario &usuario);
    void listarTarefasCompromissos(Usuario &usuario);
    void concluirTarefaCompromisso(Usuario &usuario);
    void removerTarefaCompromisso(Usuario &usuario);
};

#endif // APLICATIVOGERENCIADOR_HPP
