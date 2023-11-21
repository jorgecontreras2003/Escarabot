const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, user-scalable=no" />
    <meta charset="UTF-8">
    <title>Motor Control</title>
  </head>
  <style>
    .button {
      border: "black";
      color: rgb(0, 0, 0);
      padding: 20px 35px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 15px;
      margin: 2px 2px;
      cursor: pointer;
    }
    
    .button1 {background-color: #65e23f;}
    .button2 {background-color: #ffee00;}
    .button3 {background-color: #00fff2;} 
    .button4 {background-color: #d47b15;}
    .button5 {background-color: #ff0000;}
    .button6 {background-color: #002fff;}
    </style>
  <body>
    <h1>Motor Velocity Control</h1>

    <div class="button">
      <br>
      <button type="button" class='button button1' onClick="sendRequest('http://192.168.4.1/Button?val=1')" >ADELANTE</button>
      <br>    
      <button type="button" class='button button2' onClick="sendRequest('http://192.168.4.1/Button?val=2')">IZQUIERDA</button>
      <button type="button" class='button button2' onClick="sendRequest('http://192.168.4.1/Button?val=3')">DERECHA</button>
      <br>
      <button type="button" class='button button3' onClick="sendRequest('http://192.168.4.1/Button?val=4')">ATRAS</button>
      <br>
      <button type="button" class='button button5' onClick="sendRequest('http://192.168.4.1/Button?val=5')">STOP</button>
      <br>
      
    </div>
    
    

    <script>
      function sendRequest(url) {
			  var xhr = new XMLHttpRequest();
			  xhr.open("GET", url, true);
			  xhr.send();
        xhr.timeout = 100;
		  }
    
    </script>
  </body>
</html>




)=====";