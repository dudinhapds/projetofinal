#include "Usuario.hpp"

Usuario::Usuario(const std::string& nome, const std::string& preferenciasNotificacao)
    : nome(nome), preferenciasNotificacao(preferenciasNotificacao) {}

const std::string& Usuario::getNome() const {
    return nome;
}

const std::string& Usuario::getPreferenciasNotificacao() const {
    return preferenciasNotificacao;
}

void Usuario::configurarPreferenciasNotificacao(const std::string& preferencias) {
    preferenciasNotificacao = preferencias;
}
