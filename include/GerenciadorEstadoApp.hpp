#ifndef GERENCIADORESTADOAPP_HPP
#define GERENCIADORESTADOAPP_HPP

#include <ListaTarefasCompromissos.hpp>
#include <TarefaCompromisso.hpp>
#include <Usuario.hpp>

class GerenciadorEstadoApp {
public:
    void telaInicial();
    void fazerLogin();
    void criarConta();
    
    void menuPrincipal(Usuario &usuario);
    void adicionarTarefaCompromisso(Usuario &usuario);
    void removerTarefaCompromisso(Usuario &usuario);
    void editarTarefaCompromisso(Usuario &usuario);

    void filtrarTarefasCompromissos(Usuario &usuario);
    void filtrarConcluidas(PreferenciasLista &preferencias);
    void filtrarPassadas(PreferenciasLista &preferencias);
    void filtrarPrioridade(
        PreferenciasLista &preferencias,
        TarefaCompromisso::Prioridade prioridade
    );

    void reordenarTarefasCompromissos(Usuario &usuario);
    void reordenarData(
        PreferenciasLista &preferencias, ListaTarefasCompromissos &lista);
    void reordenarDataDecr(
        PreferenciasLista &preferencias, ListaTarefasCompromissos &lista);
    void reordenarPrioridade(
        PreferenciasLista &preferencias, ListaTarefasCompromissos &lista);
    void reordenarPrioridadeDecr(
        PreferenciasLista &preferencias, ListaTarefasCompromissos &lista);

    void menuEditarTarefa(Usuario &usuario, TarefaCompromisso &tarefa);
    void editarDescricao(TarefaCompromisso &tarefa);
    void editarDataHora(TarefaCompromisso &tarefa);
    void editarPrioridade(TarefaCompromisso &tarefa);
    void editarConcluida(TarefaCompromisso &tarefa);
};

#endif // GERENCIADORESTADOAPP_HPP
