make_kafka:
	gcc producer.c -o producer -lrdkafka -lpaho-mqtt3c -ljson-c -Wall
	gcc consumer.c -o consumer -lrdkafka -lpaho-mqtt3c -ljson-c -Wall
