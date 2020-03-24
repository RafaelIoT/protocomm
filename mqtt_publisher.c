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
#define CLIENTID       "MQTTCClientID2"

/* Substitua aqui os topicos de publish e subscribe por topicos exclusivos de sua aplicacao */
#define MQTT_PUBLISH_TOPIC     "test"

/*
*  Variaveis globais
*/
MQTTClient client;

/*
* Prototipos de funcao
*/
void publish(char *topic, char *payload);


/*
* Implementacoes
*/

/* Funcao: publicacao de mensagens MQTT
 * Parametros: cliente MQTT, topico MQTT and payload
 * Retorno: nenhum
*/
void publish(char *topic, char *payload) {
    MQTTClient_message pubmsg = MQTTClient_message_initializer;

    printf("\n publish to topic %s, message: %s ", topic, payload);

    pubmsg.payload = payload;
    pubmsg.payloadlen = strlen(pubmsg.payload);
    pubmsg.qos = 2;
    pubmsg.retained = 0;
    MQTTClient_deliveryToken token;
    MQTTClient_publishMessage(client, topic, &pubmsg, &token);
    MQTTClient_waitForCompletion(client, token, 1000L);
}


void setup_mqtt() {
    int rc;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

    /* Inicializacao do MQTT (conexao & subscribe) */
    MQTTClient_create(&client, MQTT_ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    rc = MQTTClient_connect(client, &conn_opts);

    if (rc != MQTTCLIENT_SUCCESS)
    {
        printf("\n\rFalha na conexao ao broker MQTT. Erro: %d\n", rc);
        exit(-1);
    }
}