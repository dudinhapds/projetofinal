#ifndef AUTENTICADORUSUARIO_HPP
#define AUTENTICADORUSUARIO_HPP

#include <SerializadorUsuario.hpp>
#include <optional>

class AutenticadorUsuario {
public:
    static std::optional<SerializadorUsuario> autenticar(
        std::string const &nome, std::string const &senha
    );
    
    static std::optional<SerializadorUsuario> criar(
        std::string const &nome, std::string const &senha
    );
};

#endif // AUTENTICADORUSUARIO_HPP
