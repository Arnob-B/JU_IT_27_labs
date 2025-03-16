all: run

run: server client

build_server:
	@echo "building server 🛠️"
	@ gcc -o server server.c 
run_server:
	@echo "running server ▶"
	@ ./server
clean_server:
	@ rm -rf server 
	echo "server cleaned 🧹"

server: build_server run_server clean_server

build_client:
	@echo "building client 🛠️"
	@ gcc -o client client.c 
run_client:
	@echo "running client ▶"
	@ ./client 127.0.0.1 4444
clean_client:
	@ rm -rf client
	@ echo "client cleaned 🧹"

client: build_client run_client clean_client 
