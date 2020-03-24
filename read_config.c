#include <stdio.h>
#include "include/json-c/json.h"

// gcc read_config.c -ljson-c -o read_config 

struct json_object *parsed_json;
struct json_object *kafka_server;
struct json_object *mqtt_server;

struct json_object *consumer_group;
struct json_object *consumer_topic;
struct json_object *consumer_publish_topic;

struct json_object *producer_group;
struct json_object *producer_topic;

int read_config() 
{
	FILE *fp;
	char buffer[1024];

	//size_t n_array;
	//size_t i;	

	fp = fopen("config.json","r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "kafkaServer", &kafka_server);
	json_object_object_get_ex(parsed_json, "MQTTServer", &mqtt_server);
	
    json_object_object_get_ex(parsed_json, "consumerGroup", &consumer_group);
	json_object_object_get_ex(parsed_json, "consumerTopic", &consumer_topic);
	json_object_object_get_ex(parsed_json, "consumerPublishTopic", &consumer_publish_topic);
	
    json_object_object_get_ex(parsed_json, "producerGroup", &producer_group);
	json_object_object_get_ex(parsed_json, "producerTopic", &producer_topic);

	printf("Kafka Server: %s\n", json_object_get_string(kafka_server));
	printf("MosquittoBroker: %s\n", json_object_get_string(mqtt_server));

	//array = json_object_array_length(array);
	//printf("Found %lu array elements\n",n_array);

	//for(i=0;i<n_array;i++) {
	//	element = json_object_array_get_idx(array, i);
	//	printf("%lu. %s\n",i+1,json_object_get_string(element));
	//}	
	return 1;
}

const char * get_kafka_server(){ return json_object_get_string(kafka_server);}

const char * get_mqtt_server(){ return json_object_get_string(mqtt_server);}

const char * get_consumer_group(){ return json_object_get_string(consumer_group);}
const char * get_consumer_topic(){ return json_object_get_string(consumer_topic);}
const char * get_consumer_publish_topic(){ return json_object_get_string(consumer_publish_topic);}

const char * get_producer_group(){ return json_object_get_string(producer_group);}
const char * get_producer_topic(){ return json_object_get_string(producer_topic);}