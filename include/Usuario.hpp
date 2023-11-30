#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <ListaTarefasCompromissos.hpp>
#include <PreferenciasLista.hpp>
#include <string>

/**
 * @brief Classe representando um usuário.
 * 
 * Esta classe representa a sessão do usuário atualmente logado no sistema.
 * Contém o nome do usuário, sua lista de tarefas/compromissos e suas
 * preferências.
 */
class Usuario {
public:
    /**
     * @brief Construtor da classe Usuario.
     * @param nome Nome do usuário.
     */
    Usuario(std::string const &nome);

    /**
     * @brief Construtor da classe Usuario.
     * @param nome Nome do usuário.
     * @param lista Lista de tarefas/compromissos do usuário.
     */
    Usuario(std::string const &nome, ListaTarefasCompromissos const &lista);

    /**
     * @brief Getter do nome.
     * @return Referência constante ao nome.
     */
    std::string const &getNome() const;
    /**
     * @brief Getter da lista de tarefas.
     * @return Referência à lista de tarefas.
     */
    ListaTarefasCompromissos &getListaTarefas();
    /**
     * @brief Getter das preferências.
     * @return Referência às preferências do usuário.
     */
    PreferenciasLista &getPreferencias();
private:
    /**
     * @brief Nome do usuário.
     */
    std::string nome;
    /**
     * @brief Lista de tarefas/compromissos do usuário.
     */
    ListaTarefasCompromissos listaTarefas;
    /**
     * @brief Preferências do usuário.
     */
    PreferenciasLista preferencias;

    friend class SerializadorUsuario;
};

#endif // USUARIO_HPP
