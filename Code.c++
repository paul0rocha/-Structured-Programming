#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct info_cliente
{
    char sigla;
    char local_ret[20];
    int reg_cli;

    int dia_ret;
    int mes_ret;
    int ano_ret;

    int dia_dev;
    int mes_dev;
    int ano_dev;
    char local_dev[20];
};

typedef struct vip
{
    int reg_cli;
    char nome[80];
    char CPF[15];
    char tipo;
} vip;

struct info_carro
{
    char sigla;
    char local_ret[20];
};

union estado
{

    struct info_carro car;
    struct info_cliente dados;
    struct vip base;
};

typedef struct carro
{
    int reg_car;
    char modelo[20];
    char tipo;
    float diaria;
    char categoria;
    int num;
    union estado status;

} carro;

typedef struct struct_cliente
{
    int reg_cli;
    char nome[20];
    char CPF[15];
    char sigla;
    int reg_car;
    char tipo;

    union estado status;
} struct_cliente;

void aloca_carro(carro **p, int tam);
void aloca_struct_cliente(struct_cliente **p, int tam);
void aloca_vip(vip **vp, int tam);

void cadastro_carro(carro *ph);
void cadastro_struct_cliente(struct_cliente *ph, carro *pcc);
void cadastro_struct_parcial(struct_cliente *ph, carro *pcc);
void devolucao_carro(carro *pcc, struct_cliente *ph, vip *vp);

void busca_cadastro_carro(carro *ph, int reg_car);
int  busca_registro_carro(carro *p, int num_reg);
int  busca_tipo_local_modelo_status(carro *ph, char tipo_carro, char local_retirada[20], char modelo_carro[20]);
int  busca_cpf(struct_cliente *ph, char num_cpf[15]);

void grava_cadastro_carro(carro *ph);
void grava_struct_cliente(struct_cliente *ph);
void grava_vip(carro *vp);
void grava_cadastro_carro_refresh(carro *p, char *str, int pos);
void mostra_parcial(carro *pcc, struct_cliente *ph);
void mostra_total(carro *ph, int n_status_carro);
void mostra_clientes(struct_cliente *ph);

void busca_cadastro_carro(carro *ph, int reg_car);
int  verificar_struct_cliente();
void delay(int milliseconds);

main()
{

    int op;

    carro *initializer_carro = NULL;
    aloca_carro(&initializer_carro, 1);

    struct_cliente *initializer_cliente = NULL;
    aloca_struct_cliente(&initializer_cliente, 1);

    vip *initializer_vip = NULL;
    aloca_vip(&initializer_vip, 1);

    do
    {

        system("cls");
        printf(" \n [1] Cadastro carro  \n [2] View Carros  \n [3] Consulta Parcial  - [ Alugar ou Reservar]  \n [4] Consulta Total    - [ Alugar ou Reservar ] \n [5] Devolucao \n [6] Cliente View  ");
        scanf("%i", &op);
        fflush(stdin);

        switch (op)
        {
        case 1:
            cadastro_carro(initializer_carro);
            system("pause");
            break;

        case 2:
            mostra_total(initializer_carro, 0);
            system("pause");
            break;

        case 3:
            mostra_parcial(initializer_carro, 0);
            system("pause");
            break;

        case 4:
            verificar_struct_cliente();
            cadastro_struct_cliente(initializer_cliente, initializer_carro);
            system("pause");
            break;

        case 5:
            verificar_struct_cliente();
            devolucao_carro(initializer_cliente, initializer_carro, initializer_vip);
            system("pause");
            break;


        case 6:
            verificar_struct_cliente();
            mostra_clientes(initializer_cliente);
            system("pause");
            break;

        }

    } while (op != 5);

    system("pause");
}

void aloca_carro(carro **p, int tam)
{
    if ((*p = (carro *)realloc(*p, tam * sizeof(carro))) == NULL)
        exit(1);
}

void aloca_struct_cliente(struct_cliente **p, int tam)
{
    if ((*p = (struct_cliente *)realloc(*p, tam * sizeof(struct_cliente))) == NULL)
        exit(1);
}

void aloca_vip(vip **p, int tam)
{
    if ((*p = (vip *)realloc(*p, tam * sizeof(vip))) == NULL)
        exit(1);
}

void cadastro_carro(carro *pcc)
{

    int qc, aux_carro;

    qc = verificar_cadastro_carro();

    system("cls");

    pcc->reg_car = ++qc;

    printf("\n Registro: %i\n", pcc->reg_car);

    printf("\n Modelo do carro: ");
    gets(pcc->modelo);
    fflush(stdin);

    printf("\n Tipo [P - M - G]: ");
    scanf("%c", &pcc->tipo);

    printf("\n Valor da Diaria: ");
    scanf("%f", &pcc->diaria);
    fflush(stdin);
    printf("\n");

    printf("\n Local da Retirada: ");
    gets(pcc->status.car.local_ret);
    fflush(stdin);

    pcc->status.car.sigla = 'L';

    grava_cadastro_carro(pcc);
}

void cadastro_struct_cliente(struct_cliente *ph, carro *pcc)
{

    int var_verifica_cliente, aux_carro, var_mostra_carro;

    int op;

    char num_cpf [15];

    int num_reg, pos, Fcadastro_cliente;

    do
    {
        carro *initializer_carro = NULL;
        aloca_carro(&initializer_carro, 1);

        var_verifica_cliente = verificar_struct_cliente();

        var_mostra_carro =  mostra_total_livres(initializer_carro, 0);

        printf("\n");

        if (Fcadastro_cliente = fopen("carro.bin", "rb+") == NULL)
        {
            printf("\n Arquivo carro sem cadastros");
            delay(1000);

        }
        else

        {

            printf("\n Qual registro do carro ?   ");
            scanf("%i", &num_reg);
            fflush(stdin);

            pos = busca_registro_carro(pcc, num_reg);

            printf("\n");

            printf("\n Deseja alugar ou reservar o carro ?\n  \n [1] Alugar  \n [2] Reservar  ");
            scanf("%i", &op);
            fflush(stdin);

            switch (op)

            {
            case 1:

                ph->reg_cli = ++var_verifica_cliente;


                printf("\n Qual o CPF do cliente? ");
                gets(&num_cpf);
                fflush(stdin);
                pos = busca_cpf(ph, num_cpf);

                if(strcmp(num_cpf,ph->CPF) & pcc->status.car.sigla == 'A')
                {
                    printf("CPF esta alugado!");
                    delay(2000);


                }
                else{

                printf("\n Registro: %i\n", ph->reg_cli);

                printf("\n Nome do ciente: ");
                gets(ph->nome);
                fflush(stdin);

                printf("\n");

                printf("\n CPF Cliente: ");
                gets(ph->CPF);
                fflush(stdin);
                printf("\n");

                printf("\n Data da Retirada: Dia/Mes/Ano  ");
                scanf("%d/%d/%d", &ph->status.dados.dia_ret,&ph->status.dados.mes_ret,&ph->status.dados.ano_ret);
                fflush(stdin);
                printf("\n");


                printf("\n Data da Devolucao: Dia/Mes/Ano  ");
                scanf("%d/%d/%d", &ph->status.dados.dia_dev, &ph->status.dados.mes_dev,&ph->status.dados.ano_dev);
                fflush(stdin);
                printf("\n");


                printf("\n Local da Devolucao: ");
                gets(pcc->status.dados.local_dev);
                fflush(stdin);

                pcc->status.car.sigla = 'A';
                ph->reg_car = num_reg;
                ph->tipo = pcc->tipo;

                grava_cadastro_carro_refresh(pcc, "rb+", pos);

                grava_struct_cliente(ph);




               return 0;

                }





            case 2:

                ph->reg_cli = ++var_verifica_cliente;


                printf("\n Qual o CPF do cliente? ");
                gets(&num_cpf);
                fflush(stdin);
                pos = busca_cpf(ph, num_cpf);

                if(strcmp(num_cpf,ph->CPF) & pcc->status.car.sigla == 'R')
                {
                    printf("CPF esta Reservado!");
                    delay(2000);


                }
                else{


                printf("\n Registro: %i\n", ph->reg_cli);

                printf("\n Nome do ciente: ");
                scanf("%c", &ph->nome);
                fflush(stdin);
                printf("\n");

                printf("\n CPF Cliente: ");
                scanf("%c", &ph->CPF);
                fflush(stdin);
                printf("\n");

                printf("\n Data da Retirada: Dia/Mes/Ano ");
                scanf("%d/%d/%d", &ph->status.dados.dia_ret,&ph->status.dados.mes_ret,&ph->status.dados.ano_ret);
                fflush(stdin);
                printf("\n");


                printf("\n Data da Devolucao: Dia/Mes/Ano ");
                scanf("%d/%d/%d", &ph->status.dados.dia_dev, &ph->status.dados.mes_dev,&ph->status.dados.ano_dev);
                fflush(stdin);
                printf("\n");

                printf("\n Local da Devolucao: ");
                gets(pcc->status.dados.local_dev);
                fflush(stdin);

                pcc->status.car.sigla = 'R';

                grava_cadastro_carro_refresh(pcc, "rb+", pos);

                grava_struct_cliente(ph);



                 return 0;

                }


            }
        }

    } while (op != 5);

    system("pause");
}


void cadastro_struct_parcial(struct_cliente *ph, carro *pcc)
{

    int var_verifica_cliente, aux_carro, var_mostra_carro;

    int op;
    char num_cpf [15];

    int num_reg, pos, Fcadastro_cliente;

    do
    {
        carro *initializer_carro = NULL;
        aloca_carro(&initializer_carro, 1);

        var_verifica_cliente = verificar_struct_cliente();



        printf("\n");

        if (Fcadastro_cliente = fopen("carro.bin", "rb+") == NULL)
        {
            printf("\n Arquivo carro sem cadastros");
            delay(1000);

        }
        else

        {

            printf("\n Qual registro do carro ?   ");
            scanf("%i", &num_reg);
            fflush(stdin);

            pos = busca_registro_carro(pcc, num_reg);

            printf("\n");

            printf("\n Deseja alugar ou reservar o carro ?\n  \n [1] Alugar  \n [2] Reservar  ");
            scanf("%i", &op);
            fflush(stdin);

            switch (op)

            {
            case 1:

                ph->reg_cli = ++var_verifica_cliente;


                printf("\n Qual o CPF do cliente? ");
                gets(&num_cpf);
                fflush(stdin);
                pos = busca_cpf(ph, num_cpf);

                if(strcmp(num_cpf,ph->CPF) & pcc->status.car.sigla == 'A')
                {
                    printf("CPF esta alugado!");
                    delay(2000);


                }
                else{



                printf("\n Registro: %i\n", ph->reg_cli);


                printf("\n Nome do ciente: ");
                gets(ph->nome);
                fflush(stdin);

                printf("\n");

                printf("\n CPF Cliente: ");
                gets(ph->CPF);
                fflush(stdin);


                printf("\n");

                printf("\n Data da Retirada: ");
                scanf("%d/%d/%d", &ph->status.dados.dia_ret,&ph->status.dados.mes_ret,&ph->status.dados.ano_ret);
                fflush(stdin);
                printf("\n");


                printf("\n Data da Devolucao: ");
                scanf("%d/%d/%d", &ph->status.dados.dia_dev, &ph->status.dados.mes_dev,&ph->status.dados.ano_dev);
                fflush(stdin);
                printf("\n");



                printf("\n Local da Devolucao: ");
                gets(pcc->status.dados.local_dev);
                fflush(stdin);

                pcc->status.car.sigla = 'A';
                ph->reg_car = num_reg;
                ph->tipo = pcc->tipo;

                grava_cadastro_carro_refresh(pcc, "rb+", pos);

                grava_struct_cliente(ph);


                 return 0;

                }


            case 2:

                ph->reg_cli = ++var_verifica_cliente;


                printf("\n Qual o CPF do cliente? ");
                gets(&num_cpf);
                fflush(stdin);
                pos = busca_cpf(ph, num_cpf);

                if(strcmp(num_cpf,ph->CPF) & pcc->status.car.sigla == 'R')
                {
                    printf("CPF esta Reservado!");
                    delay(2000);


                }

                printf("\n Registro: %i\n", ph->reg_cli);

                printf("\n Nome do ciente: ");
                scanf("%c", &ph->nome);
                fflush(stdin);
                printf("\n");

                printf("\n CPF Cliente: ");
                scanf("%c", &ph->CPF);
                fflush(stdin);
                printf("\n");

                printf("\n Data da Retirada: ");
                scanf("%d/%d/%d", &ph->status.dados.dia_ret,&ph->status.dados.mes_ret,&ph->status.dados.ano_ret);
                fflush(stdin);
                printf("\n");


                printf("\n Data da Devolucao: ");
                scanf("%d/%d/%d", &ph->status.dados.dia_dev, &ph->status.dados.mes_dev,&ph->status.dados.ano_dev);
                fflush(stdin);
                printf("\n");



                printf("\n Local da Devolucao: ");
                gets(pcc->status.dados.local_dev);
                fflush(stdin);

                pcc->status.car.sigla = 'R';

                grava_cadastro_carro_refresh(pcc, "rb+", pos);

                grava_struct_cliente(ph);



                 return 0;
            }
        }

    } while (op != 5);

    system("pause");
}

void mostra_parcial(carro *pcc, struct_cliente *ph)
{

    int var_verifica_cliente, aux_carro, var_mostra_carro;

    int op;

    int num_reg, pos;

    int num;

    char tipo_carro, local_retirada[20], modelo_carro[20], pos_tipo, Fconsultacarro;

    carro *initializer_carro = NULL;
    aloca_carro(&initializer_carro, 1);

    struct_cliente *initializer_cliente = NULL;
    aloca_struct_cliente(&initializer_cliente, 1);



        printf("\n");

        if (Fconsultacarro = fopen("carro.bin", "rb+") == NULL)
        {
            printf("\n Arquivo carro sem cadastros");
            delay(1000);

        }
        else

        {


            printf("\n Deseja qual tipo de Carro [P] - [M] - [G]  ? ");
            scanf("%c", &tipo_carro);
            fflush(stdin);

            printf("\n Deseja qual modelo de carro ? ");
            gets(&modelo_carro);
            fflush(stdin);

            printf("\n Qual Cidade deseja Retirar ? ");
            gets(&local_retirada);
            fflush(stdin);

            pos_tipo = busca_tipo_local_modelo_status(pcc, tipo_carro, local_retirada, modelo_carro);

            if (pcc->status.car.sigla == 'L')
            {


            printf("\n Registro do Carro: %i", pcc->reg_car);
            printf("\n Tipo: %c", pcc->tipo);
            printf("\n Modelo: %s", pcc->modelo);
            printf("\n Sigla: %c", pcc->status.car.sigla);
            printf("\n Diaria: %2.f R$", pcc->diaria);
            printf("\n Local Retirada: %s", pcc->status.car.local_ret);

            printf("\n");
            printf("\n");


            delay(2500);

            printf("\n");

            pos = busca_registro_carro(pcc, pcc->reg_car);


            cadastro_struct_parcial(initializer_cliente, initializer_carro);


            }
            else{

            }

              printf("Nao temos carro Livre com esse perfil!");
              printf("\n");


            }

}


void mostra_total(carro *ph, int n_status_carro)
{

    FILE *Fcadastro_carrro = NULL;
    int i, qh;

    qh = verificar_cadastro_carro();

    if ((Fcadastro_carrro = fopen("carro.bin", "rb")) == NULL)
        printf("\n Arquivo inexistente\n");

    else
    {
        for (i = 0; i < qh; i++)

        {
            fseek(Fcadastro_carrro, i * sizeof(carro), 0);
            fread(ph, sizeof(carro), 1, Fcadastro_carrro);


                printf("\n Registro: %i\n Modelo:%s  \n Tipo: %c \n Sigla: %c  \n Local de Retirada: %s \n Diaria: %2.f R$ ", ph->reg_car, ph->modelo, ph->tipo, ph->status.car.sigla, ph->status.car.local_ret, ph->diaria);
                printf("\n\n ");


        }
        fclose(Fcadastro_carrro);
    }
}

void mostra_total_livres(carro *ph, int n_status_carro)
{

    FILE *Fcadastro_carrro = NULL;
    int i, qh;

    qh = verificar_cadastro_carro();

    if ((Fcadastro_carrro = fopen("carro.bin", "rb")) == NULL)
        printf("\n Arquivo inexistente\n");

    else
    {
        for (i = 0; i < qh; i++)

        {
            fseek(Fcadastro_carrro, i * sizeof(carro), 0);
            fread(ph, sizeof(carro), 1, Fcadastro_carrro);

                if(ph->status.car.sigla == 'L')
                {

                printf("\n Registro: %i\n Modelo:%s  \n Tipo: %c \n Sigla: %c  \n Local de Retirada: %s \n Diaria: %2.f R$ ", ph->reg_car, ph->modelo, ph->tipo, ph->status.car.sigla, ph->status.car.local_ret, ph->diaria);
                printf("\n\n ");


                }

        }
        fclose(Fcadastro_carrro);
    }
}

void devolucao_carro(carro *pcc, struct_cliente *ph, vip *vp)
{

    carro *initializer_carro = NULL;
    aloca_carro(&initializer_carro, 1);
    struct_cliente *initializer_cliente = NULL;
    aloca_struct_cliente(&initializer_cliente, 1);

    vip *initializer_vip = NULL;
    aloca_vip(&initializer_vip, 1);

    int aux_carro;

    char num_cpf[15], pos, pos_carro, Fconsultacarro, Fconsultacliente;

    if (Fconsultacarro = fopen("carro.bin", "rb+") == NULL)
    {
        printf("\n Arquivo carro sem cadastros");
        delay(1000);

    }
    else if (Fconsultacliente = fopen("cliente.bin", "rb+") == NULL)
    {
        printf("\n Arquivo carro sem cadastros");
        delay(1000);

    }
    else

    {

        printf("\n Qual o CPF do cliente?   ");

        gets(&num_cpf);
        fflush(stdin);

        pos = busca_cpf(ph, num_cpf);

        printf("\n CPF: %s", ph->CPF);
        printf("\n");

        printf("\n Nome: %s", ph->nome);
        printf("\n");

        printf("\n Registro do carro: %i", ph->reg_car);
        printf("\n");

        printf("\n Tipo: %c", ph->tipo);
        printf("\n");




    }
}

void grava_cadastro_carro(carro *ph)
{
    FILE *File_cadastro_carro = NULL;
    if ((File_cadastro_carro = fopen("carro.bin", "ab")) == NULL)
        printf("\nErro ao abrir o arquivo");

    else
        fwrite(ph, sizeof(carro), 1, File_cadastro_carro);
    fclose(File_cadastro_carro);
}

void grava_vip(carro *vp)
{
    FILE *File_cadastro_vip = NULL;
    if ((File_cadastro_vip = fopen("vip.bin", "ab")) == NULL)
        printf("\nErro ao abrir o arquivo");

    else
        fwrite(vp, sizeof(carro), 1, File_cadastro_vip);
    fclose(File_cadastro_vip);
}

void grava_struct_cliente(struct_cliente *ph)
{
    FILE *File_cadastro_cliente = NULL;
    if ((File_cadastro_cliente = fopen("cliente.bin", "ab")) == NULL)
        printf("\nErro ao abrir o arquivo");
    else
        fwrite(ph, sizeof(struct_cliente), 1, File_cadastro_cliente);
    fclose(File_cadastro_cliente);
}

void grava_cadastro_carro_refresh(carro *p, char *str, int pos)
{
    FILE *fptr = NULL;

    if ((fptr = fopen("carro.bin", str)) == NULL)
        printf("\nErro ao abrir o arquivo");
    else
    {
        if (strcmp(str, "rb+") == 0)
            fseek(fptr, pos * sizeof(carro), 0);
        fwrite(p, sizeof(carro), 1, fptr);
    }
    fclose(fptr);
}

int verificar_cadastro_carro()
{
    long int cont = 0;
    FILE *Fcadastro_carro = NULL;
    if ((Fcadastro_carro = fopen("carro.bin", "rb")) == NULL)
        return cont;

    else
    {
        fseek(Fcadastro_carro, 0, 2);
        cont = ftell(Fcadastro_carro) / sizeof(carro);
        fclose(Fcadastro_carro);
        return cont;
    }
}

int verificar_struct_cliente()
{
    long int cont = 0;
    FILE *Fcadastro_cliente = NULL;
    if ((Fcadastro_cliente = fopen("cliente.bin", "rb")) == NULL)
        return cont;

    else
    {
        fseek(Fcadastro_cliente, 0, 2);
        cont = ftell(Fcadastro_cliente) / sizeof(struct_cliente);
        fclose(Fcadastro_cliente);
        return cont;
    }
}

void busca_cadastro_carro(carro *ph, int reg_car)
{
    FILE *Fcadastro_carro = NULL;
    int i, qh, achou = 0;

    if ((Fcadastro_carro = fopen("carro.bin", "rb+")) == NULL)
        printf("\n Arquivo inexistente\n");
    else
    {
        for (i = 0; i < qh; i++)
        {

            fseek(Fcadastro_carro, i * sizeof(carro), 0);
            fread(ph, sizeof(carro), 1, Fcadastro_carro);

            if (ph->reg_car == reg_car)
            {

                achou = 1;
                ph->status.car.sigla = 'L';
                ph->num = -1;
                fseek(Fcadastro_carro, i * sizeof(carro), 0);
                fwrite(ph, sizeof(carro), 1, Fcadastro_carro);
                i = qh;
            }
        }
        if (achou == 0)
        {
            printf("\n Nao foi encontrado carro com esse numero de registro\n\n\n");
            system("pause");
        }
    }
    fclose(Fcadastro_carro);
}

int busca_registro_carro(carro *p, int num_reg)
{
    FILE *fptr = NULL;
    int qreg, achou = -1, i;

    qreg = verificar_cadastro_carro();
    system("cls");

    if ((fptr = fopen("carro.bin", "rb")) == NULL)
        printf("\nErro");
    else
    {
        for (i = 0; i < qreg; i++)
        {
            fseek(fptr, i * sizeof(carro), 0);
            fread(p, sizeof(carro), 1, fptr);
            if (p->reg_car == num_reg)
            {
                achou = i;
                i = qreg;
            }
        }
        fclose(fptr);
    }
    return achou;
}

int busca_cpf(struct_cliente *ph, char num_cpf[15])
{
    FILE *fptr = NULL;
    int qreg, achou = -1, i;

    qreg = verificar_cadastro_carro();
    system("cls");

    if ((fptr = fopen("cliente.bin", "rb")) == NULL)
        return achou;

    else
    {
        for (i = 0; i < qreg; i++)
        {
            fseek(fptr, i * sizeof(struct_cliente), 0);
            fread(ph, sizeof(struct_cliente), 1, fptr);

            if (strcmp(ph->CPF, num_cpf) == 0)
            {
                achou = i;
                i = qreg;
            }
        }
        fclose(fptr);
    }
    return achou;
}

int busca_tipo_local_modelo_status(carro *ph, char tipo_carro, char local_retirada[20], char modelo_carro[20])
{
    FILE *fptr = NULL;
    int qreg, achou = -1, i;

    qreg = verificar_cadastro_carro();
    system("cls");

    if ((fptr = fopen("carro.bin", "rb")) == NULL)
        return achou;

    else
    {
        for (i = 0; i < qreg; i++)
        {
            fseek(fptr, i * sizeof(carro), 0);
            fread(ph, sizeof(carro), 1, fptr);

            if ((ph->tipo == tipo_carro && ph->status.car.sigla == 'L' && strcmp(ph->modelo, modelo_carro) == 0 && strcmp(ph->status.car.local_ret, local_retirada) == 0))
            {
                achou = i;
                i = qreg;
            }
        }
        fclose(fptr);
    }
    return achou;
}

void delay(int milliseconds)
{
    long pause;
    clock_t now, then;

    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    now = then = clock();
    while ((now - then) < pause)
        now = clock();
}

void mostra_clientes(struct_cliente *ph)
{

    FILE *Fcliente = NULL;
    int i, qh;

    qh = verificar_cadastro_carro();

    if ((Fcliente = fopen("cliente.bin", "rb")) == NULL)
        printf("\n Arquivo inexistente\n");

    else
    {
        for (i = 0; i < qh; i++)

        {
            fseek(Fcliente, i * sizeof(struct_cliente), 0);
            fread(ph, sizeof(struct_cliente), 1, Fcliente);


                printf("\n Registro: %i\n Nome:%s \n CPF:%s", ph->reg_cli, ph->nome, ph->CPF);
                printf("\n\n ");


        }
        fclose(Fcliente);
    }
}