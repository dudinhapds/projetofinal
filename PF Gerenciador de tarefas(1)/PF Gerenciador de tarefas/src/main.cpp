#include "AplicativoGerenciador.hpp"
#include "ListaTarefasCompromissos.hpp"
#include "Notificacoes.hpp"
#include "TarefaCompromisso.hpp"
#include "Usuario.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std; // Adicionando a declaração para usar o namespace std

int main() {
    AplicativoGerenciador aplicativo;
    aplicativo.iniciar();

    return 0;
}
