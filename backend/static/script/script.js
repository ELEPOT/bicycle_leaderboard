let user = getCookie("user")
let token = getCookie("token")

let url = `http://127.0.0.1:5000/login_auth?name=${user}&hash=${token}`

if(http_get(url) === "True") {
    document.getElementById("login").remove()
    document.getElementById("reg").remove()
    console.log('login now')
    const text = document.createElement('p');
    text.textContent = `Login as ${getCookie("user")}`
    document.body.insertBefore(text, document.body.firstChild);
    const logout = document.createElement('button');
    logout.textContent = `Logout`
    document.body.insertBefore(logout, document.body.firstChild);
    logout.addEventListener('click', () => {
        deleteCookie("user")
        deleteCookie("token")
        document.location.href="/"
    });
}

else {
    console.log(httpRequest.responseText)
}

console.log("start")
function login() {
    console.log("login");
    document.location.href="/login"
}

function reg() {
    console.log("reg");
    document.location.href = "/register"
}