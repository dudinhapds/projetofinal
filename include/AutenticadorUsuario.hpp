#ifndef AUTENTICADORUSUARIO_HPP
#define AUTENTICADORUSUARIO_HPP

#include <SerializadorUsuario.hpp>
#include <optional>

/**
 * @brief Classe estática que lida com a autenticação e criação de usuários.
 */
class AutenticadorUsuario {
public:
    /**
     * @brief Tenta fazer o login de um usuário.
     * 
     * Esta função tenta fazer o login de um usuário, isto é, verificar se
     * o usuário existe e se a senha está correta. Se sim, retorna um
     * `SerializadorUsuario` associado ao usuário logado.
     * 
     * @param nome Nome do usuário
     * @param senha Senha do usuário
     * @return Retorna um SerializadorUsuario associado ao usuário logado,
     * caso o login tenha sido bem-sucedido.
     */
    static std::optional<SerializadorUsuario> autenticar(
        std::string const &nome, std::string const &senha
    );
  
    /**
     * @brief Tenta criar um novo usuário.
     * 
     * Esta função tenta criar um novo usuário, isto é, verificar se o usuário
     * não existe e, se não existir, criar um novo usuário com o nome e senha
     * especificados.
     * 
     * @param nome Nome do usuário
     * @param senha Senha do usuário
     * @return Retorna um `SerializadorUsuario` associado ao usuário criado,
     * caso a criação tenha sido bem-sucedida.
     */
    static std::optional<SerializadorUsuario> criar(
        std::string const &nome, std::string const &senha
    );
};

#endif // AUTENTICADORUSUARIO_HPP    
