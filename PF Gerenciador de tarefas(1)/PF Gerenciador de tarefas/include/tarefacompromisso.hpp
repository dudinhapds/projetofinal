#ifndef TAREFACOMPROMISSO_HPP
#define TAREFACOMPROMISSO_HPP

#include <string>
#include <ctime>

class TarefaCompromisso {
public:
    TarefaCompromisso(const std::string& descricao, const std::tm& dataHora, bool concluida = false);

    const std::string& getDescricao() const;
    const std::tm& getDataHora() const;
    bool estaConcluida() const;
    void marcarConcluida();

private:
    std::string descricao;
    std::tm dataHora;
    bool concluida;
};

#endif // TAREFACOMPROMISSO_HPP
