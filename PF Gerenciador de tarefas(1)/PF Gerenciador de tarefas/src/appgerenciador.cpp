#include "AplicativoGerenciador.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std; // Adicionando a declaração para usar o namespace std

AplicativoGerenciador::AplicativoGerenciador() {
    // Inicialize as instâncias das classes aqui, se necessário
}

void AplicativoGerenciador::iniciar() {
    cout << "Bem-vindo ao Gerenciador de Tarefas e Compromissos!" << endl;

    while (true) {
        cout << "\nMenu Principal:" << endl;
        cout << "1. Adicionar Tarefa/Compromisso" << endl;
        cout << "2. Listar Tarefas/Compromissos" << endl;
        cout << "3. Remover Tarefa/Compromisso" << endl;
        cout << "4. Sair" << endl;
        cout << "Escolha uma opção: ";

        int escolha;
        cin >> escolha;

        switch (escolha) {
            case 1:
                adicionarTarefaCompromisso();
                break;
            case 2:
                listarTarefasCompromissos();
                break;
            case 3:
                removerTarefaCompromisso();
                break;
            case 4:
                cout << "Obrigado por usar o Gerenciador de Tarefas e Compromissos. Até logo!" << endl;
                return;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
                break;
        }
    }
}

void AplicativoGerenciador::adicionarTarefaCompromisso() {
    cin.ignore(); // Limpa o buffer de entrada

    cout << "\nAdicionar Tarefa/Compromisso:" << endl;
    cout << "Descrição: ";
    string descricao;
    getline(cin, descricao);

    // Solicitar a data e hora da tarefa/compromisso
    tm dataHora;
    dataHora.tm_sec = 0;
    dataHora.tm_min = 0;
    dataHora.tm_hour = 0;
    dataHora.tm_mday = 0;
    dataHora.tm_mon = 0;
    dataHora.tm_year = 0;

    cout << "Data (DD MM AAAA): ";
    cin >> dataHora.tm_mday >> dataHora.tm_mon >> dataHora.tm_year;
    dataHora.tm_mon -= 1; // O mês deve ser de 0 a 11
    dataHora.tm_year -= 1900; // O ano deve ser o ano atual - 1900

    cout << "Hora (HH MM): ";
    cin >> dataHora.tm_hour >> dataHora.tm_min;

    TarefaCompromisso tarefa(descricao, dataHora);

    listaTarefas.adicionarTarefaCompromisso(tarefa);

    cout << "Tarefa/Compromisso adicionado com sucesso!" << endl;

    // Simule o envio de um lembrete após 10 minutos
    notificacoes.enviarLembrete(tarefa, 10);
}

void AplicativoGerenciador::listarTarefasCompromissos() {
    cout << "\nLista de Tarefas/Compromissos:" << endl;
    listaTarefas.listarTarefasCompromissos();
}

void AplicativoGerenciador::removerTarefaCompromisso() {
    cout << "\nRemover Tarefa/Compromisso:" << endl;
    cout << "Índice da Tarefa/Compromisso a ser removida: ";

    int indice;
    cin >> indice;

    listaTarefas.removerTarefaCompromisso(indice);
    cout << "Tarefa/Compromisso removida com sucesso!" << endl;
}
