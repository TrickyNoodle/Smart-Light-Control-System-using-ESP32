String html= R"rawliteral(
<html>
<head>
    <title>Smart Light Control Hub</title>
    <style>
        .info{
            margin-top: 0px;
            font-size: inherit;
            text-align: center;
            display: none;
        }
        #manuali{
            display:block;
        }
        hr{
            margin-top: 30px;
            margin-inline: 10px;
        }
        body{
            font-family: 'Trebuchet MS', 'Lucida Sans Unicode', 'Lucida Grande', 'Lucida Sans', Arial, sans-serif;
            background-color: slategrey;
            
        }
        h1{
            text-align: center;
        }
        .modes{
            text-align: center;
            font-size: 20px;
        }
        #modeselect{
            font-family: inherit;
            box-shadow: 0px 5px 5px rgba(0, 0, 0, 0.355);
            padding-top:15px;
            padding-inline: 45px;
            padding-bottom: 15px;
            font-size:20px;
            border-radius: 50px;
            transition: ease 0.3s;
            background-color: lightgray;
        }
        #modeselect:hover{
            box-shadow: 0px 7px 7px rgba(0, 0, 0, 0.5);
        }
        #manual{
            display: block;
            button{
                font-family: inherit;
                font-size: inherit;
                padding:15px;
                border-radius:10px;
                background-color: lightgray;
                margin:5px;
                width:30%;
                padding-top:2%;
                padding-bottom:2%;
                box-shadow: 0px 5px 5px rgba(0, 0, 0, 0.325);
                transition: ease 0.3s;
            }
            button:hover{
                box-shadow: 0px 10px 10px rgba(0, 0, 0, 0.5);
                padding:3%;
                background-color: darkgray;
            }
            button:active{
                box-shadow:none;
                margin-top:10px;
                margin-bottom: 10px;
                background-color: gray;
            }
        }
        .divs{
            display: none;
            font-size: 20px;
            text-align:center;
        }
        #timermode{
            font-family: inherit;
            #timer{ 
                font-family: inherit;
                height:7%;
                width:30%;
                padding: 10px;
                font-size: inherit;
                border-radius: 15px;
                margin-bottom: 10px;
                background-color: lightgrey;
                text-align: center;
            }
            button{
                font-family: inherit;
                width:30%;
                padding:20px;
                border-radius: 50px;
                background-color: lightsalmon;
                font-size:inherit;
                box-shadow: 0px 5px 5px rgba(0, 0, 0, 0.325);
                transition: ease 0.3s;
            }
            button:hover{
                background-color: rgb(253, 137, 91);
                box-shadow: 0px 10px 10px rgba(0, 0, 0, 0.5);
            }
            button:active{
                box-shadow:none;
                margin-top:5px;
            }
        }
        #auto{
            p{
                margin: 30px;
                font-size: 30px;
            }
            .progress-bar{
                margin-inline: 10%;
                background-color: #f3f3f3;
                border-radius: 50px;
                overflow: hidden;
                #sensor1{
                    background-color: lightpink;
                    width:0%;
                    border-radius: 50px;
                }
                #sensor2{
                    background-color: lightpink;
                    width:0%;
                    border-radius: 50px;
                }
            }
        }
        .fooot{
            margin:10px;
        }
    </style>
</head>
<body>
    <h1>Smart Light Control Hub</h1>
    <div class='modes'>
        <h3>Select Mode:</h3>
        <select id='modeSelect' onchange='changeMode()'>
            <option value='0'>Manual Mode</option>
            <option value='1'>Timer Mode</option>
            <option value='2'>Auto Mode</option>
        </select></div>
        <hr>
    <div id='manual' class='divs'>
        <h2>-- Manual Mode --</h2>
        <button onclick='toggleLED(0)'>Toggle Relay 1</button>
        <br><button onclick='toggleLED(1)'>Toggle Relay 2</button>
        <br><button onclick='toggleLED(2)'>Toggle Relay 3</button>
        <br><button onclick='toggleLED(3)'>Toggle Relay 4</button>
    </div>
    
    <div id='timermode' class='divs'>
        <h2>-- Timer Mode --</h2>
        <input type='number' id='timer' placeholder='Enter timer in seconds' />
        <br><button onclick='startTimer()'>Start Timer</button>
    </div>
    
    <div id='auto' class='divs'>
        <h2>-- Auto Mode --</h2>
        <p>LDR Sensor Value </p>
        <div class='progress-bar'>
            <div id='sensor1'> 0</div>
        </div>
        <p>Ultrasonic Sensor Value </p>
        <div class='progress-bar'>
            <div id='sensor2'>0</div>
        </div>
        <h3>Lights Powered <span id='state'>Off</span></h3>
    </div>

    <script>
        const selectElement = document.getElementById('modeSelect');
        const divs = document.querySelectorAll('.divs');
        const info=document.querySelectorAll('.info');
        // Event listener for when the select option changes
        selectElement.addEventListener('change', function() {
            // Hide all divs
            divs.forEach(div => div.style.display = 'none');
            // Show the selected div based on the value of the selected option
            if (selectElement.value === '0') {
                document.getElementById('manual').style.display = 'block';
                document.getElementById('manuali').style.display = 'block';
                document.getElementById('timeri').style.display = 'none';
                document.getElementById('autoi').style.display = 'none';
            } else if (selectElement.value === '1') {
                document.getElementById('timermode').style.display = 'block';
                document.getElementById('manuali').style.display = 'none';
                document.getElementById('timeri').style.display = 'block';
                document.getElementById('autoi').style.display = 'none';
            } else if (selectElement.value === '2') {
                document.getElementById('auto').style.display = 'block';
                document.getElementById('manuali').style.display = 'none';
                document.getElementById('timeri').style.display = 'none';
                document.getElementById('autoi').style.display = 'block';
            }
        });

        function changeMode() {
            let mode = document.getElementById('modeSelect').value;
            fetch(`/changeMode?mode=${mode}`);
        }
        
        function toggleLED(n) {
            fetch('/toggleLED?r=' + n);
        }
        
        function startTimer() {
            var timer = document.getElementById('timer').value;
            fetch('/startTimer?time=' + timer);
        }
        setInterval(function() {
            fetch('/getSensorData')
                .then(response => response.json())
                .then(data => {
                    document.getElementById('modeSelect').value=data.mode;
                    document.getElementById('sensor1').innerText = data.sensor1;
                    document.getElementById('sensor2').innerText = data.sensor2;
                    document.getElementById('state').innerText=data.state;
                    if(data.state == "ON"){
                        document.getElementById('state').style.color='green';
                    }
                    else{
                        document.getElementById('state').style.color='red';
                    }
                    document.getElementById('sensor1').style.width=(data.sensor1/4095)*100 + '%';
                    document.getElementById('sensor1').textContent=Math.round((data.sensor1/4095)*100)+'%';
                    document.getElementById('sensor2').style.width=(data.sensor2/400)*100 + '%';
                    document.getElementById('sensor2').textContent=Math.round((data.sensor2/400)*100) +'cm';
                });
        },3000);
    </script>
</body>
<footer>
    <hr class='fooot'>
    <p class='info' id='manuali'> &#x1F6C8; In this Mode turn on or off specefic relay controlled devices using buttons given above!</p>
    <p class='info' id='timeri'>&#x1F6C8; Set a Timer in Seconds and hit the start timer button,the relay controlled devices will be kept on for the said time</p>
    <p class='info' id='autoi'>&#x1F6C8; Lights will be turned on or off based on sensor values,they are kept on if suffecient light is not found in the room or the if the ultrasonic sensor detects a change in distance(meaning theres some movement)</p>
    </script>
</footer>
</html>
)rawliteral";

String wifi= R"rawliteral(
     <html>
    <head>
        <title>WiFi Credentials</title>
        <style>
            body{
                margin-top: 12.5%;
                font-family: Arial, Helvetica, sans-serif;
            }
            h1{
                text-align: center;
                text-decoration-line: underline;
            }
            p{
                font-size:18px;
                margin: 0px;
                text-align: center;
            }
            form{
                font-size:20px;
                margin-top: 25px;
                text-align: center;
            }
            input{
                font-size: 18px;
                margin: 5px;
            }
            .connect{
                font-family: Arial, Helvetica, sans-serif;
                border: none;
                font-size: 18px;
                background-color: rgb(0, 255, 0);
                color: black;
                width: 30%;
                padding-top: 10px;
                padding-bottom: 10px;
                border-radius: 10px;
                cursor: pointer;
                transition: ease 0.3s;
                box-shadow: 0px 5px 5px rgba(0, 0, 0, 0.325);
            }
            .put{
                font-family: Arial, Helvetica, sans-serif;
                padding-top: 10px;
                padding-bottom: 10px;
                width:30%;
                border-radius: 50px;
                padding-inline: 10px;
            }
            .connect:hover{
                box-shadow: 0px 5px 5px rgba(0, 0, 0, 0.5);
            }
            .connect:active{
                margin-top: 10px;
                box-shadow: none;
            }
        </style>
    </head>
    <body>
        <h1>Connect ESP32 to a WiFi Network</h1>
        <p>Please Enter a Wifi name and password</p>
        <p>(If Wifi is open network simply put empty password)</p>
        <form action='/wifi' method='POST'>
            <label>SSID: </label><br><input placeholder="Wifi Name" class='put' type='text' name='ssid'><br>
            <label>Password: </label><br><input placeholder="Wifi Password" class='put'type='password' name='pass'><br>
            <input class='connect' type='submit' value='Connect'>
        </form>
    </body>
    </html>
    )rawliteral";