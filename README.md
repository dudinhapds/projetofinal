# Gerenciador de Tarefas

Este programa gerencia tarefas. As funcionalidades implementadas são:

+ Sistema de login e senha.
+ Cada usuário é salvo em um arquivo criptografado.
+ Menus interativos.
+ É possível criar, editar, e remover tarefas.
+ É possível filtrar e reordenar a lista de tarefas.
+ Cada tarefa possui descrição, data/hora, e prioridade.
+ Cada tarefa pode ter sido concluída ou não.
+ O dia da semana é calculado a partir da data.

## Como usar

+ Rode o programa usando o comando `make run`.
+ Testes unitários foram implementados. Use o comando `make test` para rodá-los
+ O código imprime no terminal com cores. Para desabilitá-las, remova a flag
  `-D_CORES` do makefile e reconstrua o projeto.
+ O executável será construído na pasta `output/`, e os arquivos dos usuários
  serão gerados na pasta `users/`. Certifique-se de que estas pastas existem
  antes de executar o programa.

## Exemplo

Neste repositório há já cadastrado um usuário cujo nome é `usuario123` e a senha
é `senha123`. Ele possui algumas tarefas de exemplo, para fins de testar o
programa.
