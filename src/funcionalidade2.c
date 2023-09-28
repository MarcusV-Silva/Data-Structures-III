#include "registro.h"

void funcionalidade2(char *dataBin) {
    FILE *dataBinFile = fopen(dataBin, "rb");

    if (!dataBinFile) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    registro *r;

    r = malloc(sizeof(registro));

    readHeaderBin(dataBinFile);

    //While que imprime os dados do arquivo
    while (!feof(dataBinFile)) {
        char nome[4] = "NULO";

        fread(&r->removido, 1, 1, dataBinFile);
        if (feof(dataBinFile)) {
            free(r);
            break;
        }

        fread(&r->grupo, sizeof(int), 1, dataBinFile);

        fread(&r->popularidade, sizeof(int), 1, dataBinFile);

        fread(&r->peso, sizeof(int), 1, dataBinFile);

        fread(&r->tamTecnologiaOrigem, sizeof(int), 1, dataBinFile);
        r->nmTecnologiaOrigem = malloc(r->tamTecnologiaOrigem);
        fread(r->nmTecnologiaOrigem, 1, r->tamTecnologiaOrigem, dataBinFile);

        if(r->tamTecnologiaOrigem == 0){
            r->nmTecnologiaOrigem = nome; 
        }

        fread(&r->tamTecnologiaDestino, sizeof(int), 1, dataBinFile);
        r->nmTecnologiaDestino = malloc(r->tamTecnologiaDestino);
        fread(r->nmTecnologiaDestino, 1, r->tamTecnologiaDestino, dataBinFile);

        if(r->tamTecnologiaDestino == 0){
            r->nmTecnologiaDestino = nome; 
        }

        printf("%s, ", r->nmTecnologiaOrigem);

        if (r->grupo == -1) {
            printf("NULO, ");
        }else{
            printf("%d, ", r->grupo);
        }

        if (r->popularidade == -1) {
            printf("NULO, ");
        }else{
            printf("%d, ", r->popularidade);
        }

        printf("%s, ", r->nmTecnologiaDestino);

        if (r->peso == -1) {
            printf("NULO \n");
        }else{
            printf("%d\n", r->peso);
        }

        int deslocamento = TAMREGISTRO - TAMREGISTROFIXO - r->tamTecnologiaOrigem - r->tamTecnologiaDestino;
        fseek(dataBinFile, deslocamento, SEEK_CUR);

    }

    free(r->nmTecnologiaOrigem);
    free(r->nmTecnologiaDestino);
    fclose(dataBinFile);
}
