#ifndef SERIALIZACAO_HPP
#define SERIALIZACAO_HPP

#include <cstdio>
#include <string>

/**
 * @brief Struct representando uma chave criptográfica.
 * 
 * A chave é usada para criptografar e descriptografar os arquivos de usuário.
 * Ela é calculada a partir da senha do usuário. Ela é usada para autenticar o
 * usuário, e é sempre armazenada no lugar da senha diretamente.
 */
struct Chave {
    /**
     * @brief Valor da chave.
     */
    std::uint64_t valor;
    /**
     * @brief Construtor padrão.
     */
    Chave();
    /**
     * @brief Construtor a partir de uma senha.
     * @param senha Referência à senha do usuário.
     */
    Chave(std::string const &senha);

    /**
     * @brief Sobrecarga do operador `==`.
     * @param outra Referência à outra chave a ser comparada.
     * @return Se `this` é igual a `outra`.
     */
    bool operator==(Chave const &outra) const;
    /**
     * @brief Sobrecarga do operador `!=`.
     * @param outra Referência à outra chave a ser comparada.
     * @return Se `this` é diferente de `outra`.
     */
    bool operator!=(Chave const &outra) const;
};

/**
 * @brief Classe leitora de arquivos.
 * 
 * Essa classe é usada para ler arquivos de usuário. Ela usa uma chave para
 * descriptografar o arquivo antes de lê-lo. Essa chave é gerada a partir da
 * senha do usuário referente ao arquivo.
 */
struct InputStream {
    /**
     * @brief Ponteiro para o arquivo.
     */
    std::FILE *arquivo;
    /**
     * @brief Chave usada para descriptografar o arquivo.
     */
    Chave chave;

    /**
     * @brief Construtor da classe InputStream.
     * @param arquivo Arquivo do qual a classe lerá os dados.
     * @param chave Chave usada para descriptografar o arquivo.
     */
    InputStream(std::FILE *arquivo, Chave chave);
    /**
     * @brief Destrutor da classe InputStream.
     */
    ~InputStream();

    /**
     * @brief Lê (e descriptografa) uma sequência de bytes do arquivo.
     * @param ptr Ponteiro para o destino dos bytes.
     * @param tamanho Número de bytes a serem lidos.
     * @return Número de bytes realmente lidos.
     */
    std::size_t read(void *ptr, std::size_t tamanho);
};

/**
 * @brief Classe escritora de arquivos.
 * 
 * Essa classe é usada para escrever arquivos de usuário. Ela usa uma chave
 * para criptografar o arquivo antes de escrevê-lo. Essa chave é gerada a
 * partir da senha do usuário referente ao arquivo.
 */
struct OutputStream {
    /**
     * @brief Ponteiro para o arquivo.
     */
    std::FILE *arquivo;
    /**
     * @brief Chave usada para criptografar o arquivo.
     */
    Chave chave;

    /**
     * @brief Construtor da classe OutputStream.
     * @param arquivo Arquivo no qual a classe escreverá os dados.
     * @param chave Chave usada para criptografar o arquivo.
     */
    OutputStream(std::FILE *arquivo, Chave chave);
    /**
     * @brief Destrutor da classe OutputStream.
     */
    ~OutputStream();
    
    /**
     * @brief Escreve (após criptografar) uma sequência de bytes no arquivo.
     * @param ptr Ponteiro para a origem dos bytes.
     * @param tamanho Número de bytes a serem escritos.
     * @return Número de bytes realmente escritos.
     */
    std::size_t write(void const *ptr, std::size_t tamanho);
};

#endif // SERIALIZACAO_HPP
