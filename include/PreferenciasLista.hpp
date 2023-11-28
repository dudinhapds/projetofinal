#ifndef PREFERENCIASLISTA_HPP
#define PREFERENCIASLISTA_HPP

#include <TarefaCompromisso.hpp>
#include <Serializacao.hpp>
#include <ctime>

class PreferenciasLista {
public:
    class Filtro {
    public:
        Filtro(PreferenciasLista const &pref);
        bool operator()(TarefaCompromisso const &tarefa) const;
    private:
        PreferenciasLista const &pref;
        std::time_t const now;
    };

    class Comparador {
    public:
        Comparador(PreferenciasLista const &pref);
        bool operator()(TarefaCompromisso const &a, TarefaCompromisso const &b) const;
    private:
        PreferenciasLista const &pref;
    };

    enum class Ordem {
        DATA            = 0,
        DATA_DECR       = 1,
        PRIORIDADE      = 2,
        PRIORIDADE_DECR = 3,
    };

    PreferenciasLista();

    bool &getConcluidas();  // Getter & Setter
    bool &getPassadas();    // Getter & Setter
    bool &getPrioridade(TarefaCompromisso::Prioridade prioridade);
    Ordem &getOrdem(); // Getter & Setter

    Filtro getFiltro() const;
    Comparador getComparador() const;

    void serializar(OutputStream &stream) const;
    void deserializar(InputStream &stream);

private:
    bool concluidas;
    bool passadas;

    bool prioridades[3];

    Ordem ordem;
};

#endif // PREFERENCIASLISTA_HPP
