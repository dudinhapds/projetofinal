#ifndef LISTATAREFASCOMPROMISSOS_HPP
#define LISTATAREFASCOMPROMISSOS_HPP

#include <TarefaCompromisso.hpp>
#include <Serializacao.hpp>
#include <optional>
#include <functional>
#include <vector>

/**
 * @brief Representa uma lista de tarefas/compromissos.
 */
class ListaTarefasCompromissos {
public:
    /**
     * @brief Adiciona uma tarefa/compromisso à lista.
     * @param tarefaCompromisso Referência à tarefa/compromisso a ser
     * adicionada.
     */
    void adicionarTarefaCompromisso(const TarefaCompromisso& tarefaCompromisso);
    /**
     * @brief Reordena a lista com base em um critério
     * 
     * Este método recebe uma função comparadora, que por sua vez recebe duas
     * tarefas/compromissos e compara-as. A lista é então reordenada com base
     * nessa função comparadora.
     * 
     * @param comparador Função comparadora que representa o critério de ordem.
     */
    void reordenarLista(
        std::function<bool(
            TarefaCompromisso const &, TarefaCompromisso const &
        )> comparador
    );
    /**
     * @brief Retorna uma referência constante à lista de tarefas/compromissos.
     * @return Referência constante à lista de tarefas/compromissos.
     */
    std::vector<TarefaCompromisso> const &getLista() const;
    /**
     * @brief Retorna opcionalmente uma tarefa/compromisso da lista.
     * 
     * Esta função falha caso o índice seja inválido, retornando `std::nullopt`.
     * 
     * @param indice Índice (começando em 1) da tarefa/compromisso a ser
     * retornada.
     * @return Tarefa/compromisso da lista.
     */
    std::optional<TarefaCompromisso> getTarefaCompromisso(size_t indice);
    /**
     * @brief Remove uma tarefa/compromisso da lista.
     * @param indice Índice (começando em 1) da tarefa/compromisso a ser
     * removida.
     * @return `true` se a tarefa/compromisso foi removida, `false` caso
     * contrário.
     */
    bool removerTarefaCompromisso(size_t indice);

    /**
     * @brief Serializa (escreve) a lista de tarefas/compromissos.
     * @param stream Stream de saída.
     */
    void serializar(OutputStream &stream) const;
    /**
     * @brief Deserializa (lê) a lista de tarefas/compromissos.
     * @param stream Stream de entrada.
     */
    void deserializar(InputStream &stream);

private:
    /**
     * @brief Membro interno que armazena a lista de tarefas/compromissos.
     */
    std::vector<TarefaCompromisso> tarefasCompromissos;
};

#endif // LISTATAREFASCOMPROMISSOS_HPP
