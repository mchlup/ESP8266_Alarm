// soubor WebServerModule.h

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <FS.h>

class WebServer {
public:
  WebServer();
  void setup();
  void update();

private:
  // Adresář na SPIFFS pro ukládání HTML souborů
  const String HTML_DIR = "/html";

  // Proměnné pro stav serveru
  ESP8266WebServer m_server;
  bool m_serverStarted;

  // Metoda pro inicializaci serveru
  void initializeServer();

  // Metoda pro načtení obsahu souboru z paměti SPIFFS
  String loadFile(const String& path);

  // Metoda pro obsluhu požadavků na kořenovou cestu "/"
  void handleRoot();

  // Metoda pro obsluhu požadavků na získání konkrétního souboru
  void handleFile();

  // Metoda pro odeslání odpovědi s obsahem souboru
  void sendFileContent(const String& content);
};

#endif
