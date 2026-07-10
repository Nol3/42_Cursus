#!/bin/sh

# Generate self-signed SSL certificate with dynamic domain
DOMAIN_NAME=${DOMAIN_NAME:-alcarden.42.fr}

openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/${DOMAIN_NAME}.key \
    -out /etc/nginx/ssl/${DOMAIN_NAME}.crt \
    -subj "/C=ES/ST=Malaga/L=Malaga/O=42Malaga/OU=student/CN=${DOMAIN_NAME}"

# Create symlinks with generic names for nginx config
ln -sf /etc/nginx/ssl/${DOMAIN_NAME}.key /etc/nginx/ssl/server.key
ln -sf /etc/nginx/ssl/${DOMAIN_NAME}.crt /etc/nginx/ssl/server.crt

# Set proper permissions
chmod 600 /etc/nginx/ssl/${DOMAIN_NAME}.key
chmod 644 /etc/nginx/ssl/${DOMAIN_NAME}.crt

echo "SSL certificates generated for ${DOMAIN_NAME}!"
