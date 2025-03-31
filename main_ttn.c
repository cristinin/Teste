#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TTN_URL "https://eu1.cloud.thethings.network/api/v3/as/applications/appmeteorologica/devices/deviceapp/uplink_message"
#define TTN_AUTH "Authorization: Bearer NNSXS.JVUUJX23OEPBHPNOKAWVEYVLP7URAYXXI6Q5BIY.ITSKE7J2FDRPONY7BNCGIFETQX62T5VSQCURD4KSRGETNOWYH5JA"
#define TAGOIO_DEVICE_TOKEN "82654422-af19-472e-b803-b6d23b1c11a0"

int main() {
    setlocale(LC_ALL, "Portuguese");

    char var1[50], var2[50];
    float val1, val2;

    printf("Informe a primeira variável: ");
    scanf("%49s", var1);
    printf("Informe o valor da primeira variável: ");
    if (scanf("%f", &val1) != 1) {
        printf("Valor inválido! Por favor, insira um número válido.\n");
        return 1;
    }

    printf("--------------------------------------------------------------------\n");

    printf("Informe a segunda variável: ");
    scanf("%49s", var2);
    printf("Informe o valor da segunda variável: ");
    if (scanf("%f", &val2) != 1) {
        printf("Valor inválido! Por favor, insira um número válido.\n");
        return 1;
    }

    char json_ttn[512];
    snprintf(json_ttn, sizeof(json_ttn),
        "'{ \"end_device_ids\": { \"device_id\": \"device-app\" },"
        " \"uplink_message\": { \"decoded_payload\": { \"%s\": %.2f, \"%s\": %.2f } } }'",
        var1, val1, var2, val2);

    char comando_ttn[800];
    snprintf(comando_ttn, sizeof(comando_ttn),
        "curl -X POST \"%s\" "
        "-H \"Content-Type: application/json\" "
        "-H \"%s\" "
        "-d %s",
        TTN_URL, TTN_AUTH, json_ttn);

    printf("\nComando executado para TTN:\n%s\n", comando_ttn);
    printf("Enviando dados para a The Things Network...\n");

    int resultado_ttn = system(comando_ttn);
    if (resultado_ttn == 0) {
        printf("Dados enviados com sucesso para a TTN!\n");
    } else {
        printf("Erro ao enviar os dados para a TTN. Código: %d\n", resultado_ttn);
        return 1;
    }

    return 0;
}
