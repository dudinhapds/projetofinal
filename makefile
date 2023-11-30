## Diretório dos arquivos-fonte
SRC_DIR = .\src

## Diretório dos arquivos-cabeçalho
INC_DIR = .\include

## Diretório dos arquivos de teste
TEST_DIR = .\test

## Diretório dos arquivos de saída
OUTPUT_DIR = .\output

# Compilador C++
CXX = g++

# Opções de compilação
CXXFLAGS = -std=c++17 -Wall -Werror -D_CORES

# Nome do arquivo executável para rodar
RELEASE = $(OUTPUT_DIR)\gerenciador_run.exe

# Nome do arquivo executável para testar
DEBUG = $(OUTPUT_DIR)\gerenciador_test.exe

# Lista de arquivos fonte
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Lista de arquivos-cabeçalho
HEADERS = $(wildcard $(INC_DIR)/*.hpp)

# Lista de arquivos de teste
TESTS = $(wildcard $(TEST_DIR)/*.cpp)

# Comando para construir o projeto
build: $(RELEASE)

# Comando para executar o programa
run: $(RELEASE)
	$(RELEASE)

# Comando para testar o programa
test: $(DEBUG)
	$(DEBUG)
	
# Comando para limpar arquivos temporários e o executável
clean:
	del $(RELEASE)
	del $(DEBUG)

# Comando para construir o executável de release
$(RELEASE): $(SOURCES) $(HEADERS) $(MAIN)
	$(CXX) $(CXXFLAGS) $(MAIN) $(SOURCES) -I $(INC_DIR) -o $(RELEASE)

# Comando para construir o executável de debug
$(DEBUG): $(SOURCES) $(HEADERS) $(TESTS) $(TEST)
	$(CXX) $(CXXFLAGS) $(TEST) $(SOURCES) -I $(INC_DIR) -o $(DEBUG)
