#ifndef SERIALIZADORUSUARIO_HPP
#define SERIALIZADORUSUARIO_HPP

#include <Usuario.hpp>

#include <string>

/**
 * @brief Classe serializadora de usuário.
 * 
 * A partir desta classe, é possível acessar e manipular os dados salvos no
 * arquivo do usuário.
 */
class SerializadorUsuario {
public:
    /**
     * @brief Construtor da classe SerializadorUsuario.
     * @param nome_arquivo Nome do arquivo do usuário.
     * @param chave Chave gerada com a senha do usuário.
     */
    SerializadorUsuario(std::string const &nome_arquivo, Chave chave);
    /**
     * @brief Destrutor da classe SerializadorUsuario.
     */
    ~SerializadorUsuario();

    /**
     * @brief Serializa os dados do usuário.
     * @param usuario Referência ao usuário.
     */
    void serializar(Usuario const &usuario);
    /**
     * @brief Deserializa os dados do usuário.
     * @param usuario Ponteiro para o usuário.
     */
    void deserializar(Usuario *usuario);
    
private:
    /**
     * @brief Nome do arquivo do usuário.
     */
    std::string nome_arquivo;
    /**
     * @brief Chave gerada com a senha do usuário.
     */
    Chave chave;
};

#endif // SERIALIZADORUSUARIO_HPP
