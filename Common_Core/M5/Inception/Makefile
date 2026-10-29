DOCKER_COMPOSE_FILE := srcs/docker-compose.yml

CERT_FILES := srcs/requirements/nginx/conf/cert.pem \
	srcs/requirements/nginx/conf/key.pem

WORDPRESS_CACHE := srcs/requirements/wordpress/cache/

# Detect IDs in the recipe shell and export them to Docker Compose.
# $${UID:-$$(id -u)} uses $UID when available, otherwise runs id -u.
COMPOSE = USER_ID="$${UID:-$$(id -u)}" GROUP_ID="$$(id -g)" docker compose -f $(DOCKER_COMPOSE_FILE)

# Mandatory targets
all: init
	$(COMPOSE) build
	$(COMPOSE) up -d --force-recreate
	$(MAKE) post-init

clean:
	$(COMPOSE) down --remove-orphans

fclean:
	$(COMPOSE) down -v --rmi all --remove-orphans
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
	$(COMPOSE) stop

down:
	$(COMPOSE) down

logs:
	$(COMPOSE) logs -f

ps:
	$(COMPOSE) ps

# Debug
re-wordpress:
	$(COMPOSE) build wordpress
	$(COMPOSE) up -d --force-recreate wordpress

re-nginx:
	$(COMPOSE) build nginx
	$(COMPOSE) up -d --force-recreate nginx

re-mariadb:
	$(COMPOSE) build mariadb
	$(COMPOSE) up -d --force-recreate mariadb

full-reinstall: fclean
	rm -rf ~/data/
	$(MAKE) all

.PHONY: all clean fclean re init post-init stop down logs ps \
	re-wordpress re-nginx re-mariadb full-reinstall
