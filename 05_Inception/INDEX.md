# Documentation Index

## 📖 Getting Started
- **[README.md](README.md)** - Project overview & quick start guide
- **[QUICKSTART.md](QUICKSTART.md)** - Step-by-step deployment instructions
- **[ARCHITECTURE.md](ARCHITECTURE.md)** - System design & technical details

## 🔄 Migration Information
- **[MIGRATION_SUMMARY.md](MIGRATION_SUMMARY.md)** - Detailed changes from inception_casa to Inception model

## 📁 Project Structure

### Configuration Files
```
srcs/
├── docker-compose.yml          # Docker service orchestration
├── .env                        # Environment variables (configured)
├── .env.example               # Environment template
└── requirements/
    ├── mariadb/
    │   ├── Dockerfile         # MariaDB container image
    │   ├── .dockerignore
    │   ├── conf/
    │   │   └── my.cnf        # MySQL server configuration
    │   └── tools/
    │       └── init_db.sh    # Database initialization script
    ├── nginx/
    │   ├── Dockerfile         # Nginx container image
    │   ├── .dockerignore
    │   ├── conf/
    │   │   ├── nginx.conf    # Nginx main configuration
    │   │   └── default.conf  # Server blocks & SSL setup
    │   └── tools/
    │       └── generate_ssl.sh # SSL certificate generation
    └── wordpress/
        ├── Dockerfile         # WordPress+PHP-FPM container
        ├── .dockerignore
        ├── conf/
        │   ├── php.ini       # PHP configuration
        │   └── www.conf      # PHP-FPM pool configuration
        └── tools/
            └── init_wordpress.sh # WordPress setup script
```

### Root Files
```
.
├── Makefile               # Build and deployment automation
├── .gitignore            # Git ignore rules
├── README.md             # Quick start guide
├── QUICKSTART.md         # Detailed deployment guide
├── MIGRATION_SUMMARY.md  # Migration details
├── ARCHITECTURE.md       # System architecture
└── LICENSE              # Project license
```

## 🎯 Quick Reference

### Make Commands
| Command | Purpose |
|---------|---------|
| `make` | Setup + build + start |
| `make setup` | Create data directories |
| `make build` | Build Docker images |
| `make up` | Start containers |
| `make down` | Stop containers |
| `make logs` | View logs |
| `make clean` | Remove images |
| `make fclean` | Full cleanup |
| `make re` | Rebuild from scratch |

### Services
| Service | Image | Port | Volume |
|---------|-------|------|--------|
| nginx | nginx:1.0 | 80, 443 | WordPress data |
| wordpress | wordpress:1.0 | 9000 | WordPress data |
| mariadb | mariadb:1.0 | 3306 | Database data |

### Environment Variables
| Variable | Default | Purpose |
|----------|---------|---------|
| DOMAIN_NAME | login.42.fr | Website domain |
| MYSQL_ROOT_PASSWORD | rootpass123 | DB root password |
| MYSQL_USER | wp_user | WordPress DB user |
| MYSQL_PASSWORD | wp_pass123 | WordPress DB password |
| WP_ADMIN_USER | admin | WordPress admin account |
| WP_ADMIN_PASSWORD | Admin123! | WordPress admin password |

## 🔗 Data Persistence
- **MariaDB**: `~/data/mariadb/` → `/var/lib/mysql`
- **WordPress**: `~/data/wordpress/` → `/var/www/html`

## 🛡️ Security
- SSL/TLS v1.2 & v1.3 enabled
- Self-signed certificates (development)
- HTTP → HTTPS redirect
- Protected wp-config.php
- Isolated Docker network

## 🚀 Deployment
1. Add domain to `/etc/hosts`
2. Run `make`
3. Access https://login.42.fr
4. Login with admin/Admin123!

## 📋 File Descriptions

### Core Configuration
- **docker-compose.yml**: Defines all services, networks, and volumes
- **Dockerfile**: Container image specifications
- **.env**: Active configuration (add to .gitignore)
- **.env.example**: Configuration template

### Service Configuration
- **nginx.conf**: Nginx HTTP server configuration
- **default.conf**: Virtual host and SSL settings
- **my.cnf**: MariaDB database server settings
- **www.conf**: PHP-FPM worker pool configuration
- **php.ini**: PHP runtime settings

### Automation Scripts
- **init_db.sh**: Creates database, users, and initializes MariaDB
- **init_wordpress.sh**: Downloads WordPress, creates config, installs via WP-CLI
- **generate_ssl.sh**: Generates self-signed SSL certificates

### Build Tools
- **Makefile**: Provides convenient commands for building and managing containers
- **Dockerfile**: Instructions for building container images
- **.dockerignore**: Files to exclude from Docker build context

## 📞 Troubleshooting

See [QUICKSTART.md](QUICKSTART.md) for common issues and solutions.

## 📚 Additional Resources

- [Docker Documentation](https://docs.docker.com/)
- [Docker Compose Reference](https://docs.docker.com/compose/compose-file/)
- [MariaDB Manual](https://mariadb.org/documentation/)
- [Nginx Documentation](https://nginx.org/en/docs/)
- [WordPress Developer Resources](https://developer.wordpress.org/)
- [PHP Documentation](https://www.php.net/docs.php)

## ⚖️ License
See [LICENSE](LICENSE) file for details.

---

**Last Updated**: December 14, 2025  
**Status**: Production Ready ✓
