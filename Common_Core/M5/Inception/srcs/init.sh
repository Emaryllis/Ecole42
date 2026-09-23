#!/usr/bin/env bash

set -e

# Generate SSL certificates
source "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/.env"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CERT_DIR="${SCRIPT_DIR}/requirements/nginx/conf"

if [ ! -f "${CERT_DIR}/cert.pem" ] || [ ! -f "${CERT_DIR}/key.pem" ]; then
  echo "Generating certificates..."
  mkdir -p "${CERT_DIR}"
  cd "${CERT_DIR}"
  mkcert -cert-file=cert.pem -key-file=key.pem ${DOMAIN_NAME}
fi


# Cache WordPress and WP-CLI
CACHE_DIR="${SCRIPT_DIR}/requirements/wordpress/cache"
mkdir -p "${CACHE_DIR}"

if [ ! -f "${CACHE_DIR}/latest.tar.gz" ]; then
  echo "Downloading WordPress..."
  curl -fSL -o "${CACHE_DIR}/latest.tar.gz" https://wordpress.org/latest.tar.gz
else
  echo "WordPress archive already cached."
fi

if [ ! -f "${CACHE_DIR}/wp-cli.phar" ]; then
  echo "Downloading WP-CLI..."
  curl -fSL -o "${CACHE_DIR}/wp-cli.phar" https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
else
  echo "WP-CLI already cached."
fi


# Create persistent volumes for MariaDB and WordPress
mkdir -p /home/${LOGIN}/data/mariadb
mkdir -p /home/${LOGIN}/data/wordpress