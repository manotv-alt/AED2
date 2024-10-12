# 🧮 Calculadora Pós-Fixada (Notação Polonesa Reversa)

Este projeto é uma **calculadora de notação pós-fixada (RPN - Reverse Polish Notation)** implementada em C utilizando uma **estrutura de pilha**. A calculadora processa expressões matemáticas onde os operadores aparecem **após os operandos**, eliminando a necessidade de parênteses.

---

## 📋 **Funcionalidades**
- Avaliação de expressões pós-fixadas com os operadores: `+`, `-`, `*`, `/`.
- Verificação de divisões por zero.
- Tratamento de erros para expressões malformadas.
- Interface interativa no terminal para entrada de expressões.

---

### **Pré-requisitos**
- GCC ou qualquer compilador C.
- Terminal ou CMD para rodar o programa.

---

### Passos para Executar

1. Clone o repositório:
   ```bash
   git clone https://github.com/manotv-alt/AED2.git

2. Entre na pasta do repositório:
   ```bash
   cd ./AED2/

3. Mantendo somente a pasta do projeto desejado (Windows):
   ```bash
   Get-ChildItem -Exclude 'Calculadora' | Remove-Item -Recurse -Force

3. Mantendo somente a pasta do projeto desejado (Linux):
   ```bash
   find . -maxdepth 1 ! -name 'Calculadora' ! -name '.' -exec rm -rf {} +

4. Entre na pasta do projeto:
   ```bash
   cd "/Calculadora/"

3. Compile o código:
    ```bash
    gcc calculator.c -o calculator

4. Execute o programa:
    ```bash
    ./calculator

---

## 📝 **Uso**

Digite a expressão pós-fixada no formato correto:

Exemplo de Expressão Válida:  
`3 4 + 2 * 7 -`

#### **Como funciona o exemplo**:
1. `3 + 4 = 7`
2. `7 * 2 = 14`
3. `14 - 7 = 7`

---

## 🚨 **Erros Comuns**
- **Divisão por zero**: O programa exibe uma mensagem e encerra.
- **Expressão malformada**: Se faltar operandos ou sobrar operadores, o programa avisará e encerrará.

---