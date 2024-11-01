# 🧮 Calculadora Pós-Fixada (Notação Polonesa Reversa)

Este projeto é uma **calculadora de notação pós-fixada (RPN - Reverse Polish Notation)** implementada em C utilizando uma **estrutura de pilha**. A calculadora processa expressões matemáticas onde os operadores aparecem **após os operandos**, eliminando a necessidade de parênteses.

---

## 📋 **Funcionalidades**
- Avaliação de expressões pós-fixadas com os operadores: `+`, `-`, `*`, `/`.
- Verificação de divisões por zero.
- Tratamento de erros para expressões malformadas.
- Interface interativa no terminal para entrada de expressões.

---

## 🛠️ **Compilação e Execução**

### **Pré-requisitos**
- GCC ou qualquer compilador C.
- Terminal ou CMD para rodar o programa.

### **Compilar o programa**

```bash
gcc calculator.c -o calculator
```

### **Executar**

```bash
./calculator
```

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