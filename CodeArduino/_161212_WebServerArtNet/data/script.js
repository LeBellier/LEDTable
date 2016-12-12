function btnAllBlackPerformed() {
    sendRequest("9C000000");
}
function btnSendPerformed() {
    sendRequest(createRequestColorForLed());
}
function sendRequest(text) {
    document.getElementById("kk").innerHTML = text;
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function () {
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
            var chiffres = "0123456789ABCDEF";
            var ledNb = xmlHttp.responseText.substr(1, 2);
            var color = xmlHttp.responseText.substr(3, 7);
            document.getElementById("led" + ledNb).setAttribute("style", "background-color: " + color + ";");
            document.getElementById("led" + ledNb).innerHTML = color;
        }
    };
    xmlHttp.open("GET", "pixel_random=" + text, true);
    xmlHttp.send();
}
function createRequestColorForLed() {
    var t = "";
    t = t + toHex(getRandomIntInclusive(0, 155));
    t = t + toHex(getRandomIntInclusive(0, 255));
    t = t + toHex(getRandomIntInclusive(0, 255));
    t = t + toHex(getRandomIntInclusive(0, 255));
    return t;
}
function getRandomIntInclusive(min, max) {
    min = Math.ceil(min);
    max = Math.floor(max);
    return Math.floor(Math.random() * (max - min + 1)) + min;
}
function toHex(number) {
    var chiffres = "0123456789ABCDEF";
    var result = "";
    result = result + chiffres.charAt(number / 16);
    result = result + chiffres.charAt(number % 16);
    return result;
}