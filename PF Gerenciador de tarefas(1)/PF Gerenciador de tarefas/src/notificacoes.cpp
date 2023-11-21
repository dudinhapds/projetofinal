#include "Notificacoes.hpp"
#include <iostream>
#include <chrono>
#include <thread>

void Notificacoes::enviarLembrete(const TarefaCompromisso& tarefaCompromisso, int minutosAntes) {
    std::cout << "Lembrete: " << tarefaCompromisso.getDescricao() << " em breve!" << std::endl;

    // Aguardar alguns segundos (simulando uma notificação em tempo real)
    std::this_thread::sleep_for(std::chrono::seconds(5));
}
