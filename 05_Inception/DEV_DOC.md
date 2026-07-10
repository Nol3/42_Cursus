# Inception - Documentación para Desarrolladores

## 🛠️ Configuración del Ambiente desde Cero

### Prerrequisitos

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install -y docker.io docker-compose git make

# Verificar instalación
docker --version
docker-compose --version
make --version

# Agregar usuario al grupo docker (evitar usar sudo)
sudo usermod -aG docker $USER
newgrp docker
```

### Clonar el Repositorio

```bash
git clone <tu-repositorio> inception_casa
cd inception_casa
```

### Configuración de Archivos Necesarios

#### 1. Configurar Secretos

Crea la carpeta `secrets/` con archivos de credenciales:

```bash
mkdir -p secrets

# Generar contraseñas seguras
echo "SecureRootPass123!#" > secrets/db_root_password.txt
echo "SecureDBPass456!#" > secrets/db_password.txt
echo "WP_ADMIN_USER=alcademin" > secrets/credentials.txt
echo "WP_ADMIN_PASSWORD=SecureWPPass789!#" >> secrets/credentials.txt
echo "WP_ADMIN_EMAIL=alcademin@alcarden.42.fr" >> secrets/credentials.txt

# Proteger permisos
chmod 600 secrets/*
```

#### 2. Configurar .env

Copia el archivo de ejemplo y actualiza valores:

```bash
cd srcs
cp .env.example .env
nano .env  # Edita DOMAIN_NAME y otros valores según sea necesario
cd ..
```

#### 3. Configurar /etc/hosts

```bash
sudo nano /etc/hosts
```

Agrega:
```
127.0.0.1    alcarden.42.fr
```

---

## 🏗️ Estructura del Proyecto

```
inception_casa/
├── Makefile                          # Automatización
├── README.md                         # Descripción general
├── USER_DOC.md                       # Documentación de usuario
├── DEV_DOC.md                        # Este archivo
├── secrets/                          # Credenciales (NO COMMITEAR)
│   ├── db_root_password.txt
│   ├── db_password.txt
│   └── credentials.txt
├── srcs/
│   ├── .env                          # Configuración (NO COMMITEAR)
│   ├── .env.example                  # Plantilla de .env
│   ├── docker-compose.yml            # Orquestación de servicios
│   └── requirements/
│       ├── mandatory/                # Servicios obligatorios
│       │   ├── nginx/
│       │   │   ├── Dockerfile
│       │   │   ├── conf/
│       │   │   └── tools/
│       │   ├── wordpress/
│       │   │   ├── Dockerfile
│       │   │   ├── conf/
│       │   │   └── tools/
│       │   └── mysql/
│       │       ├── Dockerfile
│       │       ├── conf/
│       │       └── tools/
│       └── bonus/                    # Servicios bonus
│           ├── redis/
│           └── ftp/
└── data/                             # Volúmenes (generados en ejecución)
    ├── wordpress/
    └── mysql/
```

---

## 🚀 Construcción e Inicio del Proyecto

### Comando Rápido

```bash
make up
```

Esto ejecuta:
```bash
mkdir -p $(HOME)/data/wordpress
mkdir -p $(HOME)/data/mysql
docker-compose -f ./srcs/docker-compose.yml up -d --build
```

### Paso a Paso

```bash
# Entrar en el directorio
cd inception_casa

# Construir imágenes
docker-compose -f srcs/docker-compose.yml build

# Iniciar servicios
docker-compose -f srcs/docker-compose.yml up -d

# Verificar estado
docker-compose -f srcs/docker-compose.yml ps
```

---

## 🐳 Administración de Contenedores y Volúmenes

### Comandos Docker Compose Útiles

```bash
# Ver estado de servicios
docker-compose -f srcs/docker-compose.yml ps

# Ver logs de un servicio
docker-compose -f srcs/docker-compose.yml logs wordpress
docker-compose -f srcs/docker-compose.yml logs -f nginx  # Modo seguimiento

# Ejecutar comando en un contenedor
docker-compose -f srcs/docker-compose.yml exec mysql mysql -u root -p

# Reconstruir una imagen específica
docker-compose -f srcs/docker-compose.yml build --no-cache nginx

# Detener sin eliminar datos
docker-compose -f srcs/docker-compose.yml stop

# Reiniciar servicios
docker-compose -f srcs/docker-compose.yml restart
```

### Gestión de Volúmenes

```bash
# Listar volúmenes
docker volume ls

# Ver detalles de un volumen
docker volume inspect inception_casa_wordpress_data

# Limpiar volúmenes no usados
docker volume prune

# Acceder a datos de un volumen
docker run -it --rm -v inception_casa_wordpress_data:/data busybox sh
```

### Gestión de Imágenes

```bash
# Listar imágenes locales
docker images

# Eliminar imagen
docker rmi inception_casa_nginx

# Limpiar imágenes dangling
docker image prune
```

---

## 📊 Ubicación de Datos del Proyecto

### En el Host

```bash
# Datos de volúmenes
~/data/wordpress/     # Archivos de WordPress
~/data/mysql/         # Archivos de base de datos

# Ver contenido
ls -la ~/data/wordpress
ls -la ~/data/mysql
```

### Dentro de Contenedores

| Servicio | Ruta Interna | Punto de Montaje |
|----------|-------------|-----------------|
| WordPress | `/var/www/html` | `wordpress_data` |
| MySQL | `/var/lib/mysql` | `mysql_data` |
| Nginx | `/etc/nginx` | (bind mount) |
| Redis | `/var/lib/redis` | `redis_data` |
| FTP | `/var/ftp/pub` | `ftp_data` |

### Copiar archivos entre host y contenedor

```bash
# Del host al contenedor
docker cp archivo.txt inception_wordpress:/var/www/html/

# Del contenedor al host
docker cp inception_mysql:/var/lib/mysql/backup.sql ./backup.sql
```

---

## 🔧 Tareas Comunes de Desarrollo

### Actualizar Configuración de Nginx

```bash
# Editar archivo de configuración
nano srcs/requirements/mandatory/nginx/conf/nginx.conf

# Recargar nginx sin reiniciar
docker-compose -f srcs/docker-compose.yml exec nginx nginx -s reload

# O reconstruir la imagen
docker-compose -f srcs/docker-compose.yml up -d --build nginx
```

### Instalar Extensiones PHP

1. Edita `srcs/requirements/mandatory/wordpress/Dockerfile`
2. Agrega `RUN apt-get install -y php7.4-<extension>`
3. Reconstruye:
   ```bash
   docker-compose -f srcs/docker-compose.yml up -d --build wordpress
   ```

### Conectar a la Base de Datos

```bash
# Desde el host (si tienes mysql-client instalado)
mysql -h 127.0.0.1 -u wp_user -p wordpress

# Dentro del contenedor MySQL
docker-compose -f srcs/docker-compose.yml exec mysql mysql -u root -p
```

### Respaldar y Restaurar Base de Datos

```bash
# Respaldar
docker-compose -f srcs/docker-compose.yml exec -T mysql \
  mysqldump -u root -p$(cat ../secrets/db_root_password.txt) wordpress > backup.sql

# Restaurar
docker-compose -f srcs/docker-compose.yml exec -T mysql \
  mysql -u root -p$(cat ../secrets/db_root_password.txt) wordpress < backup.sql
```

### Ejecutar Scripts SQL

```bash
docker-compose -f srcs/docker-compose.yml exec -T mysql \
  mysql -u root -p$(cat ../secrets/db_root_password.txt) < script.sql
```

---

## 🔐 Gestión de Secrets y Variables de Entorno

### Estructura Actual

**Variables de Entorno** (`.env`):
- Información no sensible
- Configuración general del proyecto
- Rutas y puertos

**Secrets** (carpeta `secrets/`):
- Contraseñas de administrador
- Credenciales de usuario
- Tokens sensibles

### Acceder a Secrets en Contenedores

En los Dockerfiles o entrypoint scripts:

```bash
# Leer contenido de un secret
cat /run/secrets/db_root_password

# Asignar a variable
DB_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)
```

### Agregar un Nuevo Secret

1. Crea archivo en `secrets/`:
   ```bash
   echo "valor_secreto" > secrets/nuevo_secret.txt
   ```

2. Agrega a `docker-compose.yml`:
   ```yaml
   secrets:
     nuevo_secret:
       file: ../secrets/nuevo_secret.txt
   ```

3. Expone en servicio:
   ```yaml
   services:
     tu_servicio:
       secrets:
         - nuevo_secret
   ```

---

## 📝 Decisiones Técnicas Clave

### Docker vs Máquina Virtual

| Aspecto | Docker | VM |
|--------|--------|-----|
| **Peso** | Ligero (MB) | Pesado (GB) |
| **Velocidad de inicio** | Segundos | Minutos |
| **Aislamiento** | A nivel de SO | Completo |
| **Overhead** | Mínimo | Alto |

Docker es ideal para microservicios; VMs para entornos aislados completos.

### Secrets vs Variables de Entorno

| Característica | Secrets | Env Vars |
|---|---|---|
| **Seguridad** | Alto | Bajo |
| **Visibilidad en logs** | No | Sí (peligroso) |
| **Uso** | Credenciales | Configuración general |
| **Cambio en tiempo de ejecución** | No (requiere reinicio) | Posible |

### Docker Network vs Host Network

| Característica | Bridge Network | Host Network |
|---|---|---|
| **Aislamiento** | Excelente | Ninguno |
| **Rendimiento** | Muy bueno | Óptimo |
| **Seguridad** | Alta | Baja |
| **Complejidad** | Media | Baja |
| **Portabilidad** | Buena | Limitada |

### Docker Volumes vs Bind Mounts

| Característica | Volumes | Bind Mounts |
|---|---|---|
| **Gestión** | Docker | Manual |
| **Portabilidad** | Multiplataforma | SO-dependiente |
| **Performance** | Optimizado | Puede ser lento |
| **Backup** | Fácil | Manual |
| **Caso de uso** | Datos persistentes | Desarrollo |

---

## 🧪 Testing y Verificación

### Verificar Conectividad entre Servicios

```bash
# Desde WordPress a MySQL
docker-compose -f srcs/docker-compose.yml exec wordpress \
  nc -zv mysql 3306

# Desde Nginx a WordPress
docker-compose -f srcs/docker-compose.yml exec nginx \
  curl -I http://wordpress:9000
```

### Verificar Certificados SSL

```bash
docker-compose -f srcs/docker-compose.yml exec nginx \
  openssl x509 -in /etc/nginx/ssl/nginx.crt -text -noout
```

### Monitorear Uso de Recursos

```bash
# Ver estadísticas en tiempo real
docker stats inception_nginx inception_wordpress inception_mysql

# Ver logs detallados
docker-compose -f srcs/docker-compose.yml logs --tail=100 -f
```

---

## 📚 Recursos Útiles

### Documentación Oficial

- [Docker Documentation](https://docs.docker.com/)
- [Docker Compose Reference](https://docs.docker.com/compose/compose-file/)
- [Nginx Configuration](https://nginx.org/en/docs/)
- [WordPress Developer Handbook](https://developer.wordpress.org/)
- [MySQL 8.0 Reference](https://dev.mysql.com/doc/refman/8.0/en/)

### Comandos Frecuentes

```bash
# Ver todo lo que Docker está ejecutando
docker ps -a
docker images
docker volume ls

# Limpiar recursos no usados
docker system prune

# Exportar configuración para inspección
docker inspect <container_id>
docker volume inspect <volume_name>
```

---

## ⚠️ Consideraciones de Seguridad

1. **Nunca commitees credenciales**
   - Usa `secrets/` para credenciales
   - Asegúrate de que `.gitignore` incluye `secrets/`

2. **Cambia contraseñas predeterminadas**
   - Edita archivos en `secrets/`
   - Usa contraseñas fuertes

3. **Actualiza imágenes base**
   - Usa versiones específicas (no `latest`)
   - Revisa vulnerabilidades: `docker scan <image>`

4. **Valida certificados SSL**
   - En producción, usa certificados válidos
   - Considera Let's Encrypt

5. **Logs y auditoría**
   - Revisa logs regularmente
   - Implementa rotación de logs

