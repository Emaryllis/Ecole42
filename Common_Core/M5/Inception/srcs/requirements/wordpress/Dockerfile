FROM debian:bookworm-slim

ARG USER_ID
ARG GROUP_ID

RUN apt-get update && \
    apt-get install -y php-fpm php-mysql php-gd php-mbstring mariadb-client curl tar iproute2 && \
    rm -rf /var/lib/apt/lists/*

RUN groupadd -g ${GROUP_ID} wpuser && \
    useradd -u ${USER_ID} -g wpuser -m wpuser

RUN if [ ! -f /usr/sbin/php-fpm ]; then ln -s /usr/sbin/php-fpm* /usr/sbin/php-fpm; fi

COPY cache/wp-cli.phar /usr/local/bin/wp
RUN chmod +x /usr/local/bin/wp

# Configure PHP-FPM to listen on TCP 9000
RUN sed -i 's|listen = /run/php/php[0-9.]*-fpm.sock|listen = 0.0.0.0:9000|' /etc/php/*/fpm/pool.d/www.conf && \
    sed -i 's/user = www-data/user = wpuser/' /etc/php/*/fpm/pool.d/www.conf && \
    sed -i 's/group = www-data/group = wpuser/' /etc/php/*/fpm/pool.d/www.conf && \
    mkdir -p /run/php

COPY cache/latest.tar.gz /opt/wordpress.tar.gz

WORKDIR /var/www/html

RUN tar -xzf /opt/wordpress.tar.gz --strip-components=1 -C /var/www/html && \
    chown -R wpuser:wpuser /var/www/html

COPY tools/init-wordpress.sh /init-wordpress.sh
RUN chmod +x /init-wordpress.sh

EXPOSE 9000

ENTRYPOINT ["/init-wordpress.sh"]