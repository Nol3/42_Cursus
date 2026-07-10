# Inception - Documentación de Usuario

## 📋 Descripción General

Inception es una infraestructura Docker completa que proporciona un sitio web WordPress funcional con todas las herramientas necesarias para gestionar tanto el contenido como la base de datos.

### Servicios Disponibles

- **WordPress** - Plataforma de gestión de contenidos
- **MySQL/MariaDB** - Base de datos
- **Nginx** - Servidor web con SSL/TLS
- **phpMyAdmin** (Bonus) - Herramienta para administrar la base de datos
- **Redis** (Bonus) - Sistema de caché
- **Servidor FTP** (Bonus) - Acceso a archivos vía FTP

---

## 🚀 Inicio y Parada del Proyecto

### Iniciar el proyecto

```bash
cd inception_casa
make up
```

Este comando:
- Crea los directorios necesarios en tu carpeta personal
- Construye todas las imágenes Docker
- Inicia los contenedores
- Configura la red y volúmenes

### Detener el proyecto

```bash
make down
```

Este comando detiene todos los contenedores sin eliminar datos.

### Reiniciar el proyecto

```bash
make re
```

Este comando elimina todo (contenedores, volúmenes, imágenes) y reinicia desde cero.

### Otros comandos

```bash
make start          # Inicia los contenedores detenidos
make stop           # Detiene los contenedores sin eliminarlos
make clean          # Limpia imágenes y contenedores huérfanos
make fclean         # Limpieza completa (elimina datos)
```

---

## 🌐 Acceder al Sitio Web

### WordPress

1. **Configura tu host local** - Edita `/etc/hosts` (requiere privilegios de administrador):

   ```bash
   sudo nano /etc/hosts
   ```

   Agrega esta línea:
   ```
   127.0.0.1    alcarden.42.fr
   ```

2. **Accede a través de HTTPS**:

   ```
   https://alcarden.42.fr
   ```

3. **Panel de administración de WordPress**:

   ```
   https://alcarden.42.fr/wp-admin
   ```

### phpMyAdmin (Herramienta de Administración de Base de Datos)

- **URL**: `https://alcarden.42.fr:8080`
- **Usuario**: `pma_user`
- **Contraseña**: Ver archivo `secrets/credentials.txt`

---

## 🔐 Gestión de Credenciales

### Ubicación de Credenciales

Todas las credenciales se encuentran en la carpeta `secrets/` en la raíz del proyecto:

```
secrets/
├── db_root_password.txt     # Contraseña de administrador de MySQL
├── db_password.txt          # Contraseña del usuario de base de datos
└── credentials.txt          # Credenciales de WordPress
```

### Cambiar Credenciales

Para cambiar cualquier contraseña:

1. **Detén el proyecto**:
   ```bash
   make fclean
   ```

2. **Edita los archivos en `secrets/`**:
   ```bash
   nano secrets/db_root_password.txt
   nano secrets/db_password.txt
   nano secrets/credentials.txt
   ```

3. **Reinicia el proyecto**:
   ```bash
   make up
   ```

⚠️ **IMPORTANTE**: Estos archivos NO deben ser compartidos ni commiteados a Git.

---

## ✅ Verificar que los Servicios Están Corriendo

### Listar contenedores en ejecución

```bash
docker ps
```

Deberías ver:
- `inception_nginx` - Servidor web
- `inception_wordpress` - WordPress
- `inception_mysql` - Base de datos
- `inception_phpmyadmin` - phpMyAdmin
- `inception_redis` - Caché (Bonus)
- `inception_ftp` - Servidor FTP (Bonus)

### Ver logs de un servicio específico

```bash
docker logs inception_wordpress
docker logs inception_mysql
docker logs inception_nginx
```

### Ver estado de salud

```bash
docker ps --format "table {{.Names}}\t{{.Status}}"
```

### Ejecutar comandos dentro de un contenedor

```bash
# Conectar a MySQL
docker exec -it inception_mysql mysql -u root -p

# Acceder a WordPress
docker exec -it inception_wordpress bash

# Verificar conexión de Redis
docker exec -it inception_redis redis-cli ping
```

---

## 📁 Ubicación de Datos

### En tu máquina host

Los datos persistentes se almacenan en:

```
~/data/
├── wordpress/    # Archivos del sitio WordPress
├── mysql/        # Base de datos MySQL
└── redis/        # Datos de caché (Bonus)
```

### Dentro de los contenedores

- **WordPress**: `/var/www/html`
- **MySQL**: `/var/lib/mysql`
- **Redis**: `/var/lib/redis`
- **Nginx**: `/etc/nginx` y `/var/log/nginx`

---

## 🔧 Tareas Comunes

### Subir nuevos temas o plugins

1. Coloca los archivos en `~/data/wordpress/wp-content/themes/` o `~/data/wordpress/wp-content/plugins/`
2. Actívalos desde el panel de WordPress

### Respaldar la base de datos

```bash
docker exec inception_mysql mysqldump -u root -p wordpress > backup.sql
```

### Restaurar una base de datos

```bash
docker exec -i inception_mysql mysql -u root -p wordpress < backup.sql
```

### Limpiar caché de Redis

```bash
docker exec inception_redis redis-cli FLUSHALL
```

### Ver uso de disco

```bash
du -sh ~/data/*
```

---

## 🚨 Solución de Problemas

### "conexión rechazada" en WordPress

- Verifica que MySQL está corriendo: `docker logs inception_mysql`
- Reinicia los servicios: `make down && make up`

### Puerto 443 ya en uso

```bash
lsof -i :443
sudo kill -9 <PID>
```

### Certificado SSL no confiable

Esto es normal en desarrollo. Acepta la advertencia en tu navegador.

### Base de datos corrupta

```bash
make fclean
make up
```

Esto recrea todo desde cero.

---

## 📞 Soporte

Para reportar problemas, verifica primero los logs:

```bash
docker-compose -f srcs/docker-compose.yml logs
```

