#ifndef SERIALIZADORUSUARIO_HPP
#define SERIALIZADORUSUARIO_HPP

#include <ListaTarefasCompromissos.hpp>

#include <string>

class ListaTarefasCompromissos;

class SerializadorUsuario {
public:
    SerializadorUsuario(std::string const &nome_arquivo, Chave chave);
    ~SerializadorUsuario();

    void serializar(ListaTarefasCompromissos const &lista);
    ListaTarefasCompromissos deserializar();
    
private:
    std::string nome_arquivo;
    Chave chave;
};

#endif // SERIALIZADORUSUARIO_HPP
