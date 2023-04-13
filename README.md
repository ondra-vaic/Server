# Checkers Game Server

### This project involved the development of a checkers game server in C++. The corresponding client is created in Unity. 

* Communication between the server and client is achieved through a text-based, unencrypted protocol over TCP.

### Server is able to:
* Concurrently serve requests from multiple clients
* Automatically reconnect briefly disconnected clients to the game
* Disconnect long-term disconnected clients
* Detect connection failures
* Disconnect clients after sending invalid messages
* Disconnect clients after sending messages that would result in illegal moves
* Disconnect clients after sending valid messages in incorrect contexts

# Seminární práce pro předmět KIV/UPS

## Server pro hru dáma

### V této seminární práci byl vytvořen server v C++ pro hru dáma. Client byl vytvořen v Unity.

* Komunikace je realizována textovým nešifrovaným protokolem nad TCP protokolem.
* Server umožňuje vybrání si místnosti v rámci níž vybírá dvojice hráčů, které spráruje do hry.  

### Server je schopen:
* Obsluhovat požadavky více klientů souběžně.
* Připojit krátce odpojeného klienta zpět do hry.
* Odpojit dlouhodobě odpojeného klienta.
* Detekovat výpadek spojení.
* Odpojit klienta po zaslání nevalidní zprávy.
* Odpojit klienta po zaslání zprávy, která by vedla k nedovolenému tahu.
* Odpojit klienta po zaslání validní zprávy v nekorektním kontextu.


Více informací a kompletní znění zadání najdete v dokumentaci [zde](UpsDoc.pdf).
