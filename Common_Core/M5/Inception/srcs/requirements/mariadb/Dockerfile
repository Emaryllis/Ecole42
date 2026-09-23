FROM debian:bookworm-slim

ARG USER_ID
ARG GROUP_ID

# Initalize mysql with the proper permissions
RUN groupadd -g ${GROUP_ID} mysql && \
    useradd -u ${USER_ID} -g mysql -d /var/lib/mysql -s /usr/sbin/nologin mysql && \
    mkdir -p /var/lib/mysql /run/mysqld && \
    chown -R mysql:mysql /var/lib/mysql /run/mysqld

# Install prerequisites
RUN apt-get update && \
    apt-get install -y mariadb-server gettext-base && \
    rm -rf /var/lib/mysql/* && \
    rm -rf /var/lib/apt/lists/*

COPY tools/init-mariadb.sh /init-mariadb.sh
COPY tools/init.sql /tmp/init.sql.template
RUN chmod +x /init-mariadb.sh

EXPOSE 3306

ENTRYPOINT ["/init-mariadb.sh"]