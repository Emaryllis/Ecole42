#!/usr/bin/env bash
set -e

MYSQL_PASSWORD="$(cat /run/secrets/db_password)"

echo "Waiting for MariaDB to be ready..."
until mysqladmin ping -h mariadb -u "${MYSQL_USER}" -p"${MYSQL_PASSWORD}" --silent; do
  sleep 2
done
echo "MariaDB is ready"

if [ ! -f /var/www/html/wp-config.php ]; then
  echo "Creating wp-config.php..."
  wp config create \
    --dbname="${MYSQL_DATABASE}" \
    --dbuser="${MYSQL_USER}" \
    --dbpass="${MYSQL_PASSWORD}" \
    --dbhost=mariadb \
    --allow-root \
    --path=/var/www/html

  echo "Installing WordPress..."
  wp core install \
    --url="https://${DOMAIN_NAME}" \
    --title="Inception" \
    --admin_user="wproot" \
    --admin_password="${MYSQL_PASSWORD}" \
    --admin_email="wproot@${DOMAIN_NAME}" \
    --allow-root \
    --path=/var/www/html \
    --skip-email

  # Create second user to fulfill requirements
  wp user create "wpuser" "wpuser@${DOMAIN_NAME}" \
    --role=subscriber \
    --user_pass="${MYSQL_PASSWORD}" \
    --allow-root \
    --path=/var/www/html

  chown -R wpuser:wpuser /var/www/html
  echo "WordPress installed successfully"
else
  echo "WordPress already configured, skipping installation"
fi

echo "127.0.0.1 ${DOMAIN_NAME}" >> /etc/hosts
exec php-fpm -F