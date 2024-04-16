//登入頁面的送出程式
function submit() {
    var name = document.getElementById('name').value//獲取使用者輸入之名稱
    var password = document.getElementById('password').value//獲取使用者輸入之密碼
    var hash = sha256(password)//將密碼轉換成雜湊值

    //把使用者名稱與雜湊密碼傳入後端做判斷
    if (http_get(`https://bike.elepot.dev/login_auth?name=${name}&hash=${hash}`) === "True") {
        //如果成立，將使用者名稱與token(雜湊密碼)加入cookie，將使用者導回首頁
        setCookie("user", name)
        setCookie("token", hash)
        document.location.href="/"
    }
    else {
        //如果不成立，跳出提示詞
        alert("使用者名稱或密碼錯誤")
    }
}