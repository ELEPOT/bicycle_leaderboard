let user = getCookie("user")
let token = getCookie("token")

let url = `https://bike.elepot.dev/login_auth?name=${user}&hash=${token}`
//把cookie裡的使用者名稱,卡號與雜湊密碼傳入後端做判斷
if(http_get(url) === "True") {//如果正確，改變HTML
    document.getElementById("login").remove()
    document.getElementById("reg").remove()
    console.log('login now')
    const text = document.createElement('p');
    text.textContent = `Login as ${getCookie("user")}`
    document.body.insertBefore(text, document.body.firstChild);
    const logout = document.createElement('button');
    logout.textContent = `登出`
    document.body.insertBefore(logout, document.body.firstChild);
    logout.addEventListener('click', () => {
        deleteCookie("user")
        deleteCookie("token")
        document.location.href="/"
    });

    let message = http_get(`http://127.0.0.1:5000/get_message?name=${user}`)
    //彈出後端訊息
    if (message !== "") {
        alert(message)
    }
}

//登入按鈕程式
function login() {
    console.log("login");
    document.location.href = "/login"
}
//註冊按鈕程式
function reg() {
    console.log("reg");
    document.location.href = "/register"
}