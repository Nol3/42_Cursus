# Inception

*This project has been created as part of the 42 curriculum.*

## Description

Inception is a System Administration project that introduces Docker containerization. The goal is to set up a small infrastructure composed of different services (NGINX, WordPress, MariaDB) running in separate Docker containers, orchestrated with Docker Compose.

The infrastructure includes:
- **NGINX**: Web server with TLSv1.2/TLSv1.3 SSL encryption (port 443)
- **WordPress + PHP-FPM**: Content management system
- **MariaDB**: Database server for WordPress

## Instructions

### Prerequisites

- Docker and Docker Compose installed
- Make utility
- Root/sudo access (for creating data directories)

### Quick Start

1. **Configure the domain name:**
```bash
echo "127.0.0.1 alcarden.42.fr" | sudo tee -a /etc/hosts
```

2. **Build and start the infrastructure:**
```bash
make
```

3. **Access the website:**
```
https://alcarden.42.fr
```

### Available Commands

| Command | Description |
|---------|-------------|
| `make` | Build and start all containers |
| `make build` | Build Docker images |
| `make up` | Start containers |
| `make down` | Stop containers |
| `make logs` | View container logs |
| `make clean` | Stop and remove images |
| `make fclean` | Full cleanup (images + data) |
| `make re` | Rebuild from scratch |
   ```

3. **Configurar dominio local**:
   ```bash
   sudo nano /etc/hosts
   # Agregar: 127.0.0.1    alcarden.42.fr
   ```

4. **Configurar variables de entorno**:
   ```bash
   cd srcs
   cp .env.example .env
   nano .env  # Verifica que DOMAIN_NAME=alcarden.42.fr
   cd ..
   ```

### Ejecución del Proyecto

```bash
# Iniciar todo
make up

# Detener servicios
make down

# Reiniciar desde cero
make re

# Limpiar completamente
make fclean
```

### Acceder a los Servicios

```
WordPress:  https://alcarden.42.fr
wp-admin:   https://alcarden.42.fr/wp-admin
phpMyAdmin: https://alcarden.42.fr:8080
```

**Credenciales**: Ver `secrets/credentials.txt`

---

## Project Description

### Decisiones Técnicas

#### Docker vs Máquinas Virtuales

| Aspecto | Docker | VM |
|---------|--------|-----|
| **Tamaño** | MB | GB |
| **Velocidad** | Segundos | Minutos |
| **Aislamiento** | A nivel SO | Completo |
| **Overhead** | Mínimo | Alto |

**Decisión**: Docker es más eficiente para microservicios. Se utilizan contenedores para cada servicio independiente.

#### Secrets vs Variables de Entorno

| Característica | Secrets | Env Vars |
|---|---|---|
| **Seguridad** | ⭐⭐⭐⭐⭐ | ⭐ |
| **Visible en logs** | ❌ | ✅ (PELIGRO) |
| **Uso** | Credenciales | Configuración |

**Decisión**: Se utilizan Docker Secrets para credenciales (en archivos separados) y .env solo para configuración no sensible.

#### Docker Network vs Host Network

| Característica | Bridge Network | Host Network |
|---|---|---|
| **Aislamiento** | ⭐⭐⭐⭐⭐ | ❌ |
| **Seguridad** | ⭐⭐⭐⭐⭐ | ⭐ |
| **Rendimiento** | Excelente | Óptimo |

**Decisión**: Se usa Bridge Network (por defecto) para aislamiento y seguridad. Esto permite que los contenedores se comuniquen de forma segura.

#### Docker Volumes vs Bind Mounts

| Característica | Volumes | Bind Mounts |
|---|---|---|
| **Portabilidad** | ✅ Multiplataforma | ❌ SO-dependiente |
| **Performance** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐ |
| **Backup** | ✅ Fácil | ❌ Manual |

**Decisión**: Se utilizan Volumes para datos persistentes (WordPress, MySQL, Redis). Esto asegura portabilidad y mejor rendimiento.

### Fuentes Incluidas

```
srcs/
├── .env                    # Variables de entorno (generado)
├── .env.example            # Plantilla de ejemplo
├── docker-compose.yml      # Orquestación de servicios
└── requirements/
    ├── mandatory/          # Servicios obligatorios
    │   ├── nginx/          # Servidor web con TLS
    │   ├── wordpress/      # CMS + PHP-FPM
    │   └── mysql/          # Base de datos
    └── bonus/              # Servicios adicionales
        ├── redis/          # Caché
        └── ftp/            # Servidor FTP
```

Cada servicio tiene su propio Dockerfile personalizado (sin usar imágenes preconstruidas, excepto Alpine/Debian).

---

## Resources

### Documentación Oficial

- [Docker Documentation](https://docs.docker.com/) - Referencia completa de Docker
- [Docker Compose Reference](https://docs.docker.com/compose/compose-file/) - Especificación de docker-compose.yml
- [Nginx Documentation](https://nginx.org/en/docs/) - Configuración de servidor web
- [WordPress Developer Handbook](https://developer.wordpress.org/) - Desarrollo con WordPress
- [MySQL Documentation](https://dev.mysql.com/doc/) - Base de datos MySQL

### Recursos de Aprendizaje

- [Best Practices for Writing Dockerfiles](https://docs.docker.com/develop/develop-images/dockerfile_best-practices/)
- [Docker Networking Guide](https://docs.docker.com/network/)
- [Understanding Docker Security](https://docs.docker.com/engine/security/)

### Cómo se usó IA en este Proyecto

**✅ Prácticas Correctas:**
- 🤖 **Consultas sobre arquitectura**: Pregunté a IA sobre patrones de Docker y microservicios, luego validé con pares
- 🤖 **Debugging**: Usé IA para entender mensajes de error, pero implementé las correcciones manualmente
- 🤖 **Documentación**: Solicité ayuda para estructurar USER_DOC.md y DEV_DOC.md, pero verifiqué cada instrucción
- 🤖 **Configuración de servicios**: Usé IA como referencia para nginx.conf y entrypoints, pero los ajusté personalmente

**⚠️ Evité:**
- ❌ Copiar código directamente sin entender
- ❌ Usar Dockerfiles generados sin revisión
- ❌ Confiar ciegamente en soluciones genéricas
- ❌ Dejar credenciales en el código

**Resultado**: Comprensión profunda del proyecto. Puedo explicar cada servicio, cada configuración, y justificar cada decisión técnica.

---

## Documentación Adicional

Para información detallada, ver:

- **[USER_DOC.md](./USER_DOC.md)** - Guía para usuarios finales (iniciar/parar servicios, acceder a WordPress, etc.)
- **[DEV_DOC.md](./DEV_DOC.md)** - Guía para desarrolladores (configuración, construcción, desarrollo)

---

## Estructura de Directorios

```
inception_casa/
├── Makefile                # Automatización
├── README.md              # Este archivo
├── USER_DOC.md            # Documentación de usuario
├── DEV_DOC.md             # Documentación de desarrollador
├── .gitignore             # Archivos ignorados por Git
├── secrets/               # 🔐 Credenciales (NO COMMITEAR)
│   ├── db_root_password.txt
│   ├── db_password.txt
│   └── credentials.txt
└── srcs/
    ├── .env               # Configuración (NO COMMITEAR)
    ├── .env.example       # Plantilla de .env
    ├── docker-compose.yml # Orquestación
    └── requirements/
        ├── mandatory/
        │   ├── nginx/     # Dockerfile + config
        │   ├── wordpress/ # Dockerfile + config
        │   └── mysql/     # Dockerfile + config
        └── bonus/
            ├── redis/     # Dockerfile + config
            └── ftp/       # Dockerfile + config
```

---

## Requisitos Cumplidos ✅

### Parte Obligatoria
- ✅ Dockerfile personalizado para cada servicio
- ✅ docker-compose.yml con todos los servicios
- ✅ Volúmenes para persistencia
- ✅ Red Docker para comunicación entre servicios
- ✅ NGINX con TLS 1.2/1.3 (puerto 443 únicamente)
- ✅ WordPress + PHP-FPM
- ✅ MariaDB con usuarios configurados
- ✅ Restart policy en contenedores
- ✅ Variables de entorno en .env
- ✅ Docker Secrets para credenciales
- ✅ Dominio configurado (alcarden.42.fr)
- ✅ Sin credenciales en Git

### Documentación
- ✅ README.md completo con todos los requisitos
- ✅ USER_DOC.md (instrucciones para usuarios)
- ✅ DEV_DOC.md (instrucciones para desarrolladores)
- ✅ Explicación de decisiones técnicas
- ✅ Comparativas Docker vs VM, Secrets vs Env, Volumes vs Bind Mounts, etc.

### Bonus
- ✅ phpMyAdmin para administración de BD
- ✅ Redis para caché
- ✅ Servidor FTP

---

## Author

*alcarden* - 42 Network Student

## License

This project is under the MIT License. See [LICENSE](./LICENSE) for details.
