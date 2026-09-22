FROM debian:bookworm-slim

ARG DOMAIN_NAME

RUN apt-get update && \
    apt-get install -y nginx gettext-base curl && \
    rm -rf /var/lib/apt/lists/*

COPY conf/nginx.conf /tmp/nginx.conf.template
COPY conf/cert.pem /etc/nginx/ssl/cert.pem
COPY conf/key.pem /etc/nginx/ssl/key.pem

RUN envsubst '${DOMAIN_NAME}' < /tmp/nginx.conf.template > /etc/nginx/nginx.conf

EXPOSE 443

ENTRYPOINT ["nginx", "-g", "daemon off;"]