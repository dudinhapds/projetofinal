#ifndef TAREFACOMPROMISSO_HPP
#define TAREFACOMPROMISSO_HPP

#include <Serializacao.hpp>

#include <string>
#include <ctime>

class TarefaCompromisso {
public:
    enum Prioridade {
        P_BAIXA = 1,
        P_MEDIA = 2,
        P_ALTA  = 3,
    };

    TarefaCompromisso() = default;
    TarefaCompromisso(
        const std::string& descricao,
        const std::time_t timestamp,
        Prioridade prioridade,
        bool concluida = false
    );

    const std::string& getDescricao() const;
    void setDescricao(const std::string &descricao);
    std::time_t getTimestamp() const;
    void setTimestamp(std::time_t timestamp);
    std::tm getDataHora() const;
    Prioridade getPrioridade() const;
    void setPrioridade(Prioridade prioridade);
    bool getConcluida() const;
    void setConcluida(bool b);

    void serializar(OutputStream &stream) const;
    void deserializar(InputStream &stream);

private:
    std::string descricao;
    std::time_t timestamp;
    Prioridade prioridade;
    bool concluida;
};

#endif // TAREFACOMPROMISSO_HPP
