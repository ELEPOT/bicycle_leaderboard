const httpRequest = new XMLHttpRequest();
function submit() {
    var name = document.getElementById('name').value
    var password = document.getElementById('password').value
    var hash = sha256(password)

    if (http_get(`http://127.0.0.1:5000/login_auth?name=${name}&hash=${hash}`) === "False") {
        alert("使用者名稱或密碼錯誤")
    }
    else {
        setCookie("user", name)
        setCookie("token", hash)
        document.location.href="/"
    }
}