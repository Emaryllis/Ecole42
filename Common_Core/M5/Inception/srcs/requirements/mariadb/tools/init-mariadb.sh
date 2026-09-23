#!/usr/bin/env bash
set -e

mkdir -p /run/mysqld
chown mysql:mysql /run/mysqld

if [ ! -d "/var/lib/mysql/mysql" ]; then
  echo "Initializing MariaDB..."
  mysql_install_db --user=mysql --datadir=/var/lib/mysql

  export MYSQL_ROOT_PASSWORD="$(cat /run/secrets/db_root_password)"
  export MYSQL_PASSWORD="$(cat /run/secrets/db_password)"

  envsubst < /tmp/init.sql.template > /tmp/init.sql
  rm -f /tmp/init.sql.template

  mysqld --user=mysql --bind-address=0.0.0.0 --init-file=/tmp/init.sql &
  MYSQL_PID=$!

  until mysqladmin ping -h 127.0.0.1 --silent 2>/dev/null; do sleep 1; done

  rm -f /tmp/init.sql
  unset MYSQL_ROOT_PASSWORD MYSQL_PASSWORD
  chown -R mysql:mysql /var/lib/mysql /run/mysqld
  wait $MYSQL_PID
else
    exec mysqld --user=mysql --bind-address=0.0.0.0
fi