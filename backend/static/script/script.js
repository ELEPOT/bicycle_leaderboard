const httpRequest = new XMLHttpRequest();
var cookie = document.cookie.split(";")
httpRequest.open("GET",  `http://127.0.0.1:5000/check?name=${cookie[0].split("=")[1]}&token=${cookie[1].split("=")[1]}`, false)
httpRequest.setRequestHeader('Content-type', 'application/ecmascript');
httpRequest.setRequestHeader('Access-Control-Allow-Origin', '*');
httpRequest.send();
if(httpRequest.responseText == "True") {
    document.getElementById("login").remove()
    document.getElementById("reg").remove()
    console.log('login now')
    const text = document.createElement('p');
    text.textContent = `Login as ${cookie[0].split("=")[1]}`
    document.body.insertBefore(text, document.body.firstChild);
    const logout = document.createElement('button');
    logout.textContent = `Logout`
    document.body.insertBefore(logout, document.body.firstChild);
}
else{
    console.log("Faild")
}

console.log("start")
function login() {
    console.log("login");
    document.location.href="/login"
}

function reg(RFID) {
    console.log("reg");
}