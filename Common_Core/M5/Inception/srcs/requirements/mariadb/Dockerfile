FROM debian:bookworm-slim

RUN apt-get update && \
    apt-get install -y mariadb-server && \
    rm -rf /var/lib/apt/lists/*

COPY tools/init-mariadb.sh /init-mariadb.sh
RUN chmod +x /init-mariadb.sh

EXPOSE 3306

ENTRYPOINT ["/init-mariadb.sh"]