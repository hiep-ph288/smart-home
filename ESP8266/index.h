extern String ledState; const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Smart Home</title>
  </head>

  <style type="text/css">
      * {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
      }
      body {
        font-family: Arial, Helvetica, sans-serif;
        /* background-color: #e4e1ff; */
        background-image: url("https://images.unsplash.com/photo-1600585154340-be6161a56a0c?ixlib=rb-4.0.3&ixid=MnwxMjA3fDB8MHxzZWFyY2h8MTF8fHNtYXJ0JTIwaG9tZXxlbnwwfHwwfHw%3D&w=1000&q=80");
        background-repeat: no-repeat;
        background-size: cover;
      }
      #bg {
        width: 90%;
        margin: 0 auto;
        /* box-shadow: 1px 1px 30px 20px rgb(178, 162, 203); */
      }
      #main {
        margin-top: 10px;
        width: 100%;
        height: 60px;
        background-image: linear-gradient(to right, #fd6935, #f83a5e);
        color: white;
        text-align: center;
        line-height: 60px;
        border-radius: 15px;
      }

      .room {
        margin-top: 10px;
        min-width: 350px;
        min-height: 200px;
        background-color: white;
        border: none;
        border-radius: 15px;
        padding: 20px;
        opacity: 0.9;
        transition: all 0.3s linear;
      }
      .room:hover {
        opacity: 1;
        transform: scale(1.05);
      }
      .container {
        display: grid;
        /* margin-top: 20px; */
        grid-template-columns: repeat(3, 1fr);
        gap: 20px;
      }
      /* .room:nth-child(1) {
        grid-column: 1/3;
         grid-row: 1/3;
      } */
      input {
        margin: 10px 0;
        height: 35px;
        border-radius: 10px;
        padding: 10px;
      }
      button {
        color: white;
        background: rgb(96, 9, 240);
        background: linear-gradient(to right, #fd6935, #f83a5e);
        border: none;
        padding: 10px;
        border-radius: 10px;
        transition: all 0.3s linear;
        margin: 0 10px;
      }
      button:before {
        height: 0%;
        width: 2px;
      }
      button:hover {
        box-shadow: 4px 4px 6px 0 rgba(255, 255, 255, 0.5),
          -4px -4px 6px 0 rgba(116, 125, 136, 0.5),
          inset -4px -4px 6px 0 rgba(255, 255, 255, 0.2),
          inset 4px 4px 6px 0 rgba(0, 0, 0, 0.4);
      }
      .content h1 {
        text-align: center;
        margin-bottom: 10px;
        border-radius: 15px;
        color: #eb032ebd;
        font-size: 30px;
        text-transform: uppercase;
      }
      .item {
        margin: 15px;
      }
      p {
        display: inline-block;

        font-weight: 600;
        font-size: 20px;
      }
      @media only screen and (max-width: 768px) {
        .room{
          padding: 10px;
          margin-top: 20px;
        }
        #main {
          position:fixed;
          top: 0;
          z-index: 10;
          margin: 0;
          border-radius: 0;
          width: 120%;
          left: -20;

        }
        .container {
         display: flex;
         flex-direction: column;
         font-size: 10px;
         margin: 40px 10px 0 10px;
        }
        #bg{
          width: 98%;
        }
        #main h1{
          font-size: 12px;
          color: white;
        }
      input {
        margin: 10px 0;
        height: 35px;
        border-radius: 10px;
        padding: 10px;
      }
      body {
        font-family: Arial, Helvetica, sans-serif;

        background-image: url("https://images.unsplash.com/photo-1661956602139-ec64991b8b16?ixlib=rb-4.0.3&ixid=MnwxMjA3fDF8MHxzZWFyY2h8MXx8Y29udGVudHxlbnwwfHwwfHw%3D&w=1000&q=80");
        background-repeat: no-repeat;
        background-size: cover;
      }
      .content{
        max-height: 200px;
        overflow: auto;
        overflow: -moz-scrollbars-none;
      -ms-overflow-style: none;

      }
      .content::-webkit-scrollbar{
        width: 0 !important;
    display: none;
      }
  </style>

  <body>
    <div id="bg">
      <div id="main">
        <h1>Giám sát và điều khiển nhà thông minh</h1>
      </div>
      <div class="container">
        <div class="room">
          <div class="content">
            <h1>Phòng Khách</h1>
            <div class="item">
              <p>Đặt nhiệt độ ( độ C )</p>
              <input
                type="number"
                id="username2"
                placeholder="Nhập nhiệt độ đặt"
                onkeyup="checkForm2()"
                onfocus="this.value=''"
              />
              <button type="button" onclick="sendData3(9)">SET TEMP</button>
            </div>
            <div class="item">
              <p>Nhiệt độ đặt ( độ C) :</p>

              <p id="result2">0</p>
            </div>
            <div class="item">
              <p>Nhiệt độ ( độ C) :</p>
              <p id="TEMPPKValue">0</p>
            </div>
            <div class="item">
              <p>Độ ẩm (%) :</p>
              <p id="HUMPKValue">0</p>
            </div>
            <div class="item">
              <p>Đèn :</p>
              <p id="LEDState"></p>
              <button type="button" onclick="sendData(1)">ON</button>
              <button type="button" onclick="sendData(0)">OFF</button>
            </div>
            <div class="item">
              <p>Quạt :</p>
              <p id="QUATStatePK"></p>
              <button type="button" onclick="sendData4PK(0)">ON</button>
              <button type="button" onclick="sendData4PK(1)">OFF</button>
            </div>
          </div>
        </div>
        <div class="room">
          <div class="content">
            <h1>Phòng Ngủ</h1>
            <div class="item">
              <p>Hẹn giờ mở / đóng rèm</p>
              <input
                type="text"
                id="username"
                placeholder="VD: 20:08"
                onkeyup="checkForm()"
                onfocus="this.value=''"
              />
              <button type="button" onclick="sendData1(9)">SET TIME</button>
            </div>
            <div class="item">
              <p>Đặt nhiệt độ ( độ C)</p>
              <input
                type="number"
                id="username1"
                placeholder="Đặt nhiệt độ"
                onkeyup="checkForm1()"
                onfocus="this.value=''"
              />
              <button type="button" onclick="sendData2(9)">SET TEMP</button>
            </div>
            <div class="item">
              <p>Thời gian hẹn:</p>

              <p id="result">0</p>
            </div>
            <div class="item">
              <p>Nhiệt độ đặt ( độ C) :</p>

              <p id="result1">0</p>
            </div>
            <div class="item">
              <p>Nhiệt độ ( độ C) :</p>
              <p id="TEMPPNValue">0</p>
            </div>
            <div class="item">
              <p>Độ ẩm (%) :</p>
              <p id="HUMPNValue">0</p>
            </div>
            <div class="item">
              <p>Đèn :</p>
              <p id="LEDStatePN"></p>
              <button type="button" onclick="sendDataPN(1)">ON</button>
              <button type="button" onclick="sendDataPN(0)">OFF</button>
            </div>
            <div class="item">
              <p>Quạt :</p>
              <p id="QUATState"></p>
              <button type="button" onclick="sendData4(0)">ON</button>
              <button type="button" onclick="sendData4(1)">OFF</button>
            </div>
          </div>
        </div>
        <div class="room">
          <div class="content">
            <h1>Phòng Bếp</h1>
            <div class="item">
              <p>Nồng độ khí gas %</p>
              <p id="GASValue">0</p>
            </div>
            <h1>Khu vườn</h1>
            <div class="item">
              <p>Độ ẩm đất %</p>
              <p id="doamdatvalue">0</p>
            </div>
            <div class="item">
              <p>Máy bơm :</p>
              <p id="statemaybom"></p>
              <button type="button" onclick="sendData4maybom(1)">ON</button>
              <button type="button" onclick="sendData4maybom(0)">OFF</button>
            </div>
          </div>
        </div>
        <div class="room">
          <div class="content">
            <h1>Khu vực cửa</h1>

            <div class="item">
              <p>Cửa chính :</p>
              <p id="ServoState"></p>
              <button type="button" onclick="sendDataCua(1)">ON</button>
              <button type="button" onclick="sendDataCua(0)">OFF</button>
            </div>
            <h1>Gara</h1>

            <div class="item">
              <p>Cửa gara :</p>
              <p id="servogarastate"></p>
              <button type="button" onclick="sendDataCuaGara(1)">ON</button>
              <button type="button" onclick="sendDataCuaGara(0)">OFF</button>
            </div>
          </div>
        </div>

        <div class="room">
          <div class="content">
            <h1>Nhà vệ sinh</h1>
            <div class="item">
              <p>Nhiệt độ ( độ C) :</p>
              <p id="TEMPWCValue">0</p>
            </div>
            <div class="item">
              <p>Độ ẩm (%) :</p>
              <p id="HUMWCValue">0</p>
            </div>
            <div class="item">
              <p>Quạt thông gió :</p>
              <p id="quatwcstate"></p>
              <button type="button" onclick="sendDataWc(1)">ON</button>
              <button type="button" onclick="sendDataWc(0)">OFF</button>
            </div>
          </div>
        </div>
      </div>
    </div>

    <script>
      /* điều khiển led bằng nút nhấn */
      function sendData(led) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("LEDState").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "setLED?LEDstate=" + led, true);
        xhttp.send();
      }
      // dieu khien cua chinh
      function sendDataCua(led) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            // document.getElementById("ServoState").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "setServo?ServoState=" + led, true);
        xhttp.send();
        // if(led==1){
        //   document.getElementById("ServoState").innerHTML = "OPEN";
        // }
        // else if(led==0){
        //   document.getElementById("ServoState").innerHTML = "CLOSE";
        // }
      }
      // dieu khien cua gara
      function sendDataCuaGara(led) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("servogarastate").innerHTML =
              this.responseText;
          }
        };
        xhttp.open("GET", "setservogara?servogarastate=" + led, true);
        xhttp.send();
      }
      // dieu khien quat wc
      function sendDataWc(led) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("quatwcstate").innerHTML =
              this.responseText;
          }
        };
        xhttp.open("GET", "setquatwc?quatwcstate=" + led, true);
        xhttp.send();
      }
      // điều khiển led phòng ngủ
      function sendDataPN(led) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("LEDStatePN").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "setLEDPN?LEDstatePN=" + led, true);
        xhttp.send();
      }

      /* điều khiển quạt bằng nút nhấn */
      function sendData4(QUAT) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("QUATState").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "setQUAT?QUATstate=" + QUAT, true);
        xhttp.send();
      }
      /* điều khiển maybom nhấn */
      function sendData4maybom(QUAT) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("statemaybom").innerHTML =
              this.responseText;
          }
        };
        xhttp.open("GET", "setmaybom?statemaybom=" + QUAT, true);
        xhttp.send();
      }
      /* điều khiển quạt bằng nút nhấn */
      function sendData4PK(QUAT) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("QUATStatePK").innerHTML =
              this.responseText;
          }
        };
        xhttp.open("GET", "setQUATPK?QUATstatePK=" + QUAT, true);
        xhttp.send();
      }

      /* gửi hẹn giờ */
      function sendData1(timer) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("result").innerHTML = this.responseText;
          }
        };
        timer = document.getElementById("username").value;
        xhttp.open("GET", "setTIME?result=" + timer, true);
        xhttp.send();
      }

      /* gửi đặt nhiệt độ điều hòa */
      function sendData2(temp) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("result1").innerHTML = this.responseText;
          }
        };
        temp = document.getElementById("username1").value;
        xhttp.open("GET", "setTEMP?result1=" + temp, true);
        xhttp.send();
      }

      /* gửi đặt nhiệt độ điều hòa PK */
      function sendData3(tempPK) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("result2").innerHTML = this.responseText;
          }
        };
        tempPK = document.getElementById("username2").value;
        xhttp.open("GET", "setTEMPPK?result2=" + tempPK, true);
        xhttp.send();
      }

      /* gửi các hàm gọi dữ liệu để nhận sau mỗi 2s */
      setInterval(function () {
        getData();
        getData1(); //led
        getData1PN();
        getData2(); // quạt
        getData2PK(); // quạt
        getData3();
        getData4();
        getData5();
        getData6();
        getData7();
        getData8();
        getData1Servo();
        getDatadoamdat();
      }, 250);

      /* gọi dữ liệu của nhiệt độ phòng ngủ */
      function getData() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("TEMPPNValue").innerHTML =
              this.responseText;
          }
        };
        xhttp.open("GET", "readTEMPPN", true);
        xhttp.send();
      }
      /* gọi dữ liệu của độ ẩm đất */
      function getDatadoamdat() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("doamdatvalue").innerHTML =
              this.responseText;
          }
        };
        xhttp.open("GET", "readdoamdat", true);
        xhttp.send();
      }

      /* gọi dữ liệu của độ ẩm phòng ngủ */
      function getData3() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("HUMPNValue").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "readHUMPN", true);
        xhttp.send();
      }

      /* gọi dữ liệu của nhiệt độ phòng khách */
      function getData4() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("TEMPPKValue").innerHTML =
              this.responseText;
          }
        };
        xhttp.open("GET", "readTEMPPK", true);
        xhttp.send();
      }

      /* gọi dữ liệu của độ ẩm phòng khách*/
      function getData5() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("HUMPKValue").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "readHUMPK", true);
        xhttp.send();
      }

      /* gọi dữ liệu của GAS */
      function getData6() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("GASValue").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "readGAS", true);
        xhttp.send();
      }

      /* gọi dữ liệu của nhiệt độ nhà vệ sinh */
      function getData7() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("TEMPWCValue").innerHTML =
              this.responseText;
          }
        };
        xhttp.open("GET", "readTEMPWC", true);
        xhttp.send();
      }

      /* gọi dữ liệu của độ ẩm nhà vệ sinh */
      function getData8() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("HUMWCValue").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "readHUMWC", true);
        xhttp.send();
      }

      /* gọi dữ liệu của led hiện tại */
      function getData1() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("LEDState").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "setLEDstt", true);
        xhttp.send();
      }
      /* gọi dữ liệu của servo hiện tại */
      function getData1Servo() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("ServoState").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "setServostt", true);
        xhttp.send();
      }
      /* gọi dữ liệu của led PN hiện tại */
      function getData1PN() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("LEDStatePN").innerHTML = this.responseText;
          }
        };
        // cap nhap trang thai cua
        xhttp.open("GET", "setLEDsttPN", true);
        xhttp.send();
      }

      /* gọi dữ liệu của quạt hiện tại là phòng ngủ */
      function getData2() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("QUATState").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "setQUATstt", true);
        xhttp.send();
      }
      // gửi dữ liệu quạt là phòng khách
      function getData2PK() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("QUATStatePK").innerHTML =
              this.responseText;
          }
        };
        xhttp.open("GET", "setQUATsttPK", true);
        xhttp.send();
      }

      /* lấy dữ liệu từ thanh nhập cho hẹn giờ */
      function checkForm() {
        const username = document.getElementById("username").value;
        document.getElementById("result").innerText = username;
      }

      /* lấy dữ liệu từ thanh nhập cho điều hòa */
      function checkForm1() {
        const username1 = document.getElementById("username1").value;
        document.getElementById("result1").innerText = username1;
      }

      /* lấy dữ liệu từ thanh nhập cho điều hòa PK */
      function checkForm2() {
        const username2 = document.getElementById("username2").value;
        document.getElementById("result2").innerText = username2;
      }
    </script>
  </body>
</html>

)=====";
