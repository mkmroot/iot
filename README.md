# iot


---------------------
for nodemcu fetch the server using get api  and run accoding to the json
1.setup flask server run api1.py
  - pip install virtualenv
  - virtualenv venv
  - source ./venv/bin/activate
  - pip install Flask
  - python api1.py
    
2.upload the code on nodemcu (api_jeson_flask.ino)
  - add the wifi credentials
  - add the api
  - add arduino librery
      > ESP8266WiFi.h
      > ArduinoJson
