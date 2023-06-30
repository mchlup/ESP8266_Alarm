// soubor WebServerModule.cpp

#include "WebServerModule.h"

WebServer::WebServer() : m_server(80), m_serverStarted(false) {}

void WebServer::setup() {
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }

  initializeServer();
}

void WebServer::update() {
  m_server.handleClient();
}

void WebServer::initializeServer() {
  m_server.on("/", std::bind(&WebServer::handleRoot, this));
  m_server.onNotFound(std::bind(&WebServer::handleFile, this));

  m_server.begin();
  m_serverStarted = true;

  Serial.println("Server started");
}

String WebServer::loadFile(const String& path) {
  File file = SPIFFS.open(path, "r");
  if (!file) {
    Serial.println("Failed to open file: " + path);
    return String();
  }

  String content = file.readString();
  file.close();

  return content;
}

void WebServer::handleRoot() {
  String content = loadFile(HTML_DIR + "/index.html");
  if (content.length() > 0) {
    sendFileContent(content);
  } else {
    m_server.send(404, "text/plain", "File not found");
  }
}

void WebServer::handleFile() {
  String path = m_server.uri();
  if (path.endsWith("/")) {
    path += "index.html";
  }

  String content = loadFile(HTML_DIR + path);
  if (content.length() > 0) {
    sendFileContent(content);
  } else {
    m_server.send(404, "text/plain", "File not found");
  }
}

void WebServer::sendFileContent(const String& content) {
  m_server.send(200, "text/html", content);
}
