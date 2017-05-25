function btnAllBlackPerformed() {
    sendRequest("LEDnb=9C&R=00&G=00&B=00");
}
function btnSendPerformed() {
    sendRequest(createRequestColorForLed());
}
function sendRequest(text) {
    document.getElementById("kk").innerHTML = text;
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "pixel?" + text, true);
    xmlHttp.send();
}
function createRequestColorForLed() {
    var t = "LEDnb=";
    t = t + toHex(getRandomIntInclusive(0, 155));
    t = t + "&R=";
    t = t + toHex(getRandomIntInclusive(0, 255));
    t = t + "&G=";
    t = t + toHex(getRandomIntInclusive(0, 255));
    t = t + "&G=";
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
function clickButton(animation, light, cycle) {
	var request = new XMLHttpRequest();
	request.onreadystatechange = function() { 
        if (request.readyState == 4 && request.status == 200)
            callback(request.responseText);
    }
	request.open("GET", "pixel?animation=" + animation + "&light=" + light + "&cycle=" + cycle, true);
	request.send(null);
}
function get_action(form) {
	clickButton(form.animation.value,form.light.value,form.cycle.value );
}
