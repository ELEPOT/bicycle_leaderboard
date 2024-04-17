import requests as req

id = "75166B38"
ip = f"https://bike.elepot.dev/data/send/?id={id}"
get = req.get(ip)
print(get.text)
