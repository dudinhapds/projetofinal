#ifndef TAREFACOMPROMISSO_HPP
#define TAREFACOMPROMISSO_HPP

#include <Serializacao.hpp>

#include <string>
#include <ctime>

/**
 * @brief Classe representando uma tarefa/compromisso.
 * 
 * Contém descrição, data/hora, prioridade e se está concluída ou não.
 */
class TarefaCompromisso {
public:
    /**
     * @brief Enumeração representando a prioridade de uma tarefa/compromisso.
     */
    enum Prioridade {
        P_BAIXA = 1,
        P_MEDIA = 2,
        P_ALTA  = 3,
    };

    /**
     * @brief Construtor padrão.
     */
    TarefaCompromisso() = default;
    /**
     * @brief Construtor da classe TarefaCompromisso.
     * @param descricao Descrição da tarefa/compromisso.
     * @param timestamp Data/hora (em `std::time_t`) da tarefa/compromisso.
     * @param prioridade Prioridade da tarefa/compromisso.
     * @param concluida Se a tarefa/compromisso está concluída ou não. Valor
     * padrão é `false`.
     */
    TarefaCompromisso(
        const std::string& descricao,
        const std::time_t timestamp,
        Prioridade prioridade,
        bool concluida = false
    );

    /**
     * @brief Getter da descrição.
     * @return Referência constante à descrição.
     */
    const std::string& getDescricao() const;
    /**
     * @brief Setter da descrição.
     * @param descricao Nova descrição.
     */
    void setDescricao(const std::string &descricao);
    /**
     * @brief Getter do timestamp.
     * @return Timestamp.
     */
    std::time_t getTimestamp() const;
    /**
     * @brief Setter do timestamp.
     * @param timestamp Novo timestamp.
     */
    void setTimestamp(std::time_t timestamp);
    /**
     * @brief Getter da data/hora.
     * @return Data/hora (gerada a partir do timestamp salvo).
     */
    std::tm getDataHora() const;
    /**
     * @brief Getter da prioridade.
     * @return Prioridade.
     */
    Prioridade getPrioridade() const;
    /**
     * @brief Setter da prioridade.
     * @param prioridade Nova prioridade.
     */
    void setPrioridade(Prioridade prioridade);
    /**
     * @brief Getter de `concluida`.
     * @return Se a tarefa/compromisso está concluída ou não.
     */
    bool getConcluida() const;
    /**
     * @brief Setter de `concluida`.
     * @param b Novo valor de `concluida`.
     */
    void setConcluida(bool b);

    /**
     * @brief Serializa (escreve) a tarefa/compromisso.
     * @param stream Stream de saída.
     */
    void serializar(OutputStream &stream) const;
    /**
     * @brief Deserializa (lê) a tarefa/compromisso.
     * @param stream Stream de entrada.
     */
    void deserializar(InputStream &stream);

private:
    /**
     * @brief Descrição da tarefa/compromisso.
     */
    std::string descricao;
    /**
     * @brief Timestamp da tarefa/compromisso.
     */
    std::time_t timestamp;
    /**
     * @brief Prioridade da tarefa/compromisso.
     */
    Prioridade prioridade;
    /**
     * @brief Se a tarefa/compromisso está concluída ou não.
     */
    bool concluida;
};

#endif // TAREFACOMPROMISSO_HPP
