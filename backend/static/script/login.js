const httpRequest = new XMLHttpRequest();
function submit() {
    var name = document.getElementById('name').value
    var password = document.getElementById('password').value
    var hash = sha256(password)
    httpRequest.open("GET",  `localhost:5000/login_auth/?name=name&hash=hash`, false)
    httpRequest.setRequestHeader('Content-type', 'application/ecmascript');
    httpRequest.setRequestHeader('Access-Control-Allow-Origin', '*');
    httpRequest.send();
    if (httpRequest.responceText == "false") {
       document.write("user name or password is incorrect")
    }
    else{
       document.location.href="/"
    }
}