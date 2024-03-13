function submit() {
    var name = document.getElementById('name').value
    var password = document.getElementById('password').value
    var id = document.getElementById('id').value

    var hash = sha256(password)

    if(http_get(`http://127.0.0.1:5000/make_account?name=${name}&hash=${hash}&id=${id}`) == "False"){
        alert("此卡號或使用者名稱已經有人使用過了")
    }
    else{
        document.location.href="/login"
    }
}