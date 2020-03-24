/*
* Includes
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/mqtt/MQTTClient.h"
/*
* Defines
*/
/* Caso desejar utilizar outro broker MQTT, substitua o endereco abaixo */
#define MQTT_ADDRESS   "tcp://127.0.0.1:1885"
/* Substitua este por um ID unico em sua aplicacao */
#define CLIENTID       "MQTTCClientID"

/* Substitua aqui os topicos de publish e subscribe por topicos exclusivos de sua aplicacao */
#define MQTT_PUBLISH_TOPIC     "test"
#define MQTT_SUBSCRIBE_TOPIC   "#"

/*
*  Variaveis globais
*/
MQTTClient client;

/*
* Prototipos de funcao
*/
int on_broker_message(void *context, char *topicName, int topicLen, MQTTClient_message *message);



/* Funcao: callback de mensagens MQTT recebidas e echo para o broker
 * Parametros: contexto, ponteiro para nome do topico da mensagem recebida, tamanho do nome do topico e mensagem recebida
 * Retorno : 1: sucesso (fixo / nao ha checagem de erro neste exemplo)
*/
int on_broker_message(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    char* payload = message->payload;

    /* Mostra a mensagem recebida */
    printf("New message from mqtt broker! \n\tTppic: %s \n\tMensagem: %s\n", topicName, payload);

    /* Faz echo da mensagem recebida */
    // publish(client, MQTT_PUBLISH_TOPIC, payload);
    //MQTTClient_freeMessage(&message);
    //MQTTClient_free(topicName);

    produce(topicName, payload);

    return 1;
}


void setup_mqtt() {
    int rc;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

    /* Inicializacao do MQTT (conexao & subscribe) */
    MQTTClient_create(&client, MQTT_ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    MQTTClient_setCallbacks(client, NULL, NULL, on_broker_message, NULL);

    rc = MQTTClient_connect(client, &conn_opts);

    if (rc != MQTTCLIENT_SUCCESS)
    {
        printf("\n\rFalha na conexao ao broker MQTT. Erro: %d\n", rc);
        exit(-1);
    }


    MQTTClient_subscribe(client, MQTT_SUBSCRIBE_TOPIC, 0);
    printf("\n\rConnected! Topics: %s\n", MQTT_SUBSCRIBE_TOPIC);
}