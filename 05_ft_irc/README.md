# Servidor IRC - ft_irc

## Compilación

```bash
g++ -std=c++98 -Wall -Wextra -Werror -o irc_server main.cpp IRC_Server/irce.cpp ProtocolManager/ProtocolManager.cpp
```

## Ejecución

```bash
./irc_server <puerto> <password>
```

Ejemplo:
```bash
./irc_server 6667 mi_password
```

## Pruebas con tres terminales

### Terminal 1 (servidor)
```bash
./irc_server 6667 test123
# Salida esperada (resumen):
# Servidor iniciado en puerto 6667
# Servidor IRC iniciado. Esperando conexiones...
```

### Terminal 2 (cliente A)
```bash
nc -C localhost 6667
PASS test123
NICK a
USER a 0 * :A
JOIN #test
# ... luego verás mensajes PRIVMSG que envíe el cliente B al canal
```

### Terminal 3 (cliente B)
```bash
nc -C localhost 6667
PASS test123
NICK b
USER b 0 * :B
JOIN #test
PRIVMSG #test :hola a todos
QUIT
```

Notas:
- Usa `nc -C` para enviar CRLF (requerido por IRC).
- La bienvenida (`001`) se envía solo tras PASS+NICK+USER válidos.
- `PRIVMSG` a `#test` se entrega a los miembros del canal.
- `QUIT` cierra la conexión y limpia el estado del cliente.

## Pruebas de autenticación estricta, registro y QUIT

Todas las pruebas asumen el servidor arrancado así en otra terminal:
```bash
./irc_server 6667 test123
```

### 1) NICK/USER sin PASS (debe rechazar por no registrado)
```bash
nc -C localhost 6667
NICK a
USER a 0 * :A
```
Esperado:
- Respuesta `451 * :You have not registered` (o equivalente), y no se envía bienvenida.

### 2) PASS incorrecta (debe responder 464 y desconectar)
```bash
nc -C localhost 6667
PASS wrong
NICK a
USER a 0 * :A
```
Esperado:
- Respuesta `464 * :Password incorrect` y cierre inmediato de la conexión (el prompt de `nc` finalizará o mostrará error al escribir más).

### 3) Flujo correcto y QUIT (bienvenida y cierre limpio)
```bash
nc -C localhost 6667
PASS test123
NICK a
USER a 0 * :A
```
Esperado:
- Respuesta de bienvenida `001 a :Welcome to IRC server`.

Enviar QUIT para cerrar:
```bash
QUIT
```
Esperado:
- Mensaje `:server QUIT :Bye` y la conexión se cierra por parte del servidor. `nc` puede mostrar `Broken pipe` si intentas escribir después, lo cual confirma el cierre.

## Características implementadas (Persona 1 - Conexiones)

- ✅ Socket servidor no bloqueante
- ✅ Aceptación de múltiples conexiones simultáneas
- ✅ Gestión de eventos con poll()
- ✅ Lectura incremental con bufferización
- ✅ Segmentación por CRLF
- ✅ Escritura no bloqueante con cola
- ✅ Manejo robusto de desconexiones
- ✅ Gestión de errores de socket
- ✅ Password del servidor
- ✅ Estado por cliente (passOk, registered, etc.)

## Próximos pasos

- Persona 2: Implementar comandos IRC (NICK, USER, JOIN, PRIVMSG, etc.)
- Persona 3: Completar protocolo IRC y manejo de eventos

## Estructura del proyecto

```
ft_irc/
├── main.cpp                    # Punto de entrada
├── IRC_Server/
│   ├── irce.hpp               # Clase principal del servidor
│   └── irce.cpp               # Implementación de conexiones
└── ProtocolManager/
    ├── ProtocolManager.hpp    # Gestor de protocolo IRC
    └── ProtocolManager.cpp    # Implementación de comandos
```