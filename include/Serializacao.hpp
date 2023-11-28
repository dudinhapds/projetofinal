#ifndef SERIALIZACAO_HPP
#define SERIALIZACAO_HPP

#include <cstdio>
#include <string>

struct Chave {
    std::uint64_t valor;
    Chave();
    Chave(std::string const &senha);

    bool operator==(Chave const &outra) const;
    bool operator!=(Chave const &outra) const;
};

struct InputStream {
    std::FILE *arquivo;
    Chave chave;

    InputStream(std::FILE *arquivo, Chave chave);
    ~InputStream();
    std::size_t read(void *ptr, std::size_t tamanho);
};

struct OutputStream {
    std::FILE *arquivo;
    Chave chave;

    OutputStream(std::FILE *arquivo, Chave chave);
    ~OutputStream();
    std::size_t write(void const *ptr, std::size_t tamanho);
};

#endif // SERIALIZACAO_HPP
