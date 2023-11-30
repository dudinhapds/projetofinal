#include <SerializadorUsuario.hpp>
#include <Serializacao.hpp>

#include <cstdio>

SerializadorUsuario::SerializadorUsuario(std::string const &nome_arquivo, Chave chave)
: nome_arquivo(nome_arquivo), chave(chave) {}

SerializadorUsuario::~SerializadorUsuario() {}

void SerializadorUsuario::serializar(Usuario const &usuario) {
    std::FILE *arquivo = std::fopen(nome_arquivo.c_str(), "wb");
    if (!arquivo) std::exit(1);
    OutputStream stream(arquivo, chave);
    stream.write(&chave, sizeof(Chave));
    
    usuario.preferencias.serializar(stream);
    usuario.listaTarefas.serializar(stream);
}

void SerializadorUsuario::deserializar(Usuario *usuario) {
    std::FILE *arquivo = std::fopen(nome_arquivo.c_str(), "rb");
    if (!arquivo) std::exit(1);
    InputStream stream(arquivo, chave);

    Chave chave_arquivo;
    stream.read(&chave_arquivo, sizeof(Chave));
    if (chave_arquivo != chave) std::exit(1);
    
    usuario->preferencias.deserializar(stream);
    usuario->listaTarefas.deserializar(stream);
}
