///////////////////////////////////////////////////////////////////
//-- code for esp8266  ------------------------------------------//
//-- websocket client  ------------------------------------------//
///////////////////////////////////////////////////////////////////

// #include <Arduino.h>

// #include <ESP8266WiFi.h>
// #include <ESP8266WiFiMulti.h>
// #include <WebSocketsClient.h>
// #include <Hash.h>

// ESP8266WiFiMulti WiFiMulti;
// WebSocketsClient webSocket;

// // dev
// //int port = 3000;
// //String server = "172.30.4.223";
// String host = "/socket";


// bool isConnected = false;

// void setup() {
//   Serial.begin(115200);

//   Serial.setDebugOutput(true);

//   Serial.println();
//   Serial.println();
//   Serial.println();

//   for(uint8_t t = 4; t > 0; t--) {
//     Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
//     Serial.flush();
//     delay(1000);
//   }

//   startWiFi();

//   // server address, port and URL
// //    webSocket.begin(server, port, host);
//    webSocket.begin("arduino-websocket-server.herokuapp.com", 80, "/socket");

//   // event handler
//   webSocket.onEvent(webSocketEvent);

//   // try ever 5000 again if connection has failed
//   webSocket.setReconnectInterval(5000);

//   // start heartbeat (optional)
//   // ping server every 15000 ms
//   // expect pong from server within 3000 ms
//   // consider connection disconnected if pong is not received 2 times
//   webSocket.enableHeartbeat(15000, 3000, 2);

// }

// void startWiFi() { // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection
//   WiFiMulti.addAP("Pavel", "123456789");   // add Wi-Fi networks you want to connect to


//   Serial.println("Connecting");
//   while (WiFiMulti.run() != WL_CONNECTED && WiFi.softAPgetStationNum() < 1) {  // Wait for the Wi-Fi to connect
//     delay(250);
//     Serial.print('.');
//   }
//   Serial.println("\r\n");
//   if(WiFi.softAPgetStationNum() == 0) {      // If the ESP is connected to an AP
//     Serial.print("Connected to ");
//     Serial.println(WiFi.SSID());             // Tell us what network we're connected to
//     Serial.print("IP address:\t");
//     Serial.print(WiFi.localIP());            // Send the IP address of the ESP8266 to the computer
//   } else {                                   // If a station is connected to the ESP SoftAP
//     Serial.print("Station connected to ESP8266 AP");
//   }
//   Serial.println("\r\n");
// }

// void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
//   switch(type) {
//     case WStype_DISCONNECTED: {
//         isConnected = false;
//         Serial.printf("[WSc] Disconnected!\n");
//       }
//       break;
//     case WStype_CONNECTED: {
//       isConnected = true;
//       Serial.printf("[WSc] Connected to url: %s\n", payload);

//       // send message to server when Connected
//       webSocket.sendTXT("Arduino connected");
//     }
//       break;
//     case WStype_TEXT:
//       Serial.write(payload[0]);

//       // send message to server
//       // webSocket.sendTXT("message here");
//       break;
//     case WStype_BIN:
//       Serial.printf("[WSc] get binary length: %u\n", length);
//       hexdump(payload, length);

//       // send data to server
//       // webSocket.sendBIN(payload, length);
//       break;
//         case WStype_PING:
//             // pong will be send automatically
//             // Serial.printf("[WSc] get ping\n");
//             // Serial.println("Hello Node.js");
//             break;
//         case WStype_PONG:
//             // answer to a ping we send
//             // webSocket.sendTXT("Hello Node.js");
//             // Serial.printf("[WSc] get pong\n");
//             break;
//     }

// }

// void loop() {
//     if(isConnected && Serial.available() > 0 ) {
//        int isSwitched = Serial.read();

//        if (isSwitched) {
//         webSocket.sendTXT(isSwitched);
//        }
//     };

//   webSocket.loop();
// }