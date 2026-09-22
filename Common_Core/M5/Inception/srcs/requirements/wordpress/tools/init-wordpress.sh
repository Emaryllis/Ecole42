#!/usr/bin/env bash
set -e

MYSQL_USER_PASSWORD="$(cat /run/secrets/db_password)"

until mysqladmin ping -h mariadb -u "${MYSQL_USER}" -p"${MYSQL_USER_PASSWORD}" --silent 2>/dev/null; do
    echo "Waiting for MariaDB..."
    sleep 2
done

echo "MariaDB is ready"

if [ ! -f /var/www/html/wp-config.php ]; then
    echo "Checking WordPress installation..."

    if [ ! -f /var/www/html/index.php ]; then
        if [ -f /opt/wordpress.tar.gz ]; then
            echo "Installing WordPress from cache..."
            tar -xzf /opt/wordpress.tar.gz --strip-components=1 -C /var/www/html
        else
            echo "Downloading WordPress..."
            curl -o /tmp/latest.tar.gz https://wordpress.org/latest.tar.gz
            tar -xzf /tmp/latest.tar.gz --strip-components=1 -C /var/www/html
            rm /tmp/latest.tar.gz
        fi
        chown -R www-data:www-data /var/www/html
    fi

    echo "Creating wp-config.php..."
    wp config create \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="${MYSQL_USER_PASSWORD}" \
        --dbhost=mariadb \
        --allow-root \
        --path=/var/www/html

    echo "Installing WordPress..."
    wp core install \
        --url="https://${DOMAIN_NAME}" \
        --title="Inception" \
        --admin_user="${MYSQL_USER}" \
        --admin_password="${MYSQL_USER_PASSWORD}" \
        --admin_email="${MYSQL_USER}@${DOMAIN_NAME}" \
        --allow-root \
        --path=/var/www/html \
        --skip-email

    echo "WordPress installed successfully"
else
    echo "WordPress already configured, skipping installation"
fi

chown -R www-data:www-data /var/www/html

exec php-fpm -F