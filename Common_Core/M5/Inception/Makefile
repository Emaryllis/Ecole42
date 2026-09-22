DOCKER_COMPOSE_FILE := srcs/docker-compose.yml
CERT_FILES := rm -f srcs/requirements/nginx/conf/cert.pem \
		srcs/requirements/nginx/conf/key.pem
all: build
	docker compose -f $(DOCKER_COMPOSE_FILE) up -d
build: init
	docker compose -f $(DOCKER_COMPOSE_FILE) build
down:
	docker compose -f $(DOCKER_COMPOSE_FILE) down
clean:
	docker compose -f $(DOCKER_COMPOSE_FILE) down -v
fclean: clean
	docker compose -f $(DOCKER_COMPOSE_FILE) down -v --rmi all
	docker rm -f nginx mariadb wordpress 2>/dev/null || true
	rm -f $(CERT_FILES)
re: fclean all
init:
	bash srcs/init.sh

# Debug
re-wordpress:
	docker compose -f $(DOCKER_COMPOSE_FILE) up -d --build wordpress
re-nginx:
	docker compose -f $(DOCKER_COMPOSE_FILE) up -d --build nginx
re-mariadb:
	docker compose -f $(DOCKER_COMPOSE_FILE) up -d --build mariadb
logs:
	docker compose -f $(DOCKER_COMPOSE_FILE) logs -f
ps:
	docker compose -f $(DOCKER_COMPOSE_FILE) ps

.PHONY: all build down clean fclean re init logs ps