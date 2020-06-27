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
