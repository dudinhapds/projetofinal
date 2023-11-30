#ifndef PREFERENCIASLISTA_HPP
#define PREFERENCIASLISTA_HPP

#include <TarefaCompromisso.hpp>
#include <Serializacao.hpp>
#include <ctime>

/**
 * @brief Preferências de filtro e ordem de uma lista de tarefas/compromissos.
 * 
 * Esta classe representa todos os filtros, e o critério de ordenação, que um
 * usuário pode aplicar a uma lista de tarefas/compromissos.
 */
class PreferenciasLista {
public:
    /**
     * @brief Subclasse representando um filtro.
     * 
     * Essa classe possui uma sobrecarga do operador `()`, que recebe uma
     * tarefa/compromisso e retorna `true` caso ela deva ser mantida na lista,
     * ou `false` caso contrário. Isso significa que uma instância dessa classe
     * pode ser passada como argumento para uma função que mostra a lista de
     * tarefas/compromissos, e essa função irá mostrar apenas as tarefas que
     * passarem no filtro.
     */
    class Filtro {
    public:
        /**
         * @brief Construtor da classe Filtro.
         * @param pref Preferências nas quais o filtro será baseado.
         */
        Filtro(PreferenciasLista const &pref);
        /**
         * @brief Sobrecarga do operador `()`.
         * @param tarefa Tarefa/compromisso a ser testada.
         * @return resultado da filtragem.
         */
        bool operator()(TarefaCompromisso const &tarefa) const;
    private:
        /**
         * @brief Referência às preferências do usuário.
         */
        PreferenciasLista const &pref;
        /**
         * @brief Timestamp do momento atual.
         */
        std::time_t const now;
    };

    /**
     * @brief Subclasse representando um comparador.
     * 
     * Essa classe possui uma sobrecarga do operador `()`, que recebe duas
     * tarefas/compromissos e retorna `true` caso a primeira deva vir antes da
     * segunda na lista, ou `false` caso contrário. Isso significa que uma
     * instância dessa classe pode ser passada como argumento para a função
     * `std::sort`, e essa função irá ordenar a lista de tarefas/compromissos
     * de acordo com o critério de ordenação definido pelo usuário.
     */
    class Comparador {
    public:
        /**
         * @brief Construtor da classe Comparador.
         * @param pref Preferências nas quais o comparador será baseado.
         */
        Comparador(PreferenciasLista const &pref);
        /**
         * @brief Sobrecarga do operador `()`.
         * @param a Tarefa/compromisso do lado esquerdo.
         * @param b Tarefa/compromisso do lado direito.
         * @return Se `a` é menor que `b`.
         */
        bool operator()(TarefaCompromisso const &a, TarefaCompromisso const &b) const;
    private:
        /**
         * @brief Referência às preferências do usuário.
         */
        PreferenciasLista const &pref;
    };

    /**
     * @brief Enumeração representando os possíveis critérios de ordenação.
     */
    enum class Ordem {
        DATA            = 0,
        DATA_DECR       = 1,
        PRIORIDADE      = 2,
        PRIORIDADE_DECR = 3,
    };

    /**
     * @brief Construtor da classe PreferenciasLista.
     */
    PreferenciasLista();

    /**
     * @brief Getter do atributo `concluidas`.
     * @return referência ao atributo `concluidas`.
     */
    bool &getConcluidas();  // Getter & Setter
    /**
     * @brief Getter do atributo `passadas`.
     * @return referência ao atributo `passadas`.
     */
    bool &getPassadas();    // Getter & Setter
    /**
     * @brief Getter do atributo `prioridades`.
     * @param prioridade Prioridade a ser obtida.
     * @return referência ao booleano de filtro da prioridade.
     */
    bool &getPrioridade(TarefaCompromisso::Prioridade prioridade);
    /**
     * @brief Getter do atributo `ordem`.
     * @return referência ao atributo `ordem`.
     */
    Ordem &getOrdem(); // Getter & Setter

    /**
     * @brief Gera um objeto Filtro a partir das preferências.
     * @return Instância de Filtro.
     */
    Filtro getFiltro() const;
    /**
     * @brief Gera um objeto Comparador a partir das preferências.
     * @return Instância de Comparador.
     */
    Comparador getComparador() const;

    /**
     * @brief Serializa (escreve) as preferências.
     * @param stream Stream de saída.
     */
    void serializar(OutputStream &stream) const;
    /**
     * @brief Deserializa (lê) as preferências.
     * @param stream Stream de entrada.
     */
    void deserializar(InputStream &stream);

private:
    /**
     * @brief Atributo que representa se tarefas/compromissos concluídos devem
     * ser mostrados.
     */
    bool concluidas;
    /**
     * @brief Atributo que representa se tarefas/compromissos passados devem
     * ser mostrados.
     */
    bool passadas;

    /**
     * @brief Atributo que representa se tarefas/compromissos de cada
     * prioridade devem ser mostrados.
     */
    bool prioridades[3];

    /**
     * @brief Atributo que representa o critério de ordenação.
     */
    Ordem ordem;
};

#endif // PREFERENCIASLISTA_HPP
