
# Default compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Default target
all: server client

build_server:
	@ echo "🛠️ building server"
	@ $(CC) $(CFLAGS) server.c -o server

run_server:
	@ echo "🚀 running server"
	@ ./server

clean_server:
	@ rm -rf server
	@ echo "🧹 cleaning server files"

server: build_server run_server clean_server


build_client:
	@ echo "🛠️ building client"
	@ $(CC) $(CFLAGS) client.c -o client

run_client:
	@ echo "🚀 running client"
	@ ./client

clean_client:
	@ rm -rf client
	@ echo "🧹 cleaning client files"

client: build_client run_client clean_client

.PHONY: all server client build_server run_server clean_server build_client run_client clean_client
