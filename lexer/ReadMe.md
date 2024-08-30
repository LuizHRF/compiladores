# Analisador Léxico em C++

Este projeto implementa um analisador léxico básico em C++ que usa um Autômato Finito Determinístico (AFD) para reconhecer tokens em uma string de entrada. O analisador léxico é capaz de identificar tokens de comparação (`==`, `!=`, `<`, `>`, `<=`, `>=`), números, e parênteses aninhados (`(` e `)`).

## Estrutura do Projeto

O projeto é dividido em três arquivos principais:

- **`lexer.h`**: Contém as definições de classes e estruturas para o analisador léxico.
- **`lexer.cpp`**: Implementa a lógica do analisador léxico, incluindo a construção do AFD e a análise da string de entrada.
- **`main.cpp`**: Contém a função principal onde o analisador léxico é utilizado para processar uma string de entrada e imprimir os tokens reconhecidos.

## Compilação

Para compilar o projeto, utilize o seguinte comando:

```bash
g++ -o lexer main.cpp lexer.cpp
```

Isso criará um executável chamado lexer.

## Execução
Para executar o programa, use o seguinte comando:

```bash
Copy code
./lexer
```

O programa irá processar uma string de entrada predefinida e imprimir os tokens reconhecidos, incluindo números e operadores de comparação, além de parênteses.

## Exemplo de Saída
A execução do programa com a string de entrada (123 >= 456) != (789 < 10) produzirá uma saída similar a:

```yaml
Copy code
Token: ( (Tipo: ( )
Token: 123 (Tipo: NUMBER)
Token: >= (Tipo: >=)
Token: 456 (Tipo: NUMBER)
Token: ) (Tipo: ) )
Token: != (Tipo: !=)
Token: ( (Tipo: ( )
Token: 789 (Tipo: NUMBER)
Token: < (Tipo: <)
Token: 10 (Tipo: NUMBER)
Token: ) (Tipo: ) )
```
## Funcionamento
Definição dos Tokens: O analisador léxico é configurado para reconhecer tokens de comparação, números e parênteses. Cada tipo de token é associado a um estado final no AFD.

Construção do AFD: O AFD é construído para reconhecer padrões específicos de tokens. O método buildDFA() define as transições entre os estados e os estados finais para cada token.

Análise da Entrada: O método analyze() processa a string de entrada caractere por caractere, usando o AFD para identificar tokens. Os tokens são então armazenados e exibidos.

Impressão dos Tokens: Os tokens reconhecidos são impressos com suas respectivas representações e tipos.

Notas
O projeto é uma implementação básica de um analisador léxico e não inclui verificação de balanceamento de parênteses. Para validar parênteses aninhados, um mecanismo adicional de verificação seria necessário.
A string de entrada é atualmente predefinida no código. Para análises diferentes, modifique a string no arquivo main.cpp.