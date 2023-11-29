#include <GerenciadorEstadoApp.hpp>
#include <AutenticadorUsuario.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Testando as chaves") {
    Chave chave1("senha");
    Chave chave2("senha");
    Chave chave3("outra senha");

    CHECK(chave1 == chave2);
    CHECK(chave1 != chave3);
}

TEST_CASE("Testando a serialização") {

    #define OUTPUT  "output/test1.tmp"

    Chave chave("senha"), chave2;
    std::uint64_t valor, valor2;

    {
        std::FILE *arquivo = std::fopen(OUTPUT, "wb");
        REQUIRE_NE(arquivo, nullptr);
        OutputStream ostream(arquivo, chave);
        valor = 0x123456789abcdef0;

        CHECK_EQ(ostream.write(&chave, sizeof(chave)), sizeof(chave));
        CHECK_EQ(ostream.write(&valor, sizeof(valor)), sizeof(valor));
    }
    
    {
        std::FILE *arquivo = std::fopen(OUTPUT, "rb");
        REQUIRE_NE(arquivo, nullptr);
        InputStream istream(arquivo, chave);
        
        CHECK_EQ(istream.read(&chave2, sizeof(chave2)), sizeof(chave2));
        CHECK_EQ(istream.read(&valor2, sizeof(valor2)), sizeof(valor2));
    }

    CHECK(chave == chave2);
    CHECK_EQ(valor, valor2);

    std::remove(OUTPUT);
    
    #undef OUTPUT
}
TEST_CASE("Testando logins") {
    // Escopos soltos forçam destrutores a serem chamados //

    #define USERNAME    "TESTUSER"
    #define SENHA       "senha123"

    {
        auto result = AutenticadorUsuario::criar(USERNAME, SENHA);
        REQUIRE(result.has_value());
    }
    {
        Chave chave(SENHA), chave2;
        std::FILE *arquivo = std::fopen("users/" USERNAME ".data", "rb");

        InputStream stream(arquivo, chave);
        stream.read(&chave2, sizeof(Chave));

        CHECK(chave == chave2);
    }


