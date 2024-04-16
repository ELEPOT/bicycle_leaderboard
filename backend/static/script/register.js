//註冊頁面的送出程式
function submit() {
    var name = document.getElementById('name').value//獲取使用者輸入之名稱
    var password = document.getElementById('password').value//獲取使用者輸入之密碼
    var id = document.getElementById('id').value//獲取使用者輸入之卡號

    var hash = sha256(password)//將密碼轉換成雜湊值

    //把使用者名稱,卡號與雜湊密碼傳入後端做判斷
    if(http_get(`https://bike.elepot.dev/make_account?name=${name}&hash=${hash}&id=${id}`) === "True"){
        document.location.href="/login"//如果成立，將使用者導向登入
    }
    else{
        //如果不成立，跳出提示詞
        alert("此卡號或使用者名稱已經有人使用過了")
    }
}