# iot

---------------------
1. For offline control, upload this file on nodemcu
        esp8266_offline_ctrl.ino
~                                 

---------------------
For nodemcu fetch the server using get api  and run accoding to the json
setup:
1. Setup flask server run api1.py
  - pip install virtualenv
  - virtualenv venv
  - source ./venv/bin/activate
  - pip install Flask
  - python api1.py
    
2. Upload the code on nodemcu (api_jeson_flask.ino)
  - add the wifi credentials
  - add the api
  - add arduino librery
       ESP8266WiFi
       ArduinoJson

3. Data save in file by hitting api
	data.json  

---------------------
operation:
server IP put in Python file (api1.py)
active venv
run flask file
1. To check API server: curl <server IP>:5000 
 
{
  "message": "Welcome to the Flask API!"
}

2. To check the saved data: curl http://192.168.0.15:5000/api/data

{
  "age": 30,
  "job": "Developer",
  "name": "John Doe"
}

3. To insert new data: curl -X POST http://192.168.0.15:5000/api/data -H "Content-Type: application/json" -d '{"name": "Alice", "age": 25}'

{
  "message": "Data received successfully",
  "received_data": {
    "age": 25,
    "name": "Alice"
  }
}

------------------------------------------------

1. Node mcu file --
	api_json_flask_fullpin 

2. pip install flask-cors
   app2.py

3. apache html-- sunil_index.html
curl command:
curl -X POST http://192.168.0.15:5000/api/data -H "Content-Type: application/json" -d '{"Pin0": "OFF", "Pin1": "OFF", "Pin2": "OFF","Pin3": "OFF","Pin4": "OFF", "Pin5": "OFF", "Pin6": "OFF","Pin7": "OFF", "Pin8": "OFF"}'

