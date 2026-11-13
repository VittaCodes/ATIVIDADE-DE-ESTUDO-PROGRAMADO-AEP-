# ATIVIDADE-DE-ESTUDO-PROGRAMADO-AEP-
Repositorio foi criado para envio da AEP, Trabalho da Unicesumar

  Turma: ADSIS2S-N-A
  Alunos:
  Vitor Fernandes Viana RA: 26002893-2
  João Vitor Gomes de Moraes - RA: 26001900-2


  # PSE em Ação

Sistema em linguagem C, executado no terminal, para planejar e acompanhar ações do Programa Saúde na Escola (PSE). Projeto da AEP, 2º semestre de 2026, Unicesumar.

Usa somente dados fictícios e coletivos. Não faz diagnóstico e não substitui profissionais de saúde.

## Integrantes

- Vitor Fernandes Viana
- João Vitor Gomes de Moraes

## Funcionalidades

1. Cadastrar ação
2. Listar ações
3. Pesquisar ações por código, escola ou tema
4. Atualizar situação (planejada, realizada ou cancelada)
5. Resumo geral
6. Material de apoio
7. Quiz sobre hábitos saudáveis
0. Sair

## Como executar

Você precisa de um compilador C, como o GCC.

```bash
gcc -o pse Saude-2.c
./pse
```

No Windows, execute `pse.exe`.

## Observações

- Os dados ficam só em memória e se perdem ao fechar o programa.
- O limite é de 100 ações.
- O programa valida código repetido, campos vazios, datas, números negativos e opções inexistentes.
