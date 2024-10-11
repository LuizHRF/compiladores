# Compilador em C++

Este projeto implementa um compilador simples em C++, composto por um analisador léxico e um analisador sintático baseados em uma gramática definida. O compilador reconhece expressões e estruturas condicionais como `if-else`, atribuições e comparações entre variáveis, números e valores booleanos.


## Estrutura do Projeto

O projeto é dividido em três arquivos principais:

- **`/lexer`**: Contém a extrutura e implementação do analisador léxico
- **`/parser`**: Contém a extrutura e implementação do analisador sintático
- **`/utils`**: Contém demaisfunções e definições auxiliares (Struct Token, enumeração de tipos) comuns a todos elementos do compilador, além da gramática.
- **`main.cpp`**: Arquivo principal que encapsula e executa o compilador
- **`input.txt`**: Contém a string de entrada para ser analisada

## Compilação

Para compilar o projeto, utilize o seguinte comando:

```bash
g++ -o compilador main.cpp parser/parser.cpp lexer/lexer.cpp utils/base.cpp utils/tinyxml2.cpp
```

Isso criará um executável chamado compilador.

## Execução
Para executar o programa, use o seguinte comando:

```bash
./compilador input.txt
```


## Funcionamento [Analisador Léxico]
Definição dos Tokens: O analisador léxico é configurado para reconhecer tokens de comparação, números e parênteses. Cada tipo de token é associado a um estado final no AFD.

Construção do AFD: O AFD é construído para reconhecer padrões específicos de tokens. O método buildDFA() define as transições entre os estados e os estados finais para cada token.

Análise da Entrada: O método analyze() processa a string de entrada caractere por caractere, usando o AFD para identificar tokens. Os tokens são então armazenados e exibidos.

## Funcionamento [Analisador Sintático]

Gramática: O analisador sintático utiliza uma gramática baseada em regras para expressões e comandos condicionais, atribuições e comparações. Ele se baseia nos tokens gerados pelo lexer para construir expressões corretas ou identificar erros sintáticos.

Parser SLR: O analisador sintático utiliza uma tabela de parsing SLR (Simple LR) para gerenciar as produções da gramática e realizar as transições de estados no processo de análise. A tabela SLR indica as ações de shift, reduce, ou erros baseados na entrada do token e no estado atual do parser. A tabela é lida de um arquivo .xml e é traduzida nas estruturas definidas em parser.h.
