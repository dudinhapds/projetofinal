## Diretório dos arquivos-fonte
SRC_DIR = src \Users\Windows 10\Desktop

# Compilador C++
CXX = g++

# Opções de compilação
CXXFLAGS = -std=c++17 -Wall

# Nome do arquivo executável
EXECUTABLE = gerenciador.exe

# Lista de arquivos fonte
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Comando para construir o executável
$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)

# Comando para limpar arquivos temporários e o executável
clean:
	del $(EXECUTABLE)

# Comando para executar o programa
run: $(EXECUTABLE)
	$(EXECUTABLE)