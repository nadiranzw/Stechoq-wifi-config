#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>

WiFiServer server(80);
WiFiManager wm;

String htmlHead = "<html>\n"
        "<head>\n"
            "<link href=\"https://cdnjs.cloudflare.com/ajax/libs/flowbite/2.3.0/flowbite.min.css\" rel=\"stylesheet\" />\n"
        "</head>";
        
String htmlBody = 
        "<body class=\"bg-gray-100 flex justify-center items-center\">\n"
            "<div class=\"mt-3 max-w-screen-lg \">\n"
              "<div class=\"flex flex-col items-center justify-center px-6 py-8 mx-auto md:h-screen lg:py-0\">\n"
                    "<img class=\" w-64 mb-10\" src=\"https://cdn.discordapp.com/attachments/1164780967274217542/1220589752420405358/INSENS_LOGO_1.png?ex=660f7dca&is=65fd08ca&hm=a87e6aac19d94a2e0119c3a46029166c55da272c8c400750d9e6ae3d4ad5f7f2&\" alt=\"logo\">\n"
                    "<div class=\"w-full bg-white rounded-lg shadow dark:border md:mt-0 sm:max-w-md xl:p-0 dark:bg-gray-800 dark:border0-gray-700\">\n"
                        "<div class=\"p-6 space-y-4 md:space-y-6 sm:p-8\">\n"
                            "<h1 class=\"text-xl text-center font-bold leading-tight tracking-tight text-gray-900 md:text-2xl dark:text-white\">Instalation NODEMCU PZEM</h1>\n"
                            "<form class=\"space-y-4 md:space-y-6\" action=\"#\">\n"
                                "<div>\n"
                                    "<label for=\"username\" class=\"block mb-2 text-sm font-medium text-gray-900 dark:text-white\">Username</label>\n"
                                    "<input type=\"username\" name=\"username\" id=\"username\" class=\"bg-gray-50 border border-gray-300 text-gray-900 sm:text-sm rounded-lg focus:ring-blue-600 focus:border-blue-600 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500\" placeholder=\"Username\" required>\n"
                                "</div>\n"
                                "<div>\n"
                                    "<label for=\"name\" class=\"slock mb-2 text-sm font-medium text-gray-900 dark:text-white\">Merek Mesin</label>\n"
                                    "<input type=\"name\" name=\"name\" id=\"name\" placeholder=\"Merek Mesin\" class=\"bg-gray-50 border border-gray-300 text-gray-900 sm:text-sm rounded-lg focus:ring-blue-600 focus:border-blue-600 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500\" required>\n"
                                "</div>\n"
                                "<div>\n"
                                    "<label for=\"email\" class=\"block mb-2 text-sm font-medium text-gray-900 dark:text-white\">Email</label>\n"
                                    "<input type=\"email\" name=\"email\" id=\"email\" class=\"bg-gray-50 border border-gray-300 text-gray-900 sm:text-sm rounded-lg focus:ring-blue-600 focus:border-blue-600 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500\" placeholder=\"name@gmail.com\" required>\n"
                                "</div>\n"
                                "<div>\n"
                                    "<label for=\"password\" class=\"block mb-2 text-sm font-medium text-gray-900 dark:text-white\">Password</label>\n"
                                    "<input type=\"password\" name=\"password\" id=\"password\" placeholder=\"••••••••\" class=\"bg-gray-50 border border-gray-300 text-gray-900 sm:text-sm rounded-lg focus:ring-blue-600 focus:border-blue-600 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500\" required>\n"
                                "</div>\n"
                                "<button type=\"submit\" class=\"w-full text-white bg-blue-600 hover:bg-blue-700 focus:ring-4 focus:outline-none focus:ring-blue-300 font-medium rounded-lg text-sm px-5 py-2.5 text-center dark:bg-blue-600 dark:hover:bg-blue-700 dark:focus:ring-blue-800\">Register</button>\n"
                            "</form>\n"
                        "</div>\n"
                    "</div>\n"
                "</div>\n"
            "</div>\n"
        "<script src=\"https://cdnjs.cloudflare.com/ajax/libs/flowbite/2.3.0/flowbite.min.js\"></script>\n"
        "</body>\n"
        "</html>";


void setup(){
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  bool res = wm.autoConnect("bebas", "12345");

  if (!res){
    Serial.println("Gagal koneksi");
  }
  else{
    Serial.print("Koneksi terhubung. IP Address: ");
    Serial.println(WiFi.localIP());
    server.begin();
  }
}

void loop(){
  WiFiClient client = server.available();
  char temp[2000];

  if (client){
    while (client.connected()){
      if (client.available()){
        String request = client.readStringUntil('\r');
        Serial.println(request);
        client.flush();

        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();
        client.println("<!DOCTYPE HTML>");
        client.println("<html>");
        client.println(htmlHead);
        client.println(htmlBody);
        break;
      }
    }
    // close the connection
    delay(1);
    client.stop();
  }
  // run WiFiManager's background task
  wm.process();
}