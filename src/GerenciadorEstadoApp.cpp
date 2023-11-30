#include <GerenciadorEstadoApp.hpp>
#include <AutenticadorUsuario.hpp>
#include <Cores.hpp>

#include <functional>
#include <iostream>
#include <ctime>

static char const *boolToStr(bool b) {
    return b ? SIM "Sim" RESET : NAO "Não" RESET;
}

static char const *prioridadeToStr(TarefaCompromisso::Prioridade p) {
    char const *prioridades[] = {
        COR_P_BAIXA "Baixa" RESET,
        COR_P_MEDIA "Média" RESET,
        COR_P_ALTA  "Alta"  RESET,
    };
    return prioridades[(int) p - 1];
}

// static char const *datefmt = "%d/%m/%Y %H:%M";
static char const *datefmt = "%a %d %b %Y - %H:%M";

static void imprimirTarefa(TarefaCompromisso const &tarefaCompromisso) {
    char buffer[32];
    std::tm dataHora = tarefaCompromisso.getDataHora();
    std::strftime(buffer, sizeof(buffer), datefmt, &dataHora);
    std::printf(
        "Descrição:    %s\n"
        "Data e Hora:  %s\n"
        "Prioridade:   %s\n"
        "Concluída:    %s\n",
        tarefaCompromisso.getDescricao().c_str(),
        buffer,
        prioridadeToStr(tarefaCompromisso.getPrioridade()),
        boolToStr(tarefaCompromisso.getConcluida())
    );
}

static void imprimirLista(
    ListaTarefasCompromissos &lista,
    std::function<bool(TarefaCompromisso const &)> filtro
) {
    char buffer[32];
    std::vector<TarefaCompromisso> const &tarefas = lista.getLista();
    for (size_t i = 0; i < tarefas.size(); ++i) {
        TarefaCompromisso const &tarefaCompromisso = tarefas[i];
        if (!filtro(tarefaCompromisso)) continue;

        std::tm dataHora = tarefaCompromisso.getDataHora();
        std::strftime(buffer, sizeof(buffer), datefmt, &dataHora);

        std::printf(
            "%02lu"
              "  Descrição:    %s\n"
            "    Data e Hora:  %s\n"
            "    Prioridade:   %s\n"
            "    Concluída:    %s\n\n",
            i + 1,
            tarefaCompromisso.getDescricao().c_str(),
            buffer,
            prioridadeToStr(tarefaCompromisso.getPrioridade()),
            boolToStr(tarefaCompromisso.getConcluida())
        );
    }
}

void GerenciadorEstadoApp::telaInicial() {
    std::cout << TELA;
    while (true) {
        std::cout
            << "=======================================================\n"
            << "= Bem-vindo ao Gerenciador de Tarefas e Compromissos! =\n"
            << "=======================================================\n"
            << "\n"
            << MENU "=== LOGIN ===" RESET "\n"
            << "\n"
            << "1. Fazer Login\n"
            << "2. Criar Conta\n"
            << "0. Sair\n"
            << "\n"
            << "Escolha uma opção: ";

        int escolha;
        std::cin >> escolha;

        switch (escolha) {
            case 1: fazerLogin(); break;
            case 2: criarConta(); break;
            
            case 0:
                std::cout
                    << "\n"
                    << MENU "Obrigado por usar o Gerenciador de Tarefas e Compromissos. Até logo!\n"
                    << "\n";
                return;
            default:
                std::cout
                    << TELA
                    << ERRO "Opção inválida. Pressione ENTER para tentar novamente." RESET "\n"
                    << "\n";
                break;
        }
    }      
}

void GerenciadorEstadoApp::fazerLogin() {
    std::cin.ignore(); // Limpa o buffer de entrada

    std::cout << "\n" MENU "=== Fazer Login ===" RESET "\n\n";
    std::cout << "Nome de usuário: ";
    std::string nome;
    std::getline(std::cin, nome);

    std::cout << "Senha: " SENHA;
    std::string senha;
    std::getline(std::cin, senha);
    std::cout << RESET;

    auto resultado = AutenticadorUsuario::autenticar(nome, senha);
    if (!resultado) {
        std::cout
            << TELA
            << ERRO "Usuário ou senha incorretos. Tente novamente." RESET "\n"
            << "\n";
        return;
    }

    SerializadorUsuario &serializador = *resultado;
    Usuario usuario = Usuario(nome);
    serializador.deserializar(&usuario);

    std::cout
        << TELA MENU "Seja bem-vindo, " << usuario.getNome() << "!" RESET "\n"
        << "\n";
    menuPrincipal(usuario);

    std::cout
        << "Salvando alterações...\n"
        << "\n";
    serializador.serializar(usuario);
}

void GerenciadorEstadoApp::criarConta() {
    std::cin.ignore(); // Limpa o buffer de entrada

    std::cout << "\n" MENU "=== Criar Conta ===" RESET "\n\n";
    std::cout << "Nome de usuário: ";
    std::string nome;
    std::getline(std::cin, nome);

    std::cout << "Senha: " SENHA;
    std::string senha;
    std::getline(std::cin, senha);
    std::cout << RESET;

    auto resultado = AutenticadorUsuario::criar(nome, senha);
    if (!resultado) {
        std::cout
            << TELA
            << ERRO "Nome de usuário já existe. Escolha outro nome." RESET "\n"
            << "\n";
        return;
    }

    SerializadorUsuario &serializador = *resultado;
    Usuario usuario = Usuario(nome, ListaTarefasCompromissos());

    std::cout
        << TELA MENU "Seja bem-vindo, " << usuario.getNome() << "!" RESET "\n"
        << "\n";
    menuPrincipal(usuario);

    std::cout
        << "Salvando alterações...\n"
        << "\n";
    serializador.serializar(usuario);
}

void GerenciadorEstadoApp::menuPrincipal(Usuario &usuario) {
    // std::cout << TELA;
    while (true) {
        std::cout
            << MENU "=== Lista Tarefas/Compromissos ===" RESET "\n"
            << "\n";

        imprimirLista(
            usuario.getListaTarefas(),
            usuario.getPreferencias().getFiltro()
        );

        std::cout
            << MENU "=== MENU ===" RESET "\n"
            << "\n"
            << "1. Adicionar Tarefa/Compromisso\n"
            << "2. Remover Tarefa/Compromisso\n"
            << "3. Filtrar Tarefas/Compromissos\n"
            << "4. Reordenar Tarefas/Compromissos\n"
            << "5. Editar Tarefa/Compromisso\n"
            << "0. Sair\n"
            << "\n"
            << "Escolha uma opção: ";

        int escolha;
        std::cin >> escolha;

        switch (escolha) {
            case 1: adicionarTarefaCompromisso(usuario);   break;
            case 2: removerTarefaCompromisso(usuario);     break;
            case 3: filtrarTarefasCompromissos(usuario);   break;
            case 4: reordenarTarefasCompromissos(usuario); break;
            case 5: editarTarefaCompromisso(usuario);      break;

            case 0:
                std::cout
                    << TELA
                    << "Efetuando logout de " << usuario.getNome() << "...\n"
                    << "\n";
                return;
            default:
                std::cout
                    << TELA
                    << ERRO "Opção inválida. Pressione ENTER para tentar novamente." RESET "\n"
                    << "\n";
                break;
        }
    }
}

void GerenciadorEstadoApp::adicionarTarefaCompromisso(Usuario &usuario) {
    std::cin.ignore(); // Limpa o buffer de entrada

    std::cout << "\n" MENU "=== Adicionar Tarefa/Compromisso ===" RESET "\n\n";
    std::cout << "Descrição: ";
    std::string descricao;
    std::getline(std::cin, descricao);

    // Solicitar a data e hora da tarefa/compromisso
    std::tm dataHora = {0};

    std::cout << "Data (DD MM AAAA): ";
    std::cin >> dataHora.tm_mday >> dataHora.tm_mon >> dataHora.tm_year;
    dataHora.tm_mon -= 1; // O mês deve ser de 0 a 11
    dataHora.tm_year -= 1900; // O ano deve ser o ano atual - 1900

    std::cout << "Hora (HH MM): ";
    std::cin >> dataHora.tm_hour >> dataHora.tm_min;

    int escolha;
    std::cout
        << "Prioridades:\n"
        << "1 - Baixa\n"
        << "2 - Média\n"
        << "3 - Alta\n"
        << "Defina uma prioridade: ";
    while (true) {
        std::cin >> escolha;
        if (escolha >= 1 && escolha <= 3) break;
        std::cout << ERRO "Prioridade inválida!" RESET " Defina uma prioridade: ";
    }

    TarefaCompromisso tarefa(
        descricao,
        std::mktime(&dataHora),
        (TarefaCompromisso::Prioridade) escolha
    );

    usuario.getListaTarefas().adicionarTarefaCompromisso(tarefa);
    usuario.getListaTarefas().reordenarLista(
        usuario.getPreferencias().getComparador()
    );

    std::cout
        << TELA
        << OK "Tarefa/Compromisso adicionado com sucesso!" RESET "\n"
        << "\n";
}

void GerenciadorEstadoApp::removerTarefaCompromisso(Usuario &usuario) {
    int indice, indice2;
    std::cout
        << "\n"
        << MENU "=== Remover Tarefa/Compromisso ===" RESET "\n"
        << "\n";

    std::cout << "Índice da Tarefa/Compromisso a ser removida: ";
    std::cin >> indice;
    std::cout << "Confirme o índice: ";
    std::cin >> indice2;

    if (indice != indice2) {
        std::cout
            << TELA
            << ERRO "Índices não coincidem!" RESET "\n"
            << "\n";
    }
    else if (!usuario.getListaTarefas().removerTarefaCompromisso(indice)) {
        std::cout
            << TELA
            << ERRO "Tarefa/Compromisso não pôde ser removida!" RESET "\n"
            << "\n";
    }
    else {
        std::cout
            << TELA
            << OK "Tarefa/Compromisso removida com sucesso!" RESET "\n"
            << "\n";
    }
}

void GerenciadorEstadoApp::filtrarTarefasCompromissos(Usuario &usuario) {
    PreferenciasLista &preferencias = usuario.getPreferencias();
    
    std::cout << TELA;
    while (true) {
        std::cout
            << MENU "=== Lista Tarefas/Compromissos ===" RESET "\n"
            << "\n";

        imprimirLista(
            usuario.getListaTarefas(),
            preferencias.getFiltro()
        );

        std::cout
            << "\n" MENU "=== Opções ===" RESET "\n"
            << "\n"
            << "1. Mostrar prioridade " COR_P_BAIXA "baixa" RESET ":  "
                << boolToStr(preferencias.getPrioridade(TarefaCompromisso::P_BAIXA)) << "\n"
            << "2. Mostrar prioridade " COR_P_MEDIA "média" RESET ":  "
                << boolToStr(preferencias.getPrioridade(TarefaCompromisso::P_MEDIA)) << "\n"
            << "3. Mostrar prioridade " COR_P_ALTA "alta" RESET ":   "
                << boolToStr(preferencias.getPrioridade(TarefaCompromisso::P_ALTA)) << "\n"
            << "4. Mostrar concluídas:  " << boolToStr(preferencias.getConcluidas()) << "\n"
            << "5. Mostrar passadas:    " << boolToStr(preferencias.getPassadas()) << "\n"
            << "0. Voltar\n"
            << "\n"
            << "Escolha uma opção: ";

        int escolha;
        std::cin >> escolha;

        switch (escolha) {
            case 1: filtrarPrioridade(preferencias, TarefaCompromisso::P_BAIXA); break;
            case 2: filtrarPrioridade(preferencias, TarefaCompromisso::P_MEDIA); break;
            case 3: filtrarPrioridade(preferencias, TarefaCompromisso::P_ALTA);  break;
            case 4: filtrarConcluidas(preferencias); break;
            case 5: filtrarPassadas(preferencias);   break;

            case 0:
                std::cout << TELA;
                return;
            default:
                std::cout
                    << TELA
                    << ERRO "Opção inválida. Pressione ENTER para tentar novamente." RESET "\n"
                    << "\n";
                break;
        }
    }
}

void GerenciadorEstadoApp::filtrarConcluidas(PreferenciasLista &preferencias) {
    preferencias.getConcluidas() = !preferencias.getConcluidas();
    std::cout << TELA;
}

void GerenciadorEstadoApp::filtrarPassadas(PreferenciasLista &preferencias) {
    preferencias.getPassadas() = !preferencias.getPassadas();
    std::cout << TELA;
}

void GerenciadorEstadoApp::filtrarPrioridade(
    PreferenciasLista &preferencias,
    TarefaCompromisso::Prioridade prioridade
) {
    preferencias.getPrioridade(prioridade) = !preferencias.getPrioridade(prioridade);
    std::cout << TELA;
}

void GerenciadorEstadoApp::reordenarTarefasCompromissos(Usuario &usuario) {
    PreferenciasLista &preferencias = usuario.getPreferencias();
    ListaTarefasCompromissos &lista = usuario.getListaTarefas();
    
    std::cout << TELA;
    while (true) {
        std::cout
            << MENU "=== Lista Tarefas/Compromissos ===" RESET "\n"
            << "\n";

        imprimirLista(lista, preferencias.getFiltro());

        std::cout
            << "\n" MENU "=== Opções ===" RESET "\n"
            << "\n"
            << "1. Ordenar por data e hora\n"
            << "2. Ordenar por data e hora (decrescente)\n"
            << "3. Ordenar por prioridade\n"
            << "4. Ordenar por prioridade (decrescente)\n"
            << "0. Voltar\n"
            << "\n"
            << "Escolha uma opção: ";

        int escolha;
        std::cin >> escolha;

        switch (escolha) {
            case 1: reordenarData(preferencias, lista);           break;
            case 2: reordenarDataDecr(preferencias, lista);       break;
            case 3: reordenarPrioridade(preferencias, lista);     break;
            case 4: reordenarPrioridadeDecr(preferencias, lista); break;

            case 0:
                std::cout << TELA;
                return;
            default:
                std::cout
                    << TELA
                    << ERRO "Opção inválida. Pressione ENTER para tentar novamente." RESET "\n"
                    << "\n";
                break;
        }
    }
}

void GerenciadorEstadoApp::reordenarData(
    PreferenciasLista &preferencias, ListaTarefasCompromissos &lista
) {
    preferencias.getOrdem() = PreferenciasLista::Ordem::DATA;
    lista.reordenarLista(preferencias.getComparador());
    std::cout << TELA;
}

void GerenciadorEstadoApp::reordenarDataDecr(
    PreferenciasLista &preferencias, ListaTarefasCompromissos &lista
) {
    preferencias.getOrdem() = PreferenciasLista::Ordem::DATA_DECR;
    lista.reordenarLista(preferencias.getComparador());
    std::cout << TELA;
}

void GerenciadorEstadoApp::reordenarPrioridade(
    PreferenciasLista &preferencias, ListaTarefasCompromissos &lista
) {
    preferencias.getOrdem() = PreferenciasLista::Ordem::PRIORIDADE;
    lista.reordenarLista(preferencias.getComparador());
    std::cout << TELA;
}

void GerenciadorEstadoApp::reordenarPrioridadeDecr(
    PreferenciasLista &preferencias, ListaTarefasCompromissos &lista
) {
    preferencias.getOrdem() = PreferenciasLista::Ordem::PRIORIDADE_DECR;
    lista.reordenarLista(preferencias.getComparador());
    std::cout << TELA;
}

void GerenciadorEstadoApp::editarTarefaCompromisso(Usuario &usuario) {
    std::cout << "\n" MENU "=== Editar Tarefa/Compromisso ===" RESET "\n\n";
    ListaTarefasCompromissos &lista = usuario.getListaTarefas();

    std::cout << "Índice da Tarefa/Compromisso: ";

    int indice;
    std::cin >> indice;

    auto result = lista.getTarefaCompromisso(indice);
    if (!result) {
        std::cout
            << TELA
            << ERRO "Tarefa/Compromisso inválida!" RESET "\n"
            << "\n";
        return;
    }
    TarefaCompromisso tarefa = *result;
    
    std::cout << TELA;
    menuEditarTarefa(usuario, tarefa);

    lista.removerTarefaCompromisso(indice);
    lista.adicionarTarefaCompromisso(tarefa);

    std::cout
        << TELA
        << OK "Tarefa/Compromisso salva!" RESET "\n"
        << "\n";
}

void GerenciadorEstadoApp::menuEditarTarefa(Usuario &usuario, TarefaCompromisso &tarefa) {
    while (true) {
        std::cout << "\n" MENU "=== Editar Tarefa/Compromisso ===" RESET "\n\n";

        imprimirTarefa(tarefa);

        std::cout
            << "\n"
            << MENU "=== Opções ===" RESET "\n"
            << "\n"
            << "1. Editar descrição\n"
            << "2. Editar data e hora\n"
            << "3. Prioridade: " << prioridadeToStr(tarefa.getPrioridade()) << "\n"
            << "4. Concluída:  " << boolToStr(tarefa.getConcluida()) << "\n"
            << "0. Voltar\n"
            << "\n"
            << "Escolha uma opção: ";

        int escolha;
        std::cin >> escolha;

        switch (escolha) {
            case 1: editarDescricao(tarefa);  break;
            case 2: editarDataHora(tarefa);   break;
            case 3: editarPrioridade(tarefa); break;
            case 4: editarConcluida(tarefa);  break;

            case 0: 
                std::cout << TELA;
                return;
            default:
                std::cout
                    << TELA
                    << ERRO "Opção inválida. Pressione ENTER para tentar novamente." RESET "\n"
                    << "\n";
                break;
        }
    }
}

void GerenciadorEstadoApp::editarDescricao(TarefaCompromisso &tarefa) {
    std::cin.ignore(); // Limpa o buffer de entrada

    std::cout << "\n" MENU "=== Editar Descrição ===" RESET "\n\n";
    std::cout << "Descrição: ";
    std::string descricao;
    std::getline(std::cin, descricao);

    tarefa.setDescricao(descricao);

    std::cout
        << TELA
        << OK "Descrição editada com sucesso!" RESET "\n"
        << "\n";
}

void GerenciadorEstadoApp::editarDataHora(TarefaCompromisso &tarefa) {
    std::cin.ignore(); // Limpa o buffer de entrada

    std::cout << "\n" MENU "=== Editar Data/Hora ===" RESET "\n\n";
    // Solicitar a data e hora da tarefa/compromisso
    std::tm dataHora = {0};

    std::cout << "Data (DD MM AAAA): ";
    std::cin >> dataHora.tm_mday >> dataHora.tm_mon >> dataHora.tm_year;
    dataHora.tm_mon -= 1; // O mês deve ser de 0 a 11
    dataHora.tm_year -= 1900; // O ano deve ser o ano atual - 1900

    std::cout << "Hora (HH MM): ";
    std::cin >> dataHora.tm_hour >> dataHora.tm_min;

    tarefa.setTimestamp(std::mktime(&dataHora));

    std::cout
        << TELA
        << OK "Data/Hora editada com sucesso!" RESET "\n"
        << "\n";
}

void GerenciadorEstadoApp::editarPrioridade(TarefaCompromisso &tarefa) {
    tarefa.setPrioridade(
        (TarefaCompromisso::Prioridade) (tarefa.getPrioridade() % 3 + 1)
    );
    std::cout << TELA;
}

void GerenciadorEstadoApp::editarConcluida(TarefaCompromisso &tarefa) {
    tarefa.setConcluida(!tarefa.getConcluida());
    std::cout << TELA;
}
