#include <stdio.h>
#include <string.h>
#include <limits.h>

#define CAPACIDADE 100
#define TEXTO 121

typedef struct {
    int codigo;
    char escola[TEXTO];
    char tema[TEXTO];
    char data[11];
    char publico[TEXTO];
    char responsavel[TEXTO];
    int previstos;
    int efetivos;
    int situacao;
} Acao;

Acao acoes[CAPACIDADE];
int total = 0;

int lerTexto(char mensagem[], char texto[], int tamanho) {
    int caractere, quantidade, excesso, inicio, fim, i;

    while (1) {
        printf("%s", mensagem);
        fflush(stdout);
        quantidade = 0;
        excesso = 0;
        caractere = getchar();

        if (caractere == EOF) {
            return 0;
        }

        while (caractere != '\n' && caractere != EOF) {
            if (quantidade < tamanho - 1) {
                texto[quantidade] = (char)caractere;
                quantidade++;
            } else {
                excesso = 1;
            }
            caractere = getchar();
        }
        texto[quantidade] = '\0';

        if (excesso == 1) {
            printf("Entrada muito longa. Tente novamente.\n");
        } else {
            inicio = 0;
            while (texto[inicio] == ' ' || texto[inicio] == '\t' || texto[inicio] == '\r') {
                inicio++;
            }

            fim = quantidade;
            while (fim > inicio && (texto[fim - 1] == ' ' || texto[fim - 1] == '\t' || texto[fim - 1] == '\r')) {
                fim--;
            }

            for (i = 0; i < fim - inicio; i++) {
                texto[i] = texto[inicio + i];
            }
            texto[i] = '\0';

            if (texto[0] == '\0') {
                printf("Campo obrigatorio. Digite um valor.\n");
            } else {
                return 1;
            }
        }
    }
}

int lerNumero(char mensagem[], int minimo, int maximo) {
    char texto[80];
    int i, numero, digito, valido;

    while (lerTexto(mensagem, texto, 80) == 1) {
        numero = 0;
        valido = 1;

        for (i = 0; texto[i] != '\0'; i++) {
            if (texto[i] >= '0' && texto[i] <= '9') {
                digito = texto[i] - '0';
                if (valido == 1) {
                    if (numero > maximo / 10 || (numero == maximo / 10 && digito > maximo % 10)) {
                        valido = 0;
                    } else {
                        numero = numero * 10 + digito;
                    }
                }
            } else {
                valido = 0;
            }
        }

        if (valido == 1 && numero >= minimo) {
            return numero;
        } else {
            printf("Numero invalido. Informe de %d a %d.\n", minimo, maximo);
        }
    }
    return -1;
}

int dataValida(char data[]) {
    int i, dia, mes, ano, limite;

    if (strlen(data) != 10) {
        return 0;
    }
    if (data[2] != '/' || data[5] != '/') {
        return 0;
    }

    for (i = 0; i < 10; i++) {
        if (i != 2 && i != 5) {
            if (data[i] < '0' || data[i] > '9') {
                return 0;
            }
        }
    }

    dia = (data[0] - '0') * 10 + data[1] - '0';
    mes = (data[3] - '0') * 10 + data[4] - '0';
    ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + data[9] - '0';

    if (ano < 1 || mes < 1 || mes > 12) {
        return 0;
    }

    limite = 31;
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        limite = 30;
    } else if (mes == 2) {
        limite = 28;
        if (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0)) {
            limite = 29;
        }
    }

    if (dia >= 1 && dia <= limite) {
        return 1;
    } else {
        return 0;
    }
}

int buscarCodigo(int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (acoes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int contemTexto(char texto[], char trecho[]) {
    int i, j;
    char letraTexto, letraTrecho;

    for (i = 0; texto[i] != '\0'; i++) {
        j = 0;
        while (trecho[j] != '\0' && texto[i + j] != '\0') {
            letraTexto = texto[i + j];
            letraTrecho = trecho[j];

            if (letraTexto >= 'A' && letraTexto <= 'Z') {
                letraTexto = letraTexto + ('a' - 'A');
            }
            if (letraTrecho >= 'A' && letraTrecho <= 'Z') {
                letraTrecho = letraTrecho + ('a' - 'A');
            }

            if (letraTexto != letraTrecho) {
                break;
            }
            j++;
        }
        if (trecho[j] == '\0') {
            return 1;
        }
    }
    return 0;
}

void mostrarAcao(int posicao) {
    printf("\nCodigo: %d\n", acoes[posicao].codigo);
    printf("Escola: %s\n", acoes[posicao].escola);
    printf("Tema: %s\n", acoes[posicao].tema);
    printf("Data prevista: %s\n", acoes[posicao].data);
    printf("Publico-alvo: %s\n", acoes[posicao].publico);
    printf("Responsavel ficticio: %s\n", acoes[posicao].responsavel);
    printf("Participantes previstos: %d\n", acoes[posicao].previstos);
    printf("Participantes efetivos: %d\n", acoes[posicao].efetivos);

    if (acoes[posicao].situacao == 1) {
        printf("Situacao: planejada\n");
    } else if (acoes[posicao].situacao == 2) {
        printf("Situacao: realizada\n");
    } else {
        printf("Situacao: cancelada\n");
    }
}

int cadastrarAcao(void) {
    Acao nova;

    if (total >= CAPACIDADE) {
        printf("Capacidade cheia: limite de 100 acoes.\n");
        return 1;
    }

    while (1) {
        nova.codigo = lerNumero("Codigo positivo: ", 1, INT_MAX);
        if (nova.codigo == -1) {
            return 0;
        }
        if (buscarCodigo(nova.codigo) == -1) {
            break;
        } else {
            printf("Codigo duplicado. Escolha outro.\n");
        }
    }

    if (lerTexto("Escola: ", nova.escola, TEXTO) == 0) {
        return 0;
    }
    if (lerTexto("Tema livre (ex.: alimentacao saudavel): ", nova.tema, TEXTO) == 0) {
        return 0;
    }

    while (1) {
        if (lerTexto("Data prevista (DD/MM/AAAA): ", nova.data, 11) == 0) {
            return 0;
        }
        if (dataValida(nova.data) == 1) {
            break;
        } else {
            printf("Data invalida.\n");
        }
    }

    if (lerTexto("Publico-alvo coletivo: ", nova.publico, TEXTO) == 0) {
        return 0;
    }
    if (lerTexto("Responsavel ficticio: ", nova.responsavel, TEXTO) == 0) {
        return 0;
    }

    nova.previstos = lerNumero("Participantes previstos: ", 0, INT_MAX);
    if (nova.previstos == -1) {
        return 0;
    }
    nova.situacao = lerNumero("Situacao (1 planejada, 2 realizada, 3 cancelada): ", 1, 3);
    if (nova.situacao == -1) {
        return 0;
    }

    nova.efetivos = 0;
    if (nova.situacao == 2) {
        nova.efetivos = lerNumero("Participantes efetivos: ", 0, INT_MAX);
        if (nova.efetivos == -1) {
            return 0;
        }
    }

    acoes[total] = nova;
    total++;
    printf("Acao cadastrada.\n");
    return 1;
}

void listarAcoes(void) {
    int i;
    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
    }
    for (i = 0; i < total; i++) {
        mostrarAcao(i);
    }
}

int pesquisarAcoes(void) {
    int modo, codigo, posicao, i, encontrados;
    char trecho[TEXTO];

    modo = lerNumero("Pesquisar (1 codigo, 2 escola, 3 tema): ", 1, 3);
    if (modo == -1) {
        return 0;
    }
    encontrados = 0;

    if (modo == 1) {
        codigo = lerNumero("Codigo: ", 1, INT_MAX);
        if (codigo == -1) {
            return 0;
        }
        posicao = buscarCodigo(codigo);
        if (posicao >= 0) {
            mostrarAcao(posicao);
            encontrados++;
        }
    } else {
        if (lerTexto("Trecho a pesquisar: ", trecho, TEXTO) == 0) {
            return 0;
        }
        for (i = 0; i < total; i++) {
            if (modo == 2) {
                if (contemTexto(acoes[i].escola, trecho) == 1) {
                    mostrarAcao(i);
                    encontrados++;
                }
            } else {
                if (contemTexto(acoes[i].tema, trecho) == 1) {
                    mostrarAcao(i);
                    encontrados++;
                }
            }
        }
    }

    if (encontrados == 0) {
        printf("Nenhuma acao encontrada.\n");
    }
    return 1;
}

int atualizarSituacao(void) {
    int codigo, posicao, novaSituacao, novosEfetivos;

    codigo = lerNumero("Codigo: ", 1, INT_MAX);
    if (codigo == -1) {
        return 0;
    }
    posicao = buscarCodigo(codigo);
    if (posicao == -1) {
        printf("Acao inexistente.\n");
        return 1;
    }

    novaSituacao = lerNumero("Situacao (1 planejada, 2 realizada, 3 cancelada): ", 1, 3);
    if (novaSituacao == -1) {
        return 0;
    }

    novosEfetivos = 0;
    if (novaSituacao == 2) {
        novosEfetivos = lerNumero("Participantes efetivos: ", 0, INT_MAX);
        if (novosEfetivos == -1) {
            return 0;
        }
    }

    acoes[posicao].situacao = novaSituacao;
    acoes[posicao].efetivos = novosEfetivos;
    printf("Situacao atualizada.\n");
    return 1;
}

void mostrarResumo(void) {
    int i, planejadas = 0, realizadas = 0, canceladas = 0;
    long long previstosGerais = 0, previstosRealizadas = 0, efetivosRealizadas = 0;
    double percentual;

    for (i = 0; i < total; i++) {
        previstosGerais = previstosGerais + acoes[i].previstos;
        if (acoes[i].situacao == 1) {
            planejadas++;
        } else if (acoes[i].situacao == 2) {
            realizadas++;
            previstosRealizadas = previstosRealizadas + acoes[i].previstos;
            efetivosRealizadas = efetivosRealizadas + acoes[i].efetivos;
        } else {
            canceladas++;
        }
    }

    printf("Planejadas: %d | Realizadas: %d | Canceladas: %d\n", planejadas, realizadas, canceladas);
    printf("Previstos gerais: %lld\n", previstosGerais);
    printf("Previstos das realizadas: %lld\n", previstosRealizadas);
    printf("Efetivos das realizadas: %lld\n", efetivosRealizadas);

    if (previstosRealizadas > 0) {
        percentual = efetivosRealizadas * 100.0 / previstosRealizadas;
        printf("Participacao nas realizadas: %.2f%%\n", percentual);
    } else {
        printf("Participacao nao calculavel: previsao das realizadas igual a zero.\n");
    }
}

void mostrarAlimentacao(void) {
    printf("\n----- ALIMENTACAO SAUDAVEL -----\n");
    printf("- Inclua frutas, legumes e verduras nas refeicoes.\n");
    printf("- Prefira alimentos naturais a doces, salgadinhos e frituras.\n");
    printf("- Evite o excesso de refrigerantes e sucos industrializados.\n");
    printf("- Beba agua ao longo do dia.\n");
    printf("- Faca as refeicoes com calma e em horarios regulares.\n");
    printf("Informacoes educativas; nao substituem orientacao profissional.\n");
}

void mostrarAtividades(void) {
    printf("\n----- ATIVIDADES FISICAS -----\n");
    printf("- Brincar ao ar livre tambem e atividade fisica.\n");
    printf("- Caminhar, correr, pedalar e dancar movimentam o corpo.\n");
    printf("- Esportes em grupo estimulam a convivencia.\n");
    printf("- Reduza o tempo parado em frente a telas.\n");
    printf("- Escolha atividades de que voce goste.\n");
    printf("Informacoes educativas; nao substituem orientacao profissional.\n");
}

void mostrarDicas(void) {
    printf("\n----- DICAS DE SAUDE -----\n");
    printf("1. O descanso faz parte de uma vida saudavel.\n");
    printf("2. Lave as maos antes das refeicoes.\n");
    printf("3. Uma fruta e uma opcao de lanche.\n");
    printf("4. Convide amigos e familiares para se movimentar junto.\n");
    printf("5. Converse com um adulto ou profissional de saude sobre duvidas.\n");
}

int materialApoio(void) {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n1 Alimentacao | 2 Atividades fisicas | 3 Dicas | 0 Voltar\n");
        opcao = lerNumero("Opcao: ", 0, 3);
        if (opcao == -1) {
            return 0;
        }
        switch (opcao) {
            case 1:
                mostrarAlimentacao();
                break;
            case 2:
                mostrarAtividades();
                break;
            case 3:
                mostrarDicas();
                break;
            case 0:
                break;
        }
    }
    return 1;
}

int executarQuiz(void) {
    int questao, resposta, pontuacao = 0;

    printf("\n===== QUIZ DE HABITOS SAUDAVEIS =====\n");
    for (questao = 1; questao <= 3; questao++) {
        printf("\nQuestao %d de 3\n", questao);
        switch (questao) {
            case 1:
                printf("Qual destes alimentos e uma opcao saudavel?\n");
                printf("1 Frutas\n2 Balas\n3 Refrigerante\n");
                break;
            case 2:
                printf("Qual atividade ajuda a manter o corpo ativo?\n");
                printf("1 Caminhar\n2 Ficar sentado o dia todo\n3 Nao realizar atividades\n");
                break;
            case 3:
                printf("Qual bebida e importante para a hidratacao?\n");
                printf("1 Agua\n2 Refrigerante\n3 Bebida energetica\n");
                break;
        }

        resposta = lerNumero("Sua resposta (1 a 3): ", 1, 3);
        if (resposta == -1) {
            return 0;
        }
        if (resposta == 1) {
            printf("Resposta correta!\n");
            pontuacao++;
        } else {
            printf("Resposta incorreta. A correta era 1: ");
            switch (questao) {
                case 1:
                    printf("Frutas.\n");
                    break;
                case 2:
                    printf("Caminhar.\n");
                    break;
                case 3:
                    printf("Agua.\n");
                    break;
            }
        }
    }

    printf("Voce acertou %d de 3 questoes.\n", pontuacao);
    if (pontuacao == 3) {
        printf("Parabens! Voce acertou todas!\n");
    } else {
        printf("Releia o material de apoio e tente novamente.\n");
    }
    return 1;
}

void executar(void) {
    int opcao, ativo = 1;

    printf("PSE em Acao | Somente dados ficticios e coletivos.\n");
    while (ativo == 1) {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 Cadastrar acao\n");
        printf("2 Listar acoes\n");
        printf("3 Pesquisar acoes\n");
        printf("4 Atualizar situacao\n");
        printf("5 Resumo geral\n");
        printf("6 Material de apoio\n");
        printf("7 Quiz sobre habitos saudaveis\n");
        printf("0 Sair\n");

        opcao = lerNumero("Opcao: ", 0, 7);
        if (opcao == -1) {
            ativo = 0;
        } else {
            switch (opcao) {
                case 0:
                    ativo = 0;
                    break;
                case 1:
                    ativo = cadastrarAcao();
                    break;
                case 2:
                    listarAcoes();
                    break;
                case 3:
                    ativo = pesquisarAcoes();
                    break;
                case 4:
                    ativo = atualizarSituacao();
                    break;
                case 5:
                    mostrarResumo();
                    break;
                case 6:
                    ativo = materialApoio();
                    break;
                case 7:
                    ativo = executarQuiz();
                    break;
            }
        }
    }
    printf("Programa encerrado. Dados em memoria descartados.\n");
}

int main(void) {
    executar();
    return 0;
}

