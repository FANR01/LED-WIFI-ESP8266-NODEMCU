const char* html_page = R"====(
<!DOCTYPE html>
<html>
<head>
  <title>Control LED</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="/style.css">
  <script>
    function sendCmd(cmd) {
      fetch('/' + cmd);
    }
  </script>
</head>
<body>
  <h2>Control LED via WiFi</h2>
  <button onclick="sendCmd('ON')">HIDUPKAN</button>
  <button onclick="sendCmd('OFF')">MATIKAN</button>
</body>
</html>
)=====";
