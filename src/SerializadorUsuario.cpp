#include <SerializadorUsuario.hpp>
#include <Serializacao.hpp>

#include <cstdio>

SerializadorUsuario::SerializadorUsuario(std::string const &nome_arquivo, Chave chave)
: nome_arquivo(nome_arquivo), chave(chave) {}

SerializadorUsuario::~SerializadorUsuario() {}

void SerializadorUsuario::serializar(ListaTarefasCompromissos const &lista) {
    std::FILE *arquivo = std::fopen(nome_arquivo.c_str(), "wb");
    if (!arquivo) std::exit(1);
    OutputStream stream(arquivo, chave);
    stream.write(&chave, sizeof(Chave));
    
    lista.serializar(stream);
}

ListaTarefasCompromissos SerializadorUsuario::deserializar() {
    std::FILE *arquivo = std::fopen(nome_arquivo.c_str(), "rb");
    if (!arquivo) std::exit(1);
    InputStream stream(arquivo, chave);

    Chave chave_arquivo;
    stream.read(&chave_arquivo, sizeof(Chave));
    if (chave_arquivo != chave) std::exit(1);
    
    ListaTarefasCompromissos lista;
    lista.deserializar(stream);
    return lista;
}
