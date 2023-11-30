#ifndef GERENCIADORESTADOAPP_HPP
#define GERENCIADORESTADOAPP_HPP

#include <ListaTarefasCompromissos.hpp>
#include <TarefaCompromisso.hpp>
#include <Usuario.hpp>

/**
 * @brief Classe que lida com a lógica de negócio do programa.
 * 
 * Esta classe é responsável por gerenciar o estado atual do programa, isto é,
 * qual tela do MENU o usuário está vendo e quais ações ele pode tomar. Cada
 * estado é um método da classe.
 */
class GerenciadorEstadoApp {
public:
    /**
     * @brief Estado da tela inicial de login.
     */
    void telaInicial();
    /**
     * @brief Pede informações e faz o login do usuário.
     */
    void fazerLogin();
    /**
     * @brief Pede informações e cria um novo usuário.
     */
    void criarConta();
    
    /**
     * @brief Estado da tela principal da aplicação.
     * @param usuario Referência ao usuário logado.
     */
    void menuPrincipal(Usuario &usuario);
    /**
     * @brief Adiciona nova tarefa/compromisso à lista do usuário.
     * @param usuario Referência ao usuário logado.
     */
    void adicionarTarefaCompromisso(Usuario &usuario);
    /**
     * @brief Remove alguma tarefa/compromisso da lista do usuário.
     * @param usuario Referência ao usuário logado.
     */
    void removerTarefaCompromisso(Usuario &usuario);
    /**
     * @brief Edita alguma tarefa/compromisso da lista do usuário.
     * @param usuario Referência ao usuário logado.
     */
    void editarTarefaCompromisso(Usuario &usuario);

    /**
     * @brief Estado da tela de listagem/filtragem de tarefas/compromissos.
     * @param usuario Referência ao usuário logado.
     */
    void filtrarTarefasCompromissos(Usuario &usuario);
    /**
     * @brief Alterna, nas preferências de usuário, entre filtrar ou não as
     * tarefas concluídas.
     * @param preferencias Referência ao objeto que guarda as preferências
     * de filtragem.
     */
    void filtrarConcluidas(PreferenciasLista &preferencias);
    /**
     * @brief Alterna, nas preferências de usuário, entre filtrar ou não as
     * tarefas passadas.
     * @param preferencias Referência ao objeto que guarda as preferências
     * de filtragem.
     */
    void filtrarPassadas(PreferenciasLista &preferencias);
    /**
     * @brief Alterna, nas preferências de usuário, entre filtrar ou não as
     * tarefas de uma determinada prioridade.
     * @param preferencias Referência ao objeto que guarda as preferências
     * de filtragem.
     * @param prioridade Prioridade a ser filtrada.
     */
    void filtrarPrioridade(
        PreferenciasLista &preferencias,
        TarefaCompromisso::Prioridade prioridade
    );

    /**
     * @brief Estado da tela de listagem/reordenação de tarefas/compromissos.
     * @param usuario Referência ao usuário logado.
     */
    void reordenarTarefasCompromissos(Usuario &usuario);
    /**
     * @brief Define a ordem da lista por Data/Hora (crescente), e reordena.
     * @param preferencias Referência ao objeto que guarda as preferências
     * de reordenação.
     * @param lista Referência à lista de tarefas/compromissos a ser
     * reordenada.
     */
    void reordenarData(
        PreferenciasLista &preferencias, ListaTarefasCompromissos &lista);
    /**
     * @brief Define a ordem da lista por Data/Hora (decrescente), e reordena.
     * @param preferencias Referência ao objeto que guarda as preferências
     * de reordenação.
     * @param lista Referência à lista de tarefas/compromissos a ser
     * reordenada.
     */
    void reordenarDataDecr(
        PreferenciasLista &preferencias, ListaTarefasCompromissos &lista);
    /**
     * @brief Define a ordem da lista por Prioridade (crescente), e reordena.
     * @param preferencias Referência ao objeto que guarda as preferências
     * de reordenação.
     * @param lista Referência à lista de tarefas/compromissos a ser
     * reordenada.
     */
    void reordenarPrioridade(
        PreferenciasLista &preferencias, ListaTarefasCompromissos &lista);
    /**
     * @brief Define a ordem da lista por Prioridade (decrescente), e reordena.
     * @param preferencias Referência ao objeto que guarda as preferências
     * de reordenação.
     * @param lista Referência à lista de tarefas/compromissos a ser
     * reordenada.
     */
    void reordenarPrioridadeDecr(
        PreferenciasLista &preferencias, ListaTarefasCompromissos &lista);

    /**
     * @brief Estado da tela de edição de uma tarefa/compromisso.
     * @param usuario Referência ao usuário logado.
     * @param tarefa Referência à tarefa/compromisso a ser editada.
     */
    void menuEditarTarefa(Usuario &usuario, TarefaCompromisso &tarefa);
    /**
     * @brief Edita a descrição de uma tarefa/compromisso.
     * @param tarefa Referência à tarefa/compromisso a ser editada.
     */
    void editarDescricao(TarefaCompromisso &tarefa);
    /**
     * @brief Edita a data e hora de uma tarefa/compromisso.
     * @param tarefa Referência à tarefa/compromisso a ser editada.
     */
    void editarDataHora(TarefaCompromisso &tarefa);
    /**
     * @brief Edita a prioridade de uma tarefa/compromisso. Esta função alterna
     * entre as prioridades possíveis, em cada chamada.
     * @param tarefa Referência à tarefa/compromisso a ser editada.
     */
    void editarPrioridade(TarefaCompromisso &tarefa);
    /**
     * @brief Edita o status de conclusão de uma tarefa/compromisso. Esta
     * função alterna entre concluída e não concluída, em cada chamada.
     * @param tarefa Referência à tarefa/compromisso a ser editada.
     */
    void editarConcluida(TarefaCompromisso &tarefa);
};

#endif // GERENCIADORESTADOAPP_HPP
