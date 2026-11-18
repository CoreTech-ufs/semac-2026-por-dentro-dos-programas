# Oficina: Por Dentro dos Programas — Dia 3
**Tema:** Falhas de memória, consequências reais e verificação com Valgrind  
**Pergunta orientadora:** *Como uma falha de memória se torna um problema real e que evidências permitem aceitar uma correção?*

---

## 1. Retomada: Os 3 Pilares da Memória em C

Antes de investigar falhas, toda análise de ponteiros e alocação dinâmica parte de três perguntas fundamentais sobre qualquer dado manipulado pelo programa:

1. **Limites:** Qual é o tamanho exato em bytes do bloco reservado e qual é o intervalo de índices válidos ($0$ até $N - 1$)?
2. **Duração (Tempo de Vida):** Onde vive a variável ponteiro (**Stack**) e onde vive o bloco apontado (**Heap**)? O dado continua válido no momento em que é acessado?
3. **Responsabilidade:** Qual função ou módulo é o "dono" daquela alocação e tem a obrigação de chamar `free()` quando o dado não for mais necessário?

---

## 2. Anatomia das Falhas de Memória

Nem todo erro de memória causa o fechamento imediato do programa (*Segmentation Fault*), e nem toda falha de memória é um simples vazamento. Na engenharia de software de baixo nível, distinguimos três comportamentos principais:

| Tipo de Falha | O que acontece na memória | Consequência prática |
| :--- | :--- | :--- |
| **Vazamento de Alocação** (`CWE-401` / *Memory Leak*) | Um bloco alocado na Heap deixa de ser liberado com `free()` após perdermos sua referência. | Consumo crescente de RAM até o sistema encerrar o processo. Por si só, **não** expõe segredos nem altera o fluxo do código. |
| **Divulgação de Dados** (`CWE-125` / *Out-of-bounds Read*) | O programa lê regiões de memória além dos limites do bloco válido ou lê memória não inicializada. | Exposição de informações sensíveis vizinhas ou residuais na RAM, mesmo que o programa continue rodando sem travar. |
| **Corrupção de Memória** (`CWE-787` / *Out-of-bounds Write* e *Use-After-Free*) | O programa escreve fora dos limites alocados ou manipula blocos já devolvidos ao sistema. | Alteração silenciosa de variáveis adjacentes, destruição de metadados da Heap ou desvio do fluxo de execução. |

### Conexão com o Mundo Real: Caso PHP (Outubro de 2026)
Em outubro de 2026, a PHP Foundation divulgou correções críticas para falhas no motor da linguagem (escrito em C):
* **`CVE-2026-109618`:** Envolve corrupção de memória durante o tratamento de falta de memória (*Out-Of-Memory*).
* **`CVE-2026-109619`:** Ocorre quando um estado interno permanece acessível após a liberação da memória correspondente, permitindo o uso após liberação (*Use-After-Free*) em uma requisição posterior.

**Lição principal:** Em sistemas reais, falhas graves raramente acontecem por esquecer um `free()` no fluxo principal. Elas costumam se esconder em **caminhos de erro pouco testados** e em **ponteiros que sobrevivem além do tempo de vida do bloco apontado**.

---

## 3. Guia Rápido de Valgrind

O **Valgrind** instrumenta a execução do programa para monitorar cada leitura, escrita, alocação e liberação na memória.

### Instalação e Configuração

Caso esteja usando seu próprio notebook ou ambiente WSL, instale o Valgrind (junto com o pacote `libc6-dbg` no Ubuntu/Debian, necessário para que a ferramenta leia os símbolos da biblioteca padrão C):

```bash
# Ubuntu / Debian / Linux Mint / WSL
sudo apt update && sudo apt install -y valgrind libc6-dbg

# Fedora
sudo dnf install -y valgrind

# Arch Linux
sudo pacman -S valgrind
```

Verifique se a instalação está funcionando:
```bash
valgrind --version
```

Configuração opcional (`~/.valgrindrc`): Para evitar digitar as opções detalhadas de vazamento a cada teste, você pode salvá-las como padrão no seu diretório pessoal:
```bash
printf -- "--leak-check=full\n--show-leak-kinds=all\n" > ~/.valgrindrc
```

### Compilação e Execução
Compile sempre com símbolos de depuração (`-g`) e sem otimizações (`-O0`) para que o relatório aponte exatamente o arquivo e a linha do código-fonte:

```bash
gcc -g -O0 arquivo.c -o programa
valgrind --leak-check=full --show-leak-kinds=all ./programa
```

### Como Ler o Relatório (De Cima para Baixo)
Ao analisar a saída no terminal, foque em quatro evidências principais:

1. **Natureza do acesso:**
   * `Invalid write of size X` $\rightarrow$ Escrita fora dos limites ou em bloco liberado (risco de corrupção).
   * `Invalid read of size X` $\rightarrow$ Leitura fora dos limites ou em bloco liberado (risco de divulgação de dados ou crash).
2. **Local exato (`at 0x...`):** Indica a função e o número da linha onde a instrução inválida ocorreu.
3. **Relação com o bloco alocado:** Linhas como `Address 0x... is 0 bytes after a block of size 16 alloc'd` mostram exatamente onde o bloco terminou e quantos bytes o programa ultrapassou.
4. **Sumário da Heap (`LEAK SUMMARY`):** O campo `definitely lost` indica quantos bytes foram alocados na Heap e não possuíam nenhum ponteiro ativo ao final da execução.

> **Atenção:** Um relatório limpo (zero erros) comprova apenas que **o caminho executado naquele teste** não realizou acessos inválidos. Se um `if` de tratamento de erro não foi acionado durante o teste, eventuais falhas dentro dele continuarão ocultas.

---

## 4. Clínica de Falhas: Investigação Prática

Para cada caso abaixo, siga rigorosamente o ciclo de investigação antes de alterar o código:
1. **Prever (Hipótese):** Leia o código e anote onde você suspeita que há problema de limite, duração ou responsabilidade.
2. **Inspecionar:** Compile com `-g -O0` e rode no Valgrind.
3. **Explicar:** Cruze a linha apontada pelo Valgrind com a linha do `malloc`.
4. **Corrigir e Verificar:** Aplique a correção, recompile e compare o novo relatório com o anterior.

### Caso 1 (Essencial): Processamento de Amostras [(clique para ver o código)](/semac-2026-por-dentro-dos-programas/dia-3/clinica_basica.c)


**Perguntas de investigação:**
* Quantos bytes foram alocados na Heap para `amostras`?
* Qual operação ultrapassa o limite do bloco e por quantos bytes?
* O programa exibe o `Total` corretamente mesmo com o erro? Por que isso é perigoso?
* Onde a memória deve ser liberada?

---

### Caso 2 (Desafio): Validação de Leituras de Sensores [(clique para ver o código)](/semac-2026-por-dentro-dos-programas/dia-3/clinica_uaf.c)

**Perguntas de investigação:**
* O que acontece com o endereço armazenado em `sensores` quando uma leitura negativa é encontrada?
* Que tipo de erro o Valgrind reporta na linha do `printf`?
* Como corrigir o contrato da função `validar_leituras` e a verificação na `main` para evitar tanto o acesso inválido quanto o vazamento de memória no caso em que todas as leituras são positivas?

---

## 5. Checklist para Aceitar uma Correção

Antes de considerar qualquer código corrigido, verifique:
* [ ] Todos os acessos respeitam o intervalo $[0, N - 1]$ do bloco alocado?
* [ ] Ponteiros que apontam para blocos já liberados recebem `NULL` imediatamente?
* [ ] Existe exatamente um `free()` correspondente para cada caminho de execução após um `malloc()` bem-sucedido?
* [ ] O relatório do Valgrind exibe `0 errors from 0 contexts` e `0 bytes in 0 blocks` perdidos?