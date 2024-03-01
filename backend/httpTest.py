import requests as req

id = "75166B38"
ip = f"http://[2001:288:4245:0:25ce:749c:451c:37f4]:5000/data/send/?id={id}"
get = req.get(ip)
print(get.text)