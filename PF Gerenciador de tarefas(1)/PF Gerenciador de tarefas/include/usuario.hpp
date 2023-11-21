#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

class Usuario {
public:
    Usuario(const std::string& nome, const std::string& preferenciasNotificacao);

    const std::string& getNome() const;
    const std::string& getPreferenciasNotificacao() const;
    void configurarPreferenciasNotificacao(const std::string& preferencias);

private:
    std::string nome;
    std::string preferenciasNotificacao;
};

#endif // USUARIO_HPP
