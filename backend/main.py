# 匯入所需模組
import pygsheets as sheet# Google表單
from HTMLTable import HTMLTable# HTML表格
from flask import Flask, render_template, request# 網站架構

app = Flask(__name__)  # 定義Flask網站架構

total_distances = list()   # 定義 total_distances

# 獲得最新表格
def get_newest_worksheet():
    gc = sheet.authorize(service_file="auth/bicyclemileagedatabase-e9a752e9691d.json")
    url = "https://docs.google.com/spreadsheets/d/1ANhQHgFkB4Ce9WfsSZ4gT-u6YW7g4n33WO7UtMNWouI/edit#gid=861705765"
    sht = gc.open_by_url(url)
    wks = sht[0]

    return wks

# 重新排列排名
def get_sorted_total_distance():
    # 開啟 Google 表單

    wks = get_newest_worksheet()

    _total_distances = {}

    id_to_username = dict(
        zip(
            wks.get_col(6, include_tailing_empty=False),
            wks.get_col(4, include_tailing_empty=False),
        )
    )

    # 把同使用者的里程數加起來，直到讀到表單最後一行為止
    for row in wks:
        distance = row[2]
        card_id = row[1]

        if distance == "" or card_id == "":
            break

        if card_id in id_to_username.keys():
            username = id_to_username[card_id]

            if username not in _total_distances.keys():
                _total_distances[username] = float(distance)
            else:
                _total_distances[username] += float(distance)

    # 將每個卡號的總里程數從大到小排列

    _total_distances = list(_total_distances.items())

    _total_distances.sort(key=lambda elem: elem[1], reverse=True)

    return _total_distances

# 首頁
@app.route("/")
def leaderboard():
    global total_distances
    total_distances = get_sorted_total_distance()

    # 將卡號與里程數轉換成 html 表格
    table = HTMLTable(caption="共享單車排行榜")

    table.append_header_rows([("名次", "使用者名稱", "距離 (m)")])

    for ranking, (username, distance) in enumerate(total_distances):
        table.append_data_rows([(ranking + 1, username, round(distance))])
    # 將 html 表格回傳給使用者
    return render_template("index.html", table=table.to_html())

# 登入介面
@app.route("/login")
def login():
    return render_template("login.html")

# 註冊介面
@app.route("/register")
def register():
    return render_template("register.html")

# 進首頁時的登入簡查API
@app.route("/login_auth")
def login_auth():
    name = request.args.get("name")
    password = request.args.get("hash")

    if name == "":
        return "False"

    wks = get_newest_worksheet()

    for row in wks:
        a_name = row[3]
        a_password = row[4]

        if name == a_name and password == a_password:
            print("success")
            return "True"

    return "False"

#註冊API
@app.route("/make_account")
def make_account():
    name = request.args.get("name")
    password = request.args.get("hash")
    i_d = request.args.get("id")

    wks = get_newest_worksheet()

    for row in wks:
        a_name = row[3]
        a_id = row[5]
        if name == a_name or i_d == a_id:
            return "False"

    for index, row in enumerate(wks):
        if row[3] == "" and row[4] == "":
            wks.update_value((index + 1, 4), name)
            wks.update_value((index + 1, 5), password)
            wks.update_value((index + 1, 6), i_d)

    return "True"

# 回傳排名，距離與卡路里
@app.route("/get_message")
def get_message():
    global total_distances

    name = request.args.get("name")

    for ranking, (username, distance) in enumerate(total_distances):
        if username == name:
            message = f"""
            恭喜你獲得第{ranking + 1}名
            總共騎乘 {distance} m
            總共消耗 {round(distance * 0.013, 2)} 大卡
            """

            if distance > 1000:
                message += "\n可獲得一次折扣"

            return message

    return ""

# 腳踏車端獲取排名API
@app.route("/data/send/")
def get_ranking():
    global total_distances

    total_distances = get_sorted_total_distance()

    for ranking, (card_id, distance) in enumerate(total_distances):
        if card_id == request.args.get("id"):
            return str(ranking + 1)

    raise f"Cannot get ranking of {request.args.get('id')}"


# 開始伺服器
if __name__ == "__main__":
    app.run()