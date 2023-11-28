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
