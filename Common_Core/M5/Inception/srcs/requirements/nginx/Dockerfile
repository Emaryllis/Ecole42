FROM debian:bookworm-slim

# Required for nginx.conf
ARG DOMAIN_NAME

# Install prerequisites
RUN apt-get update && \
    apt-get install -y nginx gettext-base curl && \
    rm -f /var/www/html/index.nginx-debian.html && \
    rm -rf /var/lib/apt/lists/*

# Copy nginx files and SSL certificates
COPY conf/nginx.conf /tmp/nginx.conf.template
COPY conf/cert.pem /etc/nginx/ssl/cert.pem
COPY conf/key.pem /etc/nginx/ssl/key.pem

RUN envsubst '${DOMAIN_NAME}' < /tmp/nginx.conf.template > /etc/nginx/nginx.conf

EXPOSE 443

ENTRYPOINT ["nginx", "-g", "daemon off;"]