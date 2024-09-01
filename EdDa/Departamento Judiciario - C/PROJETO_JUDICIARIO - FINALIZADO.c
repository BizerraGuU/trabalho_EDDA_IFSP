// Aluno: Vitor Augusto dos Santos
// Prontuario: SP3132048
// Aluno: Gustavo Bezerra de Andrade
// Prontuario: SP
// Turma: TADS Noturno 2º Semestre

/***********************************************************************************
 *                                     INCLUDES
***********************************************************************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include <malloc.h> 
#include <locale.h>

/***********************************************************************************
 *                                    ARQUIVOS
***********************************************************************************/ 
#define ARQCLI "CLIENTES.DAT"
#define ARQESTAG "ESTAGIARIOS.DAT"
#define ARQADV "ADVOGAGOS.DAT"
#define ARQDISPOADV "DISPONIBILIDADE_ADV.DAT"
#define ARQCASOATRIB "CASOSATRIBUIDOS.DAT"
#define ARQAGENDA "AGENDA.DAT"
#define ARQPUBLI "PUBLICACOES.DAT"
#define ARQCTRL "CONTROLE.DAT"

/***********************************************************************************
 *                              VALORES PRÉ DEFINIDOS
***********************************************************************************/ 
#define TAMNOME 50
#define ESPECIALIDADE 50
#define SALARIO_MINIMO 1412

/***********************************************************************************
 *                            CRIAÇÃO DAS STRUCTS
***********************************************************************************/ 
//Struct Clientes
typedef struct
{
    int cod;
    char dtAtendimento[10+1];
    char hrAtendimento[5+1];
    char hrChegada[5+1];
    char comoConheceu[50+1];
    char atendente[TAMNOME + 1];
    char pessoaFisJuri[1+1];
    char nomeCliente[TAMNOME+1];
    char genero[15+1];
    char pertLGBT[1+1];
    char etnia[8+1];
    char dtNascimento[10+1];
    char nacionalidade[15+1];
    char naturalidade[2+1];
    char cpf[11+1];
    char rg[9+1];
    char endereco[50+1];
    char celular[11+1];
    char usaWpp[1+1];
    char outroTel[11+1];
    char email[35+1];
    char escolaridade[40+1];
    char profissao[40+1];
    char situacaoEmprego[30+1];
    char estadoCivil[30+1];
    char temFilhos;
    int filhosMorando;
    int totalPessoasFam;
    char beneficioSocial;
    float valBeneficio;
    float rendaMes;
    float rendTotal;
    char gastoMedico;
    float valGastoMedico;
    char investimentoFinanc;
    float valInvestFinanceiro;
    char temCasa;
    float valCasa;
    char temApto;
    float valApto;
    char temTerreno;
    float valTerreno;
    char temImovelComerc;
    float valImovelComerc;
    char temCarro;
    float valCarro;
    char violenciaDomestica;
    char resumoCaso[200+1];
    char ramoDireito[25+1];
    char temPerfilAssist;
} CLIENTES;

//Struct Advogados
typedef struct{
    int oab;
    char nomeAdv [35+1];
    char especialidade [25+1];
    char cpf [11+1];
    char emailAdv [40+1] ;
    char celularAdv [11+1];
    int anoIngresso;
} ADVOGADOS;

//Struct disponibilidade advogados 
typedef struct{
    int oab;
    int diaSemana;
    char horaIni [5+1];
    char horaFim [5+1];
    char formato;
} DISPOADV;

//Struct casos atribuidos
typedef struct{
    char cpf[11+1];
    int cdAtendimento;
    char codEstag[11+1];
    char diAtribuido [11+1];
    char hrAtribuido [5+1];
} CASOSATRIB;

//Struct Estagiarios
typedef struct{
    char codEstag [7+1];
    char nomeEstag [20+1] ;
    char celularEstag [11+1];
    char emailEstag [40+1];
    char tipo;
} ESTAGIARIOS;

//Struct agendamento
typedef struct{
    char codEstagiario[7+1];
    int oab;
    char dtAgendada[11+1];
    char hrAgendado[5+1];
    char dtInscrito[11+1];
    char hrInscrito[5+1];
    char areaDireito[25+1];
    char tpOrientacao[35+1];
    char temPrzFatal [3+1];
    char przFatal[11+1];
    char observacoes[25+1];
    char numProcesso[25+1];
    char foiAtend[25+1];
} AGENDAMENTO;

//Struct controle
typedef struct{
    char numProcesso[25+1];
    char tema[30+1];
    char cpf[11+1];
    char polo[20+1];
    char codeEstag[8+1];
    char dtControle[13+1];
    char proxTarefa[30+1];
    char temPrazoDobro[3+1];
    char obsPrazo[40+1];
    char audiencia[40+1];
    char prazoSimples[13+1];
    char prazoDobrado[13+1];
    char movimentacao[2000+1];
    int diasProxControle;
    char dtProposicao[13+1];
} CONTROLE;

//Struct Publicacao
typedef struct{
    char codEstag[7+1];
    char dtCircula[13+1];
    char hrCircula[6+1];
    char numcnj[25+1];
    char tipoAcao[25+1];
    char varaJuizo[20+1];
    char foro[40+1];
    char cpf[11+1];
    char reclamado[70+1];
    char advReclamante[TAMNOME+1];
    char advReclamado[TAMNOME+1];
    char movimentacao[2000];
} PUBLICACAO;

/***********************************************************************************
 *                               VARIAVEIS GLOBAIS
***********************************************************************************/ 
FILE *arq;
char conf, repetir;
int codigo = 1;
char linha[50];
int op = -1;

/***********************************************************************************
 *                               MENSAGEM DE ERRO
***********************************************************************************/ 
void erro (void){
    system("cls");
    printf("ERRO"); 
    getch();
}

/***********************************************************************************
 *                         ORDENAÇÃO DA DISPONIBILIDADE
***********************************************************************************/ 
void quickSort(DISPOADV arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(DISPOADV arr[], int low, int high) {
    int pivot = arr[high].diaSemana;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].diaSemana < pivot) {
            i++;
            DISPOADV temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    DISPOADV temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void ordenarDisponibilidadePorDiaSemana() {
    FILE *arq = fopen(ARQDISPOADV, "r");
    DISPOADV *disponibilidades = NULL;
    int count = 0;

    if (arq == NULL) {
        printf("O Arquivo [DISPONIBILIDADE_ADV.DAT] nao existe!\n\n");
        return;
    }

    fseek(arq, 0, SEEK_END);
    count = ftell(arq) / sizeof(DISPOADV);
    rewind(arq);

    disponibilidades = (DISPOADV *)malloc(count * sizeof(DISPOADV));
    if (disponibilidades == NULL) {
        printf("Erro ao alocar memoria.\n");
        fclose(arq);
        return;
    }

    fread(disponibilidades, sizeof(DISPOADV), count, arq);
    fclose(arq);

    quickSort(disponibilidades, 0, count - 1);

    arq = fopen(ARQDISPOADV, "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        free(disponibilidades);
        return;
    }

    fwrite(disponibilidades, sizeof(DISPOADV), count, arq);

    printf("\nRegistros ordenados com sucesso pelo dia da semana!\n\n");

    fclose(arq);
    free(disponibilidades);
}

/***********************************************************************************
 *                            PREPARAÇÃO DA FILA
***********************************************************************************/ 
typedef int TIPOCHAVE;
#define true 1
#define false 0
typedef int bool;

typedef struct{
    TIPOCHAVE chave;
    AGENDAMENTO agenda;
} REGISTRO;

typedef struct aux{
    REGISTRO reg;
    struct aux *PROX;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct{
    PONT inicio;
    PONT fim;
} fila;

fila *fl;

/***********************************************************************************
 *                              FUNÇÕES DE VERIFICAÇÃO
***********************************************************************************/ 
// Verifica se o advogado esta cadastrado / Usado na função adicionarDisponibilidade()
int verificarOab(int oab){

    FILE *arquivo = fopen(ARQADV, "r");

    ADVOGADOS adv;

    int controle = -1;

    while(!feof(arquivo) && controle == -1){
        fread(&adv, sizeof(adv), 1, arquivo);
        if(!feof(arquivo) && oab == adv.oab){
            controle = 1;
            break;
        }
    }

    fclose(arquivo);
    return controle;
}

// Verificar codigo do estagiario
int verificarCodEstag(char cod[7+1]){

    FILE *arqui = fopen(ARQESTAG, "r");

    ESTAGIARIOS est;

    int controle = -1;

    while(!feof(arqui) && controle == -1){
        fread(&est, sizeof(est), 1, arqui);
        if(!feof(arqui) && strcmp(cod, est.codEstag) == 0){
            fclose(arqui);
            return controle = 1;
        }
    }

    fclose(arqui);
    return controle;
}

// Verificar e retorna cliente
CLIENTES verificarCliente(char cpf[11+1]){
    FILE *arquivo = fopen(ARQCLI, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo [CLIENTES.DAT].\n\n");
        system("pause");
        return;
    }

    CLIENTES cliente;   

    while (fread(&cliente, sizeof(CLIENTES), 1, arquivo)){
        if(strcmp(cliente.cpf, cpf) == 0) return cliente;
    }

    cliente.cod = -1;
    return cliente;
}

// Validar cpf cliente
bool validaCpfCli(char cpf[11+1]){
    FILE *arquivo = fopen(ARQCLI, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo [CLIENTES.DAT].\n\n");
        system("pause");
        return;
    }

    CLIENTES cliente;   

    while (fread(&cliente, sizeof(CLIENTES), 1, arquivo))
        if(strcmp(cliente.cpf, cpf) == 0) return true;
    
    return false;    
}

// Verificar estagiario plantonista
bool verificarEstaPlantonista(char cod[7+1]){
    FILE *arqui = fopen(ARQESTAG, "r");

    ESTAGIARIOS est;

    while(!feof(arqui)){
        fread(&est, sizeof(est), 1, arqui);
        if(!feof(arqui) && strcmp(cod, est.codEstag) == 0 && est.tipo == 'P'){
            fclose(arqui);
            return true;
        }
    }

    fclose(arqui);
    return false;
}

// Verificar numero do processo
bool verificaNumProcesso(char numPro[25+1]){
    FILE *arqui = fopen(ARQCTRL, "r");

    CONTROLE ctrl;

    while(!feof(arqui)){
        fread(&ctrl, sizeof(ctrl), 1, arqui);
        if(!feof(arqui) && strcmp(numPro, ctrl.numProcesso) == 0){
            fclose(arqui);
            return true;
        }
    }

    fclose(arqui);
    return false;    
}

// Verifica e retorna CONTROLE
CONTROLE verificarProcesso(char numP[25+1]){
    FILE *arquivo = fopen(ARQCTRL, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo [CONTROLE.DAT].\n\n");
        system("pause");
        return;
    }

    CONTROLE control;   

    while (fread(&control, sizeof(CONTROLE), 1, arquivo)){
        if(strcmp(control.numProcesso, numP) == 0) return control;
    }

    return control;
}

// Verifica se o processo recebeu alguma publicacao
bool verificaProcessoPub(char np[25+1]){
    FILE *arqui = fopen(ARQPUBLI, "r");

    PUBLICACAO pb;

    while(!feof(arqui)){
        fread(&pb, sizeof(pb), 1, arqui);
        if(!feof(arqui) && strcmp(np, pb.numcnj) == 0){
            fclose(arqui);
            return true;
        }
    }
    fclose(arqui);
    return false;      
}

/***********************************************************************************
 *                          CRIAÇÃO E IMPLEMENTAÇÃO DA FILA
***********************************************************************************/ 
// Iniciar fila
void inicializarFila(fila *f){
    f -> inicio = NULL;
    f -> fim = NULL;
}

// Exibir os elementos da fila
void exibirFila(fila *f){
    PONT end = f->inicio;
    system("cls");
    
    if(end == NULL) 
        printf("Nao houve nenhum agendamento!\n\n");
    
    else{
        printf("FILA DE ESTAGIARIOS\n\n");
        printf("%-11s | %-14s | %-14s | %-14s | %-14s | %-15s | %-28s | %-14s | %-15s | %-20s | %-25s | %-26s\n", "Estagiario", "Data agendada", "Hora agendada", "Data inscrito", "Hora inscrito", "Area de direito", "Tipo orientacao", "Prazo fatal", "Data prazo fatal", "Observacoes", "Nº processo", "Atendido");
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            while(end != NULL){
                printf("%-11s | %-14s | %-14s | %-14s | %-14s | %-15s | %-28s | %-14s | %-16s | %-20s | %-25s | %-26s\n", end->reg.agenda.codEstagiario, end->reg.agenda.dtAgendada, end->reg.agenda.hrAgendado, end->reg.agenda.dtInscrito, end->reg.agenda.hrInscrito, end->reg.agenda.areaDireito, end->reg.agenda.tpOrientacao, end->reg.agenda.temPrzFatal, end->reg.agenda.przFatal, end->reg.agenda.observacoes, end->reg.agenda.numProcesso, end->reg.agenda.foiAtend);
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                end = end -> PROX;
            }
    }
}

// Preencher fila com arquivo AGENDA.DAT
void preencherFilaAgenda(fila *f, int oab){

    FILE *arqFila = fopen(ARQAGENDA, "r");
    
    REGISTRO r;  
    AGENDAMENTO agd;

    while (fread(&agd, sizeof(agd), 1, arqFila)){
        if (strcmp(agd.foiAtend, "Em espera") == 0) {
            PONT novo = (PONT) malloc(sizeof(ELEMENTO));
            if (novo == NULL) {
                printf("Erro: falha ao alocar memoria.\n");
                fclose(arqFila);
                system("pause");
            } 
            if(agd.oab == oab){
                r.chave = agd.oab;
                sprintf(r.agenda.codEstagiario, "%s", agd.codEstagiario);
                r.agenda.oab = agd.oab;
                sprintf(r.agenda.dtAgendada, "%s", agd.dtAgendada);
                sprintf(r.agenda.hrAgendado, "%s", agd.hrAgendado);
                sprintf(r.agenda.dtInscrito, "%s", agd.dtInscrito);  
                sprintf(r.agenda.hrInscrito, "%s", agd.hrInscrito); 
                sprintf(r.agenda.areaDireito, "%s", agd.areaDireito);  
                sprintf(r.agenda.tpOrientacao, "%s", agd.tpOrientacao);
                sprintf(r.agenda.temPrzFatal, "%s", agd.temPrzFatal); 
                sprintf(r.agenda.przFatal, "%s", agd.przFatal); 
                sprintf(r.agenda.observacoes, "%s", agd.observacoes);  
                sprintf(r.agenda.numProcesso, "%s", agd.numProcesso);
                sprintf(r.agenda.foiAtend, "%s", agd.foiAtend);

                novo -> reg = r;
                novo -> PROX = NULL;

                if(f -> inicio == NULL)
                    f -> inicio = novo;
                else
                    f -> fim -> PROX = novo;
                f -> fim = novo;
            } 
        }
    }
    
    fclose(arqFila);
}

// Reiniciar a fila
void reinicializarFila(fila *f) 
{  
   PONT end = f->inicio;
   PONT apagar;
   while (end != NULL) 
   {  
      apagar = end;  
	  end = end->PROX;  
	  free(apagar);
   }
   f->inicio = NULL;  
   f->fim = NULL;
}

// Verifica se a fila esta vazia
bool estaVazia(fila *f){
    if(f -> inicio == NULL)
        return true;
    return false;
}

// Busca primeiro elemento da fila
REGISTRO primeiroElemento(fila *f) {
    REGISTRO regVazio = {0};  // Cria um registro vazio para casos de fila vazia

    if (f->inicio == NULL) {
        printf("Fila vazia!\n");
        return regVazio;
    }

    return f->inicio->reg;
}

/***********************************************************************************
 *                            CONTROLE DE ADVOGADOS
***********************************************************************************/ 
//Cadastrar Advogados
void cadastrarAdvogado(){

    arq = fopen(ARQADV, "a");

    int oab;

    ADVOGADOS adv;

    system("cls");
    printf("---------------- CADASTRO DE ADVOGADOS ----------------\n");

    //Recebendo os valores de entrada
    printf("OAB: ");
    scanf("%i", &oab);

    if(verificarOab(oab) == -1){
        adv.oab = oab;

        fflush(stdin);
        printf("Nome: ");
        gets(adv.nomeAdv);

        fflush(stdin);
        printf("Especialidade: ");
        gets(adv.especialidade);

        fflush(stdin);
        printf("CPF: ");
        gets(adv.cpf);

        fflush(stdin);
        printf("E-mail: ");
        gets(adv.emailAdv);

        fflush(stdin);
        printf("Celular: ");
        gets(adv.celularAdv);

        printf("Ano de ingresso: ");
        scanf("%i", &adv.anoIngresso);

        //Registrando em um arquivo os dados de entrada
        fwrite(&adv, sizeof(adv), 1, arq);

        printf("\n\nAdvogado [%s] cadastrado com sucesso!\n\n", adv.nomeAdv);
    } else 
        printf("OAB [%i] ja cadastrada no sistema!\n\n", oab);

    system("pause");

    fclose(arq);
}

// Buscar OAB
void buscarOab(int oab){

    arq = fopen(ARQADV, "r");

    ADVOGADOS adv;

    int controle = -1;

    while(!feof(arq) && controle == -1){
        fread(&adv, sizeof(adv), 1, arq);
        if(!feof(arq) && oab == adv.oab){
            printf("\n------------- ADVOGADO CADASTRADO --------------");
            printf("\nOAB: %i\nNome: %s\nEspecialidade: %s\nCPF: %s\nE-mail: %s\nCelular: %s\nAno de ingresso: %i", adv.oab, adv.nomeAdv, adv.especialidade, adv.cpf, adv.emailAdv, adv.celularAdv, adv.anoIngresso);
            printf("\n-------------------------------------------------\n\n");
            controle = 1;
            break;
        }
    }

    if(controle == -1)
        printf("\nOAB [%i] informada nao consta nos registros!\n\n", oab);
    
    fclose(arq);
    system("pause"); 
}

//Consultar advogados
void consultarAdvogados(){

    arq = fopen(ARQADV, "r");

    ADVOGADOS adv;

    int buscaOab, opc=-1;

    system("cls");

    if (arq == NULL){
        printf("O Arquivo [ADVOGADOS.DAT] nao existe!\n\n");
        system("pause");
    }

    else {

        printf("------------ EXIBIR ADVOGADOS -------------\n");
        printf("          1 - Pesquisar OAB                \n");
        printf("          2 - Pesquisa geral               \n");
        printf("-------------------------------------------\n");
        printf("    Selecione uma opcao: ");
        scanf("%i", &opc);

        if(opc == 1){
            system("cls");
            printf("Digite a OAB para pesquisa: ");
            scanf("%i", &buscaOab);
            buscarOab(buscaOab);
        }

        if(opc == 2){

            FILE *arqTmp = fopen("ADVOGADOS.TMP", "w");

            system("cls");
            fprintf(arqTmp, "%-6s | %-30s | %-25s | %-11s | %-40s | %-11s | %-4s\n", "OAB", "Nome", "Especialidade", "CPF", "E-mail", "Celular", "Ano de ingresso");
            fprintf(arqTmp, "--------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            while(!feof(arq)){
                fread(&adv, sizeof(adv), 1, arq);
                if(!feof(arq)){
                    fprintf(arqTmp, "%-6i | %-30s | %-25s | %-11s | %-40s | %-11s | %-4i\n", adv.oab, adv.nomeAdv, adv.especialidade, adv.cpf, adv.emailAdv, adv.celularAdv, adv.anoIngresso);
                    fprintf(arqTmp, "--------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                }
            }
            fclose(arqTmp);
            system("start ADVOGADOS.TMP");
            system("pause");
            remove("ADVOGADOS.TMP");
        }
    }
}

// Adicionar disponibilidade de advogados
void adicionarDisponibilidade(){

    DISPOADV dAdv;
    
    int oab;

    arq = fopen(ARQDISPOADV, "a");

    system("cls");

    if (arq == NULL){
        printf("O Arquivo [DISPONIBILIDADE_ADV.DAT] nao existe!\n\n");
        system("pause");
    } else {

        printf("---------------- CADASTRO DE DISPONIBILIDADE DO ADVOGADO ----------------\n");

        //Recebendo os valores de entrada
        printf("OAB: ");
        scanf("%i", &oab);

        if(verificarOab(oab) == 1){

            dAdv.oab = oab;

            fflush(stdin);
            printf("Dia da semana (2-segunda...6-sexta): ");
            scanf("%i", &dAdv.diaSemana);

            fflush(stdin);
            printf("Hora inicio (hh:mm): ");
            gets(dAdv.horaIni);

            fflush(stdin);
            printf("Hora fim (hh:mm): ");
            gets(dAdv.horaFim);

            fflush(stdin);
            printf("Formato (P-presencial/R-remoto): ");
            scanf("%c", &dAdv.formato);

            strupr(&dAdv.formato);

            //Registrando em um arquivo os dados de entrada
            fwrite(&dAdv, sizeof(dAdv), 1, arq);

            printf("\n\nDiponibilidade cadastrada com sucesso!\n\n");

            system("pause");

            fclose(arq);       
            ordenarDisponibilidadePorDiaSemana();
        } else {
            printf("\nOAB [%i] informada nao consta nos registros!\n\n", oab);
            system("pause");
        }
    }
}

// Plantão de advogados
void plantao(){

    ADVOGADOS adv;
    DISPOADV dAdv;

    FILE *arqAdv = fopen(ARQADV, "r");
    FILE *arqDadv = fopen(ARQDISPOADV, "r");
    FILE *arqTmp = fopen("PLANTAO.TMP", "w");

    if(arqAdv == NULL || arqDadv == NULL){
        printf("Nao foi possivel visualizar o plantao de advogados, arquivos faltando!\n\n");
        system("pause");
    } else {

        fprintf(arqTmp, "%-6s | %-58s | %-40s | %-15s | %-13s | %-13s | %-13s\n", "OAB", "Nome e especialidade", "E-mail", "Dia da semana", "Hora inicio", "Hora fim", "Formato");
        fprintf(arqTmp, "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

        while(!feof(arqDadv)){
            fread(&dAdv, sizeof(dAdv), 1, arqDadv);
            if(!feof(arqDadv)){
            while(!feof(arqAdv)){
                fread(&adv, sizeof(adv), 1, arqAdv);
                if(dAdv.oab == adv.oab && !feof(arqAdv)){
                    if(dAdv.formato == 'R'){
                        if(dAdv.diaSemana == 2)
                            fprintf(arqTmp, "%-6i | %-30s [%-25s] | %-40s | %-15s | %-13s | %-13s | %-13s\n", adv.oab, adv.nomeAdv, adv.especialidade, adv.emailAdv, "Segunda", dAdv.horaIni, dAdv.horaFim, "Remoto");
                        if(dAdv.diaSemana == 3)
                            fprintf(arqTmp, "%-6i | %-30s [%-25s] | %-40s | %-15s | %-13s | %-13s | %-13s\n", adv.oab, adv.nomeAdv, adv.especialidade, adv.emailAdv, "Terca", dAdv.horaIni, dAdv.horaFim, "Remoto");
                        if(dAdv.diaSemana == 4)
                            fprintf(arqTmp, "%-6i | %-30s [%-25s] | %-40s | %-15s | %-13s | %-13s | %-13s\n", adv.oab, adv.nomeAdv, adv.especialidade, adv.emailAdv, "Quarta", dAdv.horaIni, dAdv.horaFim, "Remoto");
                        if(dAdv.diaSemana == 5)
                            fprintf(arqTmp, "%-6i | %-30s [%-25s] | %-40s | %-15s | %-13s | %-13s | %-13s\n", adv.oab, adv.nomeAdv, adv.especialidade, adv.emailAdv, "Quinta", dAdv.horaIni, dAdv.horaFim, "Remoto");
                        if(dAdv.diaSemana == 6)
                            fprintf(arqTmp, "%-6i | %-30s [%-25s] | %-40s | %-15s | %-13s | %-13s | %-13s\n", adv.oab, adv.nomeAdv, adv.especialidade, adv.emailAdv, "Sexta", dAdv.horaIni, dAdv.horaFim, "Remoto");
                        fprintf(arqTmp, "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                    }
                    if(dAdv.formato == 'P'){
                        if(dAdv.diaSemana == 2)
                            fprintf(arqTmp, "%-6i | %-30s [%-25s] | %-40s | %-15s | %-13s | %-13s | %-13s\n", adv.oab, adv.nomeAdv, adv.especialidade, adv.emailAdv, "Segunda", dAdv.horaIni, dAdv.horaFim, "Presencial");
                        if(dAdv.diaSemana == 3)
                            fprintf(arqTmp, "%-6i | %-30s [%-25s] | %-40s | %-15s | %-13s | %-13s | %-13s\n", adv.oab, adv.nomeAdv, adv.especialidade, adv.emailAdv, "Terca", dAdv.horaIni, dAdv.horaFim, "Presencial");
                        if(dAdv.diaSemana == 4)
                            fprintf(arqTmp, "%-6i | %-30s [%-25s] | %-40s | %-15s | %-13s | %-13s | %-13s\n", adv.oab, adv.nomeAdv, adv.especialidade, adv.emailAdv, "Quarta", dAdv.horaIni, dAdv.horaFim, "Presencial");
                        if(dAdv.diaSemana == 5)
                            fprintf(arqTmp, "%-6i | %-30s [%-25s] | %-40s | %-15s | %-13s | %-13s | %-13s\n", adv.oab, adv.nomeAdv, adv.especialidade, adv.emailAdv, "Quinta", dAdv.horaIni, dAdv.horaFim, "Presencial");
                        if(dAdv.diaSemana == 6)
                            fprintf(arqTmp, "%-6i | %-30s [%-25s] | %-40s | %-15s | %-13s | %-13s | %-13s\n", adv.oab, adv.nomeAdv, adv.especialidade, adv.emailAdv, "Sexta", dAdv.horaIni, dAdv.horaFim, "Presencial");
                        fprintf(arqTmp, "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                    }
                    fseek(arqAdv, 0, SEEK_SET);
                    break;
                }
            }
          }
        }
        fclose(arqAdv);
        fclose(arqDadv);
        fclose(arqTmp);
        system("start PLANTAO.TMP");
    }    
}

// Consultar todos os agendamentos de estagiario
void consultarAgendamentos(){
    arq = fopen(ARQAGENDA, "r");

    AGENDAMENTO agd;

    system("cls");

    if (arq == NULL){
        printf("O Arquivo [AGENDA.DAT] nao existe!\n\n");
        system("pause");
    }
    
    else {
        FILE *arqTmp = fopen("AGENDA.TMP", "w");

        system("cls");
        fprintf(arqTmp, "%-11s | %-6s | %-14s | %-14s | %-14s | %-14s | %-15s | %-28s | %-14s | %-15s | %-20s | %-26s | %-26s\n", "Estagiario", "OAB", "Data agendada", "Hora agendada", "Data inscrito", "Hora inscrito", "Area de direito", "Tipo orientacao", "Prazo fatal", "Data prazo fatal", "Observacoes", "Nº processo", "Atendido");
        fprintf(arqTmp, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        while(!feof(arq)){
            fread(&agd, sizeof(agd), 1, arq);
            if(!feof(arq)){
                fprintf(arqTmp, "%-11s | %-6i | %-14s | %-14s | %-14s | %-14s | %-15s | %-28s | %-14s | %-16s | %-20s | %-25s | %-26s\n", agd.codEstagiario, agd.oab, agd.dtAgendada, agd.hrAgendado, agd.dtInscrito, agd.hrInscrito, agd.areaDireito, agd.tpOrientacao, agd.temPrzFatal, agd.przFatal, agd.observacoes, agd.numProcesso, agd.foiAtend);
                fprintf(arqTmp, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            }
        }
        
        fclose(arqTmp);
        system("start AGENDA.TMP");
        system("pause");
        remove("AGENDA.TMP");
    }        
}

// Atender estagiario
void atenderEstag(){

    AGENDAMENTO agd;
    FILE *arqAgend;

    int oab;
    char atender[25+1], opc;

    if(estaVazia(&fl) == 0)
        reinicializarFila(&fl);

    system("cls");

    printf("Digite a OAB: ");
    scanf("%i", &oab);
    
    if(verificarOab(oab)==1){

        preencherFilaAgenda(&fl, oab);

        if(estaVazia(&fl)==true){
            printf("\nNao houve nenhum agendamento\n\n");
            system("pause");
            return;
        }

        exibirFila(&fl);

        fflush(stdin);
        printf("Atender a fila? [s-sim]: ");
        scanf("%c", &opc);
        strupr(&opc);

        if(opc == 'S'){

            int encontrado=0;

            arqAgend = fopen(ARQAGENDA, "rb+");

            if(arqAgend == NULL){
                printf("Erro ao abrir o arquivo [AGENDA.DAT]");
                return;
            }

            fflush(stdin);
            printf("Foi atendido? ");
            gets(atender);

            REGISTRO reg = primeiroElemento(&fl);

            while (fread(&agd, sizeof(AGENDAMENTO), 1, arqAgend)) {
                if (strcmp(agd.codEstagiario, reg.agenda.codEstagiario) == 0 && agd.oab == reg.agenda.oab) {
                    encontrado = 1;
                    break;
                }
            }

            if (encontrado==1) {

                strncpy(agd.foiAtend, atender, sizeof(agd.foiAtend) - 1);
                agd.foiAtend[sizeof(agd.foiAtend) - 1] = '\0'; 

                fseek(arqAgend, -(long) sizeof(AGENDAMENTO), SEEK_CUR);

                fwrite(&agd, sizeof(AGENDAMENTO), 1, arqAgend);

                printf("\nAtendimento realizado com sucesso.\n\n");
            } else {
                printf("\nErro ao atender!.\n\n");
            }

            fclose(arqAgend);
        }

    } else printf("\nOAB [%i] nao registrado no sistema!\n\n", oab);

    system("pause");

}

/***********************************************************************************
 *                            CONTROLE DE ESTAGIARIOS
***********************************************************************************/ 
// Cadastrar um novo estagiario
void cadastrarEstagiario(){
    arq = fopen(ARQESTAG, "a");

    ESTAGIARIOS est;

    char cod[7];

    system("cls");
    printf("---------------- CADASTRO DE ESTAGIARIO ----------------\n");

    //Recebendo os valores de entrada
    fflush(stdin);
    printf("Codigo do estagiario: ");
    gets(cod);

    if(verificarCodEstag(cod) == -1){

        sprintf(est.codEstag, "%s", cod);

        fflush(stdin);
        printf("Nome: ");
        gets(est.nomeEstag);

        fflush(stdin);
        printf("Celular: ");
        gets(est.celularEstag);

        fflush(stdin);
        printf("E-mail: ");
        gets(est.emailEstag);
    
        fflush(stdin);
        printf("Tipo (A - atendente/P - plantonista/V - vareiro): ");
        scanf("%c", &est.tipo);
        strupr(&est.tipo);

        //Registrando em um arquivo os dados de entrada
        fwrite(&est, sizeof(est), 1, arq);

        printf("\n\nEstagiario [%s] cadastrado com sucesso!\n\n", est.nomeEstag);

    } else
        printf("O codigo [%s] ja esta cadastrado no sistema!\n\n", cod);

    system("pause");
    fclose(arq);
}

//Consultar estagiarios
void consultarEstagiario(){

    arq = fopen(ARQESTAG, "r");

    ESTAGIARIOS est;

    int opc=-1, controle = -1;
    char codEst[25+1];

    system("cls");

    if (arq == NULL){
        printf("O Arquivo [ESTAGIARIOS.DAT] nao existe!\n\n");
        system("pause");
    }
    
    else {
    
        printf("------------ EXIBIR ESTAGIARIOS -------------\n");
        printf("          1 - Pesquisar codigo               \n");
        printf("          2 - Pesquisa geral                 \n");
        printf("---------------------------------------------\n");
        printf("    Selecione uma opcao: ");
        scanf("%i", &opc);

        if(opc == 1){
            system("cls");
            printf("Informe o codigo do estagiario: ");
            fflush(stdin);
            gets(codEst);
            system("cls");
            while(!feof(arq) && controle == -1){
                fread(&est, sizeof(est), 1, arq);
                if(!feof(arq) && strcmp(codEst, est.codEstag) == 0){
                    printf("\n------------- ESTAGIARIO CADASTRADO --------------");
                    printf("\nCodigo: %s\nNome: %s\nCelular: %s\nE-mail: %s\nTipo: %c\n", est.codEstag, est.nomeEstag, est.celularEstag, est.emailEstag, est.tipo);
                    printf("-------------------------------------------------\n\n");
                    controle = 1;
                    break;
                }
            }

            if(controle == -1)
                printf("\nCodigo [%s] informado nao consta nos registros!\n\n", codEst);
            system("pause");
            return;
        }

        if(opc == 2){
            FILE *arqTmp = fopen("ESTAGIARIOS.TMP", "w");

            system("cls");
            fprintf(arqTmp, "%-8s | %-21s | %-12s | %-40s | %s\n", "Codigo", "Nome", "Celular", "E-mail", "Tipo");
            fprintf(arqTmp, "----------------------------------------------------------------------------------------------------\n");
            while(!feof(arq)){
                fread(&est, sizeof(est), 1, arq);
                if(!feof(arq)){
                    fprintf(arqTmp, "%-8s | %-21s | %-12s | %-40s | %c\n", est.codEstag, est.nomeEstag, est.celularEstag, est.emailEstag, est.tipo);
                    fprintf(arqTmp, "----------------------------------------------------------------------------------------------------\n");
                }
            }
            fclose(arqTmp);
            system("start ESTAGIARIOS.TMP");
            system("pause");
            remove("ESTAGIARIOS.TMP");
        }
    }    
}

// Agendar atendimento com advogado
void agendarAtend(){
    char pzFatal;

    //Capturando data e hora atuais
    struct tm *dt_hr_atual;
    time_t segundos;
    time(&segundos);
    dt_hr_atual = localtime(&segundos);

    AGENDAMENTO agd;

    arq = fopen(ARQAGENDA ,"a");

    if(arq == NULL){
        printf("O Arquivo [AGENDA.DAT] nao existe!\n\n");
        system("pause");
    } else {

    system("cls");

    //Recebendo os valores de entrada
    fflush(stdin);
    printf("Codigo do estagiario: ");
    gets(agd.codEstagiario);

    if(verificarCodEstag(agd.codEstagiario) == 1){

        plantao();

        fflush(stdin);
        printf("OAB do advogado: ");
        scanf("%i", &agd.oab);

        if(verificarOab(agd.oab) == 1){

            fflush(stdin);
            printf("Data agendada (dd/MM/AAAA): ");
            gets(agd.dtAgendada);

            fflush(stdin);
            printf("Hora agendada (hh:mm): ");
            gets(agd.hrAgendado);

            sprintf(agd.dtInscrito, "%.2i/%.2i/%.4i",dt_hr_atual->tm_mday, dt_hr_atual->tm_mon+1, dt_hr_atual->tm_year+1900);
            printf("Data da inscricao: %s\n", agd.dtInscrito);
            
            sprintf(agd.hrInscrito, "%.2i:%.2i",dt_hr_atual->tm_hour, dt_hr_atual->tm_min);
            printf("Hora da inscricao: %s\n", agd.hrInscrito);

            fflush(stdin);
            printf("Area do direito: ");
            gets(agd.areaDireito);

            fflush(stdin);
            printf("Tipo de orientacao: ");
            gets(agd.tpOrientacao);

            fflush(stdin);
            printf("Possui prazo fatal? [s-sim]: ");
            scanf("%c", &pzFatal);
            strupr(&pzFatal);

            if(pzFatal == 'S'){
                sprintf(agd.temPrzFatal, "Sim");
                fflush(stdin);
                printf("Prazo fatal (dd/MM/AAAA): ");
                gets(agd.przFatal);
            } else {
                memset(agd.przFatal, '\0', sizeof(agd.przFatal));
                sprintf(agd.temPrzFatal, "Nao");
            }

            fflush(stdin);
            printf("Observacoes: ");
            gets(agd.observacoes);

            fflush(stdin);
            printf("Numero do processo (opcional): ");
            gets(agd.numProcesso);

            sprintf(agd.foiAtend, "Em espera");

            //Registrando em um arquivo os dados de entrada
            fwrite(&agd, sizeof(agd), 1, arq);

            printf("\n\nAgendamento efetuado com sucesso!\n\n");

        } else printf("OAB nao cadastrada no sistema!\n\n");

    } else printf("Codigo de estagiario nao registrado!\n\n");

    system("pause");

    remove("PLANTAO.TMP");
    fclose(arq);        

    }
}

// Atribuir estagiario
void atribuirEstagiario(){
    system("cls");

    ESTAGIARIOS estg;
    CASOSATRIB casAtb;

    arq = fopen(ARQCASOATRIB, "a");

    if(arq == NULL){
        printf("Falha ao carregar o arquivo [%s]!\n\n", ARQCASOATRIB);
        system("pause");
        fclose(arq);
        return;
    }    

    // Capturando data e hora atuais
    struct tm *dt_hr_atual;
    time_t segundos;
    time(&segundos);
    dt_hr_atual = localtime(&segundos);

    char cpf[11+1], cod[7+1];

    FILE *arqEst = fopen(ARQESTAG, "r");

    if (arqEst == NULL){
        printf("O Arquivo [ESTAGIARIOS.DAT] nao existe!\n\n");
        system("pause");
        return;
    }

    printf("---------- ESTAGIARIOS  PLANTONISTAS ----------\n");
    printf("%-20s | %-21s\n", "Codigo", "Nome");
    printf("-----------------------------------------------\n");
    while(fread(&estg, sizeof(estg), 1, arqEst)){
        if(estg.tipo == 'P'){
            printf("%-20s | %-21s\n", estg.codEstag, estg.nomeEstag);
            printf("-----------------------------------------------\n");
        }
    }

    fclose(arqEst);

    printf("\n------------- ATRIBUICAO DE CASO --------------\n");
    printf("CPF do cliente: ");
    fflush(stdin);
    gets(cpf);

    CLIENTES cli = verificarCliente(cpf);

    if(cli.cod == -1){
        printf("CPF [%s] de cliente nao cadastrado!\n\n", cpf);
        system("pause");
        return;
    }

    printf("Codigo do estagiario: ");
    fflush(stdin);
    gets(cod);

    if(verificarCodEstag(cod)==-1){
        printf("Codigo [%s] do estagiario nao cadastrado!\n\n", cod);
        system("pause");
        return;
    }

    if(verificarEstaPlantonista(cod) == false){
        printf("Estagiario cadastrado com o codigo [%s] nao e plantonista!\n\n", cod);
        system("pause");
        return;
    }

    strcpy(casAtb.cpf, cpf);
    casAtb.cdAtendimento = cli.cod;
    strcpy(casAtb.codEstag, cod);

    sprintf(casAtb.diAtribuido, "%.2i/%.2i/%.4i",dt_hr_atual->tm_mday, dt_hr_atual->tm_mon+1, dt_hr_atual->tm_year+1900);
    printf("Data da atribuicao: %s\n", casAtb.diAtribuido);
    
    sprintf(casAtb.hrAtribuido, "%.2i:%.2i",dt_hr_atual->tm_hour, dt_hr_atual->tm_min);
    printf("Hora da atribuicao: %s\n", casAtb.hrAtribuido);

    fwrite(&casAtb, sizeof(CASOSATRIB), 1, arq);

    printf("Caso atribuido com sucesso!\n\n");
    fclose(arq);
    system("pause");

}

// Exibit casos atribuidos
void exibirCasosAtribuidos(){
    arq = fopen(ARQCASOATRIB, "r");

    CASOSATRIB casAtb;

    system("cls");

    if (arq == NULL){
        printf("O Arquivo [%s] nao existe!\n\n", ARQCASOATRIB);
        system("pause");
        return;
    }

    system("cls");
    printf("%-13s | %-20s | %-25s | %-23s | %-23s\n", "CPF", "Cod. Atendimento", "Cod. Estagiario", "Dia atribuido", "Hora atribuido");
    printf("-------------------------------------------------------------------------------------------------------------\n");
    while(fread(&casAtb, sizeof(casAtb), 1, arq)){
        printf("%-13s | %-20i | %-25s | %-23s | %-23s\n", casAtb.cpf, casAtb.cdAtendimento, casAtb.codEstag, casAtb.diAtribuido, casAtb.hrAtribuido);
        printf("-------------------------------------------------------------------------------------------------------------\n");
    }    
    fclose(arq);
    system("pause");    
}

/***********************************************************************************
 *                    VALIDAR ARQUIVO DE CLIENTES - TRIAGEM
***********************************************************************************/ 
void testaArquivoCliente(){
    arq = fopen(ARQCLI, "r");

    CLIENTES cl;

    if(arq != NULL){

    while(!feof(arq)) fread(&cl, sizeof(cl), 1, arq);
    int num = cl.cod;
        if(num != NULL){
            codigo = num + 1;
            fclose(arq);
        } 
    } 
}

/***********************************************************************************
 *                    CONTROLE DE CASOS - CLIENTES/TRIAGEM
***********************************************************************************/ 
//Cadastrar um caso na triagem
void triagem(){
    
    testaArquivoCliente();

    CLIENTES cli;
    ESTAGIARIOS estg;

    system("cls");

    arq = fopen(ARQCLI, "a");

    if(arq == NULL){
        printf("Erro ao abrir arquivo [CLIENTES.DAT].\n\n");
        system("pause");
        return;
    }

    FILE *arqEst = fopen(ARQESTAG, "r");

    if (arq == NULL){
        printf("O Arquivo [ESTAGIARIOS.DAT] nao existe!\n\n");
        system("pause");
        return;
    }

    printf("---------------- ESTAGIARIOS ATENDENDO ----------------\n");
    while(fread(&estg, sizeof(estg), 1, arqEst)){
        if(estg.tipo == 'A'){
            printf("%-21s\n", estg.nomeEstag);
            printf("-------------------------------------------------------\n");
        }
    }

    fclose(arqEst);

    //Capturando data e hora atuais
    struct tm *dt_hr_atual;
    time_t segundos;
    time(&segundos);
    dt_hr_atual = localtime(&segundos);

    printf("\n\n----------------- CADASTRO DE CLIENTE -----------------\n");
    printf("Codigo: %i\n", codigo);
    cli.cod = codigo;
    fflush(stdin);
    printf("Nome do atendente: ");
    gets(cli.atendente);

    sprintf(cli.dtAtendimento, "%.2i/%.2i/%.4i",dt_hr_atual->tm_mday, dt_hr_atual->tm_mon+1, dt_hr_atual->tm_year+1900);
    printf("Data do atendimento: %s\n", cli.dtAtendimento);
    
    sprintf(cli.hrAtendimento, "%.2i:%.2i",dt_hr_atual->tm_hour, dt_hr_atual->tm_min);
    printf("Hora do atendimento: %s\n", cli.hrAtendimento);

    printf("Hora de Chegada (HH:MM): ");
    gets(cli.hrChegada);

    printf("Como conheceu: ");
    gets(cli.comoConheceu);

    printf("Pessoa Fisica ou Juridica (F/J): ");
    fflush(stdin);
    gets(cli.pessoaFisJuri);
    strupr(&cli.pessoaFisJuri);

    printf("Nome: ");
    fflush(stdin);
    gets(cli.nomeCliente);

    printf("Genero: ");
    fflush(stdin);
    gets(cli.genero);

    printf("Pertence a comunidade LGBT? (S/N): ");
    fflush(stdin);
    gets(cli.pertLGBT);
    strupr(&cli.pertLGBT);

    printf("Etnia: ");
    fflush(stdin);
    gets(cli.etnia);

    printf("Data de Nascimento (DD/MM/AAAA): ");
    fflush(stdin);
    gets(cli.dtNascimento);

    printf("Nacionalidade: ");
    fflush(stdin);
    gets(cli.nacionalidade);

    printf("Naturalidade (UF): ");
    fflush(stdin);
    gets(cli.naturalidade);
    strupr(&cli.naturalidade);

    printf("CPF: ");
    fflush(stdin);
    gets(cli.cpf);

    printf("RG: ");
    fflush(stdin);
    gets(cli.rg);

    printf("Endereco: ");
    fflush(stdin);
    gets(cli.endereco);

    printf("Celular: ");
    fflush(stdin);
    gets(cli.celular);

    printf("Usa WhatsApp? (S/N): ");
    fflush(stdin);
    gets(cli.usaWpp);
    strupr(&cli.usaWpp);

    printf("Outro Telefone: ");
    fflush(stdin);
    gets(cli.outroTel);

    printf("E-mail: ");
    fflush(stdin);
    gets(cli.email);

    printf("Escolaridade: ");
    fflush(stdin);
    gets(cli.escolaridade);

    printf("Profissao: ");
    fflush(stdin);
    gets(cli.profissao);

    printf("Situacao de emprego: ");
    fflush(stdin);
    gets(cli.situacaoEmprego);

    printf("Estado civil: ");
    fflush(stdin);
    gets(cli.estadoCivil);

    printf("Tem filhos? (S/N): ");
    fflush(stdin);
    scanf("%c", &cli.temFilhos);
    strupr(&cli.temFilhos);
    
    if(cli.temFilhos == 'S'){
        printf("Quantos filhos moram na casa: ");
        fflush(stdin);
        scanf("%i", &cli.filhosMorando);
    } else cli.filhosMorando = 0;

    printf("Total de Pessoas na Familia: ");
    fflush(stdin);
    scanf("%i", &cli.totalPessoasFam);

    printf("Possui beneficio Social? (S/N): ");
    fflush(stdin);
    scanf("%c", &cli.beneficioSocial);
    strupr(&cli.beneficioSocial);

    if(cli.beneficioSocial == 'S'){
        printf("Valor do beneficio: ");
        fflush(stdin);
        scanf("%f", &cli.valBeneficio);
    } else cli.valBeneficio = 0;

    printf("Renda mensal individual do cliente: ");
    fflush(stdin);
    scanf("%f", &cli.rendaMes);

    printf("Renda Total (outros familiares): ");
    fflush(stdin);
    scanf("%f", &cli.rendTotal);

    printf("Possui gasto medico? (S/N): ");
    fflush(stdin);
    scanf("%c", &cli.gastoMedico);
    strupr(&cli.gastoMedico);

    if(cli.gastoMedico == 'S'){
        printf("Valor com gasto medico: ");
        fflush(stdin);
        scanf("%f", &cli.valGastoMedico);
    } else cli.valGastoMedico = 0;

    printf("Possui investimento Financeiro? (S/N): ");
    fflush(stdin);
    scanf("%c", &cli.investimentoFinanc);
    strupr(&cli.investimentoFinanc);

    if(cli.investimentoFinanc == 'S'){
        printf("Valor do Investimento Financeiro: ");
        fflush(stdin);
        scanf("%f", &cli.valInvestFinanceiro);
    } else cli.valInvestFinanceiro = 0;

    printf("Tem casa? (S/N): ");
    fflush(stdin);
    scanf("%c", &cli.temCasa);
    strupr(&cli.temCasa);

    if(cli.temCasa == 'S'){
        printf("Valor da Casa: ");
        fflush(stdin);
        scanf("%f", &cli.valCasa);
    } else cli.valCasa = 0;

    printf("Tem Apartamento? (S/N): ");
    fflush(stdin);
    scanf("%c", &cli.temApto);
    strupr(&cli.temApto);

    if(cli.temApto == 'S'){
        printf("Valor do apartamento: ");
        fflush(stdin);
        scanf("%f", &cli.valApto);
    } else cli.valApto = 0;

    printf("Tem Terreno? (S/N): ");
    fflush(stdin);
    scanf("%c", &cli.temTerreno);
    strupr(&cli.temTerreno);

    if(cli.temTerreno == 'S'){
        printf("Valor do terreno: ");
        fflush(stdin);
        scanf("%f", &cli.valTerreno);
    } else cli.valTerreno = 0;

    printf("Tem imovel comercial? (S/N): ");
    fflush(stdin);
    scanf("%c", &cli.temImovelComerc);
    strupr(&cli.temImovelComerc);

    if(cli.temImovelComerc == 'S'){
        printf("Valor do imovel comercial: ");
        fflush(stdin);
        scanf("%f", &cli.valImovelComerc);
    } else cli.valImovelComerc = 0;    

    printf("Tem Carro? (S/N): ");
    fflush(stdin);
    scanf("%c", &cli.temCarro);
    strupr(&cli.temCarro);

    if(cli.temCarro == 'S'){
        printf("Valor do carro: ");
        fflush(stdin);
        scanf("%f", &cli.valCarro);
    } else cli.valCarro = 0;        

    printf("Violencia domestica? (S/N): ");
    fflush(stdin);
    scanf("%c", &cli.violenciaDomestica);
    strupr(&cli.violenciaDomestica);

    printf("Resumo do Caso: ");
    fflush(stdin);
    gets(cli.resumoCaso);

    printf("Ramo do Direito: ");
    fflush(stdin);
    gets(cli.ramoDireito);

    int controle=-1;

    float renda = cli.rendaMes + cli.rendTotal;

    float tresSalarios = 3 * SALARIO_MINIMO;
    if(renda <= tresSalarios){
        cli.temPerfilAssist = 'S';
        controle = 1;
    }

    float quatroSalarios = 4 * SALARIO_MINIMO;
    if(renda <= quatroSalarios && (cli.totalPessoasFam > 5 || cli.valGastoMedico > 0)){
        cli.temPerfilAssist = 'S';
        controle = 1;
    }

    if(controle == -1)
        cli.temPerfilAssist = 'N';

    printf("\nCadastro de cliente realizado com sucesso!\n\n");

    system("pause");

    fwrite(&cli, sizeof(cli), 1, arq);

    fclose(arq);
}

// Exibir casos
void exibirClientes(){
    system("cls");

    CLIENTES cliente;

    int opc=-1, controle = -1;
    char cpfCliente[11+1];

    FILE *arquivo = fopen(ARQCLI, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo [CLIENTES.DAT].\n\n");
        system("pause");
        return;
    } else {

        printf("------------ EXIBIR CLIENTES -------------\n");
        printf("          1 - Pesquisar CPF                  \n");
        printf("          2 - Pesquisa geral                 \n");
        printf("------------------------------------------\n");
        printf("    Selecione uma opcao: ");
        scanf("%i", &opc);

        if(opc == 1){
            system("cls");
            printf("Informe o CPF do cliente: ");
            fflush(stdin);
            gets(cpfCliente);
            system("cls");
            while(fread(&cliente, sizeof(CLIENTES), 1, arquivo)){
                if(strcmp(cliente.cpf, cpfCliente) == 0){
                    printf("------------- CLIENTE CADASTRADO --------------\n");
                    printf("Codigo: %i\n", cliente.cod);
                    printf("Data de Atendimento: %s\n", cliente.dtAtendimento);
                    printf("Hora de Atendimento: %s\n", cliente.hrAtendimento);
                    printf("Hora de Chegada: %s\n", cliente.hrChegada);
                    printf("Como conheceu: %s\n", cliente.comoConheceu);
                    printf("Atendente: %s\n", cliente.atendente);
                    printf("Pessoa Fisica ou Juridica: %s\n", cliente.pessoaFisJuri);
                    printf("Nome do Cliente: %s\n", cliente.nomeCliente);
                    printf("Genero: %s\n", cliente.genero);
                    printf("Pertence a comunidade LGBT: %s\n", cliente.pertLGBT);
                    printf("Etnia: %s\n", cliente.etnia);
                    printf("Data de Nascimento: %s\n", cliente.dtNascimento);
                    printf("Nacionalidade: %s\n", cliente.nacionalidade);
                    printf("Naturalidade (UF): %s\n", cliente.naturalidade);
                    printf("CPF: %s\n", cliente.cpf);
                    printf("RG: %s\n", cliente.rg);
                    printf("Endereco: %s\n", cliente.endereco);
                    printf("Celular: %s\n", cliente.celular);
                    printf("Usa WhatsApp: %s\n", cliente.usaWpp);
                    printf("Outro Telefone: %s\n", cliente.outroTel);
                    printf("Email: %s\n", cliente.email);
                    printf("Escolaridade: %s\n", cliente.escolaridade);
                    printf("Profissao: %s\n", cliente.profissao);
                    printf("Situacao de Emprego: %s\n", cliente.situacaoEmprego);
                    printf("Estado Civil: %s\n", cliente.estadoCivil);
                    printf("Tem filhos: %c\n", cliente.temFilhos);
                    printf("Filhos morando: %d\n", cliente.filhosMorando);
                    printf("Total de Pessoas na Familia: %d\n", cliente.totalPessoasFam);
                    printf("Possui beneficio social: %c\n", cliente.beneficioSocial);
                    printf("Valor do Beneficio: %.2f\n", cliente.valBeneficio);
                    printf("Renda mensal individual: %.2f\n", cliente.rendaMes);
                    printf("Renda total (outros familiares): %.2f\n", cliente.rendTotal);
                    printf("Gasto Medico: %c\n", cliente.gastoMedico);
                    printf("Valor do Gasto Medico: %.2f\n", cliente.valGastoMedico);
                    printf("Possui investimento financeiro: %c\n", cliente.investimentoFinanc);
                    printf("Valor do Investimento Financeiro: %.2f\n", cliente.valInvestFinanceiro);
                    printf("Tem Casa: %c\n", cliente.temCasa);
                    printf("Valor da Casa: %.2f\n", cliente.valCasa);
                    printf("Tem Apartamento: %c\n", cliente.temApto);
                    printf("Valor do Apartamento: %.2f\n", cliente.valApto);
                    printf("Tem Terreno: %c\n", cliente.temTerreno);
                    printf("Valor do Terreno: %.2f\n", cliente.valTerreno);
                    printf("Tem Imovel Comercial: %c\n", cliente.temImovelComerc);
                    printf("Valor do Imovel Comercial: %.2f\n", cliente.valImovelComerc);
                    printf("Tem Carro: %c\n", cliente.temCarro);
                    printf("Valor do Carro: %.2f\n", cliente.valCarro);
                    printf("Violencia Domestica: %c\n", cliente.violenciaDomestica);
                    printf("Resumo do Caso: %s\n", cliente.resumoCaso);
                    printf("Ramo do Direito: %s\n", cliente.ramoDireito);
                    printf("Tem Perfil Assistencial: %c\n", cliente.temPerfilAssist);
                    printf("-------------------------------------------------\n\n");
                    controle = 1;
                    break;
                }
            }

            if(controle == -1)
                printf("\nCPF [%s] informado nao consta nos registros!\n\n", cpfCliente);
            system("pause");
            return;
        }

        if(op == 2){
            system("cls");
            // Criação do arquivo temporário
            FILE *tempFile = fopen("CLIENTES.TMP", "w");
            if (tempFile == NULL) {
                printf("Erro ao criar arquivo temporário.\n\n");
                fclose(arquivo);
                system("pause");
                return;
            }

            fprintf(tempFile, "--------------------------- CLIENTES CADASTRADOS ---------------------------\n");

            while (fread(&cliente, sizeof(CLIENTES), 1, arquivo)) {
                fprintf(tempFile, "Código: %i\n", cliente.cod);
                fprintf(tempFile, "Data de Atendimento: %s\n", cliente.dtAtendimento);
                fprintf(tempFile, "Hora de Atendimento: %s\n", cliente.hrAtendimento);
                fprintf(tempFile, "Hora de Chegada: %s\n", cliente.hrChegada);
                fprintf(tempFile, "Como conheceu: %s\n", cliente.comoConheceu);
                fprintf(tempFile, "Atendente: %s\n", cliente.atendente);
                fprintf(tempFile, "Pessoa Física ou Jurídica: %s\n", cliente.pessoaFisJuri);
                fprintf(tempFile, "Nome do Cliente: %s\n", cliente.nomeCliente);
                fprintf(tempFile, "Gênero: %s\n", cliente.genero);
                fprintf(tempFile, "Pertence à comunidade LGBT: %s\n", cliente.pertLGBT);
                fprintf(tempFile, "Etnia: %s\n", cliente.etnia);
                fprintf(tempFile, "Data de Nascimento: %s\n", cliente.dtNascimento);
                fprintf(tempFile, "Nacionalidade: %s\n", cliente.nacionalidade);
                fprintf(tempFile, "Naturalidade (UF): %s\n", cliente.naturalidade);
                fprintf(tempFile, "CPF: %s\n", cliente.cpf);
                fprintf(tempFile, "RG: %s\n", cliente.rg);
                fprintf(tempFile, "Endereço: %s\n", cliente.endereco);
                fprintf(tempFile, "Celular: %s\n", cliente.celular);
                fprintf(tempFile, "Usa WhatsApp: %s\n", cliente.usaWpp);
                fprintf(tempFile, "Outro Telefone: %s\n", cliente.outroTel);
                fprintf(tempFile, "Email: %s\n", cliente.email);
                fprintf(tempFile, "Escolaridade: %s\n", cliente.escolaridade);
                fprintf(tempFile, "Profissão: %s\n", cliente.profissao);
                fprintf(tempFile, "Situação de Emprego: %s\n", cliente.situacaoEmprego);
                fprintf(tempFile, "Estado Civil: %s\n", cliente.estadoCivil);
                fprintf(tempFile, "Tem filhos: %c\n", cliente.temFilhos);
                fprintf(tempFile, "Filhos morando: %d\n", cliente.filhosMorando);
                fprintf(tempFile, "Total de Pessoas na Família: %d\n", cliente.totalPessoasFam);
                fprintf(tempFile, "Possui benefício social: %c\n", cliente.beneficioSocial);
                fprintf(tempFile, "Valor do Benefício: %.2f\n", cliente.valBeneficio);
                fprintf(tempFile, "Renda mensal individual: %.2f\n", cliente.rendaMes);
                fprintf(tempFile, "Renda total (outros familiares): %.2f\n", cliente.rendTotal);
                fprintf(tempFile, "Gasto Médico: %c\n", cliente.gastoMedico);
                fprintf(tempFile, "Valor do Gasto Médico: %.2f\n", cliente.valGastoMedico);
                fprintf(tempFile, "Possui investimento financeiro: %c\n", cliente.investimentoFinanc);
                fprintf(tempFile, "Valor do Investimento Financeiro: %.2f\n", cliente.valInvestFinanceiro);
                fprintf(tempFile, "Tem Casa: %c\n", cliente.temCasa);
                fprintf(tempFile, "Valor da Casa: %.2f\n", cliente.valCasa);
                fprintf(tempFile, "Tem Apartamento: %c\n", cliente.temApto);
                fprintf(tempFile, "Valor do Apartamento: %.2f\n", cliente.valApto);
                fprintf(tempFile, "Tem Terreno: %c\n", cliente.temTerreno);
                fprintf(tempFile, "Valor do Terreno: %.2f\n", cliente.valTerreno);
                fprintf(tempFile, "Tem Imóvel Comercial: %c\n", cliente.temImovelComerc);
                fprintf(tempFile, "Valor do Imóvel Comercial: %.2f\n", cliente.valImovelComerc);
                fprintf(tempFile, "Tem Carro: %c\n", cliente.temCarro);
                fprintf(tempFile, "Valor do Carro: %.2f\n", cliente.valCarro);
                fprintf(tempFile, "Violência Doméstica: %c\n", cliente.violenciaDomestica);
                fprintf(tempFile, "Resumo do Caso: %s\n", cliente.resumoCaso);
                fprintf(tempFile, "Ramo do Direito: %s\n", cliente.ramoDireito);
                fprintf(tempFile, "Tem Perfil Assistencial: %c\n", cliente.temPerfilAssist);
                fprintf(tempFile, "----------------------------------------------------------------------------\n");
                fprintf(tempFile, "----------------------------------------------------------------------------\n");
            }

            fclose(arquivo);
            fclose(tempFile);

            system("start CLIENTES.TMP");
            system("pause");
            remove("CLIENTES.TMP");
        }
    }
}

/***********************************************************************************
 *                            CONTROLE PUBLICAÇÃO
***********************************************************************************/ 
// Cadastrar publicação
void adicionarPublicacao(){

    system("cls");
    PUBLICACAO pub;
    FILE *arquivo = fopen(ARQPUBLI, "a");

    // Capturando data e hora atuais
    struct tm *dt_hr_atual;
    time_t segundos;
    time(&segundos);
    dt_hr_atual = localtime(&segundos);

    printf("Codigo do Estagiario: ");
    fflush(stdin);
    gets(pub.codEstag);

    if(verificarCodEstag(pub.codEstag)==-1){
        printf("Estagiario nao cadastrado!\n\n");
        system("pause");
        return;
    }

    sprintf(pub.dtCircula, "%.2i/%.2i/%.4i", dt_hr_atual->tm_mday, dt_hr_atual->tm_mon+1, dt_hr_atual->tm_year+1900);
    printf("Data da Circulacao: %s\n", pub.dtCircula);

    sprintf(pub.hrCircula, "%.2i:%.2i",dt_hr_atual->tm_hour, dt_hr_atual->tm_min);
    printf("Hora do Circulacao: %s\n", pub.hrCircula);

    printf("Numero processo (cnj): ");
    fflush(stdin);
    gets(pub.numcnj);

    printf("Tipo de Acao: ");
    fflush(stdin);
    gets(pub.tipoAcao);

    printf("Vara/Juizo: ");
    fflush(stdin);
    gets(pub.varaJuizo);

    printf("Foro: ");
    fflush(stdin);
    gets(pub.foro);

    printf("CPF: ");
    fflush(stdin);
    gets(pub.cpf);

    if(validaCpfCli(pub.cpf)==false){
        printf("CPF do cliente nao encontrado na base de dados!\n\n");
        system("pause");
        return;
    }

    printf("Reclamado: ");
    fflush(stdin);
    gets(pub.reclamado);

    printf("Advogado do Reclamante: ");
    fflush(stdin);
    gets(pub.advReclamante);

    printf("Advogado do Reclamado: ");
    fflush(stdin);
    gets(pub.advReclamado);

    printf("Movimentacao: ");
    fflush(stdin);
    gets(pub.movimentacao);

    fwrite(&pub, sizeof(PUBLICACAO), 1, arquivo);

    printf("\nPublicacao cadastrada com sucesso!\n\n");

    fclose(arquivo); 
    system("pause");

}

// Exibir publicacoes
void exibirPublicacoes(){
    system("cls");

    FILE *arquivo = fopen(ARQPUBLI, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo [PUBLICACOES.DAT].\n\n");
        system("pause");
        return;
    }

    PUBLICACAO pub;
    
    printf("------------ PUBLICACOES REGISTRADAS ------------\n");
    while (fread(&pub, sizeof(PUBLICACAO), 1, arquivo)) {
        printf("Codigo do Estagiario: %s\n", pub.codEstag);
        printf("Data da Circulacao: %s\n", pub.dtCircula);
        printf("Hora da Circulacao: %s\n", pub.hrCircula);
        printf("Numero CNJ: %s\n", pub.numcnj);
        printf("Tipo de Acao: %s\n", pub.tipoAcao);
        printf("Vara/Juizo: %s\n", pub.varaJuizo);
        printf("Foro: %s\n", pub.foro);
        printf("CPF: %s\n", pub.cpf);
        printf("Reclamado: %s\n", pub.reclamado);
        printf("Advogado do Reclamante: %s\n", pub.advReclamante);
        printf("Advogado do Reclamado: %s\n", pub.advReclamado);
        printf("Movimentacao: %s\n", pub.movimentacao);
        printf("------------------------------------------------\n\n");
    }

    fclose(arquivo);
    system("pause");
}

/***********************************************************************************
 *                            FUNÇÕES DO CONTROLE.DAT
***********************************************************************************/ 
// Cadastro de processo
void cadastrarProcesso(){

    // Capturando data e hora atuais
    struct tm *dt_hr_atual;
    time_t segundos;
    time(&segundos);
    dt_hr_atual = localtime(&segundos);

    CONTROLE controle;
    
    FILE *arquivo = fopen(ARQCTRL, "a");

    char przDobro;

    system("cls");

    printf("---------------- CADASTRO DE CONTROLE ----------------\n");

    fflush(stdin);
    printf("Numero do Processo: ");
    gets(controle.numProcesso);

    fflush(stdin);
    printf("Tema: ");
    gets(controle.tema);

    fflush(stdin);
    printf("CPF: ");
    gets(controle.cpf);

    if(validaCpfCli(controle.cpf) == false){
        printf("CPF nao encontrado nos registros de casos!\n\n");
        system("pause");
        return;
    }

    fflush(stdin);
    printf("Polo: ");
    gets(controle.polo);

    fflush(stdin);
    printf("Codigo do Estagiario: ");
    gets(controle.codeEstag);

    if(verificarCodEstag(controle.codeEstag) == -1){
        printf("Estagiario nao cadastrado!\n");
        system("pause");
        return;
    }

    fflush(stdin);
    sprintf(controle.dtControle, "%.2i/%.2i/%.4i", dt_hr_atual->tm_mday, dt_hr_atual->tm_mon+1, dt_hr_atual->tm_year+1900);
    printf("Data do controle: %s\n", controle.dtControle);

    fflush(stdin);
    printf("Proxima Tarefa: ");
    gets(controle.proxTarefa);

    fflush(stdin);
    printf("Prazo em Dobro (S/N): ");
    scanf("%c", &przDobro);
    strupr(&przDobro);

    strcpy(controle.temPrazoDobro, "Nao");
    if(przDobro == 'S')
        strcpy(controle.temPrazoDobro, "Sim");
    
    fflush(stdin);
    printf("Observacao do Prazo: ");
    gets(controle.obsPrazo);

    fflush(stdin);
    printf("Audiencia: ");
    gets(controle.audiencia);

    fflush(stdin);
    printf("Prazo Simples (DD/MM/AAAA): ");
    gets(controle.prazoSimples);

    fflush(stdin);
    printf("Prazo Dobrado (DD/MM/AAAA): ");
    gets(controle.prazoDobrado);

    fflush(stdin);
    printf("Movimentacao: ");
    gets(controle.movimentacao);

    fflush(stdin);
    printf("Dias para o Proximo Controle: ");
    scanf("%d", &controle.diasProxControle);
    fflush(stdin);

    fflush(stdin);
    printf("Data da Proposicao (DD/MM/AAAA): ");
    gets(controle.dtProposicao);

    fwrite(&controle, sizeof(CONTROLE), 1, arquivo);

    fclose(arquivo);

    printf("\nCadastro realizado com sucesso!\n\n");
    system("pause");

}

// Atualizar processo
void atualizarProcesso(char numPro[25+1]){
    
    // Capturando data e hora atuais
    struct tm *dt_hr_atual;
    time_t segundos;
    time(&segundos);
    dt_hr_atual = localtime(&segundos);

    int encontrado=0,  op;
    char motivo[200];

    FILE *arqCtrl = fopen(ARQCTRL, "rb+");

    if(arqCtrl == NULL){
        printf("Erro ao abrir o arquivo [CONTROLE.DAT]");
        return;
    }

    system("cls");

    printf("------------ PROX. TAREFA - ATUALIZAR PROCESSO -------------\n");
    printf("            1 - Peticionar                                  \n");
    printf("            2 - Acompanhar                                  \n");
    printf("            3 - Renuncia                                    \n");
    printf("            4 - Encerrar atendimento                        \n");
    printf("            5 - Audiencia                                   \n");
    printf("            6 - Diligencia                                  \n");
    printf("            7 - Transferir                                  \n");
    printf("------------------------------------------------------------\n");
    printf("    Selecione uma opcao: ");
    scanf("%d", &op);

    CONTROLE cont = verificarProcesso(numPro);

    if(op == 1){
        strncpy(cont.proxTarefa, "Peticionar", sizeof(cont.proxTarefa) - 1);
        cont.proxTarefa[sizeof(cont.proxTarefa) - 1] = '\0';
        sprintf(cont.dtControle, "%.2i/%.2i/%.4i", dt_hr_atual->tm_mday, dt_hr_atual->tm_mon+1, dt_hr_atual->tm_year+1900);
        sprintf(cont.movimentacao,"%s\n(%s) %s", cont.movimentacao, cont.dtControle,"Peticionar; estagiario ciente"); 
    }

    if(op == 2){
        strncpy(cont.proxTarefa, "Acompanhar", sizeof(cont.proxTarefa) - 1);
        cont.proxTarefa[sizeof(cont.proxTarefa) - 1] = '\0';
        sprintf(cont.dtControle, "%.2i/%.2i/%.4i", dt_hr_atual->tm_mday, dt_hr_atual->tm_mon+1, dt_hr_atual->tm_year+1900);
        sprintf(cont.movimentacao,"%s\n(%s) %s", cont.movimentacao, cont.dtControle,"Acompanhamento; estagiario ciente");  
    }

    if(op == 3){
        strncpy(cont.proxTarefa, "Renuncia", sizeof(cont.proxTarefa) - 1);
        cont.proxTarefa[sizeof(cont.proxTarefa) - 1] = '\0';
        sprintf(cont.dtControle, "%.2i/%.2i/%.4i", dt_hr_atual->tm_mday, dt_hr_atual->tm_mon+1, dt_hr_atual->tm_year+1900);
        sprintf(cont.movimentacao,"%s\n(%s) %s", cont.movimentacao, cont.dtControle,"Renuncia; estagiario ciente");  
    }

    if(op == 4){
        strncpy(cont.proxTarefa, "Encerrar atendimento", sizeof(cont.proxTarefa) - 1);
        cont.proxTarefa[sizeof(cont.proxTarefa) - 1] = '\0'; 
        system("cls");
        printf("Motivo do encerramento: ");
        fflush(stdin);
        gets(motivo);
        sprintf(cont.dtControle, "%.2i/%.2i/%.4i", dt_hr_atual->tm_mday, dt_hr_atual->tm_mon+1, dt_hr_atual->tm_year+1900);
        sprintf(cont.movimentacao,"%s\n(%s) %s; estagiario ciente", cont.movimentacao, cont.dtControle,motivo);
    }

    if(op == 5){
        strncpy(cont.proxTarefa, "Audiencia", sizeof(cont.proxTarefa) - 1);
        cont.proxTarefa[sizeof(cont.proxTarefa) - 1] = '\0';
        sprintf(cont.dtControle, "%.2i/%.2i/%.4i", dt_hr_atual->tm_mday, dt_hr_atual->tm_mon+1, dt_hr_atual->tm_year+1900);
        sprintf(cont.movimentacao,"%s\n(%s) %s", cont.movimentacao, cont.dtControle,"Audiencia; estagiario ciente"); 
    }

    if(op == 6){
        strncpy(cont.proxTarefa, "Diligencia", sizeof(cont.proxTarefa) - 1);
        cont.proxTarefa[sizeof(cont.proxTarefa) - 1] = '\0';
        sprintf(cont.dtControle, "%.2i/%.2i/%.4i", dt_hr_atual->tm_mday, dt_hr_atual->tm_mon+1, dt_hr_atual->tm_year+1900);
        sprintf(cont.movimentacao,"%s\n(%s) %s", cont.movimentacao, cont.dtControle,"Diligencia; estagiario ciente");  
    }

    if(op == 7){
        strncpy(cont.proxTarefa, "Transferir", sizeof(cont.proxTarefa) - 1);
        cont.proxTarefa[sizeof(cont.proxTarefa) - 1] = '\0';
        sprintf(cont.dtControle, "%.2i/%.2i/%.4i", dt_hr_atual->tm_mday, dt_hr_atual->tm_mon+1, dt_hr_atual->tm_year+1900);
        sprintf(cont.movimentacao,"%s\n(%s) %s", cont.movimentacao, cont.dtControle,"Transferencia; estagiario ciente");  
    }

    fseek(arqCtrl, -(long) sizeof(CONTROLE), SEEK_CUR);
    fwrite(&cont, sizeof(CONTROLE), 1, arqCtrl);

    fclose(arqCtrl);
    system("cls");
    printf("Processo atualizado com sucesso!\n\n");
    system("pause");
}

// Exibis processos
void exibirProcessos(){
    CONTROLE controle;
    FILE *arquivo = fopen(ARQCTRL, "r");
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo [CONTROLE.DAT].\n\n");
        return;
    }

    system("cls");

    printf("---------------- PROCESSOS EM ANDAMENTO -----------------\n");

    while (fread(&controle, sizeof(CONTROLE), 1, arquivo)) {
        printf("Numero do Processo: %s\n", controle.numProcesso);
        printf("Tema: %s\n", controle.tema);
        printf("CPF: %s\n", controle.cpf);
        printf("Polo: %s\n", controle.polo);
        printf("Codigo do Estagiario: %s\n", controle.codeEstag);
        printf("Data do Controle: %s\n", controle.dtControle);
        printf("Proxima Tarefa: %s\n", controle.proxTarefa);
        printf("Prazo em Dobro: %s\n", controle.temPrazoDobro);
        printf("Observacao do Prazo: %s\n", controle.obsPrazo);
        printf("Audiencia: %s\n", controle.audiencia);
        printf("Prazo Simples: %s\n", controle.prazoSimples);
        printf("Prazo Dobrado: %s\n", controle.prazoDobrado);
        printf("Movimentacao: %s\n", controle.movimentacao);
        printf("Dias para o Proximo Controle: %d\n", controle.diasProxControle);
        printf("Data da Proposicao: %s\n", controle.dtProposicao);
        printf("--------------------------------------------------------\n");
    }

    fclose(arquivo);
    system("pause");
}

// Menu de controle
void menuControle(){
    int opc=-1;
    char numPro[25+1];

    system("cls");

    printf("------------ GERENCIAR CONTROLE -------------\n");
    printf("          1 - Adicionar processo             \n");
    printf("          2 - Atualizar processo             \n");
    printf("          3 - Ver processos                  \n");
    printf("          4 - Ver publicacoes                \n");
    printf("          0 - Voltar                         \n");
    printf("---------------------------------------------\n");
    printf("    Selecione uma opcao: ");
    scanf("%i", &opc);

    if(opc == 1)
        cadastrarProcesso();
    
    if(opc == 2){
        system("cls");
        printf("Digite o numero do processo: ");
        fflush(stdin);
        gets(numPro);

        if(verificaNumProcesso(numPro) == false){
            printf("Processo nao encontrado!\n\n");
            system("pause");
            return;
        }

        if(verificaProcessoPub(numPro)==false){
            printf("O processo nao recebeu nenhuma publicacao!\n\n");
            system("pause");
            return;
        }

        atualizarProcesso(numPro);
    }

    if(opc == 3)
        exibirProcessos();  

    if(opc == 4)
        exibirPublicacoes();

    return;
}

/***********************************************************************************
 *                            MENU PRINCIPAL DO SISTEMA
***********************************************************************************/ 
void menuPrincipal(){
    setlocale (LC_ALL, "Portuguese"); 
    while (op != 0)
    {
        system("cls");
        printf("------------ DEPARTAMENTO JUDICIARIO -------------\n");
        printf("           1 -  Triagem                           \n");
        printf("           2 -  Exibir clientes                   \n");
        printf("           3 -  Acompanhamento de casos           \n");
        printf("           4 -  Adicionar publicacao              \n");
        printf("           5 -  Adicionar advogado                \n");
        printf("           6 -  Exibir advogado                   \n");
        printf("           7 -  Adicionar disponibilidade         \n");
        printf("           8 -  Atender estagiario                \n");
        printf("           9 -  Adicionar estagiario              \n");
        printf("          10 -  Exibir estagiario                 \n");
        printf("          11 -  Agendar atendimento com advogado  \n");
        printf("          12 -  Atribuir estagiario               \n");
        printf("          13 -  Exibir agendamentos               \n");
        printf("          14 -  Exibir casos atribuidos           \n");
        printf("           0 -  Sair                              \n");
        printf("--------------------------------------------------\n");
        printf("        Selecione a opcao desejada: ");
        fflush(stdin);
        scanf("%d", &op);

        switch (op) {
            case  1: triagem(); break; // Triagem de clientes
            case  2: exibirClientes(); break; // Exibe os clientes cadastrados em CLIENTES.DAT
            case  3: menuControle(); break; // Opções para o CONTROLE.DAT e exibe o PUBLICACOES.DAT
            case  4: adicionarPublicacao(); break; // Acrescenta uma publicação no arquivo de publicações
            case  5: cadastrarAdvogado(); break; // Adicionar advogados
            case  6: consultarAdvogados(); break; // Exibir advogados
            case  7: adicionarDisponibilidade(); break; // Registrar disponibilidade - advogado
            case  8: atenderEstag(); break; // Atender fila de estagiarios 
            case  9: cadastrarEstagiario(); break; // Adicionar estagiario
            case 10: consultarEstagiario(); break; // Exibir estagiarios
            case 11: agendarAtend(); break; // Agenda atendimento com advogado
            case 12: atribuirEstagiario(); break; // Atribuir caso ao estagiario
            case 13: consultarAgendamentos(); break; // Atender estagiario 
            case 14: exibirCasosAtribuidos(); break; // Mostrar casos atribuidos
            case  0: exit(0); break; // Fechar o programa
            default: erro(); break; // Opção escolhida inválida
        }   
    } 
}

/***********************************************************************************
 *                                  MÉTODO MAIN
***********************************************************************************/ 
//Menu inicial
int main(){
    inicializarFila(&fl);
    menuPrincipal();
    return 0;
}
