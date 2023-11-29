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
    {
        auto result = AutenticadorUsuario::criar(USERNAME, SENHA);
        CHECK_FALSE(result.has_value());
    }

    {
        auto result = AutenticadorUsuario::autenticar(USERNAME, SENHA);
        CHECK(result.has_value());
    }


    {
        auto result = AutenticadorUsuario::autenticar(USERNAME, SENHA "errada");
        CHECK_FALSE(result.has_value());
    }

    {
        auto result = AutenticadorUsuario::autenticar(USERNAME "errado", SENHA);
        CHECK_FALSE(result.has_value());
    }

    std::remove("users/" USERNAME ".data");

    #undef USERNAME
    #undef SENHA

    }
    static void testarTarefa(
    TarefaCompromisso const &tarefa1, TarefaCompromisso *tarefa2,
    char const *filename, Chave const &chave
) {
    {
        std::FILE *arquivo = std::fopen(filename, "wb");
        OutputStream ostream(arquivo, chave);
        
        tarefa1.serializar(ostream);
    }

    {
        std::FILE *arquivo = std::fopen(filename, "rb");
        InputStream istream(arquivo, chave);
        
        tarefa2->deserializar(istream);
    }
}
TEST_CASE("Testando a serialização de uma tarefa") {
    #define OUTPUT  "output/test2.tmp"

    Chave chave("senha");

    SUBCASE("Exemplo de tarefa 1") {
        std::time_t now = std::time(nullptr);
        TarefaCompromisso tarefa1(
            "Tarefa 1", now, TarefaCompromisso::P_ALTA, true
        );
        TarefaCompromisso tarefa2;

        testarTarefa(tarefa1, &tarefa2, OUTPUT, chave);

        CHECK_EQ(tarefa1.getDescricao(), tarefa2.getDescricao());
        CHECK_EQ(tarefa1.getTimestamp(), tarefa2.getTimestamp());
        CHECK_EQ(tarefa1.getPrioridade(), tarefa2.getPrioridade());
        CHECK_EQ(tarefa1.getConcluida(), tarefa2.getConcluida());
    }
  SUBCASE("Exemplo de tarefa 2") {
        std::tm tm {
            .tm_sec = 0,
            .tm_min = 30,
            .tm_hour = 12,
            .tm_mday = 23,
            .tm_mon = 10, // Nov
            .tm_year = 2023 - 1900,
        };
        std::time_t timestamp = std::mktime(&tm);
        
        TarefaCompromisso tarefa1(
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
            "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut "
            "enim ad minim veniam, quis nostrud exercitation ullamco laboris "
            "nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor "
            "in reprehenderit in voluptate velit esse cillum dolore eu fugiat "
            "nulla pariatur. Excepteur sint occaecat cupidatat non proident, "
            "sunt in culpa qui officia deserunt mollit anim id est laborum.",
            timestamp, TarefaCompromisso::P_BAIXA, false
        );
        TarefaCompromisso tarefa2;

        testarTarefa(tarefa1, &tarefa2, OUTPUT, chave);

        CHECK_EQ(tarefa1.getDescricao(), tarefa2.getDescricao());
        CHECK_EQ(tarefa1.getTimestamp(), tarefa2.getTimestamp());
        CHECK_EQ(tarefa1.getPrioridade(), tarefa2.getPrioridade());
        CHECK_EQ(tarefa1.getConcluida(), tarefa2.getConcluida());
    }
SUBCASE("Exemplo de tarefa 3") {
        std::time_t now = std::time(nullptr);
        TarefaCompromisso tarefa1(
            "Tarefa 3 !!!/", now, TarefaCompromisso::P_MEDIA, true
        );
        TarefaCompromisso tarefa2;

        testarTarefa(tarefa1, &tarefa2, OUTPUT, chave);

        CHECK_EQ(tarefa1.getDescricao(), tarefa2.getDescricao());
        CHECK_EQ(tarefa1.getTimestamp(), tarefa2.getTimestamp());
        CHECK_EQ(tarefa1.getPrioridade(), tarefa2.getPrioridade());
        CHECK_EQ(tarefa1.getConcluida(), tarefa2.getConcluida());
    }
    

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

    {
        auto result = AutenticadorUsuario::criar(USERNAME, SENHA);
        CHECK_FALSE(result.has_value());
    }

    {
        auto result = AutenticadorUsuario::autenticar(USERNAME, SENHA);
        CHECK(result.has_value());
    }


    {
        auto result = AutenticadorUsuario::autenticar(USERNAME, SENHA "errada");
        CHECK_FALSE(result.has_value());
    }

    {
        auto result = AutenticadorUsuario::autenticar(USERNAME "errado", SENHA);
        CHECK_FALSE(result.has_value());
    }

    std::remove("users/" USERNAME ".data");

    #undef USERNAME
    #undef SENHA

}
static void testarTarefa(
    TarefaCompromisso const &tarefa1, TarefaCompromisso *tarefa2,
    char const *filename, Chave const &chave
) {
    {
        std::FILE *arquivo = std::fopen(filename, "wb");
        OutputStream ostream(arquivo, chave);
        
        tarefa1.serializar(ostream);
    }

    {
        std::FILE *arquivo = std::fopen(filename, "rb");
        InputStream istream(arquivo, chave);
        
        tarefa2->deserializar(istream);
    }
}





