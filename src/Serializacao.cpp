#include <Serializacao.hpp>
#include <cstring>

Chave::Chave() {}

static std::uint64_t constexpr INICIAL = 0x3D9CA05D5422EDE9L;
static std::uint64_t constexpr EMBARALHA = 0xECD96C09EEFC5F6DL;
static std::uint64_t constexpr MULT = 709;

Chave::Chave(std::string const &senha) 
{
    std::uint64_t hash = INICIAL;
    for (char c : senha) {
        hash = (hash * MULT) + (c * EMBARALHA);
    }
    valor = hash;
}

bool Chave::operator==(Chave const &outra) const 
{
    return valor == outra.valor;
}

bool Chave::operator!=(Chave const &outra) const {
    return valor != outra.valor;
}

InputStream::InputStream(std::FILE *arquivo, Chave chave)
: arquivo(arquivo), chave(chave) {}

InputStream::~InputStream() {
    std::fclose(arquivo);
}

std::size_t InputStream::read(
    void *ptr, std::size_t tamanho
) {
    std::size_t bytes_lidos = std::fread(ptr, 1, tamanho, arquivo);
    for (std::size_t i = 0; i < bytes_lidos; ++i) {
        chave.valor *= MULT;

        unsigned char &c = ((unsigned char *) ptr)[i];
        unsigned char x = chave.valor >> (i * 8 % 64);

        chave.valor += c * EMBARALHA;
        c -= x;
    }
    return bytes_lidos;
}

OutputStream::OutputStream(std::FILE *arquivo, Chave chave)
: arquivo(arquivo), chave(chave) {}

OutputStream::~OutputStream() {
    std::fclose(arquivo);
}

std::size_t OutputStream::write(
    void const *ptr, std::size_t tamanho
) {
    unsigned char *buffer = (unsigned char *) std::malloc(tamanho);
    std::memcpy(buffer, ptr, tamanho);

    for (std::size_t i = 0; i < tamanho; ++i) {
        chave.valor *= MULT;

        unsigned char &c = buffer[i];
        unsigned char x = chave.valor >> (i * 8 % 64);

        c += x;
        chave.valor += c * EMBARALHA;
    }

    return std::fwrite(buffer, 1, tamanho, arquivo);
}
