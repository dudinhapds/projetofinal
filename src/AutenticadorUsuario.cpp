#include <Serializacao.hpp>
#include <AutenticadorUsuario.hpp>

std::optional<SerializadorUsuario> AutenticadorUsuario::autenticar(
    std::string const &nome, std::string const &senha
) {
    Chave chave(senha);
    std::string nome_arquivo = "users/" + nome + ".data";
    std::FILE *arquivo = std::fopen(nome_arquivo.c_str(), "rb");
    if (!arquivo) return std::nullopt;

    Chave chave2;
    InputStream stream(arquivo, chave);
    stream.read(&chave2, sizeof(Chave));
    
    if (chave != chave2) return std::nullopt;

    return SerializadorUsuario(nome_arquivo, chave);
}

std::optional<SerializadorUsuario> AutenticadorUsuario::criar(
    std::string const &nome, std::string const &senha
) {
    Chave chave(senha);
    std::string nome_arquivo = "users/" + nome + ".data";
    std::FILE *arquivo = std::fopen(nome_arquivo.c_str(), "rb");
    if (arquivo) {
        std::fclose(arquivo);
        return std::nullopt;
    }

    arquivo = std::fopen(nome_arquivo.c_str(), "wb");
    OutputStream stream(arquivo, chave);
    stream.write(&chave, sizeof(Chave));

    return SerializadorUsuario(nome_arquivo, chave);
}
