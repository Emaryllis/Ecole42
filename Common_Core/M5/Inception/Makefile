DOCKER_COMPOSE_FILE := srcs/docker-compose.yml
CERT_FILES := srcs/requirements/nginx/conf/cert.pem \
	srcs/requirements/nginx/conf/key.pem
WORDPRESS_CACHE := srcs/requirements/wordpress/cache/
UID := $(shell id -u)
GID := $(shell id -g)

# Mandatory targets
all: init
	docker compose -f srcs/docker-compose.yml build \
    		--build-arg USER_ID=$(UID) \
    		--build-arg GROUP_ID=$(GID)
	docker compose -f $(DOCKER_COMPOSE_FILE) up -d --force-recreate
	make post-init
clean:
	docker compose -f $(DOCKER_COMPOSE_FILE) down --remove-orphans
fclean:
	docker compose -f $(DOCKER_COMPOSE_FILE) down -v --rmi all \
	--remove-orphans
	docker rm -f nginx mariadb wordpress 2>/dev/null || true
	docker network rm srcs_inception 2>/dev/null || true
	rm -f $(CERT_FILES)
	rm -rf $(WORDPRESS_CACHE)
re: fclean all

# Optional QOL targets
init:
	bash srcs/init.sh
post-init:
	bash srcs/post-init.sh
stop:
	docker compose -f $(DOCKER_COMPOSE_FILE) stop
down:
	docker compose -f $(DOCKER_COMPOSE_FILE) down
logs:
	docker compose -f $(DOCKER_COMPOSE_FILE) logs -f
ps:
	docker compose -f $(DOCKER_COMPOSE_FILE) ps

# Debug
re-wordpress:
	docker compose -f $(DOCKER_COMPOSE_FILE) build \
		--build-arg USER_ID=$(UID) --build-arg GROUP_ID=$(GID) wordpress
	docker compose -f $(DOCKER_COMPOSE_FILE) up -d --force-recreate wordpress
re-nginx:
	docker compose -f $(DOCKER_COMPOSE_FILE) build nginx
	docker compose -f $(DOCKER_COMPOSE_FILE) up -d --force-recreate nginx
re-mariadb:
	docker compose -f $(DOCKER_COMPOSE_FILE) build \
		--build-arg USER_ID=$(UID) --build-arg GROUP_ID=$(GID) mariadb
	docker compose -f $(DOCKER_COMPOSE_FILE) up -d --force-recreate mariadb
full-reinstall: fclean
	rm -rf ~/data/
	make all

.PHONY: all clean fclean re init post-init stop down logs ps \
	re-wordpress re-nginx re-mariadb full-reinstall