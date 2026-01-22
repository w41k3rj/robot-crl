#include <Arduino.h>
  #include <WiFi.h>
  #include <WebServer.h>
  #include <ESP32Servo.h>
  #include <Ultrasonic.h>
  #include <ESPAsyncWebServer.h>
  
  const char* ssid = "W41K3RJ";
  const char* password = "HUMANOIDROBOT.";
  
  WebServer server(80);
  
  Servo headServo;
  Servo leftHandServo;
  Servo rightHandServo;
  Servo right2Servo;
  
  const int trigPin = 5;
  const int echoPin = 18;
  Ultrasonic ultrasonic(trigPin, echoPin);
  
  const int leftMotorForward = 12;
  const int leftMotorBackward = 13;
  const int rightMotorForward = 27;
  const int rightMotorBackward = 26;
  
  int motorSpeed = 300; // Initial speed (adjust as needed)
  
  void handleRoot() {
    server.send(200, "text/html", R"rawliteral(
  
    <!DOCTYPE html>
    <html>
      <head>
        <title>JUNIOR HUMANOID ROBOT CONTROL SYSTEM</title>
        <!-- Include Bootstrap CSS -->
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH" crossorigin="anonymous">
        <!-- Custom CSS -->
        <style>
          button {
              padding: 20px 20px;
              font-size: 16px;
              margin: 10px;
              border: none;
              border-radius: 100px;
          }
      </style>
      </head>
      <body>
        <div class="container-fluid col-lg-10 col-md-10 col-sm-12 border-primary" style="width:80%;margin: 0px auto;padding: 0px;">  
           <div class="card col">
          <center><h5 style="color: blue;">W41K3RJ ROBOT CONTROL  </h5></center>
          <center><h5 style="color: blue;">JUNIOR WIFI ROBOT CONTROL </h5></center>
  
          <table align="center" style="border-collapse: collapse;padding: 0px;" border="0">
            <tr height="30px">
              <td></td>
              <td><button id="forward" >Move Forward</button></td>
              <td></td>
            </tr>
  
            <tr height="30px">
              <td><button id="left">Move Left</button></td>
              <td><center><p id="message"></p></center></td>
              <td><button id="right">Move Right</button></td>
            </tr>
  
            <tr height="30px">
              <td></td>
              <td><button id="backward" >Move Backward</button></td>
              <td></td>
            </tr>
          
         
        </table>
        </div>
    
          <!-- Servo control sliders -->
          <div class="card col" style="margin: 30px auto;padding: 10px;">
            <label for="servo1">HEAD</label>
              <input type="range" id="servo1" name="servo1" min="0" max="180" oninput="moveServo(1, this.value)"><br>
  
            <label for="servo2">R HAND</label>
              <input type="range" id="servo2" name="servo2" min="0" max="180" oninput="moveServo(2, this.value)">
            <br>
            <label for="servo3">L HAND </label>
              <input type="range" id="servo3" name="servo3" min="0" max="180" oninput="moveServo(3, this.value)"><br>
  
            <label for="servo4">B ELBOW </label>
              <input type="range" id="servo4" name="servo4" min="0" max="180" oninput="moveServo(4, this.value)">
          </div>
        </div>
  
  
      <script>
        let forwardInterval;
        let backwardInterval;
        let leftInterval;
        let rightInterval;

        // function move(command) {console.log("Command:", command);}

  //  -----------------------------  SENDING COMMAND TO ARDUINO VIA HTTP REQUEST------------------------------------------
         function move(direction){let API = fetch(`/command?cmd=${direction}`); return API;console.log("Command:", API);}
  //  -----------------------------  END  HTTP REQUEST---------------------------------------------------------------------

        function moveForward() {move('10');document.getElementById('message').innerHTML = "ON";}

        function moveBackward() {move('20');document.getElementById('message').innerHTML = "ON";}

        function moveLeft() {move('400');document.getElementById('message').innerHTML = "ON";}

        function moveRight() {move('500');document.getElementById('message').innerHTML = "ON";}

  // --------------------------------------------TIME INTERVAL FOR EACH BUTTON----------------------------------------------------
        function startMovingForward() {forwardInterval = setInterval(moveForward, 50);}
        function stopMovingForward() {clearInterval(forwardInterval); document.getElementById('message').innerHTML = "OFF";}

        function startMovingBackward() {backwardInterval = setInterval(moveBackward, 50);}
        function stopMovingBackward() {clearInterval(backwardInterval);document.getElementById('message').innerHTML = "OFF";}

        function startMovingLeft() {leftInterval = setInterval(moveLeft, 50);}
        function stopMovingLeft() {clearInterval(leftInterval);document.getElementById('message').innerHTML = "OFF";}

        function startMovingRight() {rightInterval = setInterval(moveRight, 50);}
        function stopMovingRight() {clearInterval(rightInterval);document.getElementById('message').innerHTML = "OFF";}
        // ------------------------------------------------------------------------------------------------------------
        
  // ============================ Forward button event listeners==========================
        document.getElementById('forward').addEventListener('mousedown', startMovingForward);
        document.getElementById('forward').addEventListener('mouseup', stopMovingForward);
        document.getElementById('forward').addEventListener('mouseleave', stopMovingForward);
        document.getElementById('forward').addEventListener('touchstart', function(event) {
            event.preventDefault();
            startMovingForward();
        });
        document.getElementById('forward').addEventListener('touchend', function(event) {
            event.preventDefault();
            stopMovingForward();
        });
   // ============================ Forward button event listeners==========================


    // =============================  Backward button event listeners  ==========================
        document.getElementById('backward').addEventListener('mousedown', startMovingBackward);
        document.getElementById('backward').addEventListener('mouseup', stopMovingBackward);
        document.getElementById('backward').addEventListener('mouseleave', stopMovingBackward);
        document.getElementById('backward').addEventListener('touchstart', function(event) {
            event.preventDefault();
            startMovingBackward();
        });
        document.getElementById('backward').addEventListener('touchend', function(event) {
            event.preventDefault();
            stopMovingBackward();
        });
    // ============================= END  Backward button event listeners  ==========================

     // =============================  Left button event listeners ==============================
        document.getElementById('left').addEventListener('mousedown', startMovingLeft);
        document.getElementById('left').addEventListener('mouseup', stopMovingLeft);
        document.getElementById('left').addEventListener('mouseleave', stopMovingLeft);
        document.getElementById('left').addEventListener('touchstart', function(event) {
            event.preventDefault();
            startMovingLeft();
        });
        document.getElementById('left').addEventListener('touchend', function(event) {
            event.preventDefault();
            stopMovingLeft();
        });
     // =============================  END LEFT  button event listeners ==============================

    // =============================  Right button event listeners ================================
        document.getElementById('right').addEventListener('mousedown', startMovingRight);
        document.getElementById('right').addEventListener('mouseup', stopMovingRight);
        document.getElementById('right').addEventListener('mouseleave', stopMovingRight);
        document.getElementById('right').addEventListener('touchstart', function(event) {
            event.preventDefault();
            startMovingRight();
        });
        document.getElementById('right').addEventListener('touchend', function(event) {
            event.preventDefault();
            stopMovingRight();
        });
    // =============================END  Right button event listeners ================================



        // // Event listeners for control buttons
        // document.getElementById('front').addEventListener('click', function() {
        //   move(10); // Send command to move forward
        // });
      
        // document.getElementById('back').addEventListener('click', function() {
        //   move(20); // Send command to move backward
        // });
      
        // document.getElementById('left').addEventListener('click', function() {
        //   move(400); // Send command to move right
        // });
      
        // document.getElementById('right').addEventListener('click', function() {
        //   move(500); // Send command to move left
        // });
      
        // document.getElementById('stop').addEventListener('click', function() {
        //   move(null); // Stop all motors
        // });
      

  
  // ---------------------------START SERVO SLIDERS SCRIPT---------------------------
        document.getElementById("servo1").addEventListener("input", function() {
            moveServoValue("H", this.value);
        });
  
        document.getElementById("servo2").addEventListener("input", function() {
            moveServoValue("LH", this.value);
        });
  
        document.getElementById("servo3").addEventListener("input", function() {
            moveServoValue("RH", this.value);
        });
  
        document.getElementById("servo4").addEventListener("input", function() {
            moveServoValue("R2", this.value);
        });
  
        function moveServo(command) {
            fetch(`/command?cmd=${command}`);
        }
  
        function moveServoValue(servo, value) {
            fetch(`/servo?servo=${servo}&value=${value}`);
        }
  // ---------------------------END SERVO SLIDERS SCRIPT---------------------------
  
      </script>
      
     
    </body>
  </html>
    )rawliteral");
  }
  
  void stopAllMotors() {
    digitalWrite(leftMotorForward, LOW);
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorBackward, LOW);
  }
  
  void handleCommand() {
    String cmd = server.arg("cmd");
    int command = cmd.toInt(); // Convert cmd to an integer
  
    Serial.print("Command received: ");
    Serial.println(cmd); // Display the value of cmd in the serial monitor
  
    if (command == 10) {
      // Move forward
      digitalWrite(leftMotorBackward, LOW);  // Ensure backward is off
      digitalWrite(rightMotorBackward, LOW); // Ensure backward is off
      digitalWrite(leftMotorForward, HIGH);  // Move forward
      digitalWrite(rightMotorForward, HIGH); // Move forward
    } else if (command == 20) {
      // Move backward
      digitalWrite(leftMotorForward, LOW);   // Ensure forward is off
      digitalWrite(rightMotorForward, LOW);  // Ensure forward is off
      digitalWrite(leftMotorBackward, HIGH); // Move backward
      digitalWrite(rightMotorBackward, HIGH);// Move backward
    } else if (command == 400) {
      // Move right
      digitalWrite(leftMotorForward, HIGH);  // Left motor forward
      digitalWrite(rightMotorForward, LOW);  // Right motor stop
      digitalWrite(leftMotorBackward, LOW);
      digitalWrite(rightMotorBackward, LOW);
    } else if (command == 500) {
      // Move left
      digitalWrite(leftMotorForward, LOW);   // Left motor stop
      digitalWrite(rightMotorForward, HIGH); // Right motor forward
      digitalWrite(leftMotorBackward, LOW);
      digitalWrite(rightMotorBackward, LOW);
    } else {
      // Invalid command, stop all motors
      stopAllMotors();
    }
    
    server.send(200, "text/plain", "OK");
  }
  
  // --------------------------------------------START SERVO SLIDERS CONFIGURATIONS---------------------------------------
  void handleServo() {
    String servo = server.arg("servo");
    int value = server.arg("value").toInt();
    if (servo == "H") {
      headServo.write(value);
    } else if (servo == "LH") {
      leftHandServo.write(value);
    } else if (servo == "RH") {
      rightHandServo.write(value);
    } else if (servo == "R2") {
      right2Servo.write(value);
    }
    server.send(200, "text/plain", "OK");
  }
  
  void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
  
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
  
    server.on("/", handleRoot);
    server.on("/command", handleCommand);
    server.on("/servo", handleServo);
    server.begin();
  
    pinMode(leftMotorForward, OUTPUT);
    pinMode(leftMotorBackward, OUTPUT);
    pinMode(rightMotorForward, OUTPUT);
    pinMode(rightMotorBackward, OUTPUT);
  
    headServo.attach(14);
    leftHandServo.attach(33);
    rightHandServo.attach(32);
    right2Servo.attach(25);
  }
  
  void loop() {
    server.handleClient();
    int distance = ultrasonic.read();
    if (distance <= 10) {
      digitalWrite(leftMotorForward, LOW);
      digitalWrite(rightMotorForward, LOW);
      digitalWrite(leftMotorBackward, LOW);
      digitalWrite(rightMotorBackward, LOW);
    }
  }
  // -------------------- END SERVO SLIDERS CONFIGURATIONS -------------------------
